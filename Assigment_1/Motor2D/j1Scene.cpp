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
#include "j1Entities.h"
#include "Player.h"

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

		//App->entities->AddEnemy(PLAYER, 10, 0);
	
		//enemies
		App->entities->AddEnemy(ZOMBIE, 1300, 600);
		App->entities->AddEnemy(ZOMBIE, 2500, 600);
		App->entities->AddEnemy(ZOMBIE, 19369, 827);
		App->entities->AddEnemy(ZOMBIE, 7000, 600);
		App->entities->AddEnemy(ZOMBIE, 9812, 668);
		//App->colliders->AddCollider({ 32,600,32,1 }, COLLIDER_FLOOR, this);
		//App->colliders->AddCollider({ 64,600,32,1 }, COLLIDER_FLOOR, this);
		App->entities->AddEnemy(PLANE, 2000, 100);
		App->colliders->AddCollider({ 11104,636,608,64 }, COLLIDER_DEATH);
		App->colliders->AddCollider({ 22112,829,288,32 }, COLLIDER_DEATH);
	}

	if (Map_2)
	{
		App->map->Load("Map_2.tmx");
		App->audio->PlayMusic("audio/music/map1_music.ogg");
		App->map->Draw_Colliders();

		App->colliders->AddCollider({ 25400,0,50,310 }, COLLIDER_WIN2, this);
		App->colliders->AddCollider({ 18923,0,50,310 }, COLLIDER_WIN2, this);
		App->colliders->AddCollider({ 21087,828,320,32 }, COLLIDER_DEATH);

		//App->enemies->AddEnemy(ZOMBIE, 10, 10);
		App->entities->AddEnemy(ZOMBIE, 19461,825);
		App->entities->AddEnemy(ZOMBIE, 18467, 825);
		App->entities->AddEnemy(ZOMBIE, 4949, 828);

		App->entities->AddEnemy(PLANE, 1500, 100);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate_Scene1 ", Profiler::Color::Orchid)
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene1 ", Profiler::Color::MediumOrchid)

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
		iPoint PlayerPosition = { (int)App->entities->player->original_pos.x, (int)App->entities->player->position.y+50 };
		
		if (App->pathfinding->CreatePath({ 0,0 }, PlayerPosition) != -1)
		{
			App->pathfinding->Path(PlayerPosition.x, PlayerPosition.y, path_test);
		}
		LOG("Path created");
	}

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (App->Cap_on)
		{
			App->Cap_on = false;
		}
		else
		{
			App->Cap_on = true;
		}
	}	

	//Camera Movement--------------------------------------
	int map_height = App->map->data.height * App->map->data.tile_height;
	int map_width = App->map->data.width * App->map->data.tile_width;
	int win_height = App->entities->player->win_height;
	int win_width = App->entities->player->win_width;
	int win_position_y = App->render->camera.y*-1;
	int limit_y = map_height - win_height;
	int limit_x = map_width - win_width;

	if (App->entities->player->original_pos.x > win_width / 2 && App->entities->player->original_pos.x <= limit_x)
	{
		App->render->camera.x = App->entities->player->win_width / 2 - App->entities->player->original_pos.x;
	}
	
	if (!App->win->fullscreen_window && App->entities->player->original_pos.y > win_height / 2 && win_position_y+win_height <map_height)
	{
		if (App->entities->player->original_pos.y + win_height / 2 < map_height)
		{
			App->render->camera.y = -App->entities->player->original_pos.y + win_height / 2;
		}
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
	BROFILER_CATEGORY("PosUpdate_Scene1 ", Profiler::Color::DarkOrchid)
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	
	App->entities->CleanUp();
	App->colliders->CleanUp();
	App->map->CleanUp();
	App->pathfinding->CleanUp();
	App->tex->CleanUp();

	return true;
}

//go to the begining
void j1Scene::StartCurrentScene()
{
	App->entities->player->original_pos.x = 60;
	App->entities->player->original_pos.y = 215;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
}

//Change to scene 2
void j1Scene::ChangeScene(int x, int y)
{
	CleanUp();
	
	if (Map_1 && App->entities->player->Curr_map==1)
	{
		Map_1 = false;
		Map_2 = true;

		App->scene->Start();
		App->pathfinding->Start();
		App->entities->player->original_pos.y = y;
		App->entities->player->original_pos.x = x;
		App->render->camera.x = 0;
		App->render->camera.y = 0;
		App->entities->player->Curr_map = 2;
		App->entities->Start();
	}
	else
	{
		Map_1 = true;
		Map_2 = false;

		App->scene->Start();
		App->pathfinding->Start();
		App->entities->player->original_pos.y = y;
		App->entities->player->original_pos.x = x;
		App->render->camera.x = 0;
		App->render->camera.y = 0;
		App->entities->player->Curr_map = 1;
		App->entities->Start();
	}
	
}