#ifndef __j1WINDOW_H__
#define __j1WINDOW_H__

#include "j1Module.h"

struct SDL_Window;
struct SDL_Surface;

class j1Window : public j1Module
{
public:

	j1Window();

	virtual ~j1Window();

	bool Awake(pugi::xml_node&);
	bool CleanUp();

	void SetTitle(const char* new_title);
	void GetWindowSize(uint& width, uint& height) const;

	uint GetScale() const;

public:

	SDL_Window* window =nullptr;

	SDL_Surface* screen_surface = nullptr;

	bool fullscreen_window=false;


private:

	p2SString	title;
	uint		width;
	uint		height;
	uint		scale;

};

#endif // __j1WINDOW_H__