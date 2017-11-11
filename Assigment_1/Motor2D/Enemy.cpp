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

}

Enemy::~Enemy()
{
	//App->tex->UnLoad(b1);

	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites, float direction)
{
	Red_now = SDL_GetTicks() - Red_Start_time;

	if (collider != nullptr)
		collider->SetPos(position.x-120, position.y);

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
		
		App->render->Blit(sprites, position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()), direction,1.0f);
	
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
	if (collider->type == COLLIDER_ENEMY)
	{

	}
	if ((collider->type == COLLIDER_NONE || collider->type == COLLIDER_NONE) && die == false)
	{
		/*switch (collider->part->type)
		{
		case P_MARION_BULLET_P1:
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
		Draw(sprites,scale);
	}
}

void Enemy::DeadAnim()
{
	animation = nullptr;
}


void Enemy::Drop()
{

}