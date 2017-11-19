#include <stdlib.h>

#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "Brofiler\Brofiler.h"
#include "SDL/include/SDL.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "Brofiler/ProfilerCore32.lib")

enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

j1App* App = NULL;

int main(int argc, char* args[])
{
	LOG("Engine starting ... %d");
	MainState state = MainState::CREATE;
	int result = EXIT_FAILURE;

	while(state != EXIT)
	{
		switch(state)
		{

			case CREATE:
			LOG("CREATION PHASE ===============================");

			App = new j1App(argc, args);

			if(App != NULL)
				state = AWAKE;
			else
				state = FAIL;

			break;

			case AWAKE:
			LOG("AWAKE PHASE ===============================");
			if(App->Awake() == true)
				state = START;
			else
			{
				LOG("ERROR: Awake failed");
				state = FAIL;
			}

			break;

			case START:
			LOG("START PHASE ===============================");
			if(App->Start() == true)
			{
				
				state = LOOP;
			
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = FAIL;
				LOG("ERROR: Start failed");
			}
			break;

			case LOOP:
			{
				BROFILER_FRAME("Ninjas Path");
				if (App->Update() == false)
					state = CLEAN;
			}

			break;

			case CLEAN:
			LOG("CLEANUP PHASE ===============================");
			if(App->CleanUp() == true)
			{
				RELEASE(App);
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			case FAIL:
			LOG("Exiting with errors");
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
	}

	LOG("... Bye!\n");

	return result;
}