#ifndef __PYRO_PAPERMENU_H__
#define __PYRO_PAPERMENU_H__

#include "Paper.h"
#include "InkButton.h"
#include <Floreto/UI/TouchProtocol.h>

namespace Pyro
{
	namespace Components
	{

		class PaperMenu : public Paper, public Floreto::TouchGroup
		{
			typedef Paper Super;

		public:
			struct MenuItem : public cocos2d::Ref
			{
				friend class PaperMenu;

			public:
				MenuItem(void)
					: text(""), tag(0), callback(nullptr), parent(nullptr), separator(false)
				{
				}

				void asSeparator(void)
				{
					this->separator = true;
				}

				void init(const std::string &text, int tag = 0, const std::function<void(MenuItem &)> &callback = nullptr)
				{
					this->text = text;
					this->tag = 0;
					this->callback = callback;
					this->separator = false;
				}

			public:
				const std::string & getText(void) const
				{
					return this->text;
				}

				void setText(const std::string &text)
				{
					static_cast<cocos2d::Label *>(button->getIcon())->setString(text);
					this->getParent()->refreshSize();
					this->text = text;
				}

				bool isSeparator(void) const
				{
					return this->separator;
				}

				PaperMenu * getParent(void) const
				{
					return parent;
				}

				InkButton * getButton(void) const
				{
					return button;
				}

			private:
				std::string text;
				int tag;
				std::function<void(MenuItem &)> callback;
				bool separator;

				PaperMenu *parent;
				union
				{
					cocos2d::Node *lineNode;
					InkButton *button;
				};
			};

			struct CreateParams
			{
				std::string textFont;
				int textFontSize;
				cocos2d::Color3B textColor;
				cocos2d::Color3B paperColor;
				std::vector<MenuItem> items;
			};

		public:
			static PaperMenu * create(const CreateParams &params);
			static void closeCurrent(void);

		public:
			PaperMenu(void);
			virtual ~PaperMenu(void);

		protected:
			virtual bool init(const CreateParams &params);

		protected:
			void onItemTouch(MenuItem *item, InkButton *button, const cocos2d::Vec2 &position, Floreto::TouchPhase phase);
			void refreshSize(void);

		public:
			void show(const cocos2d::Vec2 &origin, const cocos2d::Vec2 &anchorPoint, float duration = 0.3f);
			void close(void);

		protected:
			cocos2d::Node *list;
			cocos2d::Node *touchGuard;
			cocos2d::Vector<MenuItem *> items;

		public:
			static const float XPADDING;
			static const float YPADDING;
			static const char *NODE_NAME;
		};

	} //namespace Pyro::Components
} //namespace Pyro

#endif//__PYRO_PAPERMENU_H__
