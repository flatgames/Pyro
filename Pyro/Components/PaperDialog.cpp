#include "PaperDialog.h"
#include <Floreto/Floreto.h>

#include "InkButton.h"
#include "../Animations/AnimationUtils.h"
#include "../Animations/SequenceBuilder.h"
#include "../Animations/SpawnBuilder.h"

using namespace cocos2d;
using namespace Floreto;
using namespace Pyro::Animations;

namespace Pyro
{
	namespace Components
	{

		const cocos2d::Color3B PaperDialog::MESSAGE_COLOR = Color3B(66, 66, 66);
		const cocos2d::Color3B PaperDialog::BUTTON_TEXT_COLOR = Color3B(0, 102, 204);

		const float PaperDialog::DIALOG_PADDING = 32;
		const float PaperDialog::DIALOG_MIN_MARGIN = 64;

		PaperDialog * PaperDialog::create(const CreateParams &params)
		{
			auto dialog = new PaperDialog();
			if (dialog && dialog->init(params))
			{
				dialog->autorelease();
				return dialog;
			}

			CC_SAFE_DELETE(dialog);
			return nullptr;
		}

		PaperDialog::PaperDialog(void)
			: _dialog(nullptr), _touchGuard(nullptr), _background(nullptr),
			_messageLabel(nullptr), _firstButtonLabel(nullptr), _secondButtonLabel(nullptr),
			_firstCallback(nullptr), _secondCallback(nullptr), _dismissCallback(nullptr)
		{
		}

		PaperDialog::~PaperDialog(void)
		{
		}

		void PaperDialog::onEnter(void)
		{
			Super::onEnter();
			BackKeyUtils::getInstance()->pushListener(this, [this](void)
			{
				if (this->_dismissCallback)
					this->_dismissCallback(this);

				this->dismiss();
				return false;
			});
		}

		void PaperDialog::onExit(void)
		{
			BackKeyUtils::getInstance()->popListener(this);
			Super::onExit();
		}

