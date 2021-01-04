#ifndef GAME2D_DROPDOWN_H
#define GAME2D_DROPDOWN_H

#include "Button.h"

namespace Game2D
{
	class Dropdown
	{
	private:
		Button mainButton;
		std::vector<Button> buttons;

		bool down;
		int selectedItem;
		unsigned int fontSize;
	public:
		Dropdown();
		Dropdown(Rect r);

		inline void addAnims(AnimatedSprite anims, int stateFrames[5]) { mainButton.addAnims(anims, stateFrames); }
		inline void addStateSprites(Sprite none, Sprite hover, Sprite mouseDown, Sprite click, Sprite disable) { mainButton.addStateSprites(none, hover, mouseDown, click, disable); }

		ClickableObject::ClickState update(Pos2 mousePos, KeyState::State state, float time);

		inline void addItem(Button b) { buttons.push_back(b); }
		void addLastItemCopy(std::string text);

		inline void setFontSize(unsigned int size) { this->fontSize = size; mainButton.setFontSize(fontSize); }
		inline void setText(std::string text) { mainButton.setText(text); }

		inline void setSelectedItem(int i) { if (i < buttons.size()) { selectedItem = i; mainButton.setText(buttons[i].getText()); } std::cout << "Button text" << buttons[i].getText() << "\n"; }
		inline int getSelectedItem() const { return selectedItem; }

		inline std::string getText() const { return mainButton.getText(); }

		inline void clear() { buttons.clear(); }

		void draw() const;
	};
}

#endif // !GAME2D_DROPDOWN_H