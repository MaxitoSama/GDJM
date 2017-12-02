#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "UIElements.h"

class UIWindow : public UIElements
{
public:

	UIWindow(int x, int y, UIElementType type, j1Module* modul, p2List<UIElements*>* elementslist);
	~UIWindow();

	void Draw();
	void Action();

private:

	p2List<UIElements*>* windowelements;
	SDL_Rect window;

	iPoint mousestart;
	iPoint mouseend = { 0,0 };

};

#endif //__WINDOW_H__
