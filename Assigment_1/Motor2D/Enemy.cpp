#include "j1App.h"
#include "Enemy.h"
#include "j1Colliders.h"
#include "j1Particle.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "SDL/include/SDL_timer.h"
#include "j1Audio.h"

Enemy::Enemy(int x, int y, int wave, int id) : position(x, y), original_pos(x, y), wave(wave), id(id), collider_pos(0, 0)
{
	b1 = App->tex->Load("assets/enemies/explosions/big2.png");
	b2 = App->tex->Load("assets/enemies/explosions/big1.png");
	m1 = App->tex->Load("assets/enemies/explosions/medium1.png");
	m2 = App->tex->Load("assets/enemies/explosions/medium2.png");
	s1 = App->tex->Load("assets/enemies/explosions/small1.png");
	s2 = App->tex->Load("assets/enemies/explosions/small2.png");
	fm = App->tex->Load("assets/enemies/explosions/flying_machine.png");

	//Big1
	anim_b1.PushBack({ 12, 14, 106, 106 });
	anim_b1.PushBack({ 130, 13, 106, 106 });
	anim_b1.PushBack({ 253, 13, 106, 106 });
	anim_b1.PushBack({ 382, 16, 106, 106 });

	anim_b1.PushBack({ 9, 147, 106, 106 });
	anim_b1.PushBack({ 129, 145, 106, 106 });
	anim_b1.PushBack({ 251, 146, 106, 106 });
	anim_b1.PushBack({ 376, 147, 106, 106 });

	anim_b1.PushBack({ 14, 279, 106, 106 });
	anim_b1.PushBack({ 133, 279, 106, 106 });
	anim_b1.PushBack({ 258, 279, 106, 106 });
	anim_b1.PushBack({ 374, 279, 106, 106 });
	anim_b1.PushBack({ 0, 0, 0, 0 }); //last one should be always transparent
	anim_b1.speed = 0.5f;
	anim_b1.loop = false;

	//big2
	anim_b2.PushBack({ 6, 20, 106, 106 });
	anim_b2.PushBack({ 122, 21, 106, 106 });
	anim_b2.PushBack({ 256, 19, 106, 106 });
	anim_b2.PushBack({ 384, 22, 106, 106 });

	anim_b2.PushBack({ 6, 139, 106, 106 });
	anim_b2.PushBack({ 130, 138, 106, 106 });
	anim_b2.PushBack({ 260, 137, 106, 106 });
	anim_b2.PushBack({ 380, 140, 106, 106 });

	anim_b2.PushBack({ 5, 265, 106, 106 });
	anim_b2.PushBack({ 129, 266, 106, 106 });
	anim_b2.PushBack({ 257, 265, 106, 106 });
	anim_b2.PushBack({ 378, 265, 106, 106 });
	anim_b2.PushBack({ 0, 0, 0, 0 });
	anim_b2.speed = 0.5f;
	anim_b2.loop = false;

	//mid1
	anim_m1.PushBack({ 16, 20, 56, 68 });
	anim_m1.PushBack({ 88, 20, 56, 68 });
	anim_m1.PushBack({ 159, 20, 56, 68 });
	anim_m1.PushBack({ 235, 20, 56, 68 });
	anim_m1.PushBack({ 310, 20, 56, 68 });

	anim_m1.PushBack({ 21, 102, 56, 68 });
	anim_m1.PushBack({ 87, 103, 56, 68 });
	anim_m1.PushBack({ 158, 102, 56, 68 });
	anim_m1.PushBack({ 229, 105, 56, 68 });
	anim_m1.PushBack({ 307, 105, 56, 68 });

	anim_m1.PushBack({ 15, 201, 56, 68 });
	anim_m1.PushBack({ 88, 201, 56, 68 });
	anim_m1.PushBack({ 162, 201, 56, 68 });
	anim_m1.PushBack({ 231, 201, 56, 68 });
	anim_m1.PushBack({ 307, 201, 56, 68 });
	anim_m1.PushBack({ 0, 0, 0, 0 });
	anim_m1.speed = 0.5f;
	anim_m1.loop = false;

	//mid2
	anim_m2.PushBack({ 26, 16, 56, 68 });
	anim_m2.PushBack({ 98, 16, 56, 68 });
	anim_m2.PushBack({ 176, 16, 56, 68 });
	anim_m2.PushBack({ 250, 19, 56, 68 });
	anim_m2.PushBack({ 328, 17, 56, 68 });

	anim_m2.PushBack({ 30, 98, 56, 68 });
	anim_m2.PushBack({ 106, 97, 56, 68 });
	anim_m2.PushBack({ 180, 98, 56, 68 });
	anim_m2.PushBack({ 257, 97, 56, 68 });
	anim_m2.PushBack({ 333, 99, 56, 68 });

	anim_m2.PushBack({ 31, 193, 56, 68 });
	anim_m2.PushBack({ 110, 193, 56, 68 });
	anim_m2.PushBack({ 186, 193, 56, 68 });
	anim_m2.PushBack({ 259, 197, 56, 68 });
	anim_m2.PushBack({ 319, 197, 56, 68 });
	anim_m2.PushBack({ 0, 0, 0, 0 });
	anim_m2.speed = 0.5f;
	anim_m2.loop = false;

	//small1
	anim_s1.PushBack({ 12, 10, 48, 37 });
	anim_s1.PushBack({ 77, 11, 48, 37 });
	anim_s1.PushBack({ 137, 13, 48, 37 });
	anim_s1.PushBack({ 197, 12, 48, 37 });

	anim_s1.PushBack({ 12, 61, 48, 37 });
	anim_s1.PushBack({ 72, 62, 48, 37 });
	anim_s1.PushBack({ 136, 62, 48, 37 });
	anim_s1.PushBack({ 196, 62, 48, 37 });

	anim_s1.PushBack({ 12, 110, 48, 37 });
	anim_s1.PushBack({ 73, 111, 48, 37 });
	anim_s1.PushBack({ 134, 111, 48, 37 });
	anim_s1.PushBack({ 194, 111, 48, 37 });

	anim_s1.PushBack({ 12, 153, 48, 37 });
	anim_s1.PushBack({ 73, 153, 48, 37 });
	anim_s1.PushBack({ 134, 153, 48, 37 });
	anim_s1.PushBack({ 194, 153, 48, 37 });
	anim_s1.PushBack({ 0, 0, 0, 0 });
	anim_s1.speed = 1.0f;
	anim_s1.loop = false;

	//small2
	anim_s2.PushBack({ 13, 10, 48, 37 });
	anim_s2.PushBack({ 74, 11, 48, 37 });
	anim_s2.PushBack({ 135, 12, 48, 37 });
	anim_s2.PushBack({ 195, 13, 48, 37 });

	anim_s2.PushBack({ 12, 60, 48, 37 });
	anim_s2.PushBack({ 74, 61, 48, 37 });
	anim_s2.PushBack({ 137, 62, 48, 37 });
	anim_s2.PushBack({ 196, 62, 48, 37 });

	anim_s2.PushBack({ 13, 111, 48, 37 });
	anim_s2.PushBack({ 77, 111, 48, 37 });
	anim_s2.PushBack({ 136, 111, 48, 37 });
	anim_s2.PushBack({ 196, 111, 48, 37 });

	anim_s2.PushBack({ 13, 153, 48, 37 });
	anim_s2.PushBack({ 77, 153, 48, 37 });
	anim_s2.PushBack({ 136, 153, 48, 37 });
	anim_s2.PushBack({ 196, 153, 48, 37 });
	anim_s2.PushBack({ 0, 0, 0, 0 });
	anim_s2.speed = 1.0f;
	anim_s2.loop = false;

	//flying machine
	anim_fm.PushBack({ 35, 11, 128, 140 });
	anim_fm.PushBack({ 171, 11, 128, 140 });
	anim_fm.PushBack({ 310, 11, 128, 140 });
	anim_fm.PushBack({ 446, 11, 128, 140 });
	anim_fm.PushBack({ 591, 11, 128, 140 });
	anim_fm.PushBack({ 748, 11, 128, 140 });

	anim_fm.PushBack({ 35, 167, 128, 140 });
	anim_fm.PushBack({ 178, 167, 128, 140 });
	anim_fm.PushBack({ 310, 167, 128, 140 });
	anim_fm.PushBack({ 446, 167, 128, 140 });
	anim_fm.PushBack({ 589, 167, 128, 140 });
	anim_fm.PushBack({ 750, 167, 128, 140 });

	anim_fm.PushBack({ 34, 340, 128, 140 });
	anim_fm.PushBack({ 168, 340, 128, 140 });
	anim_fm.PushBack({ 309, 338, 128, 140 });
	anim_fm.PushBack({ 445, 338, 128, 140 });
	anim_fm.PushBack({ 591, 337, 128, 140 });
	anim_fm.PushBack({ 746, 339, 128, 140 });

	anim_fm.PushBack({ 35, 499, 128, 140 });
	anim_fm.PushBack({ 170, 499, 128, 140 });
	anim_fm.PushBack({ 308, 495, 128, 140 });
	anim_fm.PushBack({ 443, 493, 128, 140 });
	anim_fm.PushBack({ 590, 494, 128, 140 });
	anim_fm.PushBack({ 750, 489, 128, 140 });

	anim_fm.PushBack({ 36, 643, 128, 140 });
	anim_fm.PushBack({ 170, 641, 128, 140 });
	anim_fm.PushBack({ 312, 636, 128, 140 });
	anim_fm.PushBack({ 444, 636, 128, 140 });
	anim_fm.PushBack({ 588, 636, 128, 140 });
	anim_fm.PushBack({ 750, 636, 128, 140 });
	anim_fm.PushBack({ 0, 0, 0, 0 });
	anim_fm.speed = 0.75f;
	anim_fm.loop = false;
}

