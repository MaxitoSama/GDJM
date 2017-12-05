#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "UIElements.h"

class SDL_Rect;
class SDL_Texture;

class UIButton : public UIElements
{
public:

	UIButton(int x, int y, UIElementType type, SDL_Rect* RecTex, const char* text, j1Module* modul);
	~UIButton();

	void Draw();
	void Action();

private:

	const char* buttontext = nullptr;

	SDL_Texture*	ButtonTex;
	SDL_Texture*	ButtonText;

	uint sizeTx;
	uint sizeTy;

	SDL_Rect*		RectTexture;

	bool light = false;



};

#endif //__BUTTONS_H__

