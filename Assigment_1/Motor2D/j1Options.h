#ifndef __J1OPTIONS_H__
#define __J1OPTIONS_H__

#include "j1Module.h"

class j1Options:public j1Module
{
public:

	j1Options();
	virtual ~j1Options();

	bool Awake(pugi::xml_node&);
	bool Start();
	/*bool PreUpdate();*/
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void StartMenu();
	bool GUIEvent(UIEvents eventType, UIElements* element);
	

private:

	SDL_Rect rect_button_play;
	SDL_Rect rect_button_options;
	SDL_Rect rect_button_exit;
	SDL_Rect rect_button_back;

	UIElements* button_play = nullptr;
	UIElements* button_options = nullptr;
	UIElements* button_exit = nullptr;
	UIElements* button_back = nullptr;

	bool exit = true;

};

#endif // __J1MENU_H__

