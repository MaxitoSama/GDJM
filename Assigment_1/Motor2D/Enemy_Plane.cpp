#include "Enemy_Plane.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Entities.h"
#include "Player.h"

Enemy_Plane::Enemy_Plane(int x, int y): Entity(x, y)
{
	//Open all textures
	NormalSprite = App->tex->Load("assets/enemies/plane/plane.png");
	//RedSprite = App->tex->Load("assets/enemies/hitten/hitten_red_Balloon.png");
	//WhiteSprite = App->tex->Load("assets/enemies/hitten/hitten_white_Balloon.png");

	//Set animation steps, speed and loop
	anim.PushBack({ 49, 40, 639, 412 });
	anim.PushBack({ 806, 40, 639, 412 });
	anim.speed = 18.0f;
	anim.loop = true;

	moving.PushBack({ 49, 40, 639, 412 });
	moving.PushBack({ 49, 37, 639, 412 });
	moving.PushBack({ 806, 40, 639, 412 });
	moving.PushBack({ 806, 43, 639, 412 });
	moving.speed = 18.0f;
	moving.loop = true;

	dead.PushBack({ 1539, 40, 639, 412 });
	dead.speed = 18.0f;
	dead.loop = true;


	
	scale = -0.3;
	colliderXsize = (639 * 2) / 5;
	initial_pos.x = original_pos.x;
	initial_pos.y = original_pos.y;
	
	right = true;
	left = false;

	animation = &anim;

	//Add and save collider
	collider_pos.x = 0;
	collider_pos.y = 0;
	collider = App->colliders->AddCollider({ x, y, (639*2)/5, (412*2)/5 }, COLLIDER_ENEMY, (j1Module*)App->entities);
}

Enemy_Plane::~Enemy_Plane()
{
	App->tex->UnLoad(NormalSprite);
}

void Enemy_Plane::Move(float dt)
{
	iPoint enemyposition = { (int)original_pos.x,(int)original_pos.y };

	position = original_pos;
	//original_pos.y += speed.y;


	if (abs((int)App->entities->player->original_pos.x - (int)original_pos.x) <= 600 && !going)
	{
		going = true;
		go_x = true;
		go_y = true;
		goback = false;
		iPoint player = { (int)App->entities->player->original_pos.x, (int)App->entities->player->original_pos.y + 50 };
		App->pathfinding->CreatePath(enemyposition, player);
		App->pathfinding->Path(App->entities->player->original_pos.x, App->entities->player->original_pos.y, Enemypath);
	}

	if (!going && !goback)
	{
		animation = &moving;

		if (original_pos.x<(float)initial_pos.x + 200 && right == true)
		{
			speed.x = 100 * dt;
			original_pos.x += speed.x;
			scale = 0.4;
			if (original_pos.x >= (float)initial_pos.x + 200)
			{
				left = true;
				right = false;
			}
		}
		if (original_pos.x>(float)initial_pos.x - 200 && left == true)
		{
			speed.x = -100 * dt;
			original_pos.x += speed.x;
			scale = -0.4;
			if (original_pos.x <= (float)initial_pos.x - 200)
			{
				left = false;
				right = true;
			}
		}
	}

	else
	{
		
		if (enemyposition.x != (int)App->entities->player->original_pos.x && enemyposition.y != (int)App->entities->player->original_pos.y)
		{
			iPoint PositiontoGo = App->map->MapToWorld(Enemypath[pathcounter].x, Enemypath[pathcounter].y);
			if (App->entities->player->original_pos.x<original_pos.x)
			{
				scale = -0.4;
			}
			else
			{
				scale = 0.4;
			}
			if (go_x)
			{
				if (PositiontoGo.x < (int)original_pos.x)
				{
					speed.x = -200 * dt;
					original_pos.x += speed.x;
					if (PositiontoGo.x >= (int)original_pos.x)
					{
						go_x = false;
					}
				}
				else
				{
					speed.x = 200 * dt;
					original_pos.x += speed.x;
					if (PositiontoGo.x <= (int)original_pos.x)
					{
						go_x = false;
					}
				}
			}
			
			if (go_y)
			{
				if (PositiontoGo.y < (int)original_pos.y)
				{
					speed.y = -200 * dt;
					original_pos.y += speed.y;
					if (PositiontoGo.y >= (int)original_pos.y)
					{
						go_y = false;
					}
				}
				else
				{
					speed.y = 200 * dt;
					original_pos.y += speed.y;
					if (PositiontoGo.y <= (int)original_pos.y)
					{
						go_y = false;
					}
				}
			}

			if (!go_y && !go_x)
			{
				pathcounter++;
				if (pathcounter < Enemypath.Count())
				{
					go_x = true;
					go_y = true;
				}
				else
				{
					if (going)
					{
						going = false;
					}
					if (goback)
					{
						goback = false;
					}
					pathcounter = 0;
				}
			}
		}
		
		if (abs((int)App->entities->player->original_pos.x - (int)original_pos.x) >= 500 && going )
		{
			pathcounter = 0;
			going = false;
			goback = true;
			go_x = true;
			go_y = true;
			
			iPoint start = { (int)initial_pos.x, (int)initial_pos.y};
			App->pathfinding->CreatePath(enemyposition, start);
			App->pathfinding->Path(start.x,start.y, Enemypath);
		}
	}
}

void Enemy_Plane::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
