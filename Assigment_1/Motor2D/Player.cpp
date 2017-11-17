#include "Player.h"
#include "j1Window.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Player.h"


Player::Player(int x, int y) : Entity(x, y)
{
	LOG("Loading Player Sheet");

	//IDLE RIGHT----------------------------------------------------
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
		idle_right.speed = 30.0f;
	}

	//IDLE LEFT----------------------------------------------------
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
		idle_left.speed = 30.0f;
	}


	// MOVE RICHT----------------------------------------------------
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
		right.speed = 30.0f;
	}

	// MOVE LEFT----------------------------------------------------
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
		left.speed = 30.0f;
	}

	//JUMP_RIGHT----------------------------------------------------
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
		jump_right.speed = 15.0f;
	}

	//JUMP_LEFT----------------------------------------------------
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
		jump_left.speed = 15.0f;
	}

	//SLIDE RIGHT----------------------------------------------------
	{
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
		slide_right.speed = 30.0f;
	}


	//SLIDE LEFT----------------------------------------------------
	{
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
		slide_left.speed = 30.0f;
	}


	//Death------------------------------------------------------------
	{
		death.PushBack({ 76,2574,220,346 });
		death.PushBack({ 296,2574,220,346 });
		death.PushBack({ 513,2574,274,346 });
		death.PushBack({ 786,2574,314,346 });
		death.PushBack({ 1099,2574,332,346 });
		death.PushBack({ 1430,2574,340,346 });
		death.PushBack({ 1769,2574,349,346 });
		death.PushBack({ 2117,2574,349,346 });
		death.PushBack({ 2468,2574,349,346 });
		death.loop = false;
		death.speed = 30.0f;
	}

	

	LOG("Loading Player Collider");
	

	//Init Screen vars----------------------------------------------------
	win_width = App->win->screen_surface->w;
	win_height = App->win->screen_surface->h;
	win_scale = App->win->GetScale();


	animation = &idle_right;
	colliderXsize = 100;
	scale = 0.5f;
	colliderXsize = 120;
	velocity = 1000;
	gravity = 500;
	initial_pos = original_pos.x;
	jump_height= 300;
	jump_vel= 1000;
	accel_counter=10;
	slide_counter=0;
	Curr_map = 1;

	Jump = false;
	fall = false;
}


Player::~Player()
{
	LOG("Unloading player Sheet");
	App->tex->UnLoad(NormalSprite);

	LOG("Destroying Player Collider");
	if (collider_feet != nullptr)
		collider_feet->to_delete = true;
	if (collider_player != nullptr)
		collider_player->to_delete = true;
}

void Player::Start()
{
	LOG("Loading Player Sheet");

	NormalSprite = App->tex->Load("assets/character/character.png");
	//godmode = App->tex->Load("assets/character/god_mode.png");

	LOG("Loading Player Collider");
	collider = App->colliders->AddCollider({ (int)original_pos.x, (int)original_pos.y, 200 / 2, 332 / 2 }, COLLIDER_PLAYER, (j1Module*)App->entities);
	collider_feet = App->colliders->AddCollider({ ((int)original_pos.x + (263 / 4) - 54), (int)original_pos.y + (310 / 2) - 1, 64, 10 }, COLLIDER_FEET, (j1Module*)App->entities);

	//Init Screen vars----------------------------------------------------
	win_width = App->win->screen_surface->w;
	win_height = App->win->screen_surface->h;
	win_scale = App->win->GetScale();
	//GOD = false;
}

