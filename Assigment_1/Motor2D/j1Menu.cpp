#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Colliders.h"
#include "j1Pathfinding.h"
#include "j1Menu.h"
#include "j1Scene.h"
#include "j1Entities.h"
#include "Player.h"
#include "j1Gui.h"
#include "UIButton.h"


j1Menu::j1Menu()
{
	name.create("menu");
}

j1Menu::~j1Menu()
{

}

bool j1Menu::Awake(pugi::xml_node& config)
{
	return true;
}

bool j1Menu::Start()
{
	App->scene->active = false;

	//MAIN_MENU
	rect_button_play = { 400, 972, 183, 191 };
	rect_button_options = { 3093, 318, 183, 191 };
	rect_button_options_in = { 3093 + 205, 318, 183, 191 };
	rect_button_options_click = { 3093 + 410,318,183,191 };
	rect_button_exit = { 2556,1407,183,191 };

	//OPTIONS_MENU
	rect_button_back = { 3094,101,179,182 };

	return true;
}

bool j1Menu::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		StartGame();
	}
	switch (menu_state)
	{
	case MAIN_MENU:
		App->gui->AddBackground(0, 0, BACKGROUND, this);
		button_play = App->gui->AddElementButton(150, 450, BUTTON, &rect_button_play, this);
		button_options = App->gui->AddElementButton(150, 600, BUTTON, &rect_button_options, this);
		button_exit = App->gui->AddElementButton(150, 750, BUTTON, &rect_button_exit, this);
		break;

	case OPTIONS_MENU:
		button_back = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this);
		break;

	case HIDE_MENU:

		break;
	}
	return true;
}

bool j1Menu::PostUpdate()
{
	BROFILER_CATEGORY("PosUpdate_Scene1 ", Profiler::Color::DarkOrchid)
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			exit=false;

	return exit;
}

bool j1Menu::CleanUp()
{
	
	return true;
}

bool j1Menu::GUIEvent(UIEvents eventType, UIElements* element)
{
	if (App->menu->active == true)
	{
		switch (eventType)
		{
		case MOUSE_ENTER:
			if (menu_state == MAIN_MENU)
			{
				if (element == button_play)
				{

				}
				if (element == button_options)
				{
					button_options_in = App->gui->AddElementButton(150, 600, BUTTON, &rect_button_options_in, this);
				}
				if (element == button_exit)
				{

				}
			}

			break;
		case MOUSE_LEAVE:
			if (menu_state == MAIN_MENU)
			{
				if (element == button_play)
				{

				}
				if (element == button_options)
				{
					button_options = App->gui->AddElementButton(150, 600, BUTTON, &rect_button_options, this);
				}
				if (element == button_exit)
				{

				}
			}

			break;
		case MOUSE_CLICK:
			if (menu_state == MAIN_MENU)
			{
				if (element == button_play)
				{

				}
				if (element == button_options)
				{
					button_options_click = App->gui->AddElementButton(150, 600, BUTTON, &rect_button_options_click, this);
				}
				if (element == button_exit)
				{

				}
			}

			break;
		case MOUSE_STOP_CLICK:
			if (menu_state == MAIN_MENU)
			{
				if (element == button_play)
				{
					App->gui->startgame = true;
				}
				if (element == button_options)
				{
					StartOptions();
				}
				if (element == button_exit)
				{
					exit = false;
				}
			}
			if (menu_state == OPTIONS_MENU)
			{
				if (element == button_back)
				{
					StartMainMenu();
				}
			}
			break;
		default:
			break;
		}
	}
	return true;
}

void j1Menu::StartGame()
{
	App->menu->active = false;
	App->scene->active = true;
	App->scene->Start();
	App->entities->Start();
}

void j1Menu::StartButton()
{
	StartGame();
}

void j1Menu::OptionsButton()
{
	StartOptions();
}

void j1Menu::StartOptions()
{
	menu_state = OPTIONS_MENU;

}

void j1Menu::StartMainMenu()
{
	menu_state = MAIN_MENU;
}