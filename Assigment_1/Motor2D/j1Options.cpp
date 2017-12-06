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
#include "j1Options.h"
#include "Player.h"
#include "j1Gui.h"
#include "UIButton.h"



j1Options::j1Options()
{
	name.create("menu");
}

j1Options::~j1Options()
{

}

bool j1Options::Awake(pugi::xml_node& config)
{
	
	return true;
}

bool j1Options::Start()
{
	if (!App->menu->active)
	{
		rect_button_play = { 400, 972, 183, 191 };
		rect_button_options = { 3093, 318, 183, 191 };
		rect_button_exit = { 2556,1407,183,191 };
		rect_button_back = { 3094,101,179,182 };

		App->gui->AddBackground(0, 0, BACKGROUND, this);
		//button_play = App->gui->AddElementButton(150, 450, BUTTON, &rect_button_play, this);
		//button_options=App->gui->AddElementButton(150, 600, BUTTON, &rect_button_options, this);
		//button_exit = App->gui->AddElementButton(150, 750, BUTTON, &rect_button_exit, this);
		button_back = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this);
	}
	return true;
}

bool j1Options::Update(float dt)
{

	return true;
}

bool j1Options::PostUpdate()
{
	BROFILER_CATEGORY("PosUpdate_Scene1 ", Profiler::Color::DarkOrchid)
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			exit=false;

	return exit;
}

bool j1Options::CleanUp()
{
	return true;
}

bool j1Options::GUIEvent(UIEvents eventType, UIElements* element)
{
	switch (eventType)
	{
	case MOUSE_ENTER:
		if (element == button_play)
		{

		}
		if (element == button_options)
		{

		}
		if (element == button_exit)
		{

		}
		break;
	case MOUSE_LEAVE:
		if (element == button_play)
		{

		}
		if (element == button_options)
		{

		}
		if (element == button_exit)
		{

		}
		break;
	case MOUSE_CLICK:
		if (element == button_play)
		{
			
		}
		if (element == button_options)
		{

		}
		if (element == button_exit)
		{

		}
		break;
	case MOUSE_STOP_CLICK:
		if (element == button_play)
		{
			App->gui->startgame = true;
		}
		if (element == button_options)
		{

		}
		if (element == button_exit)
		{
			exit = false;
		}
		if (element == button_back)
		{
			StartMenu();
		}
		break;
	default:
		break;
	}
	return true;
}

void j1Options::StartMenu()
{
	App->options->active = false;
	App->menu->active = true;
	App->menu->Start();
}




