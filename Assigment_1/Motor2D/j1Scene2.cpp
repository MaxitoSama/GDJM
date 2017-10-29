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
#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1Player.h"

j1Scene2::j1Scene2() : j1Module()
{
	name.create("scene2");
}

// Destructor
j1Scene2::~j1Scene2()
{}

// Called before render is available
bool j1Scene2::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	if (App->scene->active == true)
	{
		active = false;
	}

	return ret;
}

// Called before the first frame
bool j1Scene2::Start()
{
	if (active)
	{
		App->map->Load("Map_2.tmx");
		App->audio->PlayMusic("audio/music/map1_music.ogg");
		App->map->Draw_Colliders();

		App->colliders->AddCollider({ 25400,0,50,310 }, COLLIDER_WIN2, this);
		App->colliders->AddCollider({ 18923,0,50,310 }, COLLIDER_WIN2, this);
		App->player->Curr_map = 2;

		App->player->Start();
	}
	
	return true;
}

// Called each loop iteration
bool j1Scene2::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene2::Update(float dt)
{
	int dist = App->player->win_width / 2;

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		Change_to_Scene_1(0,0);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		StartCurrentScene();


	if (App->player->position.x >= dist && App->player->position.x <= 24630)
	{
		App->render->camera.x = -App->player->position.x + App->player->win_width / 2;
	}

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene2::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene2::CleanUp()
{
	LOG("Freeing scene");
	
	App->colliders->CleanUp();
	App->map->CleanUp();
	App->tex->CleanUp();

	return true;
}

//Change to scene 1
void j1Scene2::Change_to_Scene_1(int x, int y)
{
	active = false;
	App->scene->active = true;
	CleanUp();
	App->scene->Start();
	App->player->position.y = y;
	App->player->position.x = x;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->player->Start();
}

//Go to the begining
void j1Scene2::StartCurrentScene()
{
	App->player->position.y = 215;
	App->player->position.x = 60;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
}
