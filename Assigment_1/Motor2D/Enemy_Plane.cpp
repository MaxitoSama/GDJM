#include "Enemy_Plane.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
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
	anim.speed = 0.3f;
	anim.loop = true;

	dead.PushBack({ 1539, 40, 639, 412 });
	dead.speed = 0.3f;
	dead.loop = true;
	//Set path
	//path.PushBack({ 0.0f, 0.0f}, 40, &anim); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay


	//Set lives, initial_hp, points adn extra_anim
	//lives = 25;
	//initial_hp = lives;
	//points = 400;
	extra_anim = false;
	scale = -0.5;
	//explosion_type = BIG1; //Explosion type

	//shooting mechanic
	
	//shoot = particle_type::P_BIG_SHOT;
	//big_shoot = &App->particles->big_shot_particle;
	//Shot_Total_time = (Uint32)(2000.0f);
	animation = &anim;

	//Add and save collider
	collider_pos.x = 0;
	collider_pos.y = 0;
	collider = App->colliders->AddCollider({ x, y, -639/2, 412/2 }, COLLIDER_ENEMY, (j1Module*)App->enemies);
}

Enemy_Plane::~Enemy_Plane()
{
	App->tex->UnLoad(NormalSprite);
}

void Enemy_Plane::Move()
{
	position = original_pos;
	
	Shot_now = SDL_GetTicks() - Shot_Start_time;
	if (Shot_now > Shot_Total_time)
	{
		Shot_Start_time = SDL_GetTicks();

		//App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 18, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 248, ANGLE);
	}
}

void Enemy_Plane::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}

void Enemy_Plane::Drop()
{
	//App->powerup->AddPowerUp(UPGRADE, App->render->camera.x + position.x, App->render->camera.y + position.y);
}