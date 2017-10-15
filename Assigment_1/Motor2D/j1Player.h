#ifndef __J1Player_H__
#define __J1Player_H__

#define BULLET_SPEED 5
#define GRENADE_SPEED 1.3f
#define SHOTS_PER_BURST 1
#define SHOT_DELAY 0
#define GRAVITY 0;

#include "j1Module.h"
#include "p2Animation.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PostUpdate();
	bool CleanUp();
	void Jump_Method();
	void Slide_Method();
	void Acceleration_Method();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;


public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;

	Mix_Chunk* jump_sound = NULL;
	

	SDL_Rect bridge;

	Animation* current_animation = nullptr;
	Animation idle_right;
	Animation idle_left;
	Animation left;
	Animation right;
	Animation left_back;
	Animation right_back;
	Animation die;
	Animation bullet_explosion;
	Animation Scythe_Right;
	Animation Scythe_Left;
	Animation jump_right;
	Animation jump_left;
	Animation slide_right;
	Animation slide_left;

	Collider* collider_feet;
	Collider* collider_player;

	int font_score = -1;
	int speed;
	int Pos_jump;
	int velocity;


	enum LastDirection { UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT };
	LastDirection player_last_direction;
	iPoint position;
	
	bool Jump = false;
	bool fall = false;
	bool dead=false;

	uint win_width;
	uint win_height;
	uint win_scale;
	uint acceleration;
	uint gravity;

private:

	uint jump_height;
	uint jump_vel;
	uint accel_counter;
	uint slide_counter;
};

#endif