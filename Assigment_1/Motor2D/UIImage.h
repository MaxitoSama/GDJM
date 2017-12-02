#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__

#include "UIElements.h"

class SDL_Rect;
class SDL_Texture;

class UIImage :public UIElements
{
public:

	UIImage(int x, int y, UIElementType type, SDL_Rect* rect, j1Module* modul);
	~UIImage();

	void Draw();

public:

	SDL_Rect* rectangle;
	SDL_Texture* texture;

};

#endif //__UIIMAGE_H__