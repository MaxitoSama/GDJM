#ifndef __UITEXT_H__
#define __UITEXT_H__

#include "p2SString.h"
#include "UIElements.h"

class SDL_Texture;
class _TTF_Font;

class UIText :public UIElements
{
public:

	UIText(int x, int y, UIElementType type, const char* text, j1Module* modul, bool actualize, bool show);
	~UIText();

	void Draw();

public:

	SDL_Texture*	texture=nullptr;
	SDL_Texture*	BlackBackground=nullptr;
	
	const char*		string=nullptr;
	p2SString		actstring;

	_TTF_Font*      textFont=nullptr;

	uint			text_width;
	uint			text_height;

	bool			actualizable = false;

	

};

#endif //__UITENT_H__

