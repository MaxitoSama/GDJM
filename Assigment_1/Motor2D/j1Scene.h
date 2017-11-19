#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "p2Point.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	virtual ~j1Scene();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void ChangeScene(int x, int y);
	void StartCurrentScene();

public:

	p2DynArray<iPoint> path_test;

private:

	bool Map_1=true;
	bool Map_2=false;
};

#endif // __j1SCENE_H__