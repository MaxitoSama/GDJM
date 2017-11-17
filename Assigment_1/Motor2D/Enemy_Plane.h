#ifndef __PLANE_H__
#define __PLANE_H__

#include "Entity.h"
#include "p2Path.h"
#include "j1Particle.h"

class Enemy_Plane : public Entity
{
public:

	Enemy_Plane(int x, int y);
	~Enemy_Plane();

	void Move(float dt);
	void DeadAnim();


public:

	Animation anim;
	Animation dead;
	Animation moving;

private:

	bool goback = false;
	bool goback_x = false;
	bool goback_y = false;
	bool go_x = false;
	bool go_y = false;

};

#endif // !__BALLOON_H__
