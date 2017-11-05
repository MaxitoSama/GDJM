#include "Enemy_Zombie.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Player.h"


Enemy_Zombie::Enemy_Zombie(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->tex->Load("assets/enemies/zombie/zombie.png");
	RedSprite = App->tex->Load("assets/enemies/hitten/hitten_red_Balloon.png");
	WhiteSprite = App->tex->Load("assets/enemies/hitten/hitten_white_Balloon.png");

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
	anim.speed = 0.5f;
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
	dead.speed = 0.5f;
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
	walking.speed = 0.5f;
	walking.loop = true;
	
	//Set path
	path.PushBack({ 0.0f, 0.0f}, 40, &dead); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	//path.PushBack({ 0.0f, -0.3f }, 240, &anim);
	//path.PushBack({ 0.0f, 0.9f }, 60, &anim);
	//path.PushBack({ 0.0f, -0.3f }, 350, &anim);
	//path.PushBack({ 0.0f, 0.9f }, 600, &anim);

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	//points = 400;
	extra_anim = false;
	//explosion_type = BIG1; //Explosion type

	//shooting mechanic
	
	//shoot = particle_type::P_BIG_SHOT;
	//big_shoot = &App->particles->big_shot_particle;
	Shot_Total_time = (Uint32)(2000.0f);

	collider = App->colliders->AddCollider({ (int)position.x, (int)position.y, -120, 342/2 }, COLLIDER_ENEMY, (j1Module*)App->enemies);
}

Enemy_Zombie::~Enemy_Zombie()
{
	App->tex->UnLoad(NormalSprite);
}

void Enemy_Zombie::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	original_pos.x -= 1;
	original_pos.y += 10;
	
	Shot_now = SDL_GetTicks() - Shot_Start_time;
	if (Shot_now > Shot_Total_time)
	{
		Shot_Start_time = SDL_GetTicks();

		//App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 18, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 248, ANGLE);

	}
	
}

void Enemy_Zombie::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}

void Enemy_Zombie::Drop()
{

}