		bool PaperDialog::init(const CreateParams &params)
		{
			if (!Super::init())
				return false;

			float maxDialogWidth = VisibleView::width() - DIALOG_MIN_MARGIN * 2 - DIALOG_PADDING * 2;
			float dialogWidth = 0;

			if (params.textFontSize > 0)
			{
				_messageLabel = Label::createWithTTF(params.message, params.textFont, params.textFontSize);
			}
			else
			{
				_messageLabel = Label::createWithBMFont(params.textFont, params.message);
				_messageLabel->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
			}

			_messageLabel->setColor(MESSAGE_COLOR);

			if (_messageLabel->getContentSize().width + DIALOG_PADDING * 2 > maxDialogWidth)
				_messageLabel->setWidth(maxDialogWidth - DIALOG_PADDING * 2);

			InkButton *firstButton = nullptr, *secondButton = nullptr;

			InkButton::CreateParams btnparams;
			btnparams.textColor = BUTTON_TEXT_COLOR;
			btnparams.roundedCorner = false;
			btnparams.paperVisible = false;

			if (params.secondButtonText.empty())
			{
				if (params.textFontSize > 0)
				{
					_firstButtonLabel = Label::createWithTTF(params.firstButtonText, params.textFont, params.textFontSize);
				}
				else
				{
					_firstButtonLabel = Label::createWithBMFont(params.textFont, params.firstButtonText);
					_firstButtonLabel->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
				}

				dialogWidth = std::max(_messageLabel->getContentSize().width + DIALOG_PADDING * 2, _firstButtonLabel->getContentSize().width + 32);
				if (dialogWidth > maxDialogWidth)
					dialogWidth = maxDialogWidth;

				btnparams.size.setSize(dialogWidth, ceilf(_firstButtonLabel->getContentSize().height) + DIALOG_PADDING * 2);

				firstButton = InkButton::create(btnparams.withIcon(_firstButtonLabel),
					[this](InkButton *, const Vec2 &, TouchPhase phase)
				{
					if (phase == TouchPhase::Ended && this->_firstCallback)
						this->_firstCallback(this);
				});
				firstButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				firstButton->setPosition(Vec2::ZERO);
				firstButton->setTouchEnabled(true);

				_firstCallback = params.firstButtonCallback;
			}
			else
			{
				if (params.textFontSize > 0)
				{
					_firstButtonLabel = Label::createWithTTF(params.firstButtonText, params.textFont, params.textFontSize);
					_secondButtonLabel = Label::createWithTTF(params.secondButtonText, params.textFont, params.textFontSize);
				}
				else
				{
					_firstButtonLabel = Label::createWithBMFont(params.textFont, params.firstButtonText);
					_firstButtonLabel->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
					_secondButtonLabel = Label::createWithBMFont(params.textFont, params.secondButtonText);
					_secondButtonLabel->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
				}

				dialogWidth = std::max(_messageLabel->getContentSize().width + DIALOG_PADDING * 2,
					_firstButtonLabel->getContentSize().width + 32 + _secondButtonLabel->getContentSize().width + 32);

				if (dialogWidth > maxDialogWidth)
					dialogWidth = maxDialogWidth;

				auto totalPadding = dialogWidth - _firstButtonLabel->getContentSize().width - _secondButtonLabel->getContentSize().width;

				btnparams.icon = _firstButtonLabel;
				btnparams.size.setSize(
					ceilf(_firstButtonLabel->getContentSize().width) + totalPadding / 2,
					ceilf(_firstButtonLabel->getContentSize().height) + DIALOG_PADDING * 2);

				firstButton = InkButton::create(btnparams,
					[this](InkButton *, const Vec2 &, TouchPhase phase)
				{
					if (phase == TouchPhase::Ended && this->_firstCallback)
						this->_firstCallback(this);
				});
				firstButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
				firstButton->setPosition(dialogWidth, 0);
				firstButton->setTouchEnabled(true);

				_firstCallback = params.firstButtonCallback;

				btnparams.icon = _secondButtonLabel;
				btnparams.textColor = UIUtils::lightenColor(BUTTON_TEXT_COLOR, 0.3f);
				btnparams.size.setSize(
					ceilf(_secondButtonLabel->getContentSize().width) + totalPadding / 2,
					ceilf(_firstButtonLabel->getContentSize().height) + DIALOG_PADDING * 2);

				secondButton = InkButton::create(btnparams,
					[this](InkButton *, const Vec2 &, TouchPhase phase)
				{
					if (phase == TouchPhase::Ended && this->_secondCallback)
						this->_secondCallback(this);
				});
				secondButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				secondButton->setPosition(0, 0);
				secondButton->setTouchEnabled(true);

				_secondCallback = params.secondButtonCallback;
			}

			auto size = Size(dialogWidth, _messageLabel->getContentSize().height + DIALOG_PADDING * 2 + _firstButtonLabel->getContentSize().height + DIALOG_PADDING * 2);

			_dialog = Paper::create(size, true, Color3B::WHITE);
			_dialog->enableShadow(5);
			_dialog->setPosition(VisibleView::cx(), VisibleView::cy());
			_dialog->getContainer()->setCascadeOpacityEnabled(true);
			this->addChild(_dialog, 1);

			_messageLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
			_messageLabel->setPosition(size.width / 2, size.height - DIALOG_PADDING);
			_dialog->getContainer()->addChild(_messageLabel);

			_dialog->getContainer()->addChild(firstButton);
			if (secondButton)
				_dialog->getContainer()->addChild(secondButton);

			auto divider = UIUtils::createRectangle(size.width, VisibleView::onePixel(), Color3B(230, 230, 230));
			divider->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
			divider->setPosition(size.width / 2, firstButton->getContentSize().height);
			_dialog->getContainer()->addChild(divider);

			_background = UIUtils::createRectangle(VisibleView::width(), VisibleView::height(), Color3B::BLACK);
			_background->setOpacity(96);
			_background->setPosition(VisibleView::cx(), VisibleView::cy());
			this->addChild(_background, -1);

			_touchGuard = Button::create(Button::createSimpleDelegate([](void) { }), false);
			_touchGuard->setContentSize(Size(VisibleView::width(), VisibleView::height()));
			_touchGuard->setPosition(VisibleView::cx(), VisibleView::cy());
			_touchGuard->setTouchEnabled(true);
			this->addChild(_touchGuard, -1);

			_dismissCallback = params.dismissCallback;

			return true;
		}

		void PaperDialog::show(int zOrder)
		{
			Director::getInstance()->getRunningScene()->addChild(this, zOrder);

			_dialog->setOpacity(0);
			_dialog->setScale(0.01f);

			SpawnBuilder(_dialog)
				.fadeIn<EaseQuadraticActionOut>(0.3f)
				.scaleTo<EaseQuadraticActionOut>(0.3f, 1)
				.run();

			AnimationUtils::fadeFromTo<EaseQuadraticActionOut>(_background, 0, 96, 0.3f);
		}

		void PaperDialog::dismiss(void)
		{
			SequenceBuilder(_dialog)
				.beginSpawn()
				.fadeOut(0.2f)
				.scaleTo(0.2f, 0.01f)
				.endSpawn()
				.call([this](void)
			{
				this->removeFromParent();
			})
				.run();

			AnimationUtils::fadeFromTo(_background, 96, 0, 0.2f);
		}

	} //namespace Pyro::Components
} //namespace Pyro
