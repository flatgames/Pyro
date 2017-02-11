#ifndef __PYRO_PAPERDIALOG_H__
#define __PYRO_PAPERDIALOG_H__

#include "Paper.h"

#include <Floreto/UI/Button.h>

namespace Pyro
{
	namespace Components
	{

		class PaperDialog : public cocos2d::Node
		{
			typedef cocos2d::Node Super;

		public:
			typedef std::function<void(PaperDialog *dialog)> Callback;

		public:
			// The parameters given to the create function.
			// If textFontSize is not positive, then textFont indicates a FNT (bitmap font) file.
			// Otherwise textFont indicates a TTF file.
			struct CreateParams
			{
				std::string textFont;
				int textFontSize;

				std::string message;
				std::string firstButtonText;
				std::string secondButtonText;
				PaperDialog::Callback firstButtonCallback;
				PaperDialog::Callback secondButtonCallback;
				PaperDialog::Callback dismissCallback;

				CreateParams(void)
				{
					firstButtonCallback = nullptr;
					secondButtonCallback = nullptr;
					dismissCallback = nullptr;
				}
			};

		public:
			static PaperDialog * create(const CreateParams &params);

		public:
			PaperDialog(void);
			virtual ~PaperDialog(void);

			virtual void onEnter(void) override;
			virtual void onExit(void) override;

		protected:
			bool init(const CreateParams &params);

		public:
			void show(int zOrder = 100);
			void dismiss(void);

		protected:
			Pyro::Components::Paper *_dialog;
			Floreto::Button *_touchGuard;
			cocos2d::Sprite *_background;
			cocos2d::Label *_messageLabel;
			cocos2d::Label *_firstButtonLabel;
			cocos2d::Label *_secondButtonLabel;
			Callback _firstCallback;
			Callback _secondCallback;
			Callback _dismissCallback;

		public:
			static const cocos2d::Color3B MESSAGE_COLOR;
			static const cocos2d::Color3B BUTTON_TEXT_COLOR;

			static const float DIALOG_PADDING;
			static const float DIALOG_MIN_MARGIN;
		};
		
	} //namespace Pyro::Components
} //namespace Pyro

#endif//__PYRO_PAPERDIALOG_H__
