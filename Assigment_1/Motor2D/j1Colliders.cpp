#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1Player.h"
#include "j1Entities.h"
#include "Entity.h"
#include "Player.h"
#include "j1Pathfinding.h"
#include "j1Scene.h"
#include "j1Scene2.h"

j1Colliders::j1Colliders() : j1Module()
{
	name.create("colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_DEATH] = false;
	matrix[COLLIDER_WALL][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_WALL][COLLIDER_FEET] = false;
	matrix[COLLIDER_WALL][COLLIDER_WIN] = false;
	matrix[COLLIDER_WALL][COLLIDER_WIN2] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;


	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FEET] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_WIN] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_WIN2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_WALL] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_DEATH][COLLIDER_FEET] = true;
	matrix[COLLIDER_DEATH][COLLIDER_WIN] = false;
	matrix[COLLIDER_DEATH][COLLIDER_WIN2] = false;

	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_DEATH] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_WALL] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_FEET] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_WIN] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_WIN2] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_FEET][COLLIDER_FEET] = false;
	matrix[COLLIDER_FEET][COLLIDER_WALL] = false;
	matrix[COLLIDER_FEET][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_FEET][COLLIDER_DEATH] = true;
	matrix[COLLIDER_FEET][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_FEET][COLLIDER_WIN] = true;
	matrix[COLLIDER_FEET][COLLIDER_WIN2] = true;

	matrix[COLLIDER_WIN][COLLIDER_WIN] = false;
	matrix[COLLIDER_WIN][COLLIDER_WALL] = false;
	matrix[COLLIDER_WIN][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_WIN][COLLIDER_DEATH] = true;
	matrix[COLLIDER_WIN][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_WIN][COLLIDER_FEET] = true;
	matrix[COLLIDER_WIN][COLLIDER_WIN2] = false;

	matrix[COLLIDER_WIN2][COLLIDER_WIN2] = false;
	matrix[COLLIDER_WIN2][COLLIDER_WALL] = false;
	matrix[COLLIDER_WIN2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_WIN2][COLLIDER_DEATH] = true;
	matrix[COLLIDER_WIN2][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_WIN2][COLLIDER_FEET] = true;
	matrix[COLLIDER_WIN2][COLLIDER_WIN] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;


}

// Destructor
j1Colliders::~j1Colliders()
{

}

bool j1Colliders::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool j1Colliders::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate Colliders ", Profiler::Color::Red)
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

// Called before render is available
bool j1Colliders::Update(float dt)
{
	BROFILER_CATEGORY("Update Colliders ", Profiler::Color::PaleVioletRed)
	Collider* c1;
	Collider* c2;


	int distance_2;
	int distance_3;
	int distance_4;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr || colliders[i]->type==COLLIDER_NONE)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			PlayerFloorCollision(c1, c2, dt);


			if (c1->type == COLLIDER_WALL && c2->type == COLLIDER_PLAYER && c1->CheckFutureCrashColision(c2->rect,distance_2, App->player->speed) == true 
				&& (App->input->GetKey(SDL_SCANCODE_D )==KEY_REPEAT|| App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && App->input->GetKey(SDL_SCANCODE_S)==KEY_IDLE)
			{
				App->player->position.x -= distance_2;
			}

			if (c1->type == COLLIDER_DEATH && c2->type == COLLIDER_PLAYER && c1->CheckCollision(c2->rect) == true)
			{
				App->player->dead = true;			
			}

			if (c1->type == COLLIDER_WIN && c2->type == COLLIDER_FEET && c1->CheckCollision(c2->rect) == true)
			{
				App->scene->ChangeScene(60,215);
			}
			
			if (c1->type == COLLIDER_WIN2 && c2->type == COLLIDER_FEET && c1->CheckCollision(c2->rect) == true)
			{
				App->scene->ChangeScene(60, 215);
			}
			
			if (c1->type == COLLIDER_FLOOR && c2->type == COLLIDER_ENEMY && c1->CheckFutureFallColision(c2->rect, distance_4,dt, App->player->gravity) == true)
			{
				App->entities->OnCollision(c2, c1, distance_4);
			}
			
			if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY && c1->CheckFutureCrashColision(c2->rect, distance_2, App->player->speed) == true && !App->player->GOD)
			{

				App->player->dead = true;				
			}

			if ( App->entities->player != nullptr && c1->type == COLLIDER_FLOOR && c2->type == COLLIDER_FEET && c1->CheckFutureFallColision(c2->rect, distance_3, dt, App->entities->player->gravity) == true)
			{
				if(c2 == App->entities->player->collider_feet)
				{
					App->entities->OnCollision(c2, c1, distance_3);
					App->entities->player->original_pos.y -= distance_3;
					App->entities->player->dead = false;

					if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
					{
						App->entities->player->Jump = false;
						App->entities->player->fall = false;
					}
				}
				
			}


			for (uint i = 0; i < MAX_ENEMIES; ++i)
			{
				if (App->entities->entities[i] != nullptr)
				{
					if (c1->type == COLLIDER_WALL && c2->type == COLLIDER_ENEMY && c1->CheckFutureCrashColision(c2->rect, distance_2, App->entities->entities[i]->speed.x) == true)
					{
						App->entities->OnCollision(c2, c1, distance_2);
					}
				}
			}
		}
	}

	DebugDraw();

	return true;
}

