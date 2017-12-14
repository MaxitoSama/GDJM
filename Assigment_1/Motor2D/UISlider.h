#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "UIElements.h"

class SDL_Rect;
class SDL_Texture;

class UISlider :public UIElements
{
public:

	UISlider(int x, int y, UIElementType type, SDL_Rect* slider, SDL_Rect* button, j1Module* modul, UIElements* element_button, bool show = false);
	~UISlider();

	void Draw();
	void Action();

public:

	SDL_Rect* slider;
	SDL_Rect* button;
	SDL_Texture* texture;

	iPoint mouse_origin;
	iPoint mouse_vector;
	iPoint button_point;
	int mouse_button = 0;
};

#endif //__UIIMAGE_H__