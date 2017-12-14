#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "UIElements.h"

class SDL_Rect;
class SDL_Texture;

class UISlider :public UIElements
{
public:

	UISlider(int x, int y, UIElementType type, SDL_Rect* slider, SDL_Rect* button, j1Module* modul, p2List<UIElements*>* elementslist, bool show = false);
	~UISlider();

	void Draw();
	void Action();

public:

	SDL_Rect* slider;
	SDL_Rect* button;
	SDL_Texture* texture;
	p2List<UIElements*>* sliderelements;

	iPoint mousestart;
	iPoint mouseend = { 0,0 };
};

#endif //__UIIMAGE_H__