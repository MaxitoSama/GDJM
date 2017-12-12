#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "UIElements.h"

class SDL_Rect;
class SDL_Texture;

class UISlider :public UIElements
{
public:

	UISlider(int x, int y, UIElementType type, SDL_Rect* rect, j1Module* modul, bool show = false);
	~UISlider();

	void Draw();

public:

	SDL_Rect* rectangle;
	SDL_Texture* texture;

};

#endif //__UIIMAGE_H__