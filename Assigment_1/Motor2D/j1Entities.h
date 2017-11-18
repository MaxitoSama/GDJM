#ifndef __J1ENEMIES_H__
#define __J1ENEMIES_H__

#include "j1Module.h"

#define MAX_ENEMIES 100
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 320

class Entity;
class Player;
enum ENEMY_TYPES
{
	NO_TYPE,
	PLAYER,
	ZOMBIE,
	PLANE
};

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

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2, float distance);
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int wave = 1, int id = 0);
public:

	bool draw_underlayed = false;
	Entity* entities[MAX_ENEMIES];
	Player* player;
	pugi::xml_node entity_config;
	pugi::xml_document config_file;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:
	EnemyInfo queue[MAX_ENEMIES];
	

};

#endif // __J1ENEMIES_H__