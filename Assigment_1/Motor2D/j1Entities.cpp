#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1Entities.h"
#include "j1Particle.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "Entity.h"

//Include all enemies
#include "Enemy_Zombie.h"
#include "Enemy_Plane.h"

#define SPAWN_MARGIN 2000

j1Entities::j1Entities()
{
	name.create("enemies");
}

// Destructor
j1Entities::~j1Entities()
{
}

bool j1Entities::Start()
{
	LOG("loading enemies");
	// Create a prototype for each enemy available so we can copy them around
	//sprites = App->textures->Load("rtype/enemies.png");

	return true;
}

bool j1Entities::PreUpdate()
{
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
	if (draw_underlayed)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)

			if (enemies[i] != nullptr) enemies[i]->Draw(enemies[i]->sprites, enemies[i]->scale, enemies[i]->colliderXsize);
	}
	else
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr)
			{
				enemies[i]->Move(dt);
			}
		}

		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && (enemies[i]->collider == nullptr))
			{
				enemies[i]->Draw(enemies[i]->sprites, enemies[i]->scale, enemies[i]->colliderXsize);
			}
		}

		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && (enemies[i]->collider != nullptr) && (enemies[i]->collider->type == COLLIDER_ENEMY))
			{
				enemies[i]->Draw(enemies[i]->sprites, enemies[i]->scale, enemies[i]->colliderXsize);
			}
		}
	}

	return true;
}

bool j1Entities::PostUpdate()
{
	// check camera position to decide what to despawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.y >(-App->render->camera.y + SCREEN_HEIGHT + (SPAWN_MARGIN + 1)) || enemies[i]->position.y < (-App->render->camera.y - (SPAWN_MARGIN + 1)))
				//if ((abs((int)App->render->camera.y) + SCREEN_HEIGHT + SPAWN_MARGIN) < enemies[i]->position.y)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
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
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		if (queue[i].type != NO_TYPE)
		{
			queue[i].type = NO_TYPE;
		}
	}

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
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::ZOMBIE:
			enemies[i] = new Enemy_Zombie(info.x, info.y);
			break;
		case ENEMY_TYPES::PLANE:
			enemies[i] = new Enemy_Plane(info.x, info.y);
			break;
		}
	}
}

void j1Entities::OnCollision(Collider* c1, Collider* c2, int distance)
{
	
	/*for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2);
			if (enemies[i]->lives <= 0 && enemies[i]->die == false)
			{
				enemies[i]->collider->to_delete = true;
				enemies[i]->collider = nullptr;
			}
			break;
		}
	}*/

	if (c2->type == COLLIDER_FLOOR)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				enemies[i]->original_pos.y-= distance;
			}
		}
	}

	if (c2->type == COLLIDER_WALL)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				enemies[i]->original_pos.x -= distance;
			}
		}
	}

	if (c2->type == COLLIDER_PLAYER)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				enemies[i]->original_pos.x += 1;
			}
		}
	}
}