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
#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1Player.h"
#include "j1Enemies.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	Map_1 = true;
	Map_2 = false;


	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (Map_1)
	{
		App->map->Load("Map_1.tmx");
		App->audio->PlayMusic("audio/music/map1_music.ogg");
		App->map->Draw_Colliders();
		App->colliders->AddCollider({ 25400,0,50,380 }, COLLIDER_WIN, this);

		//enemies
		App->enemies->AddEnemy(ZOMBIE, 1500, 0);
		App->enemies->AddEnemy(ZOMBIE, 11398, 245); 
		App->colliders->AddCollider({ 32,600,32,1 }, COLLIDER_FLOOR, this);
		App->colliders->AddCollider({ 64,600,32,1 }, COLLIDER_FLOOR, this);
		App->enemies->AddEnemy(PLANE, 1500, 100);
		App->enemies->AddEnemy(PLANE, 2000, 100);
		App->colliders->AddCollider({ 11104,636,608,64 }, COLLIDER_DEATH);
		App->colliders->AddCollider({ 22112,829,288,32 }, COLLIDER_DEATH);
		App->player->Curr_map = 1;
	}

	if (Map_2)
	{
		App->map->Load("Map_2.tmx");
		App->audio->PlayMusic("audio/music/map1_music.ogg");
		App->map->Draw_Colliders();

		App->colliders->AddCollider({ 25400,0,50,310 }, COLLIDER_WIN2, this);
		App->colliders->AddCollider({ 18923,0,50,310 }, COLLIDER_WIN2, this);
		App->colliders->AddCollider({ 21087,828,320,32 }, COLLIDER_DEATH);

		App->player->Curr_map = 2;
		//App->enemies->AddEnemy(ZOMBIE, 10, 10);
		App->enemies->AddEnemy(ZOMBIE, 20076,284);
		App->enemies->AddEnemy(ZOMBIE, 19088, 60);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	int dist1 = App->player->win_width / 2;
	int dist2 = App->player->win_height / 2;

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (Map_1)
		{
			StartCurrentScene();
		}
		else
		{
			ChangeScene(60, 215);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		StartCurrentScene();

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		ChangeScene(60,215);

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		App->pathfinding->ResetPath();
		iPoint PlayerPosition = { App->player->position.x, App->player->position.y };
		
		if (App->pathfinding->CreatePath({ 0,0 }, PlayerPosition) != -1)
		{
			App->pathfinding->Path(PlayerPosition.x, PlayerPosition.y, path_test);
		}
		LOG("Path created");
	}
		
	if (App->player->position.x > dist1 && App->player->position.x <= 24630)
	{
		App->render->camera.x = -App->player->position.x + App->player->win_width / 2;
	}
	if (App->player->position.y > dist2 && App->player->position.y <App->player->win_height-50 && !App->win->fullscreen_window)
	{
		App->render->camera.y = -App->player->position.y + App->player->win_height / 2;
	}



	App->map->Draw();
	App->pathfinding->DrawPath(path_test);

	p2SString title("%s",App->GetTitle());

	//App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	
	App->enemies->CleanUp();
	App->colliders->CleanUp();
	App->map->CleanUp();
	App->pathfinding->CleanUp();
	App->tex->CleanUp();

	return true;
}

//go to the begining
void j1Scene::StartCurrentScene()
{
	App->player->position.x = 60;
	App->player->position.y = 215;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
}

//Change to scene 2
void j1Scene::ChangeScene(int x, int y)
{
	CleanUp();
	App->player->speed = 0;
	
	if (Map_1 && App->player->Curr_map==1)
	{
		Map_1 = false;
		Map_2 = true;

		App->scene->Start();
		App->pathfinding->Start();
		App->player->position.y = y;
		App->player->position.x = x;
		App->render->camera.x = 0;
		App->render->camera.y = 0;
		App->player->Start();
	}
	else
	{
		Map_1 = true;
		Map_2 = false;
		App->scene->Start();
		App->pathfinding->Start();
		App->player->position.y = y;
		App->player->position.x = x;
		App->render->camera.x = 0;
		App->render->camera.y = 0;
		App->player->Start();
	}
	
}