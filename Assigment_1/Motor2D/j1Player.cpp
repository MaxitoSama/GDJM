#include <iostream>
#include <math.h>
#include "p2Defs.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Colliders.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Scene2.h"

using namespace std;

j1Player::j1Player():j1Module()
{
	name.create("player");
	graphics = NULL;
	current_animation = NULL;

	//idle animation Right
	{
		idle_right.PushBack({ 64,111,176,331 });
		idle_right.PushBack({ 310,111,176,331 });
		idle_right.PushBack({ 575,111,176,331 });
		idle_right.PushBack({ 845,111,176,331 });
		idle_right.PushBack({ 1138,111,176,331 });
		idle_right.PushBack({ 1450,111,176,331 });
		idle_right.PushBack({ 1735,111,176,331 });
		idle_right.PushBack({ 2019,111,176,331 });
		idle_right.PushBack({ 2284,111,176,331 });
		idle_right.PushBack({ 2559,111,176,331 });

		idle_right.loop = true;
		idle_right.speed = 0.5f;
	}

	//idle animation Left
	{
		idle_left.PushBack({ 64,1159,176,329 });
		idle_left.PushBack({ 311,1159,176,329 });
		idle_left.PushBack({ 577,1159,176,329 });
		idle_left.PushBack({ 848,1159,176,329 });
		idle_left.PushBack({ 1142,1159,176,329 });
		idle_left.PushBack({ 1455,1159,176,329 });
		idle_left.PushBack({ 1739,1159,176,329 });
		idle_left.PushBack({ 2022,1159,176,329 });
		idle_left.PushBack({ 2286,1159,176,329 });
		idle_left.PushBack({ 2560,1159,176,329 });

		idle_left.loop = true;
		//idle_left.speed = 0.001f;
		idle_left.speed = 0.5f;
	}

	
	// Move Right
	{
		right.PushBack({ 64,472,263,332 });
		right.PushBack({ 327,472,263,332 });
		right.PushBack({ 590,472,263,332 });
		right.PushBack({ 853,472,263,332 });
		right.PushBack({ 1137,472,263,332 });
		right.PushBack({ 1449,472,263,332 });
		right.PushBack({ 1734,472,263,332 });
		right.PushBack({ 2019,472,263,332 });
		right.PushBack({ 2286,472,263,332 });
		right.PushBack({ 2560,472,263,332 });

		right.loop = true;
		right.speed = 0.5f;
	}

	//Move Right back
	right_back.PushBack({ 0,0,50,50 });

	right_back.loop = true;
	right_back.speed = 0.5f;

	// Move Left
	{
	left.PushBack({ 2611,813,283,341 });
	left.PushBack({ 2328,813,283,341 });
	left.PushBack({ 2045,813,283,341 });
	left.PushBack({ 1762,813,283,341 });
	left.PushBack({ 1479,813,283,341 });
	left.PushBack({ 1196,813,283,341 });
	left.PushBack({ 913,813,283,341 });
	left.PushBack({ 630,813,283,341 });
	left.PushBack({ 347,813,283,341 });
	left.PushBack({ 64,813,283,341 });

	left.loop = true;
	left.speed = 0.5;
	}

	//Move Left Back
	left_back.PushBack({ 0,0,50,50 });

	left_back.loop = true;
	left_back.speed = 0.5f;

	//DIE
	die.PushBack({ 331,190,29,26 });
	die.PushBack({ 361,190,29,26 });
	die.PushBack({ 391,190,29,26 });
	die.loop =true;
	die.speed = 0.5f;

	//JUMP_RIGHT
	{
		jump_right.PushBack({ 64,471,263,332 });
		jump_right.PushBack({ 327,471,263,332 });
		jump_right.PushBack({ 590,471,263,332 });
		jump_right.PushBack({ 853,471,263,332 });
		jump_right.PushBack({ 1137,471,263,332 });
		jump_right.PushBack({ 1449,471,263,332 });
		jump_right.PushBack({ 1734,471,263,332 });
		jump_right.PushBack({ 2019,471,263,332 });
		jump_right.PushBack({ 2286,471,263,332 });
		jump_right.PushBack({ 2560,471,263,332 });

		jump_right.loop = false;
		jump_right.speed = 0.05f;
	}

	//JUMP_LEFT
	{
		jump_left.PushBack({ 64,2200,263,332 });
		jump_left.PushBack({ 327,2200,263,332 });
		jump_left.PushBack({ 590,2200,263,332 });
		jump_left.PushBack({ 853,2200,263,332 });
		jump_left.PushBack({ 1137,2200,263,332 });
		jump_left.PushBack({ 1449,2200,263,332 });
		jump_left.PushBack({ 1734,2200,263,332 });
		jump_left.PushBack({ 2019,2200,263,332 });
		jump_left.PushBack({ 2286,2200,263,332 });
		jump_left.PushBack({ 2560,2200,263,332 });

		jump_left.loop = false;
		jump_left.speed = 0.5f;
	}

	//Sliding_right
	slide_right.PushBack({ 65,1521,283,320 });
	slide_right.PushBack({ 347,1521,283,320 });
	slide_right.PushBack({ 632,1521,283,320 });
	slide_right.PushBack({ 913,1521,283,320 });
	slide_right.PushBack({ 1197,1521,283,320 });
	slide_right.PushBack({ 1480,1521,283,320 });
	slide_right.PushBack({ 1763,1521,283,320 });
	slide_right.PushBack({ 2045,1521,283,320 });
	slide_right.PushBack({ 2328,1521,283,320 });
	slide_right.PushBack({ 2610,1521,283,320 });

	slide_right.loop = true;
	slide_right.speed = 0.5f;

	//Sliding_left
	
		slide_left.PushBack({ 65,1840,283,320 });
	slide_left.PushBack({ 347,1840,283,320 });
	slide_left.PushBack({ 632,1840,283,320 });
	slide_left.PushBack({ 913,1840,283,320 });
	slide_left.PushBack({ 1197,1840,283,320 });
	slide_left.PushBack({ 1480,1840,283,320 });
	slide_left.PushBack({ 1763,1840,283,320 });
	slide_left.PushBack({ 2045,1840,283,320 });
	slide_left.PushBack({ 2328,1840,283,320 });
	slide_left.PushBack({ 2610,1840,283,320 });

	slide_left.loop = true;
	slide_left.speed = 0.5f;
	

}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Init Player config");

	//Init position var
	position.x= config.child("position").attribute("pos_x").as_uint(10);
	position.y= config.child("position").attribute("pos_y").as_uint(10);

	//Init Velocity var
	gravity = config.child("gravity").attribute("value").as_uint(10);
	acceleration = config.child("acceleration").attribute("value").as_uint(0);
	accel_counter = config.child("accel_counter").attribute("value").as_uint(0);
	velocity = config.child("velocity").attribute("value").as_uint(1);
	slide_counter = config.child("slide_counter").attribute("value").as_uint(0);

	//Jump vars
	jump_height = config.child("jump").attribute("jump_height").as_uint(300);
	jump_vel = config.child("jump").attribute("jump_vel").as_uint(10);
	fall = config.child("jump_bool").attribute("value").as_bool(false);
	Jump = config.child("fall_bool").attribute("value").as_bool(false);

	bool ret = true;

	return ret;
}
// Load assets
bool j1Player::Start()
{
	LOG("Loading Player Sheet");

	graphics = App->tex->Load("assets/character/character.png");

	LOG("Loading Player Collider");
	collider_player = App->colliders->AddCollider({ position.x, position.y, 200/2, 332/2 }, COLLIDER_PLAYER, this);
	collider_feet = App->colliders->AddCollider({ (position.x+(263/4)-54), position.y+ (310 / 2), 64, 10 }, COLLIDER_FEET, this);

	//Init Screen vars
	win_width = App->win->screen_surface->w;
	win_height = App->win->screen_surface->h;
	win_scale = App->win->GetScale();

	return true;
}

