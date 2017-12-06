#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "p2Point.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GuiWindw;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Change to scene 1
	void ChangeScene(int x, int y);

	//Start again
	void StartCurrentScene();

public:
	p2DynArray<iPoint> path_test;

private:
	bool Map_1;
	bool Map_2;

	GuiText* text = nullptr;

	UIElements* QuitButton = nullptr;
	UIElements* Score = nullptr;

	SDL_Rect button_play;
	SDL_Rect display_score;

	int score;
	p2SString score_string;
};

#endif // __j1SCENE_H__