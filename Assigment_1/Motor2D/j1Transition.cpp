#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Entities.h"
#include "j1Menu.h"
#include "j1Scene.h"
#include "j1Transition.h"




j1Transition::j1Transition()
{
	screen = { 0, 0,1500, 1000 };
}

j1Transition::~j1Transition()
{
}

bool j1Transition::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool j1Transition::Update(float dt)
{
	bool ret=true;

	if (current_step == fade_step::none)
	{
		ret == true;
	}
	else
	{
		switch (current_step)
		{
		case fade_step::fade_to_black:
		{
			if (clock.ReadSec() >= 3)
			{
				to_disable->active = false;

				App->render->camera.x = 0;
				App->render->camera.y = 0;

				if (to_enable == App->scene)
				{
					App->menu->StartGame();
				}
				else
				{
					App->scene->GoToMenu();
				}

				to_enable->active = true;
				current_step = fade_step::fade_from_black;
			}
		} 
		break;

		case fade_step::fade_from_black:
		{
			current_step = fade_step::none;
		}
		break;
		}

		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(App->render->renderer, &screen);
	}

	return ret;
}

bool j1Transition::Transition(j1Module* module_off, j1Module* module_on)
{
	bool ret=false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		to_disable = module_off;
		to_enable = module_on;
		clock.Start();
		ret = true;
	}
	
	return ret;
}