void j1Colliders::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		LOG("YOu can see the colliders");
		debug = !debug;
	}

	if (debug == false) {
		return;
	}
	else {

		Uint8 alpha = 255;
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == nullptr)
				continue;

			switch (colliders[i]->type)
			{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha,false);
				break;
			case COLLIDER_WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha,false);
				break;
			case COLLIDER_PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha,false);
				break;
			case COLLIDER_DEATH: // pink
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha, false);
				break;
			case COLLIDER_FLOOR: // light blue
				App->render->DrawQuad(colliders[i]->rect, 135, 206, 250, alpha, false);
				break;
			case COLLIDER_FEET: // light blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha, false);
				break;
			case COLLIDER_WIN: // light blue
				App->render->DrawQuad(colliders[i]->rect, 0, 206, 250, alpha, false);
				break;
			case COLLIDER_WIN2: // light blue
				App->render->DrawQuad(colliders[i]->rect, 0, 206, 250, alpha, false);
				break;
			case COLLIDER_ENEMY: // light blue
				App->render->DrawQuad(colliders[i]->rect, 100, 206, 250, alpha, false);
				break;
				
			}

		}

		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (App->entities->entities[i] != nullptr)
			{
				App->pathfinding->DrawPath(App->entities->entities[i]->Enemypath);
			}
		}
	}
}

bool j1Colliders::checkColisionList(Collider * enemCollider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr)
			continue;
		if (enemCollider->CheckCollision(colliders[i]->rect))
			return true;
	}
	return false;
}

void j1Colliders::PlayerFloorCollision(Collider* collider_floor, Collider* collider_feet, float dt)
{
	if (collider_feet!=App->entities->player->collider_feet
		&&collider_floor->type == COLLIDER_FLOOR
		&& collider_feet->type == COLLIDER_FEET
		&& collider_floor->CheckFutureFallColision(collider_feet->rect, distance_1, dt, App->entities->player->gravity) == true) //en els arguments llargs posar funció
	{
		App->player->position.y -= distance_1;
		App->player->dead = false;

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
		{
			App->player->Jump = false;
			App->player->fall = false;
		}
	}
}

// Called before quitting
bool j1Colliders::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Colliders::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool j1Colliders::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r)const
{
	if ((rect.x < r.x + r.w && rect.x + rect.w > r.x) || (rect.x < r.x + r.w  && rect.x + rect.w > r.x))
	{
		if (rect.y < r.y + r.h && rect.y + rect.h > r.y)
		{
			return true;
		}
	}
	return false;
}

bool Collider::CheckFutureFallColision(const SDL_Rect& r, int& distance, float dt,float speed)
{
	if (rect.x < r.x + r.w && rect.x + rect.w > r.x)
	{
		if (rect.y < r.y + r.h + 500*dt && rect.y && rect.y + rect.h > r.y)
		{
			distance = r.y + r.h + 500*dt - rect.y;
			return true;
		}
	}
	return false;
}

bool Collider::CheckFutureCrashColision(const SDL_Rect& r,int& distance, float speed)
{
	if (speed >0)
	{
		if (rect.x  < r.x + r.w + speed && rect.x + rect.w > r.x)
		{
			if (rect.y < r.y + r.h  && rect.y + rect.h > r.y)
			{
				distance = r.x + r.w + speed - rect.x;
				return true;
			}
		}
	}
	if (speed <0)
	{
		if (rect.x < r.x + r.w && rect.x + rect.w > r.x+speed)
		{
			if (rect.y < r.y + r.h  && rect.y + rect.h > r.y)
			{
				distance = r.x-(rect.x + rect.w -speed);
				return true;
			}
		}
	}
	
	return false;
}