// Unload assets
bool j1Player::CleanUp()
{
	LOG("Unloading player Sheet");
	App->tex->UnLoad(graphics);

	LOG("Destroying Player Collider");
	if (collider_feet != nullptr)
		collider_feet->to_delete = true;
	if (collider_player != nullptr)
		collider_player->to_delete = true;

	return true;
}
// Update: draw background
bool j1Player::PostUpdate()
{
	SDL_Event e;
	
	//MOVE_LEFT----------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && !dead)
	{
		if (position.x >= 2)
		{
			speed = -(velocity + (int)acceleration);
			position.x += speed;
			Acceleration_Method();
		}

		if (current_animation != &left && !Jump)
		{
			left.Reset();
			current_animation = &left;
			player_last_direction = LEFT;
		}

	}

	//MOVE_RIGHT---------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && !dead)
	{
		if(position.x < 25600) //800 number of tiles and 32 the pixels per tiles there is.
		{
			speed = (velocity + acceleration);
			position.x += speed;
			Acceleration_Method();
		}


		if (current_animation != &right && !Jump)
		{
			right.Reset();
			current_animation = &right;
			player_last_direction = RIGHT;
		}
	}
	
	//ACCELERATION RESET---------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP || App->input->GetKey(SDL_SCANCODE_A) == KEY_UP || App->input->GetKey(SDL_SCANCODE_S) == KEY_UP || dead)
	{

		acceleration = 1; //+ max speed
		accel_counter = 0; //times added acceleration
		speed = 4; //ammount of speed
	}

	//SLIDING_RIGHT--------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && !dead)
	{
		if (speed > 0)
		{
			Slide_Method();
			position.x += speed;
			if (current_animation != &slide_right && !Jump)
			{
				slide_right.Reset();
				current_animation = &slide_right;
				player_last_direction = RIGHT;
			}
		}

		else
		{
			current_animation = &idle_right;
		}		
	}

	//SLIDING_LEFT----------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && !dead)
	{
		if (speed < 0)
		{
			Slide_Method();
			position.x += speed;
			if (current_animation != &slide_left && !Jump)
			{
				slide_left.Reset();
				current_animation = &slide_left;
				player_last_direction = LEFT;
			}
		}

		else
		{
			current_animation = &idle_left;
		}
	}
	//JUMP_ONPLACE----------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !fall && !dead)
	{
		App->audio->PlayFx(1);
		if (!Jump)
		{
           	Pos_jump = position.y - jump_height;
			gravity = 10;
			Jump = true;
		}
		
		if (player_last_direction == RIGHT)
		{
			if (current_animation != &jump_right)
			{
				jump_right.Reset();
				current_animation = &jump_right;
				player_last_direction = RIGHT;
			}
		}
		
		if (player_last_direction == LEFT)
		{
			if (current_animation != &jump_left)
			{
				jump_left.Reset();
				current_animation = &jump_left;
				player_last_direction = LEFT;
			}
		}
	}

	//JUMP_RIGHT------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !fall && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !dead)
	{
		if (!Jump)
		{
			Pos_jump = position.y - jump_height;
			gravity = 10;
			Jump = true;
		}

		if (current_animation != &jump_right)
		{
			jump_right.Reset();
			current_animation = &jump_right;
			player_last_direction = RIGHT;
		}
		
	}
	//JUMP_LEFT-------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !fall && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !dead)
	{
		if (!Jump)
		{
			Pos_jump = position.y - jump_height;
			Jump = true;
		}

		if (current_animation != &jump_left)
		{
			jump_left.Reset();
			current_animation = &jump_left;
			player_last_direction = LEFT;
		}

	}
	
	//Call Jump_Method-----------------------------------------
	Jump_Method();

	//IDLE ANIMATIONS------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
	{
		switch (player_last_direction)
		{
		case j1Player::UP:
			current_animation = &idle_right;
			break;
		case j1Player::DOWN:
			current_animation = &idle_right;
			break;
		case j1Player::LEFT:
			current_animation = &idle_left;
			break;
		case j1Player::RIGHT:
			current_animation = &idle_right;
			break;
		default:
			break;
		}
	}

	//Player Colliders Position--------------------------------
	collider_player->SetPos(position.x,position.y);
	collider_feet->SetPos((position.x + (263 / 4) - 54), position.y + (310 / 2));

	// Draw everything ----------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()),0.5f);

	return true;
}

