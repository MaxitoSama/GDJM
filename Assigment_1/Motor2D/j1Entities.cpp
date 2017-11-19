#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "Entity.h"

//Include all enemies
#include "Enemy_Zombie.h"
#include "Enemy_Plane.h"
#include "Player.h"

#define SPAWN_MARGIN 2000

j1Entities::j1Entities()
{
	name.create("entity");
}

// Destructor
j1Entities::~j1Entities()
{
}

bool j1Entities::Awake(pugi::xml_node& config)
{
	config_file.load_file("config.xml");
	entity_config = config_file.child("config").child("entity");

	return true;
}

bool j1Entities::Start()
{
	LOG("loading enemies");
	// Create a prototype for each enemy available so we can copy them around
	//sprites = App->textures->Load("rtype/enemies.png");
	if (player == nullptr)
	{
		player = new Player(10, 100);
		player->Awake(entity_config);
		player->Start();
	}
	

	return true;
}

bool j1Entities::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate Entities", Profiler::Color::Orange);
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (-queue[i].y < App->render->camera.y + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}


	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{
	BROFILER_CATEGORY("Update Entities", Profiler::Color::OrangeRed);
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Update(dt);
		}
	}

	if (player != nullptr)
	{
		player->Update(dt);
		player->Draw(player->sprites, player->scale, player->colliderXsize);
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr && (entities[i]->collider == nullptr))
		{
			entities[i]->Draw(entities[i]->sprites, entities[i]->scale, entities[i]->colliderXsize);
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr && (entities[i]->collider != nullptr) && ((entities[i]->collider->type == COLLIDER_ENEMY)|| (entities[i]->collider->type == COLLIDER_PLAYER)))
		{
			entities[i]->Draw(entities[i]->sprites, entities[i]->scale, entities[i]->colliderXsize);
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->die)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}


	return true;
}

bool j1Entities::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate Entities", Profiler::Color::DarkOrange);
	// check camera position to decide what to despawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->position.y >(-App->render->camera.y + SCREEN_HEIGHT + (SPAWN_MARGIN + 1)) || entities[i]->position.y < (-App->render->camera.y - (SPAWN_MARGIN + 1)))
				//if ((abs((int)App->render->camera.y) + SCREEN_HEIGHT + SPAWN_MARGIN) < enemies[i]->position.y)
			{
				LOG("DeSpawning enemy at %d", entities[i]->position.y * SCREEN_SIZE);
				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}

	return true;
}

// Called before quitting
bool j1Entities::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
		if (queue[i].type != NO_TYPE)
		{
			queue[i].type = NO_TYPE;
		}
	}

	/*if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}*/
	return true;
}

bool j1Entities::AddEnemy(ENEMY_TYPES type, int x, int y, int wave, int id)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].wave = wave;
			queue[i].id = id;
			ret = true;
			break;
		}
	}

	return ret;
}

void j1Entities::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::ZOMBIE:
			entities[i] = new Enemy_Zombie(info.x, info.y);
			entities[i]->Awake(entity_config);
			break;
		case ENEMY_TYPES::PLANE:
			entities[i] = new Enemy_Plane(info.x, info.y);
			entities[i]->Awake(entity_config);
			break;
		case ENEMY_TYPES::PLAYER:
			entities[i] = new Player(info.x, info.y);
			break;
		}
	}
}

void j1Entities::OnCollision(Collider* c1, Collider* c2, float distance)
{
	if (c2->type == COLLIDER_WALL)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
			{
				entities[i]->original_pos.x -= distance;
			}
		}
	}

	if (c2->type == COLLIDER_PLAYER)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
			{
				entities[i]->original_pos.x += 1;
			}
		}
	}
}

bool j1Entities::Load(pugi::xml_node& data)
{
	int map = data.child("player").attribute("Map").as_int();
	int x = data.child("player").attribute("x").as_int();
	int y = data.child("player").attribute("y").as_int();

	if (player->Curr_map != map)
	{
		App->scene->ChangeScene(x, y);
	}

	else
	{
		player->original_pos.x = data.child("player").attribute("x").as_int();
		player->original_pos.y = data.child("player").attribute("y").as_int();
	}

	return true;
}

bool j1Entities::Save(pugi::xml_node& data) const
{
	pugi::xml_node playernode = data.append_child("player");

	playernode.append_attribute("x") = player->original_pos.x;
	playernode.append_attribute("y") = player->original_pos.y;
	playernode.append_attribute("Map") = player->Curr_map;

	return true;
}