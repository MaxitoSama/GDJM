#include "Enemy_Plane.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Player.h"

Enemy_Plane::Enemy_Plane(int x, int y): Enemy(x, y)
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
	initial_pos = original_pos.x;
	
	right = true;
	left = false;

	animation = &anim;

	//Add and save collider
	collider_pos.x = 0;
	collider_pos.y = 0;
	collider = App->colliders->AddCollider({ x, y, (639*2)/5, (412*2)/5 }, COLLIDER_ENEMY, (j1Module*)App->enemies);
}

Enemy_Plane::~Enemy_Plane()
{
	App->tex->UnLoad(NormalSprite);
}

void Enemy_Plane::Move()
{
	iPoint enemyposition = { (int)original_pos.x,(int)original_pos.y };
	fPoint speed;

	position = original_pos;
	//original_pos.y += speed.y;

	if (abs((int)App->player->position.x - (int)original_pos.x) <= 600 && !going)
	{
		going = true;
		pathcounter = 0;
		App->pathfinding->CreatePath(enemyposition, App->player->position);
		App->pathfinding->Path(App->player->position.x, App->player->position.y, Enemypath);
	}

	if (!going)
	{
		animation = &moving;

		if (original_pos.x<(float)initial_pos + 200 && right == true)
		{
			original_pos.x += 10;
			scale = 0.4;
			if (original_pos.x >= (float)initial_pos + 200)
			{
				left = true;
				right = false;
			}
		}
		if (original_pos.x>(float)initial_pos - 200 && left == true)
		{
			original_pos.x -= 10;
			scale = -0.4;
			if (original_pos.x <= (float)initial_pos - 200)
			{
				left = false;
				right = true;
			}
		}
	}

	else
	{
		
		if (enemyposition != App->player->position)
		{
			if (App->player->position.x < enemyposition.x)
			{
				speed.x = -8;
				scale = -0.4f;
			}
			
			else
			{
				speed.x = 8;
				scale = 0.4f;
			}
			
			if (App->player->position.y < enemyposition.y)
			{
				speed.y = -8;
			}
			
			else
			{
				speed.y = 8;
			}

			iPoint PositiontoGo = App->map->MapToWorld(Enemypath[pathcounter].x, Enemypath[pathcounter].y);

			if ((int)original_pos.x != PositiontoGo.x)
			{
				original_pos.x += speed.x;
			}
			if ((int)original_pos.y != PositiontoGo.y)
			{
				original_pos.y += speed.y;
			}

			if ((int)original_pos.x == PositiontoGo.x && (int)original_pos.y == PositiontoGo.y)
			{
				pathcounter++;
			}
		}
		if (abs((int)App->player->position.x - (int)original_pos.x) >= 500)
		{
			going = false;
			initial_pos = original_pos.x;
		}
	}
}

void Enemy_Plane::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
