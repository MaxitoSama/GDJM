#ifndef __J1ENEMIES_H__
#define __J1ENEMIES_H__

#include "j1Module.h"

#define MAX_ENEMIES 100
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 320

enum ENEMY_TYPES
{
	NO_TYPE,
	ZOMBIE,
	PLANE
};

class Entity;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, wave, id;
};

class j1Entities : public j1Module
{
public:

	j1Entities();
	~j1Entities();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2, int distance);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int wave = 1, int id = 0);

public:

	bool draw_underlayed = false;
	Entity* entities[MAX_ENEMIES];
	bool boss_death = false;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];

};

#endif // __J1ENEMIES_H__