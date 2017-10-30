#include <math.h>
//#include "Globals.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Particles.h"
#include "j1Audio.h"
#include "j1Colliders.h"
//#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "j1Player.h"
//#include "ModulePowerUp.h"
#include "SDL/include/SDL_timer.h"

#define PI 3.14159265

j1Particles::j1Particles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

j1Particles::~j1Particles()
{}

// Load assets
bool j1Particles::Start()
{
	//LOG("Loading particles");
	/*
	MARION_bullet_texture = App->textures->Load("assets/characters/marion.png");

	ASH_bullet_texture = App->textures->Load("assets/characters/ash.png");
	ASH_bomb = App->textures->Load("assets/characters/Ash Bomb.png");

	big_shot_texture = App->textures->Load("assets/enemies/Bullets Big.png");
	mid_shot_texture = App->textures->Load("Assets/enemies/Bullets Medium.png");
	small_shot_texture = App->textures->Load("assets/enemies/Bullets Small.png");

	upgrade_texture = App->textures->Load("assets/items/upgrade.png");
	bomb_texture = App->textures->Load("assets/items/bomb.png");
	coin_texture = App->textures->Load("assets/items/coin.png");

	// Marion Bullets
	MARION_bullet_p1_particle.anim.PushBack({ 166, 127, 7, 30 });
	MARION_bullet_p1_particle.speed.y = -8;
	MARION_bullet_p1_particle.anim.loop = false;
	MARION_bullet_p1_particle.anim.speed = 0.5f;
	MARION_bullet_p1_particle.damage = 1;

	MARION_bullet_p2_particle.anim.PushBack({ 192, 127, 15, 29 });
	MARION_bullet_p2_particle.speed.y = -8;
	MARION_bullet_p2_particle.anim.loop = false;
	MARION_bullet_p2_particle.anim.speed = 0.5f;
	MARION_bullet_p2_particle.damage = 2;
	
	//stage 3
	MARION_bullet_p3_left_particle.anim.PushBack({ 225, 67, 5, 28 });
	MARION_bullet_p3_left_particle.anim.PushBack({ 225, 97, 5, 28 });
	MARION_bullet_p3_left_particle.anim.PushBack({ 225, 127, 5, 28 });

	MARION_bullet_p3_right_particle.anim.PushBack({ 258, 67, 5, 28 });
	MARION_bullet_p3_right_particle.anim.PushBack({ 258, 97, 5, 28 });
	MARION_bullet_p3_right_particle.anim.PushBack({ 258, 127, 5, 28 });

	MARION_bullet_p3_left_particle.speed.y = -8;
	MARION_bullet_p3_left_particle.anim.loop = true;
	MARION_bullet_p3_left_particle.anim.speed = 0.5f;
	MARION_bullet_p3_left_particle.damage = 1;

	MARION_bullet_p3_right_particle.speed.y = -8;
	MARION_bullet_p3_right_particle.anim.loop = true;
	MARION_bullet_p3_right_particle.anim.speed = 0.5f;
	MARION_bullet_p3_right_particle.damage = 1;
	
	//stage 4
	MARION_bullet_p4_left_particle.anim.PushBack({ 286, 127, 15, 28 });
	MARION_bullet_p4_left_particle.anim.PushBack({ 286, 97, 15, 28 });
	MARION_bullet_p4_left_particle.anim.PushBack({ 286, 67, 15, 28 });
	MARION_bullet_p4_left_particle.speed.y = -8;
	MARION_bullet_p4_left_particle.anim.loop = false;
	MARION_bullet_p4_left_particle.anim.speed = 0.05f;
	MARION_bullet_p4_left_particle.damage = 2;

	MARION_bullet_p4_right_particle.anim.PushBack({ 316, 127, 15, 28 });
	MARION_bullet_p4_right_particle.anim.PushBack({ 316, 97, 15, 28 });
	MARION_bullet_p4_right_particle.anim.PushBack({ 316, 67, 15, 28 });

	MARION_bullet_p4_right_particle.speed.y = -8;
	MARION_bullet_p4_right_particle.anim.loop = false;
	MARION_bullet_p4_right_particle.anim.speed = 0.05f;
	MARION_bullet_p4_right_particle.damage = 2;

	MARION_star_particle.anim.PushBack({132, 76, 15, 15});
	MARION_star_particle.anim.speed = 0.2f;
	MARION_star_particle.damage = 2;
	MARION_star_particle.speed.y = -3.0f;

	// Ash Bullets
	ASH_bullet_p1_particle.anim.PushBack({ 175, 29, 9, 29});
	ASH_bullet_p1_particle.speed.y = -8;
	ASH_bullet_p1_particle.anim.loop = false;
	ASH_bullet_p1_particle.anim.speed = 0.5f;
	ASH_bullet_p1_particle.damage = 1;

	ASH_bullet_p2_particle.anim.PushBack({ 170, 68, 19, 37 });
	ASH_bullet_p2_particle.speed.y = -8;
	ASH_bullet_p2_particle.anim.loop = false;
	ASH_bullet_p2_particle.anim.speed = 0.5f;
	ASH_bullet_p2_particle.damage = 2;

	ASH_bullet_p3_particle.anim.PushBack({ 163, 111, 31, 43 });
	ASH_bullet_p3_particle.anim.PushBack({ 197, 111, 31, 43 });
	ASH_bullet_p3_particle.speed.y = -8;
	ASH_bullet_p3_particle.anim.loop = false;
	ASH_bullet_p3_particle.anim.speed = 0.5f;
	ASH_bullet_p3_particle.damage = 3;

	ASH_bullet_p3_donut_particle.anim.PushBack({ 18, 214, 52, 29 });
	ASH_bullet_p3_donut_particle.anim.PushBack({ 95, 214, 52, 29 });
	ASH_bullet_p3_donut_particle.anim.PushBack({ 176, 214, 52, 29 });
	ASH_bullet_p3_donut_particle.anim.PushBack({ 262, 214, 52, 29 });
	ASH_bullet_p3_donut_particle.speed.y = -11;
	ASH_bullet_p3_donut_particle.anim.loop = false;
	ASH_bullet_p3_donut_particle.anim.speed = 0.1f;
	ASH_bullet_p3_donut_particle.damage = 3;

	ASH_bullet_p4_particle.anim.PushBack({ 161, 158, 38, 45 });
	ASH_bullet_p4_particle.anim.PushBack({ 195, 158, 38, 45 });
	ASH_bullet_p4_particle.anim.PushBack({ 233, 158, 38, 45 });
	ASH_bullet_p4_particle.speed.y = -8;
	ASH_bullet_p4_particle.anim.loop = false;
	ASH_bullet_p4_particle.anim.speed = 0.5f;
	ASH_bullet_p4_particle.damage = 4;

	ASH_bullet_p4_donut_particle.anim.PushBack({ 8, 245, 74, 33 });
	ASH_bullet_p4_donut_particle.anim.PushBack({ 83, 245, 74, 33 });
	ASH_bullet_p4_donut_particle.anim.PushBack({ 165, 245, 74, 33 });
	ASH_bullet_p4_donut_particle.anim.PushBack({ 251, 245, 74, 33 });
	ASH_bullet_p4_donut_particle.anim.PushBack({ 338, 245, 74, 33 });
	ASH_bullet_p4_donut_particle.speed.y = -11;
	ASH_bullet_p4_donut_particle.anim.loop = false;
	ASH_bullet_p4_donut_particle.anim.speed = 0.1f;
	ASH_bullet_p4_donut_particle.damage = 3;

	// Small shot
	small_shot_particle.anim.PushBack({ 9, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 41, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 73, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 105, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 137, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 185, 9, 6, 6 });
	small_shot_particle.anim.PushBack({ 9, 25, 6, 6 });
	small_shot_particle.anim.PushBack({ 41, 25, 6, 6 });
	small_shot_particle.speed.x = 0;
	small_shot_particle.speed.y = 0;
	small_shot_particle.anim.loop = true;
	small_shot_particle.anim.speed = 0.5f;
	
	// Mid_Shoot
	mid_shot_particle.anim.PushBack({ 0, 0, 8, 8 });
	mid_shot_particle.anim.PushBack({ 9, 0, 8, 8 });
	mid_shot_particle.anim.PushBack({ 18, 0, 8, 8 });

	mid_shot_particle.anim.PushBack({ 0, 9, 8, 8 });
	mid_shot_particle.anim.PushBack({ 9, 9, 8, 8 });
	mid_shot_particle.anim.PushBack({ 18, 9, 8, 8 });

	mid_shot_particle.anim.PushBack({ 0, 18, 8, 8 });
	mid_shot_particle.anim.PushBack({ 9, 18, 8, 8 });
	mid_shot_particle.speed.x = 0;
	mid_shot_particle.speed.y = 0;
	mid_shot_particle.anim.loop = true;
	mid_shot_particle.anim.speed = 0.75f;

	// Big_Shoot
	big_shot_particle.anim.PushBack({ 96, 97, 12, 12 });
	big_shot_particle.anim.PushBack({ 153, 98, 12, 12 });
	big_shot_particle.speed.x = 0;
	big_shot_particle.speed.y = -8;
	big_shot_particle.anim.loop = true;
	big_shot_particle.anim.speed = 0.5f;
	big_shot_particle.damage = 1;

	// Upgrade
	upgrade_particle.anim.PushBack({ 4, 31, 22, 13 });
	upgrade_particle.anim.PushBack({ 54, 31, 22, 13 });
	upgrade_particle.anim.PushBack({ 104, 31, 22, 13 });
	upgrade_particle.anim.PushBack({ 54, 47, 22, 13 });
	upgrade_particle.anim.PushBack({ 104, 47, 22, 13 });
	upgrade_particle.anim.PushBack({ 54, 64, 22, 13 });
	upgrade_particle.anim.PushBack({ 104, 64, 22, 13 });
	upgrade_particle.anim.PushBack({ 56, 83, 22, 13 });
	upgrade_particle.anim.PushBack({ 81, 83, 22, 13 });
	upgrade_particle.anim.loop = true;
	upgrade_particle.anim.speed = 0.2f;

	// Bomb
	bomb_particle.anim.PushBack({ 2, 3, 23, 12 });
	bomb_particle.anim.PushBack({ 30, 3, 23, 12 });
	bomb_particle.anim.PushBack({ 59, 3, 23, 12 });
	bomb_particle.anim.PushBack({ 2, 23, 23, 12 });
	bomb_particle.anim.PushBack({ 30, 23, 23, 12 });
	bomb_particle.anim.PushBack({ 59, 23, 23, 12 });
	bomb_particle.anim.PushBack({ 2, 43, 23, 12 });
	bomb_particle.anim.PushBack({ 30, 43, 23, 12 });
	bomb_particle.anim.loop = true;
	bomb_particle.anim.speed = 0.2f;

	// Coin
	coin_particle.anim.PushBack({ 4, 4, 12, 16 });
	coin_particle.anim.PushBack({ 27, 4, 12, 16 });
	coin_particle.anim.PushBack({ 50, 4, 12, 16 });
	coin_particle.anim.PushBack({ 4, 29, 12, 16 });
	coin_particle.anim.PushBack({ 27, 29, 12, 16 });
	coin_particle.anim.PushBack({ 50, 29, 12, 16 });
	coin_particle.anim.PushBack({ 4, 57, 12, 16 });
	coin_particle.anim.PushBack({ 27, 57, 12, 16 });
	coin_particle.anim.loop = true;
	coin_particle.anim.speed = 0.25f;
	coin_particle.speed.y = 0.09f + App->render->cam_speed;
	
	*/
	
	return true;
}

