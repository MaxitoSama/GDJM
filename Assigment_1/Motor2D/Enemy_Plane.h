#ifndef __BALLOON_H__
#define __BALLOON_H__

#include "Enemy.h"
#include "p2Path.h"
#include "j1Particle.h"

class Enemy_Plane : public Enemy
{
public:

	Enemy_Plane(int x, int y);
	~Enemy_Plane();

	void Move();
	void DeadAnim();
	void Drop();

public:

	Path path;
	Animation anim;
	Animation dead;

	char* shot_path;
	//particle_type shoot;
	Particle* big_shoot;
};

#endif // !__BALLOON_H__
