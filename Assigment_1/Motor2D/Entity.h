#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "p2DynArray.h"
#include "p2animation.h"
#include "SDL/include/SDL_timer.h"

struct SDL_Texture;
struct Collider;

class Entity
{
protected:
	Animation* animation = nullptr;
	Animation anim_b1;
	Animation anim_b2;
	Animation anim_m1;
	Animation anim_m2;
	Animation anim_s1;
	Animation anim_s2;
	Animation anim_fm;

public:
	enum Explosions
	{
		//The diference between x1 and x2 is 
		//the animation is inverted, but remains the same.
		BIG1 = 1,
		BIG2,
		MID1,
		MID2,
		SMALL1,
		SMALL2,
		FLYINGMACHINE
	};
	fPoint position;
	fPoint collider_pos;
	fPoint original_pos;
	SDL_Texture* sprites = nullptr; //Using texture
	SDL_Texture* NormalSprite = nullptr;
	SDL_Texture* RedSprite = nullptr;
	SDL_Texture* WhiteSprite = nullptr;
	SDL_Texture* Shoot = nullptr;

	//Time between red ticks
	Uint32 Red_now;
	Uint32 Red_Start_time;
	Uint32 Red_Total_time = (Uint32)(2.0f * 0.5f * 700.0f);
	//Time between shots
	Uint32 Shot_now;
	Uint32 Shot_Start_time;
	Uint32 Shot_Total_time;
	Uint32 Shot_Total_time1;
	Uint32 Shot_Total_time2;
	Uint32 Shot_Total_time3;

	
	float scale;
	fPoint speed;
	int colliderXsize;
	int initial_pos;
	bool left;
	bool right;
	
	Collider* collider = nullptr;
	int collision_distance_1;
	

public:
	
	Entity(int x, int y);
	virtual ~Entity();

	const Collider* GetCollider() const;

	p2DynArray<iPoint>	Enemypath;
	uint				pathcounter = 0;
	bool				going = false;

	virtual void Move(float dt) {};
	virtual void ExtraAnim(SDL_Texture* texture) {};
	//virtual void ExtraAnim2(SDL_Texture* texture) {};
	//virtual void ExtraAnim3(SDL_Texture* texture) {};
	virtual void DeadAnim();
	virtual void Draw(SDL_Texture* sprites, float direction, int ColliderPosition);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__