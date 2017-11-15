#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "Enemy.h"
#include "p2Path.h"
#include "j1Particle.h"

class Enemy_Zombie : public Enemy
{
public:

	Enemy_Zombie(int x, int y);
	~Enemy_Zombie();

	void Move(float dt);
	void DeadAnim();

public:

	Animation anim;
	Animation dead;
	Animation walking;

	char* shot_path;
	//particle_type shoot;
	Particle* big_shoot;
};

#endif
