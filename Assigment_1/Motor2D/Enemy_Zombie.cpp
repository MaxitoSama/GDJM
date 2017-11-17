#include "Enemy_Zombie.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Entities.h"
#include "Player.h"


Enemy_Zombie::Enemy_Zombie(int x, int y): Entity(x, y)
{
	//Open all textures
	NormalSprite = App->tex->Load("assets/enemies/zombie/zombie.png");
	//RedSprite = App->tex->Load("assets/enemies/hitten/hitten_red_Balloon.png");
	//WhiteSprite = App->tex->Load("assets/enemies/hitten/hitten_white_Balloon.png");

	//Set animation steps, speed and loop
	//Idle
	anim.PushBack({ 55, 432, 240, 342 });
	anim.PushBack({ 295, 432, 240, 342 });
	anim.PushBack({ 540, 432, 240, 342 });
	anim.PushBack({ 805, 432, 240, 342 });
	anim.PushBack({ 1060, 432, 240, 342 });
	anim.PushBack({ 1332, 432, 240, 342 });
	anim.PushBack({ 1579, 432, 240, 342 });
	anim.PushBack({ 1832, 432, 240, 342 });
	anim.PushBack({ 2086, 432, 240, 342 });
	anim.PushBack({ 2362, 432, 240, 342 });
	anim.PushBack({ 2640, 432, 240, 342 });
	anim.PushBack({ 2879, 432, 240, 342 });
	anim.PushBack({ 3154, 432, 240, 342 });
	anim.PushBack({ 3412, 432, 240, 342 });
	anim.PushBack({ 3670, 432, 240, 342 });
	anim.speed = 30.0f;
	anim.loop = true;

	//dead
	dead.PushBack({ 0, 0, 290, 367 });
	dead.PushBack({ 290, 0, 327, 367 });
	dead.PushBack({ 617, 0, 314, 367 });
	dead.PushBack({ 930, 0, 300, 367 });
	dead.PushBack({ 1220, 0, 250, 367 });
	dead.PushBack({ 1470, 0, 290, 367 });
	dead.PushBack({ 1740, 0, 290, 367 });
	dead.PushBack({ 2020, 0, 330, 367 });
	dead.PushBack({ 2366, 0, 380, 367 });
	dead.PushBack({ 2765, 0, 380, 367 });
	dead.PushBack({ 3148, 0, 380, 367 });
	dead.PushBack({ 3556, 0, 390, 367 });
	dead.speed = 30.0f;
	dead.loop = true;

	//walking
	walking.PushBack({ 11, 809, 264, 361 });
	walking.PushBack({ 311, 809, 264, 360 });
	walking.PushBack({ 621, 809, 264, 360 });
	walking.PushBack({ 920, 809, 264, 360 });
	walking.PushBack({ 1220, 809, 264, 360 });
	walking.PushBack({ 1501, 809, 264, 360 });
	walking.PushBack({ 1806, 809, 264, 360 });
	walking.PushBack({ 2069, 809, 264, 360 });
	walking.PushBack({ 2333, 809, 264, 360 });
	walking.PushBack({ 2596, 809, 264, 360 });
	walking.speed = 30.0f;
	walking.loop = true;
	
	//Set path
	//path.PushBack({ 0.0f, 0.0f}, 40, &walking); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	//path.PushBack({ 0.0f, -0.3f }, 240, &anim);
	//path.PushBack({ 0.0f, 0.9f }, 60, &anim);
	//path.PushBack({ 0.0f, -0.3f }, 350, &anim);
	//path.PushBack({ 0.0f, 0.9f }, 600, &anim);

	//Set lives, initial_hp, points adn extra_anim
	

	animation = &walking;
	scale = -0.5;
	colliderXsize = 120;
	initial_pos.x = original_pos.x;

	right = true;
	left = false;
	speed = { 0,500 };

	collider = App->colliders->AddCollider({ (int)(position.x-120), (int)position.y, 120, 360/2 }, COLLIDER_ENEMY, (j1Module*)App->entities);
}

Enemy_Zombie::~Enemy_Zombie()
{
	App->tex->UnLoad(NormalSprite);
}

void Enemy_Zombie::Move(float dt)
{
	iPoint enemyposition = { (int)original_pos.x,(int)original_pos.y+10 };
	
	
	original_pos.y += speed.y*dt;
	
	if (abs((int)App->entities->player->original_pos.x - (int)original_pos.x)<=500 && !going)
	{
		going	= true;
		go_x	= true;
		pathcounter = 0;
		speed = { 0.0f,0.0f };

		iPoint player = { (int)App->entities->player->original_pos.x, (int)App->entities->player->original_pos.y};
		App->pathfinding->CreatePath(enemyposition, player);
		App->pathfinding->Path(App->entities->player->original_pos.x, App->entities->player->original_pos.y,Enemypath);
	}
	

	if (!going)
	{
		animation = &walking;

		if(original_pos.x<initial_pos.x+150 && right==true)
		{
			speed.x = 250 * dt;
			original_pos.x += speed.x;
			scale = 0.5;
			if (original_pos.x >= initial_pos.x + 150)
			{
				left = true;
				right = false;
			}
		}
		if(original_pos.x>initial_pos.x - 150 && left == true)
		{
			speed.x = -250 * dt;
			original_pos.x +=speed.x;
			scale = -0.5;
			if (original_pos.x <= initial_pos.x - 150)
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

			if (go_x)
			{
				if (PositiontoGo.x < (int)original_pos.x)
				{
					speed.x = -200 * dt;
					original_pos.x += speed.x;
					scale = -0.5;
					if (PositiontoGo.x >= (int)original_pos.x)
					{
						go_x = false;
					}
				}
				else
				{
					speed.x = 200 * dt;
					original_pos.x += speed.x;
					scale = 0.5;
					if (PositiontoGo.x <= (int)original_pos.x)
					{
						go_x = false;
					}
				}
			}

			if (!go_x)
			{
				pathcounter++;
				if (pathcounter < Enemypath.Count())
				{
					go_x = true;
				}
				else
				{
					going = false;
				}
			}
		}
	}

	if (abs((int)App->entities->player->original_pos.x - (int)original_pos.x) > 501 && going)
	{
		going = false;
		initial_pos.x = original_pos.x;
	}
	
	position = original_pos;
	LOG("Zombie pos %f", original_pos.x-App->entities->player->original_pos.x);
}

void Enemy_Zombie::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
