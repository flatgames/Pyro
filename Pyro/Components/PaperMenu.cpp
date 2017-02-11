#include "PaperMenu.h"
#include <Floreto/Floreto.h>

#include "../Animations/AnimationUtils.h"

using namespace cocos2d;
using namespace Floreto;

namespace Pyro
{
	namespace Components
	{
		const float PaperMenu::XPADDING = 24;
		const float PaperMenu::YPADDING = 24;
		const char * PaperMenu::NODE_NAME = "Pyro::Components::PaperMenu";

		PaperMenu * PaperMenu::create(const CreateParams &params)
		{
			auto menu = new PaperMenu();
			if (menu && menu->init(params))
			{
				menu->autorelease();
				return menu;
			}

			CC_SAFE_DELETE(menu);
			return nullptr;
		}

		void PaperMenu::closeCurrent(void)
		{
			auto lastMenu = Director::getInstance()->getRunningScene()->getChildByName<PaperMenu *>(NODE_NAME);
			if (lastMenu)
				lastMenu->close();
		}

		PaperMenu::PaperMenu(void)
			: list(nullptr), touchGuard(nullptr)
		{
		}

		PaperMenu::~PaperMenu(void)
		{
		}

		bool PaperMenu::init(const CreateParams &params)
		{
			list = Node::create();
			list->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			list->setPosition(Vec2::ZERO);
			list->setCascadeOpacityEnabled(true);

			InkButton::CreateParams btnparams;
			btnparams.size.setSize(10, 10);
			btnparams.roundedCorner = false;
			btnparams.textColor = params.textColor;
			btnparams.textFont = params.textFont;
			btnparams.textFontSize = params.textFontSize;
			btnparams.paperVisible = false;

			float y = 0, w = 0, h = 0;
			const auto &items = params.items;
			for (unsigned int i = 0, c = items.size(); i < c; ++i)
			{
				const auto &item = items[i];

				if (item.isSeparator())
				{
					auto node = Node::create();
					node->setContentSize(Size(10, VisibleView::onePixel()));
					node->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
					node->setPosition(0, y);
					
					list->addChild(node);

					auto line = UIUtils::createRectangle(1, VisibleView::onePixel(), Color3B(230, 230, 230));
					line->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
					line->setPosition(Vec2::ZERO);
					node->addChild(line);

					MenuItem *newItem = new MenuItem(item);
					newItem->parent = this;
					newItem->lineNode = node;
					this->items.pushBack(newItem);

					y -= VisibleView::onePixel();
					h += VisibleView::onePixel();
				}
				else
				{
					MenuItem *newItem = new MenuItem(item);
					newItem->parent = this;
					this->items.pushBack(newItem);

					auto itemCallback = std::bind(&PaperMenu::onItemTouch, this, newItem,
						std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

					auto button = InkButton::create(btnparams.withText(item.text), itemCallback);
					auto lbl = button->getIcon();
					auto size = Size(lbl->getContentSize().width + XPADDING * 2, lbl->getContentSize().height + YPADDING * 2);
					button->setContentSize(size);
					button->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
					button->setPosition(0, y);
					button->getContainer()->setCascadeOpacityEnabled(true);
					lbl->setPosition(size.width / 2, size.height / 2);

					list->addChild(button);
					this->addElement(button);

					newItem->button = button;

					y -= size.height;
					if (w < size.width)
						w = size.width;
					h += size.height;
				}
			}

			if (!Super::init(Size(w, h), true, params.paperColor))
				return false;

			{
				auto guard = Button::create(Button::createSimpleDelegate([](void) { }), false);
				guard->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				guard->setPosition(Vec2::ZERO);
				this->getContainer()->addChild(guard, 1, "touchGuard");
				this->addElement(guard);
			}

			this->enableShadow(3);

			this->getContainer()->addChild(list, 2);
			this->getContainer()->setCascadeOpacityEnabled(true);
			this->refreshSize();

			return true;
		}

		void PaperMenu::onItemTouch(MenuItem *item, InkButton *button, const Vec2 &position, TouchPhase phase)
		{
			if (phase == TouchPhase::Ended)
			{
				if (item->callback)
					item->callback(*item);
			}
		}

		void PaperMenu::refreshSize(void)
		{
			UIUtils::calculateContentNodeSize(this->list);
			float maxWidth = this->list->getContentSize().width;

			for (unsigned int i = 0, c = items.size(); i < c; ++i)
			{
				auto item = items.at(i);
				if (item->isSeparator())
				{
					item->lineNode->setContentSize(Size(maxWidth, VisibleView::onePixel()));
					
					auto sprite = item->lineNode->getChildren().at(0);
					sprite->setScaleX(maxWidth);
				}
				else
				{
					item->button->setContentSize(Size(maxWidth, item->button->getContentSize().height));

					auto lbl = item->button->getIcon();
					lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
					lbl->setPosition(XPADDING, item->button->getContentSize().height / 2);
				}
			}

			this->setContentSize(this->list->getContentSize());
			this->getContainer()->getChildByName<Button *>("touchGuard")->setContentSize(this->list->getContentSize());
		}

		void PaperMenu::show(const Vec2 &origin, const cocos2d::Vec2 &anchorPoint, float duration)
		{
			PaperMenu::closeCurrent();
			Director::getInstance()->getRunningScene()->addChild(this, 1000, NODE_NAME);

			this->setPosition(origin);

			// touch guard
			{
				Button::SingleTouchDelegate delegate = MakeSingleTouchDelegate([this], button, touch, phase)
				{
					if (phase == TouchPhase::Began)
						this->close();

					return false;
				};
				auto touchGuard = Button::create(delegate, false);
				touchGuard->setContentSize(Size(VisibleView::width(), VisibleView::height()));
				touchGuard->setPosition(VisibleView::cx(), VisibleView::cy());
				touchGuard->setTouchEnabled(true);
				Director::getInstance()->getRunningScene()->addChild(touchGuard, this->getLocalZOrder() - 1);
				
				this->touchGuard = touchGuard;
			}

			this->setAnchorPoint(anchorPoint);

			Animations::AnimationUtils::fadeFromTo<EaseQuadraticActionOut>(this, 0, 255, duration);
			Animations::AnimationUtils::scaleFromTo<EaseQuadraticActionOut>(this,
				Vec2(16 / this->getContentSize().width, 16 / this->getContentSize().height),
				Vec2::ONE, duration);
			Animations::AnimationUtils::fadeFromTo<EaseQuadraticActionOut>(this->list, 0, 255, 0.2f, duration);

			Animations::AnimationUtils::runWithDelay(this, duration + 0.2f, std::bind(&PaperMenu::setTouchEnabled, this, true));
		}

		void PaperMenu::close(void)
		{
			if (touchGuard)
				touchGuard->removeFromParent();

			Node::setName("");

            float animTime = 0.1f + items.size() * 0.02f;

			Animations::AnimationUtils::fadeFromTo<EaseQuadraticActionIn>(this, 255, 0, animTime);
			Animations::AnimationUtils::scaleFromTo<EaseQuadraticActionIn>(this, 1, 0.01f, animTime);
			Animations::AnimationUtils::fadeOut<EaseQuadraticActionIn>(this->list, 0.1f);

			Animations::AnimationUtils::runWithDelay(this, 0.3f, std::bind(&PaperMenu::removeFromParent, this));
		}

	} //namespace Pyro::Components
} //namespace Pyro
