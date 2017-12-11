#include "p2Defs.h"
#include "p2Log.h"
#include "p2Animation.h"
#include "p2Path.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Colliders.h"
#include "j1Pathfinding.h"
#include "j1Menu.h"
#include "j1Scene.h"
#include "j1Entities.h"
#include "Player.h"
#include "j1Gui.h"
#include "UIButton.h"


j1Menu::j1Menu()
{
	name.create("menu");

	ninja.PushBack({ 64,111,176,331 });
	ninja.PushBack({ 310,111,176,331 });
	ninja.PushBack({ 575,111,176,331 });
	ninja.PushBack({ 845,111,176,331 });
	ninja.PushBack({ 1138,111,176,331 });
	ninja.PushBack({ 1450,111,176,331 });
	ninja.PushBack({ 1735,111,176,331 });
	ninja.PushBack({ 2019,111,176,331 });
	ninja.PushBack({ 2284,111,176,331 });
	ninja.PushBack({ 2559,111,176,331 });

	ninja.loop = true;
	ninja.speed = 30.0f;
}

j1Menu::~j1Menu()
{

}

bool j1Menu::Awake(pugi::xml_node& config)
{
	return true;
}

bool j1Menu::Start()
{
	sprites_ninja = App->tex->Load("assets/character/character.png");
	animation = &ninja;

	App->scene->active = false;

	//MAIN_MENU
	rect_button_play = { 400, 972, 183, 191 };
	rect_button_options = { 3093, 318, 183, 191 };
	rect_button_exit = { 2556,1407,183,191 };
	rect_button_credits = { 1142,1191,183,191 };

	//OPTIONS_MENU
	rect_button_back = { 3094,101,179,182 };
	rect_button_music = { 2148,1844,183,191 };
	rect_button_sound = { 2148,2062,183,191 };

	App->gui->AddBackground(0, 0, BACKGROUND, this);
	button_play = App->gui->AddElementButton(150, 300, BUTTON, &rect_button_play, this);
	text_start = App->gui->AddElementText(250, 340, TEXT, 1, this, "Start Game");
	button_options = App->gui->AddElementButton(150, 450, BUTTON, &rect_button_options, this);
	text_option = App->gui->AddElementText(250, 490, TEXT, 1, this, "Option");
	button_exit = App->gui->AddElementButton(150, 750, BUTTON, &rect_button_exit, this);
	text_exit = App->gui->AddElementText(250, 640, TEXT,1, this, "Credits");
	button_credits = App->gui->AddElementButton(150, 600, BUTTON,&rect_button_credits, this);
	text_credits = App->gui->AddElementText(250, 790, TEXT, 1, this, "Exit");
	button_back = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this,nullptr,false);
	button_back_credits = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this, nullptr, false);

	button_sound = App->gui->AddElementButton(150, 150, BUTTON, &rect_button_sound, this,nullptr,false);
	text_sound = App->gui->AddElementText(250, 190, TEXT, 1, this, "Volume", false, false);
	button_music = App->gui->AddElementButton(150, 300, BUTTON, &rect_button_music, this, nullptr,false);
	text_music = App->gui->AddElementText(250, 340, TEXT, 1, this, "Music", false, false);

	License_1 = App->gui->AddElementText(50, 110,TEXT, 2, this, "MIT License",false,false);
	License_2 = App->gui->AddElementText(50, 140, TEXT, 2, this, "Copyright (c) 2017 Marc Garcia, Josep Pi", false, false);
	License_3 = App->gui->AddElementText(50, 180, TEXT, 2, this, "Permission is hereby granted, free of charge, to any person obtaining a copy", false, false);
	License_4 = App->gui->AddElementText(50, 200, TEXT, 2, this, "of this software and associated documentation files (the \"Software\"), to deal", false, false);
	License_5 = App->gui->AddElementText(50, 220, TEXT, 2, this, "in the Software without restriction, including without limitation the rights", false, false);
	License_6 = App->gui->AddElementText(50, 240, TEXT, 2, this, "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell", false, false);
	License_7 = App->gui->AddElementText(50, 260, TEXT, 2, this, "copies of the Software, and to permit persons to whom the Software is", false, false);
	License_8 = App->gui->AddElementText(50, 280, TEXT, 2, this, "furnished to do so, subject to the following conditions:", false, false);
	License_9 = App->gui->AddElementText(50, 300, TEXT, 2, this, "The above copyright notice and this permission notice shall be included in all", false, false);
	License_10 = App->gui->AddElementText(50, 320, TEXT, 2, this, "copies or substantial portions of the Software.", false, false);
	License_11 = App->gui->AddElementText(50, 340, TEXT, 2, this, "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR", false, false);
	License_12 = App->gui->AddElementText(50, 360, TEXT, 2, this, "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,", false, false);
	License_13 = App->gui->AddElementText(50, 380, TEXT, 2, this, "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE", false, false);
	License_14 = App->gui->AddElementText(50, 400, TEXT, 2, this, "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER", false, false);
	License_15 = App->gui->AddElementText(50, 420, TEXT, 2, this, "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,", false, false);
	License_16 = App->gui->AddElementText(50, 440, TEXT, 2, this, "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE", false, false);

	License_text.add(License_1);
	License_text.add(License_2);
	License_text.add(License_3);
	License_text.add(License_4);
	License_text.add(License_5);
	License_text.add(License_6);
	License_text.add(License_7);
	License_text.add(License_8);
	License_text.add(License_9);
	License_text.add(License_10);
	License_text.add(License_11);
	License_text.add(License_12);
	License_text.add(License_13);
	License_text.add(License_14);
	License_text.add(License_15);
	License_text.add(License_16);

	License_window = App->gui->AddElementWindow(300, 200, WINDOWS, this, &License_text, { 1055,160,930,742 }, false);

	return true;
}

