#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "p2DynArray.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2Defs.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1Colliders;
class j1Map;
class j1Entities;
class j1PathFinding;

class j1App
{
public:

	j1App(int argc, char* args[]);

	virtual ~j1App();

	bool Awake();
	bool Start();
	bool Update();
	bool CleanUp();

	void AddModule(j1Module* module);

	int GetArgc() const;

	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame();
	void SaveGame() const;
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

private:

	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	void PrepareUpdate();
	void FinishUpdate();

	bool PreUpdate();
	bool DoUpdate();
	bool PostUpdate();
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;
	j1Colliders*		colliders;
	j1Map*				map;
	j1Entities*			entities;
	j1PathFinding*		pathfinding;

	float				dt;

	bool				Cap_on = false;

private:

	p2List<j1Module*>	modules;
	uint32				frames;
	
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game;
	mutable p2SString	save_game;

	j1PerfTimer			ptimer;
	uint32				frame_count=0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	uint16_t			framerate_cap;
	int					capped_ms = -1;
};

extern j1App* App; 

#endif