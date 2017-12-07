#ifndef __J1MENU_H__
#define __J1MENU_H__

#include "j1Module.h"
enum MenuState
{
	MAIN_MENU,
	OPTIONS_MENU,
	HIDE_MENU
};

class j1Menu:public j1Module
{
public:

	j1Menu();
	virtual ~j1Menu();

	bool Awake(pugi::xml_node&);
	bool Start();
	/*bool PreUpdate();*/
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void StartGame();
	void StartButton();
	void OptionsButton();
	void StartOptions();
	void StartMainMenu();
	bool GUIEvent(UIEvents eventType, UIElements* element);
	

private:

	SDL_Rect rect_button_play;

	SDL_Rect rect_button_options;
	SDL_Rect rect_button_options_in;
	SDL_Rect rect_button_options_click;

	SDL_Rect rect_button_exit;

	SDL_Rect rect_button_back;


	UIElements* button_play=nullptr;
	UIElements* button_options=nullptr;
	UIElements* button_options_in=nullptr;
	UIElements* button_options_click=nullptr;
	UIElements* button_exit=nullptr;
	UIElements* button_back = nullptr;

	MenuState menu_state;

	bool exit = true;
	

};

#endif // __J1MENU_H__