void Player::Move(float dt)
{
	SDL_Event e;

	//MOVE_LEFT----------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT  && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && !dead)
	{
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		{
			if (original_pos.x >= 0)
			{

				speed.x = -(velocity + Acceleration_Method())*dt;
				original_pos.x += speed.x;
				Acceleration_Method();
			}

			if (animation != &left && !Jump)
			{
				left.Reset();
				animation = &left;
				player_last_direction = LEFT;
			}
		}
		else
		{
			animation = &idle_left;
		}

	}

	//MOVE_RIGHT---------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT  && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && !dead)
	{
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE)
		{
			if (original_pos.x < 25600)
			{
				speed.x = (velocity + Acceleration_Method())*dt;
				original_pos.x += speed.x;
				Acceleration_Method();
			}


			if (animation != &right && !Jump)
			{
				right.Reset();
				animation = &right;
				player_last_direction = RIGHT;
			}
		}
		else
		{
			animation = &idle_right;
		}

	}

	//ACCELERATION RESET---------------------------------------
	/*if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP || App->input->GetKey(SDL_SCANCODE_A) == KEY_UP || App->input->GetKey(SDL_SCANCODE_S) == KEY_UP || dead)
	{

		acceleration = 1;
		accel_counter = 0;
		speed.x = 4;
	}*/

	//SLIDING_RIGHT--------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && !dead)
	{
		if (speed.x > 0)
		{
			Slide_Method(dt);
			original_pos.x += speed.x;
			if (animation != &slide_right && !Jump)
			{
				slide_right.Reset();
				animation = &slide_right;
				player_last_direction = RIGHT;
			}
		}

		else
		{
			animation = &idle_right;
		}
	}

	//SLIDING_LEFT----------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && !dead)
	{
		if (speed.x < 0 && original_pos.x >= 0)
		{
			Slide_Method(dt);
			original_pos.x += speed.x;
			if (animation != &slide_left && !Jump)
			{
				slide_left.Reset();
				animation = &slide_left;
				player_last_direction = LEFT;
			}
		}
		else
		{
			animation = &idle_left;
		}
	}

	//DEATH ANIMATION TEST
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT)
	{

		animation = &death;
		player_last_direction = DEATH;
	}

	//JUMP_ONPLACE----------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !fall && !dead)
	{
		App->audio->PlayFx(1);
		if (!Jump)
		{
			Pos_jump = original_pos.y - jump_height;
			gravity = 500;
			Jump = true;
		}

		if (player_last_direction == RIGHT)
		{
			if (animation != &jump_right)
			{
				jump_right.Reset();
				animation = &jump_right;
				player_last_direction = RIGHT;
			}
		}

		if (player_last_direction == LEFT)
		{
			if (animation != &jump_left)
			{
				jump_left.Reset();
				animation = &jump_left;
				player_last_direction = LEFT;
			}
		}
	}

	//JUMP_RIGHT------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !fall && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !dead)
	{
		if (!Jump)
		{
			Pos_jump = original_pos.y - jump_height;
			gravity = 500;
			Jump = true;
		}

		if (animation != &jump_right)
		{
			jump_right.Reset();
			animation = &jump_right;
			player_last_direction = RIGHT;
		}

	}
	//JUMP_LEFT-------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !fall && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !dead)
	{
		if (!Jump)
		{
			Pos_jump = original_pos.y - jump_height;
			Jump = true;
		}

		if (animation != &jump_left)
		{
			jump_left.Reset();
			animation = &jump_left;
			player_last_direction = LEFT;
		}

	}

	if (dead == true)
	{
		gravity = 0;
		animation = &death;
		if (death.Finished() == true)
		{
			gravity = 500;
			dead = false;
			original_pos.x = 60;
			original_pos.y = 215;
			App->render->camera.x = 0;
			App->render->camera.y = 0;
			death.Reset();
		}
	}

	/*if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
	{
		App->particles->bullet.speed.y = -01.0f;
		App->particles->AddParticle(App->particles->bullet, original_pos.x, original_pos.y, COLLIDER_FEET);
	}*/

	//Call Jump_Method-----------------------------------------
	Jump_Method(dt);

	//IDLE ANIMATIONS------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
	{
		switch (player_last_direction)
		{
		case Player::UP:
			animation = &idle_right;
			break;
		case Player::DOWN:
			animation = &idle_right;
			break;
		case Player::LEFT:
			animation = &idle_left;
			break;
		case Player::RIGHT:
			animation = &idle_right;
			break;
		default:
			break;
		}
	}

	//Player Colliders Position--------------------------------
	//collider->SetPos(original_pos.x, original_pos.y);
	
	if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		collider->rect = slide_rect = { (int)original_pos.x, (int)original_pos.y + 40, 200 / 2, 150 };
	}
	else
	{
		SDL_Rect idle_rect = { original_pos.x, original_pos.y, 200 / 2,332 / 2 };
		collider->rect = idle_rect;
	}

	position = original_pos;
	LOG("player position %f", original_pos.x);

}

void Player::Jump_Method(float dt)
{
	if (!Jump) {
		original_pos.y += gravity*dt;
	}

	if (Jump == true && original_pos.y != Pos_jump)
	{
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			original_pos.y -= jump_vel*dt;
		}

		if (original_pos.y <= Pos_jump || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			gravity = 500;
			Jump = false;
			fall = true;
		}
	}
}

//Acceleration Method
float Player::Acceleration_Method()
{
	float vel = 0;

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_IDLE || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		vel = 0;
	}
	else
	{
		vel = 500;
	}

	return vel;
}

void Player::Slide_Method(float dt)
{


	slide_counter += 1;
	if (slide_counter % 10 == 0 && speed.x >= 0)
	{
		speed.x -= 100 * dt;
	}
	if (slide_counter % 10 == 0 && speed.x <= 0)
	{
		speed.x += 100 * dt;
	}
}
