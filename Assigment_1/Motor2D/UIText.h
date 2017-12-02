#ifndef __UITEXT_H__
#define __UITEXT_H__

#include "p2SString.h"
#include "UIElements.h"

class SDL_Texture;
class _TTF_Font;

class UIText :public UIElements
{
public:

	UIText(int x, int y, UIElementType type, const char* text, j1Module* modul);
	~UIText();

	void Draw();

public:

	SDL_Texture*	texture;
	SDL_Texture*	BlackBackground;
	uint			text_width;
	uint			text_height;
	const char*		string;
	_TTF_Font*      textFont;

};

#endif //__UITENT_H__

