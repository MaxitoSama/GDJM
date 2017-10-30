#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "j1Module.h"
#include "p2Animation.h"
//#include "Globals.h"
#include "p2Point.h"
#include "j1Colliders.h"
#include "Enemy.h"
#include "j1Enemies.h"

#define MAX_ACTIVE_PARTICLES 200
#define SMALL_SHOT_SPEED 2.0
#define BIG_SHOT_SPEED 2.0
#define MAX_BULLETS 4
#define PARTICLES_MARGIN 50

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum particle_type
{
	P_MARION_BULLET_P1,
	P_MARION_BULLET_P2,
	P_MARION_BULLET_P3_LEFT,
	P_MARION_BULLET_P3_RIGHT,
	P_MARION_BULLET_P4_LEFT,
	P_MARION_BULLET_P4_RIGHT,
	P_MARION_BOMB,
	P_ASH_BULLET_P1,
	P_ASH_BULLET_P2,
	P_ASH_BULLET_P3,
	P_ASH_BULLET_P3_DONUT,
	P_ASH_BULLET_P4,
	P_ASH_BULLET_P4_DONUT,
	P_MARION_STAR,
	P_ASH_BOMB,
	P_UPGRADE,
	P_BOMB,
	P_COIN,
	P_SMALL_SHOT,
	P_MID_SHOT,
	P_BIG_SHOT
};

enum shot_type
{
	PLAYER,
	ANGLE
};

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	bool to_delete = false;
	bool fx_played = false;
	particle_type type;
	bool going_up = true;
	int damage = 1;
	int life = 100000000;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class j1Particles : public j1Module
{
public:
	j1Particles();
	~j1Particles();

	bool Start();
	bool Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	Particle* AddParticle(const Particle& particle, particle_type type, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, float x_phase = 0, shot_type shotAt = PLAYER);

public:

	SDL_Texture* MARION_bullet_texture = nullptr;

	SDL_Texture* ASH_bullet_texture = nullptr;
	SDL_Texture* ASH_bomb = nullptr;

	SDL_Texture* upgrade_texture = nullptr;
	SDL_Texture* bomb_texture = nullptr;
	SDL_Texture* coin_texture = nullptr;
	SDL_Texture* small_shot_texture = nullptr;
	SDL_Texture* mid_shot_texture = nullptr;
	SDL_Texture* big_shot_texture = nullptr;
	SDL_Texture* explosions_texture = nullptr;
	SDL_Texture* explosion_building1_texture = nullptr;
	SDL_Texture* explosion_torpedo_texture = nullptr;
	SDL_Texture* explosion_antiaircraft_texture = nullptr;
	SDL_Texture* explosion_pot_texture = nullptr;

	Particle* active[MAX_ACTIVE_PARTICLES];
	fPoint vector;
	float modul;
	float y_phase;
	int distance[2];

public:

	Particle MARION_bullet_p1_particle;
	Particle MARION_bullet_p2_particle;
	Particle MARION_bullet_p3_left_particle;
	Particle MARION_bullet_p3_right_particle;
	Particle MARION_bullet_p4_left_particle;
	Particle MARION_bullet_p4_right_particle;
	Particle MARION_star_particle;

	Particle ASH_bullet_p1_particle;
	Particle ASH_bullet_p2_particle;
	Particle ASH_bullet_p3_particle;
	Particle ASH_bullet_p3_donut_particle;
	Particle ASH_bullet_p4_particle;
	Particle ASH_bullet_p4_donut_particle;

	Particle upgrade_particle;
	Particle coin_particle;
	Particle bomb_particle;
	Particle small_shot_particle;
	Particle mid_shot_particle;
	Particle big_shot_particle;
	Particle explosions_particle;
	Particle exploison_building1_particle;
	Particle exploison_torpedo_particle;
	Particle exploison_antiaricraft_particle;
	Particle exploison_pot_particle;
};

#endif // __j1PARTICLES_H__