// Unload assets
bool j1Particles::CleanUp()
{
	/*
		App->textures->Unload(MARION_bullet_texture);
	MARION_bullet_texture = nullptr;
	App->textures->Unload(ASH_bullet_texture);
	ASH_bullet_texture = nullptr;
	App->textures->Unload(ASH_bomb);
	ASH_bomb = nullptr;

	App->textures->Unload(big_shot_texture);
	big_shot_texture = nullptr;
	App->textures->Unload(mid_shot_texture);
	mid_shot_texture = nullptr;
	App->textures->Unload(small_shot_texture);
	small_shot_texture = nullptr;

	App->textures->Unload(upgrade_texture);
	upgrade_texture = nullptr;
	
	LOG("Unloading particles");

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	*/

	return true;
}





// Update: draw background
bool j1Particles::Update()
{
	Particle* p = new Particle;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			switch (p->type)
			{
			case P_MARION_BULLET_P1:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BULLET_P2:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BULLET_P3_LEFT:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BULLET_P3_RIGHT:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BULLET_P4_LEFT:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BULLET_P4_RIGHT:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_STAR:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MARION_BOMB:
				App->render->Blit(MARION_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P1:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P2:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P3:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P3_DONUT:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P4:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BULLET_P4_DONUT:
				App->render->Blit(ASH_bullet_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_ASH_BOMB:
				App->render->Blit(ASH_bomb, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_UPGRADE:
				App->render->Blit(upgrade_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_BOMB:
				App->render->Blit(bomb_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_COIN:
				App->render->Blit(coin_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_SMALL_SHOT:
				App->render->Blit(small_shot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_BIG_SHOT:
				App->render->Blit(big_shot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case P_MID_SHOT:
				App->render->Blit(mid_shot_texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			}

			if (p->fx_played == false)
			{
				p->fx_played = true;
			}

			if (p->position.x < -PARTICLES_MARGIN || p->position.x >(App->render->camera.w + PARTICLES_MARGIN) || p->position.y < -PARTICLES_MARGIN || p->position.y >(App->render->camera.h + PARTICLES_MARGIN))
			{
				if (p->type != P_ASH_BOMB)
				{
					p->to_delete = true;
					delete p;
					active[i] = nullptr;
				}
			}
		}


	}

	return true;
}
Particle* j1Particles::AddParticle(const Particle& particle, particle_type type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, float x_phase, shot_type shotAt)
{
	Particle* temp_p = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->type = type;
			switch (collider_type)
			{
			case COLLIDER_PLAYER:
				p->collider = App->colliders->AddCollider({ (int)p->position.x, (int)p->position.y, p->anim.GetCurrentFrame().w, p->anim.GetCurrentFrame().h }, collider_type, this);
				if (x_phase == 360)
				{
					p->collider->to_delete = true;
					p->collider = nullptr;
				}
				if (shotAt == ANGLE)
				{
					vector.x = (x_phase < 90 || x_phase > 270) ? 1 : -1;
					vector.y = vector.x * tan(x_phase * PI / 180);
					vector.y = -vector.y;

					modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
					vector.x /= modul;
					vector.y /= modul;
					p->speed.x = vector.x * BIG_SHOT_SPEED;
					p->speed.y = vector.y * BIG_SHOT_SPEED * 3;
				}
				break;
				/*
				case COLLIDER_ENEMY_SHOT:
					p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
					switch (type)
					{
					case P_SMALL_SHOT:

					case P_BIG_SHOT:

					case P_MID_SHOT:
						switch (shotAt)
						{
						case PLAYER:
							Player* player;
							if (App->player1->IsEnabled() && App->player2->IsEnabled())
							{
								vector.x = (App->player1->position.x - (App->render->camera.x + x));
								vector.y = (App->player1->position.y - (App->render->camera.y + y));
								distance[0] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
								vector.x = (App->player2->position.x - (App->render->camera.x + x));
								vector.y = (App->player2->position.y - (App->render->camera.y + y));
								distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
								if (distance[0] < distance[1])
									player = App->player1;
								else
									player = App->player2;
							}
							else if (App->player1->IsEnabled() == false)
							{
								player = App->player2;
							}
							else
							{
								player = App->player1;
							}

							y_phase = 16 + ((y - player->position.y == 0) ? 0 : (((x - player->position.x) / (y - player->position.y)) * 12)); //Error when position y is the same
							if (player->position.x - x < 0)
							{
								if (x_phase < 0)
								{
									y_phase = -y_phase;
								}
							}
							else
							{
								if (x_phase > 0)
								{
									y_phase = -y_phase;
								}
							}
							vector.x = player->position.x + 10 + x_phase - x;
							vector.y = player->position.y - 16 + y_phase - y;
							modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
							vector.x /= modul;
							vector.y /= modul;
							p->speed.x = vector.x * SMALL_SHOT_SPEED;
							p->speed.y = vector.y * SMALL_SHOT_SPEED;
							break;
						case ANGLE:
							vector.x = (x_phase < 90 || x_phase > 270) ? 1 : -1;
							vector.y = vector.x * tan(x_phase * PI / 180);
							vector.y = -vector.y;

							modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
							vector.x /= modul;
							vector.y /= modul;
							p->speed.x = vector.x * BIG_SHOT_SPEED;
							p->speed.y = vector.y * BIG_SHOT_SPEED;
							break;
						}

						break;
					}
				}
				*/
				active[i] = p;
				temp_p = p;
				break;
			}
		}

		return temp_p;
	}
}


//j1Particles::OnCollision(Collider* c1, Collider* c2)
//{
//for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//{
//
//// Always destroy particles that collide
//if (active[i] != nullptr && active[i]->collider == c1 && (active[i]->type != P_MARION_BOMB && active[i]->type != P_ASH_BOMB) && !(c1->type == COLLIDER_NONE/*COLLIDER_ENEMY_SHOT*/ && c2->type == COLLIDER_NONE/*COLLIDER_POWER_UP*///) && !(c1->type == COLLIDER_NONE/*COLLIDER_ENEMY_SHOT*/ && c2->part != nullptr &&c2->part->type != P_ASH_BOMB))
//		{
//		//friendly shots with enemy. Animation here!
//
//		active[i]->to_delete = true;;
//		break;
//		}
//	}
//}


// -------------------------------------------------------------
// -------------------------------------------------------------

/*
Particle::Particle()
{
position.SetToZero();
speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), damage(p.damage), life(p.life)
{}

Particle::~Particle()
{
if (collider != nullptr)
{
collider->to_delete = true;
}
}

bool Particle::Update()
{
if (type == P_MARION_STAR)
{
Enemy* enemy = nullptr;
fPoint vector;
int distance[2];
distance[0] = 320;
for (int i = 0; i < MAX_ENEMIES; i++)
{
if (App->enemies->enemies[i] != nullptr && App->enemies->enemies[i]->collider != nullptr)
{
vector.x = App->enemies->enemies[i]->position.x - (position.x);
vector.y = App->enemies->enemies[i]->position.y - (position.y - App->render->camera.y);
distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
if (distance[1] < distance[0])
{
distance[0] = distance[1];
enemy = App->enemies->enemies[i];
}
}
}
if (enemy != nullptr)
{
vector.x = (enemy->position.x + (enemy->collider->rect.w/2)) - (position.x);
vector.y = (enemy->position.y + (enemy->collider->rect.h/2)) - (position.y - App->render->camera.y);

float modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
vector.x /= modul;
vector.y /= modul;
speed.x = vector.x * 3.5;
speed.y = vector.y * 3.5;
}
}

position.x += speed.x;
position.y += speed.y;

if (collider != nullptr)
{
collider->SetPos(position.x, position.y);
}

if (SDL_GetTicks() - born > life)
{
to_delete = true;
}

return !(to_delete);
}
*/