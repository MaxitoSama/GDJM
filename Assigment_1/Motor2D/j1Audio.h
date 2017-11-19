#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "p2List.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();

	virtual ~j1Audio();
	bool Awake(pugi::xml_node&);
	bool CleanUp();
	bool Update(float dt);
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	unsigned int LoadFx(const char* path);
	bool PlayFx(unsigned int fx, int repeat = 0);
	bool Save(pugi::xml_node&)const;
	bool Load(const pugi::xml_node&);

public:

	int					fx_volume;
	int					music_volume;

private:

	_Mix_Music*			music;
	p2List<Mix_Chunk*>	fx;
	
};

#endif // __j1AUDIO_H__