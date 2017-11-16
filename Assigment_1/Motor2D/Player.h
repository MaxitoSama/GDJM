#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "p2Path.h"
#include "j1Particle.h"

#define BULLET_SPEED 5
#define GRENADE_SPEED 1.3f
#define SHOTS_PER_BURST 1
#define SHOT_DELAY 0
#define GRAVITY 0;



class Player : public Entity
{
	enum LastDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UPRIGHT,
		UPLEFT,
		DOWNRIGHT,
		DOWNLEFT,
		DEATH
	};

public:

	Player(int x, int y);
	~Player();

	void Move(float dt);

	bool Awake(pugi::xml_node&);
	void Start();
	bool Update(float dt);
	bool CleanUp();
	void Jump_Method(float dt);
	void Slide_Method(float dt);
	int Acceleration_Method();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;


public:

	SDL_Texture*	graphics = nullptr;
	SDL_Texture*	textures = nullptr;

	Mix_Chunk*		jump_sound = NULL;

	Animation*		current_animation = nullptr;
	Animation		idle_right;
	Animation		idle_left;
	Animation		left;
	Animation		right;
	Animation		jump_right;
	Animation		jump_left;
	Animation		slide_right;
	Animation		slide_left;
	Animation		death;

	//Collider*		collider_feet;
	Collider*		collider_player;

	//int				speed;
	int				Pos_jump;
	int				velocity;
	int				Curr_map;
	uint			win_width;
	uint			win_height;
	uint			win_scale;
	uint			acceleration;
	uint			gravity;
	SDL_Rect		slide_rect;


	LastDirection	player_last_direction;
	//iPoint			position;

	bool			Jump = false;
	bool			fall = false;
	bool			dead = false;


private:

	uint		jump_height;
	uint		jump_vel;
	uint		accel_counter;
	uint		slide_counter;

};

#endif // _PLAYER_H_
