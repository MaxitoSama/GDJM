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
	button_play = { 400, 972, 183, 191 };
	button_options = { 3093, 318, 183, 191 };
	button_exit = { 2556,1407,183,191 };
;
	return true;
}

bool j1Menu::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		StartGame();
	}

	App->gui->AddElementButton(300, 450, BUTTON, &button_play, this);
	App->gui->AddElementButton(300, 600, BUTTON, &button_options, this);
	App->gui->AddElementButton(300, 750, BUTTON, &button_exit, this);
	return true;
}

bool j1Menu::PostUpdate()
{
	bool ret = true;
	BROFILER_CATEGORY("PosUpdate_Scene1 ", Profiler::Color::DarkOrchid)
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			ret = false;

	return ret;
}

bool j1Menu::CleanUp()
{
	return true;
}

bool j1Menu::GUIEvent(UIEvents eventType, UIElements* element)
{
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
}

void j1Menu::ExitButtion()
{
}
