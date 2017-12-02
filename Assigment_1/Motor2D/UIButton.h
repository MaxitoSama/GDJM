#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "UIElements.h"

class SDL_Rect;
class SDL_Texture;

enum ButtonType {

	BUTTON_1,
	BUTTON_2
};

class UIButton : public UIElements
{
public:

	UIButton(int x, int y, UIElementType type, ButtonType buttontype, const char* text, j1Module* modul);
	~UIButton();

	void Draw();
	void Action();

private:

	const char* buttontext = nullptr;

	ButtonType btype;

	SDL_Texture*	ButtonTex;
	SDL_Texture*	ButtonText;

	uint sizeTx;
	uint sizeTy;

	bool light = false;



};

#endif //__BUTTONS_H__

