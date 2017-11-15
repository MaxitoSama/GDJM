#include "j1App.h"
#include "Enemy.h"
#include "j1Colliders.h"
#include "j1Particle.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "SDL/include/SDL_timer.h"
#include "j1Audio.h"

Enemy::Enemy(int x, int y) : position(x, y), original_pos(x, y), collider_pos(0, 0)
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

void Enemy::Draw(SDL_Texture* sprites, float direction, int ColliderPosition)
{
	Red_now = SDL_GetTicks() - Red_Start_time;

	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y);
	}
		

	if (animation != nullptr)
	{
		sprites = NormalSprite;
		
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()), direction, 1.0f);
		
	}
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_ENEMY)
	{

	}
	if ((collider->type == COLLIDER_NONE || collider->type == COLLIDER_NONE) )
	{
		
	}
	else if (collider->type == COLLIDER_NONE)
	{
		Draw(sprites,scale,colliderXsize);
	}
}

void Enemy::DeadAnim()
{
	animation = nullptr;
}