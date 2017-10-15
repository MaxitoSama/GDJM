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
		//App->colliders->AddCollider({ 200,900,50,50 }, COLLIDER_WIN, this);
		App->colliders->AddCollider({ 25400,320,50,50 }, COLLIDER_WIN, this);
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
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		Change_to_Scene_1(0,0);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		StartCurrentScene();


	if (App->player->position.x >= App->player->win_width / 2 && App->player->position.x <= 24630)//App->player->win_width)
	{
		App->render->camera.x = -App->player->position.x + App->player->win_width / 2;// + App->player->win_width / 2;
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	// TODO 7: Set the window title like
	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Player.x=%i Player.y=%i CameraPosition.x=%i CameraPosition.y=%i Acceleration=%d X=%d Y=%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count(), App->player->position.x,
		App->player->position.y, App->render->camera.x,
		App->render->camera.y, App->player->acceleration,
		App->player->position.x, App->player->position.y);

	App->win->SetTitle(title.GetString());
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
	App->map->CleanUp();
	App->colliders->CleanUp();

	return true;
}

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

void j1Scene2::StartCurrentScene()
{
	App->player->position.y = 215;
	App->player->position.x = 60;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
}
