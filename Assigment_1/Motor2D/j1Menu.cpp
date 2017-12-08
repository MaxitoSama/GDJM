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
	rect_button_exit = { 2556,1407,183,191 };

	//OPTIONS_MENU
	rect_button_back = { 3094,101,179,182 };

	App->gui->AddBackground(0, 0, BACKGROUND, this);
	button_play = App->gui->AddElementButton(150, 450, BUTTON, &rect_button_play, this);
	button_options = App->gui->AddElementButton(150, 600, BUTTON, &rect_button_options, this);
	button_exit = App->gui->AddElementButton(150, 750, BUTTON, &rect_button_exit, this);
	button_back = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this,nullptr,false);

	return true;
}

bool j1Menu::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->gui->startgame = true;
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
	switch (eventType)
		{
		case MOUSE_ENTER:
			if (element == button_play && element->show)
			{
			}
			if (element == button_options && element->show)
			{
				
			}
			if (element == button_exit && element->show)
			{
				
			}
			break;

		case MOUSE_LEAVE:
			if (element == button_play && element->show)
			{
			}
			if (element == button_options && element->show)
			{
				
			}
			if (element == button_exit && element->show)
			{

			}
			break;

		case MOUSE_CLICK:
			if (element == button_play && element->show)
			{
			}
			if (element == button_options && element->show)
			{
				
			}
			if (element == button_exit && element->show)
			{
			}
			break;

		case MOUSE_STOP_CLICK:
			if (element == button_play && element->show)
			{
				App->gui->startgame = true;
			}
			if (element == button_options && element->show)
			{
				OptionsButton();
			}
			if (element == button_exit && element->show)
			{
				exit = false;
			}
			if (element == button_back && element->show)
			{
				OptionsButton();
			}
			break;
		
		default:
			break;
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

void j1Menu::OptionsButton()
{
	if (button_options->show)
	{
		button_exit->show = false;
		button_options->show = false;
		button_play->show = false;
		button_back->show = true;
	}
	else
	{
		button_exit->show = true;
		button_options->show = true;
		button_play->show = true;
		button_back->show = false;
	}

}
