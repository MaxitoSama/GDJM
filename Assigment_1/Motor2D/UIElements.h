#ifndef __UIELEMENTS_H__
#define __UIELEMENTS_H__

#include "j1Gui.h"
#include "p2Point.h"
#include "SDL\include\SDL_rect.h"

enum UIElementType
{
	BACKGROUND,
	TEXT,
	IMAGE,
	BUTTON,
	TEXTBOX,
	WINDOWS
};

class UIElements :public j1Gui
{
public:

	UIElements(int x, int y, UIElementType type, j1Module* modul);
	~UIElements();

	virtual void Draw() {};
	virtual void Action() {};

public:

	SDL_Rect		Elementrect;
	fPoint			position;
	UIElementType	type;

	j1Module*		callback = nullptr;

	uint			size_x;
	uint			size_y;

	bool			mousein = false;
	bool			mouseout = true;
	bool			action = false;
	bool			debug = false;
	bool			show = false;
	bool			isWindowElement = false;

	SDL_Texture*	ElementTexture = nullptr;

	float scale;

};

#endif// __UIELEMENTS_H__