#include "j1App.h"
#include "Entity.h"
#include "j1Entities.h"
#include "j1Colliders.h"
#include "j1Particle.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "Player.h"
#include "SDL/include/SDL_timer.h"
#include "j1Audio.h"

Entity::Entity(int x, int y) : position(x, y), original_pos(x, y), collider_pos(0, 0)
{

}

bool Entity::Awake(pugi::xml_node& enemy)
{
	Awake(enemy);

	return true;
}

Entity::~Entity()
{
	//App->tex->UnLoad(b1);

	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Entity::GetCollider() const
{
	return collider;
}
const Collider* Entity::GetColliderFloor() const 
{
	return collider_feet;
}
const Collider* Entity::GetColliderHead() const
{
	return collider_head;
}

void Entity::Draw(SDL_Texture* sprites, float direction, int ColliderPosition)
{
	//Red_now = SDL_GetTicks() - Red_Start_time;

	if (collider != nullptr)
	{
		
		if (collider->type == COLLIDER_PLAYER && App->entities->player->slide)
		{
			collider->SetPos((int)position.x, (int)position.y+40);
		}
		else
		{
			collider->SetPos((int)position.x, (int)position.y);
		}
	}

	if (collider_feet != nullptr)
	{
		collider_feet->SetPos((position.x + (263 / 4) - 54), position.y + (310 / 2) - 1);
	}

	if (collider_head != nullptr)
	{
		collider_head->SetPos(position.x + 30, position.y-3);
	}
		

	if (animation != nullptr)
	{
		sprites = NormalSprite;
		
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()), direction, 1.0f);
		
	}
}

void Entity::OnCollision(Collider* collider)
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

void Entity::DeadAnim()
{

}