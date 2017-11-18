#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "Entity.h"
#include "p2Path.h"
#include "j1Particle.h"

class Enemy_Zombie : public Entity
{
public:

	Enemy_Zombie(int x, int y);
	~Enemy_Zombie();

	bool Awake(pugi::xml_node&);
	void Move(float dt);
	void DeadAnim();

public:

	Animation anim;
	Animation dead;
	Animation walking;

private:

	bool	goback = false;
	bool	go_x = false;
	float	idle_speed = 0;
	float	path_speed = 0;

};

#endif