Enemy::~Enemy()
{
	App->tex->UnLoad(sprites);
	App->tex->UnLoad(NormalSprite);
	App->tex->UnLoad(RedSprite);
	App->tex->UnLoad(WhiteSprite);
	App->tex->UnLoad(b1);
	App->tex->UnLoad(b2);
	App->tex->UnLoad(m2);
	App->tex->UnLoad(m1);
	App->tex->UnLoad(s2);
	App->tex->UnLoad(s1);
	App->tex->UnLoad(fm);
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	Red_now = SDL_GetTicks() - Red_Start_time;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
	{
		sprites = NormalSprite;
		if (hit && WhiteSprite != nullptr && white_counter > 3)
		{
			sprites = WhiteSprite;
			hit = false;
			white_counter = 0;
		}
		else if (RedSprite != nullptr && lives <= (initial_hp / 5) && lives > 0 && Red_now >= Red_Total_time && Red_now <= (Red_Total_time + 50))
		{
			sprites = RedSprite;
		}
		else if (RedSprite != nullptr && lives <= (initial_hp / 5) && lives > 0 && Red_now >= (Red_Total_time + 150))
		{
			sprites = RedSprite;
			Red_Start_time = SDL_GetTicks();
		}
		
		App->render->Blit(sprites, position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()), -0.5f,1.0f);
	
		if (extra_anim && lives > 0)
			ExtraAnim(sprites);
		white_counter++;
	}
	/*if (lives <= 0 && die == false)
		die = explode();
	if (lives <= 0 && die)
		explode();*/
}

void Enemy::OnCollision(Collider* collider)
{
	if ((collider->type == COLLIDER_NONE || collider->type == COLLIDER_NONE) && die == false)
	{
		/*switch (collider->part->type)
		{
		case P_MARION_BULLET_P1:
			lives -= 1;
			break;
		case P_MARION_BULLET_P2:
			lives -= 2;
			break;
		case P_MARION_BOMB:
			lives -= 1;
			break;
		case P_ASH_BULLET_P1:
			lives -= 1;
			break;
		case P_ASH_BULLET_P2:
			lives -= 2;
			break;
		case P_ASH_BOMB:
			lives -= 1;
			break;
		default:
			lives -= 1;
			break;
		}*/
		hit = true;
		if (lives <= 0)
		{
			if (collider->type == COLLIDER_NONE)
				//App->player->points += points;
			

			Drop();
		}
	}
	else if (collider->type == COLLIDER_NONE)
	{
		Draw(sprites);
	}
}

void Enemy::DeadAnim()
{
	animation = nullptr;
}


void Enemy::Drop()
{

}