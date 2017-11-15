#include <math.h>
#include "p2Defs.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Colliders.h"
#include "j1Particle.h"
#include "j1Input.h"
#include "j1Player.h"

#include "SDL/include/SDL_timer.h"

//j1Particle::j1Particle()
//{
//	name.create("scene");
//
//	active = false;
//
//	// Explosion particle
//	explosion.anim.loop = false;
//	explosion.anim.speed = 0.3f;
//
//	//granade particle
//	grenade.display_dead_animation = true;
//	grenade.has_dead_collider = true;
//	grenade.anim.PushBack({ 1,315,16,16 });
//	grenade.anim.PushBack({ 18,315,16,16 });
//	grenade.anim.PushBack({ 35,315,16,16 });
//	grenade.anim.loop = true;
//	grenade.anim.speed = 0.05f;
//	grenade.life = 1000;
//	grenade.speed.y = -GRENADE_SPEED;
//
//	grenade.dead_animation.PushBack({ 1,332,32,32 });
//	grenade.dead_animation.PushBack({ 34,332,32,32 });
//	grenade.dead_animation.PushBack({ 67,332,32,32 });
//	grenade.dead_animation.PushBack({ 100,332,32,32 });
//	//grenade.dead_animation.loop = false;
//	grenade.dead_animation.speed = 0.1f;
//	grenade.dead_animation_life = 20;
//	grenade.type = Particle::PLAYER_GRANADE;
//
//	//enemy granade particle
//	enemy_grenade.display_dead_animation = true;
//	enemy_grenade.has_dead_collider = true;
//	enemy_grenade.anim.PushBack({ 1,315,16,16 });
//	enemy_grenade.anim.PushBack({ 18,315,16,16 });
//	enemy_grenade.anim.PushBack({ 35,315,16,16 });
//	enemy_grenade.anim.loop = true;
//	enemy_grenade.anim.speed = 0.05f;
//	enemy_grenade.life = 1300;
//
//	enemy_grenade.dead_animation.PushBack({ 1,332,32,32 });
//	enemy_grenade.dead_animation.PushBack({ 34,332,32,32 });
//	enemy_grenade.dead_animation.PushBack({ 67,332,32,32 });
//	enemy_grenade.dead_animation.PushBack({ 100,332,32,32 });
//	//enemy_grenade.dead_animation.loop = false;
//	enemy_grenade.dead_animation.speed = 0.1f;
//	enemy_grenade.dead_animation_life = 20;
//
//	//bullets particle
//	bullet.display_dead_animation = true;
//	bullet.anim.PushBack({ 7,304,100,100 });
//	bullet.anim.loop = true;
//	bullet.anim.speed = 0.1f;
//	bullet.life = 350;
//
//	bullet.dead_animation.PushBack({ 18,298,16,16 });
//	bullet.dead_animation.PushBack({ 35,298,16,16 });
//	bullet.dead_animation.PushBack({ 52,298,16,16 });
//	bullet.dead_animation.PushBack({ 69,298,16,16 });
//	bullet.dead_animation.PushBack({ 86,298,16,16 });
//	bullet.dead_animation.PushBack({ 103,298,16,16 });
//	bullet.dead_animation.PushBack({ 120,298,16,16 });
//	bullet.dead_animation.PushBack({ 137,298,16,16 });
//	bullet.dead_animation.speed = 0.4f;
//	bullet.dead_animation_life = 15;
//
//	//Enemy bullet
//
//	enemy_bullet.display_dead_animation = true;
//	enemy_bullet.anim.PushBack({ 7,304,4,4 });
//	enemy_bullet.anim.loop = true;
//	enemy_bullet.anim.speed = 0.1f;
//	enemy_bullet.life = 1450;
//
//	enemy_bullet.dead_animation.PushBack({ 18,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 35,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 52,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 69,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 86,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 103,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 120,298,16,16 });
//	enemy_bullet.dead_animation.PushBack({ 137,298,16,16 });
//	enemy_bullet.dead_animation.speed = 0.4f;
//	enemy_bullet.dead_animation_life = 15;
//};
//
//
//
//j1Particle::~j1Particle()
//{}
//
//// Load assets
//bool j1Particle::Start()
//{
//	LOG("Loading particles");
//
//	graphics = App->tex->Load("assets/PlaceHolder_Sprites.png");
//	bullets = App->tex->Load("assets/Shot.png");
//	//music = App->audio->LoadFx("assets/Commando_12_Player_Shot.wav");
//
//	return true;
//}
//
//// Unload assets
//bool j1Particle::CleanUp()
//{
//	LOG("Unloading particles");
//	App->tex->UnLoad(graphics);
//	App->tex->UnLoad(bullets);
//
//	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//	{
//		if (activePart[i] != nullptr)
//		{
//			delete activePart[i];
//			activePart[i] = nullptr;
//		}
//	}
//
//	return true;
//}
//
//// Update: draw background
//bool j1Particle::Update(float dt)
//{
//	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//	{
//		Particle* p = activePart[i];
//
//		if (p == nullptr)
//			continue;
//
//		if (p->Update() == false)  // La idea es que si la particula ha de mostrar una animacio al "morir", ha d'aguantar una mica més  -pol
//		{
//			eliminateParticle(p, i);
//		}
//		else if (SDL_GetTicks() >= p->born)
//		{
//			App->render->Blit(bullets, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
//			if (p->fx_played == false)
//			{
//				p->fx_played = true;
//				// Play particle fx here
//				Mix_PlayChannel(0, music, 0);
//			}
//		}
//	}
//
//	return true;
//}
//
//void j1Particle::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
//{
//	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//	{
//		if (activePart[i] == nullptr)
//		{
//			Particle* p = new Particle(particle);
//			p->born = SDL_GetTicks() + delay;
//			p->position.x = x;
//			p->position.y = y;
//			if (collider_type != COLLIDER_NONE)
//				p->collider = App->colliders->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
//			activePart[i] = p;
//			break;
//		}
//	}
//}
//
//void j1Particle::OnCollision(Collider* c1, Collider* c2)
//{
//	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//	{
//		// Always destroy particles that collide
//		if (activePart[i] != nullptr && activePart[i]->collider == c1)
//		{
//			//delete active[i];                  //No ho descomenteu -pol
//			//active[i] = nullptr;
//			eliminateParticle(activePart[i], i);
//			//break;
//		}
//	}
//
//}
//
//void j1Particle::eliminateParticle(Particle* p, int i) {
//	if (p->display_dead_animation) {
//		if (p->alive) {
//			if (p->has_dead_collider) {
//				if (p->type != Particle::PLAYER_GRANADE)
//					p->dead_collider = App->colliders->AddCollider({ -80,0,24,24 }, COLLIDER_NONE, this);
//				else
//					p->dead_collider = App->colliders->AddCollider({ -80,0,24,24 }, COLLIDER_NONE, this);
//			}
//		}
//		App->render->Blit(graphics, p->position.x - 8, p->position.y - 8, &p->dead_animation.GetCurrentFrame(), 0.75f);
//		if (p->dead_animation_current_life < p->dead_animation_life) {
//			p->alive = false;
//			p->dead_animation_current_life++;
//			//if (p->collider != nullptr)
//			//p->collider->to_delete = true;
//			if (p->dead_collider != nullptr)
//				p->dead_collider->SetPos(p->position.x - 3, p->position.y - 3);
//		}
//		else {
//			App->colliders->EraseCollider(p->dead_collider);
//			if (p->dead_collider != nullptr)
//				p->dead_collider->to_delete = true;
//			delete p;
//			activePart[i] = nullptr;
//
//		}
//	}
//	else {
//		delete p;
//		activePart[i] = nullptr;
//	}
//}
//
//// -------------------------------------------------------------
//// -------------------------------------------------------------
//
//Particle::Particle()
//{
//	position.SetToZero();
//	speed.SetToZero();
//}
//
//Particle::Particle(const Particle& p) :
//	anim(p.anim), position(p.position), speed(p.speed),
//	fx(p.fx), born(p.born), life(p.life)
//{
//	//aixo de sota tambe ho he afegit jo al codi original del ric -pol
//	display_dead_animation = p.display_dead_animation;
//	dead_animation = p.dead_animation;
//	dead_animation_life = p.dead_animation_life;
//	dead_collider = p.dead_collider;
//	has_dead_collider = p.has_dead_collider;
//	type = p.type;
//}
//
//Particle::~Particle()
//{
//	if (collider != nullptr)
//		App->colliders->EraseCollider(collider);
//}
//
//bool Particle::Update()
//{
//	bool ret = true;
//
//	if (life > 0)
//	{
//		if ((SDL_GetTicks() - born) > life) {
//			ret = false;
//		}
//	}
//	else
//	{
//		if (anim.Finished())
//			ret = false;
//	}
//
//	if (alive) {
//		position.x += speed.x;
//		position.y += speed.y;
//	}
//
//	if (collider != nullptr)
//		collider->SetPos(position.x, position.y);
//
//	return ret;
//}