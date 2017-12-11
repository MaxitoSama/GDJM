#ifndef __J1MENU_H__
#define __J1MENU_H__

#include "j1Module.h"
#include "p2Animation.h"

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
	void OptionsButton();
	void CreditsButton();
	bool GUIEvent(UIEvents eventType, UIElements* element);
	

private:

	SDL_Texture* sprites_ninja = nullptr;

	SDL_Rect rect_button_play;
	SDL_Rect rect_button_options;
	SDL_Rect rect_button_options_in;
	SDL_Rect rect_button_options_click;
	SDL_Rect rect_button_credits;
	SDL_Rect rect_button_exit;
	SDL_Rect rect_button_back;
	SDL_Rect rect_button_sound;
	SDL_Rect rect_button_music;

	UIElements* button_play=nullptr;
	UIElements* button_options=nullptr;
	UIElements* button_options_in=nullptr;
	UIElements* button_options_click=nullptr;
	UIElements* button_exit=nullptr;
	UIElements* button_back = nullptr;
	UIElements* button_credits = nullptr;
	UIElements* button_back_credits = nullptr;
	UIElements* img_slide = nullptr;
	UIElements* button_music = nullptr;
	UIElements* button_sound = nullptr;
	
	UIElements* License_window = nullptr;
	p2List<UIElements*> License_text;
	UIElements* License_1 = nullptr;
	UIElements* License_2 = nullptr;
	UIElements* License_3 = nullptr;
	UIElements* License_4 = nullptr;
	UIElements* License_5 = nullptr;
	UIElements* License_6 = nullptr;
	UIElements* License_7 = nullptr;
	UIElements* License_8 = nullptr;
	UIElements* License_9 = nullptr;
	UIElements* License_10 = nullptr;
	UIElements* License_11 = nullptr;
	UIElements* License_12 = nullptr;
	UIElements* License_13 = nullptr;
	UIElements* License_14 = nullptr;
	UIElements* License_15 = nullptr;
	UIElements* License_16 = nullptr;

	UIElements* text_start = nullptr;
	UIElements* text_option = nullptr;
	UIElements* text_exit = nullptr;
	UIElements* text_credits = nullptr;
	UIElements* text_sound = nullptr;
	UIElements* text_music = nullptr;

	Animation* animation = nullptr;
	Animation ninja;

	float dt;

	bool exit = true;
	

};

#endif // __J1MENU_H__

