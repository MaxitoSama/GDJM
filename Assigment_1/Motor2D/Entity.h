#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "p2DynArray.h"
#include "p2animation.h"
#include "p2Log.h"
#include "SDL/include/SDL_timer.h"
#include "SDL_mixer\include\SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;
struct Collider;

class Entity
{
protected:
	Animation* animation = nullptr;
	//Animation anim_b1;

public:
	enum Explosions
	{
		//The diference between x1 and x2 is 
		//the animation is inverted, but remains the same.
		BIG1 = 1,
	};
	fPoint			position;
	fPoint			collider_pos;
	fPoint			original_pos;
	SDL_Texture*	sprites = nullptr;
	SDL_Texture*	NormalSprite = nullptr;
	SDL_Texture*	Shoot = nullptr;


	float			scale;
	fPoint			speed;
	int				colliderXsize;
	fPoint			initial_pos;
	bool			left;
	bool			right;
	bool			alive = true;
	bool			die = false;
	
	Collider*		collider = nullptr;
	Collider*		collider_feet = nullptr;
	Collider*		collider_head = nullptr;
	int				collision_distance_1;

	p2DynArray<iPoint>	Enemypath;
	uint				Timepath=0;
	uint				pathcounter = 0;
	bool				going = false;
	

public:
	
	Entity(int x, int y);
	virtual ~Entity();

	const Collider*		GetCollider() const;
	const Collider*		GetColliderFloor() const;
	const Collider*		GetColliderHead() const;

	virtual bool Awake(pugi::xml_node&);
	virtual void Move(float dt) {};
	virtual void ExtraAnim(SDL_Texture* texture) {};
	virtual void DeadAnim();
	virtual void Draw(SDL_Texture* sprites, float direction, int ColliderPosition);
	virtual void OnCollision(Collider* collider);

};

#endif // __ENEMY_H__