bool j1Menu::Update(float dt)
{
	this->dt = dt;
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->gui->startgame = true;
	}

	return true;
}

bool j1Menu::PostUpdate()
{
	BROFILER_CATEGORY("PosUpdate_Scene1 ", Profiler::Color::DarkOrchid)
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			exit=false;
	if (button_play->show == true)
	{
		App->render->Blit(sprites_ninja, 870, 340, &(animation->GetCurrentFrame(dt)), -1.6f);
	}

	return exit;
}

bool j1Menu::CleanUp()
{
	App->tex->UnLoad(sprites_ninja);
	
	License_text.clear();

	return true;
}

bool j1Menu::GUIEvent(UIEvents eventType, UIElements* element)
{
	switch (eventType)
		{
		case MOUSE_ENTER:
			if (element == button_play && element->show)
			{
			}
			if (element == button_options && element->show)
			{
				
			}
			if (element == button_exit && element->show)
			{
				
			}
			break;

		case MOUSE_LEAVE:
			if (element == button_play && element->show)
			{
			}
			if (element == button_options && element->show)
			{
				
			}
			if (element == button_exit && element->show)
			{

			}
			break;

		case MOUSE_CLICK:
			if (element == button_play && element->show)
			{
			}
			if (element == button_options && element->show)
			{
				
			}
			if (element == button_exit && element->show)
			{
			}
			break;

		case MOUSE_STOP_CLICK:
			App->audio->PlayFx(3);
			if (element == button_play && element->show)
			{
				App->gui->startgame = true;
			}
			if (element == button_options && element->show)
			{
				OptionsButton();
			}
			if (element == button_exit && element->show)
			{
				exit = false;
			}
			if (element == button_back && element->show)
			{
				OptionsButton();
			}
			if (element == button_credits && element->show)
			{
				CreditsButton();
			}
			if (element == button_back_credits && element->show)
			{
				CreditsButton();
			}
			break;
		
		default:
			break;
		}
	return true;
}

void j1Menu::StartGame()
{
	CleanUp();
	App->menu->active = false;
	App->scene->active = true;
	App->scene->Start();
	App->entities->Start();
}

void j1Menu::OptionsButton()
{
	if (button_options->show)
	{
		button_exit->show = false;
		button_options->show = false;
		button_play->show = false;
		button_credits->show = false;

		text_start->show = false;
		text_option->show = false;
		text_exit->show = false;
		text_credits->show = false;

		button_back->show = true;
		button_sound->show = true;
		button_music->show = true;

		text_sound->show = true;
		text_music->show = true;
		
	}
	else
	{
		button_exit->show = true;
		button_options->show = true;
		button_play->show = true;
		button_credits->show = true;

		text_start->show = true;
		text_option->show = true;
		text_exit->show = true;
		text_credits->show = true;

		button_back->show = false;
		button_sound->show = false;
		button_music->show = false;

		text_sound->show = false;
		text_music->show = false;
	}

}

void j1Menu::CreditsButton()
{
	if (button_options->show)
	{
		button_exit->show = false;
		button_options->show = false;
		button_play->show = false;
		button_credits->show = false;

		text_start->show = false;
		text_option->show = false;
		text_exit->show = false;
		text_credits->show = false;

		button_back_credits->show = true;
		License_window->show = true;

		/*License_1->show = true;
		License_2->show = true;
		License_3->show = true;
		License_4->show = true;
		License_5->show = true;
		License_6->show = true;
		License_7->show = true;
		License_8->show = true;
		License_9->show = true;
		License_10->show = true;
		License_11->show = true;
		License_12->show = true;
		License_13->show = true;
		License_15->show = true;
		License_16->show = true;*/

	}
	else
	{
		button_exit->show = true;
		button_options->show = true;
		button_play->show = true;
		button_credits->show = true;

		text_start->show = true;
		text_option->show = true;
		text_exit->show = true;
		text_credits->show = true;

		button_back_credits->show = false;
		License_window->show = false;

		/*License_1->show = false;
		License_2->show = false;
		License_3->show = false;
		License_4->show = false;
		License_5->show = false;
		License_6->show = false;
		License_7->show = false;
		License_8->show = false;
		License_9->show = false;
		License_10->show = false;
		License_11->show = false;
		License_12->show = false;
		License_13->show = false;
		License_15->show = false;
		License_16->show = false;*/
	}
}