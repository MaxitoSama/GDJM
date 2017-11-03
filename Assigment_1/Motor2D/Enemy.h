#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "p2animation.h"
#include "SDL/include/SDL_timer.h"

struct SDL_Texture;
struct Collider;

class Enemy
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

	//Explosions textures
	SDL_Texture* b1;
	SDL_Texture* b2;
	SDL_Texture* m1;
	SDL_Texture* m2;
	SDL_Texture* s1;
	SDL_Texture* s2;
	SDL_Texture* fm;

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

	int lives; //Hit points
	int initial_hp; //To calculate when to turn red
	bool hit; //When to turn white
	bool extra_anim = false; //Something moving over basic animation?
	bool die = false; //enemy is dead if it's true.
	bool lower_level = false; //Is the enemy behing the overlayed map?
	Explosions explosion_type;

	int wave;
	int id = -1; //Id of an enemy inside a wave
	int points = 0; //Points that give to the player
	Collider* collider = nullptr;
	int white_counter;

public:
	Enemy(int x, int y, int wave = 1, int id = 0);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void ExtraAnim(SDL_Texture* texture) {};
	//virtual void ExtraAnim2(SDL_Texture* texture) {};
	//virtual void ExtraAnim3(SDL_Texture* texture) {};
	virtual void DeadAnim();
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual void Drop();
};

#endif // __ENEMY_H__