// Load / Save
bool j1Player::Load(pugi::xml_node& data)
{
	int map = data.child("player").attribute("Map").as_int();
	int x = data.child("player").attribute("x").as_int();
	int y = data.child("player").attribute("y").as_int();
	
	if (Curr_map != map)
	{
		if (map == 1)
		{
			App->scene2->Change_to_Scene_1(x,y);
		}
		if (map == 2)
		{
			App->scene->Change_to_Scene_2(x,y);
		}
	}

	else
	{
		position.x = data.child("player").attribute("x").as_int();
		position.y = data.child("player").attribute("y").as_int();
	}
	
	

	return true;

}
bool j1Player::Save(pugi::xml_node& data) const 
{
	pugi::xml_node player = data.append_child("player");

	player.append_attribute("x") = position.x;
	player.append_attribute("y") = position.y;
	player.append_attribute("Map") = Curr_map;

	return true;
}

void j1Player::Jump_Method()
{
	if (!Jump) {
		position.y += gravity;
	}

	if (Jump == true && position.y != Pos_jump )
	{
		if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
 			position.y -= jump_vel;
		}
		
		if (position.y <= Pos_jump || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			gravity = 10;
			Jump = false;
			fall = true;
		}
	}
}

//Acceleration Method
void j1Player::Acceleration_Method()
{
	accel_counter += 1;

	if (accel_counter % 10 == 0 && accel_counter <= 200)
	{
		acceleration += 1;
	}
}

void j1Player::Slide_Method()
{
	slide_counter += 1;

	if (slide_counter % 10 == 0 && speed>=0)
	{
		speed -= 2;
	}
	if (slide_counter % 10 == 0 && speed <= 0)
	{
		speed += 5;
	}
}

