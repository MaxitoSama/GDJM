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
#include "j1Transition.h"
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
	App->audio->PlayMusic("audio/music/menu_music.ogg");
	App->GamePaused = false;
	sprites_ninja = App->tex->Load("assets/character/character.png");
	ninja.Reset();
	animation = &ninja;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->scene->active = false;
	//Put fade to black once everything is done (ric feedback)

	//MAIN_MENU
	rect_button_play_2 = { 400, 972, 183, 191 };
	rect_button_play = { 196, 972, 183, 191 };
	rect_button_options = { 3093, 318, 183, 191 };
	rect_button_exit = { 2556,1407,183,191 };
	rect_button_credits = { 1142,1191,183,191 };
	rect_button_continue = { 197,2498,183,191 };

	//OPTIONS_MENU
	rect_button_back = { 3094, 101, 179, 182 };
	rect_button_music = { 2148, 1844,183, 191 };
	rect_button_sound = { 2148, 2062,183, 191 };
	rect_slider_vertical = { 1534, 2977, 12, 602 };

	rect_slider_horizontal = { 2981, 3626, 604, 14 };
	rect_button_horizontal = { 3094, 2280, 183, 191 };

	App->gui->AddBackground(0, 0, BACKGROUND, this);

	//MAIN_MENU
	button_play = App->gui->AddElementButton(150, 150, BUTTON, &rect_button_play, this);
	text_start = App->gui->AddElementText(250, 190, TEXT, 1,255,255,0, this, "Start Game");
	button_continue = App->gui->AddElementButton(150, 300, BUTTON, &rect_button_continue, this);
	text_continue= App->gui->AddElementText(250, 340, TEXT, 1, 255, 255, 0, this, "Continue");
	button_options = App->gui->AddElementButton(150, 450, BUTTON, &rect_button_options, this);
	text_option = App->gui->AddElementText(250, 490, TEXT, 1, 255, 255, 0, this, "Option");
	button_exit = App->gui->AddElementButton(150, 750, BUTTON, &rect_button_exit, this);
	text_exit = App->gui->AddElementText(250, 640, TEXT,1, 255, 255, 0, this, "Credits");

	//CREDITS
	button_credits = App->gui->AddElementButton(150, 600, BUTTON,&rect_button_credits, this);
	text_credits = App->gui->AddElementText(250, 790, TEXT, 1, 255, 255, 0, this, "Exit");
	button_back = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this,nullptr,false);
	button_back_credits = App->gui->AddElementButton(1300, 750, BUTTON, &rect_button_back, this, nullptr, false);

	//OPTIONS_MENU
	button_sound = App->gui->AddElementButton(150, 150, BUTTON, &rect_button_sound, this,nullptr,false);
	text_sound = App->gui->AddElementText(250, 190, TEXT, 1, 255, 255, 0, this, "Volume", false, false);
	button_music = App->gui->AddElementButton(150, 300, BUTTON, &rect_button_music, this, nullptr,false);
	slider_horizontal = App->gui->AddElementSlider(800, 220, BUTTON, &rect_slider_horizontal, &rect_button_horizontal, this, slider_button_horizontal);

	//use xml to insert the licence once everything is done (ric feedback)
	{
		text_music = App->gui->AddElementText(250, 340, TEXT, 1, 255, 255, 0, this, "Music", false, false);

		License_1 = App->gui->AddElementText(60, 180, TEXT, 2, 0, 0, 0, this, "MIT License", false, false);
		License_2 = App->gui->AddElementText(60, 210, TEXT, 2, 0, 0, 0, this, "Copyright (c) 2017 Marc Garcia, Josep Pi", false, false);
		License_3 = App->gui->AddElementText(60, 250 + 5, TEXT, 2, 0, 0, 0, this, "Permission is hereby granted, free of charge, to any person obtaining a copy", false, false);
		License_4 = App->gui->AddElementText(60, 270 + 5, TEXT, 2, 0, 0, 0, this, "of this software and associated documentation files (the \"Software\"), to deal", false, false);
		License_5 = App->gui->AddElementText(60, 290 + 5, TEXT, 2, 0, 0, 0, this, "in the Software without restriction, including without limitation the rights", false, false);
		License_6 = App->gui->AddElementText(60, 310 + 5, TEXT, 2, 0, 0, 0, this, "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell", false, false);
		License_7 = App->gui->AddElementText(60, 330 + 5, TEXT, 2, 0, 0, 0, this, "copies of the Software, and to permit persons to whom the Software is", false, false);
		License_8 = App->gui->AddElementText(60, 350 + 5, TEXT, 2, 0, 0, 0, this, "furnished to do so, subject to the following conditions:", false, false);
		License_9 = App->gui->AddElementText(60, 370 + 5, TEXT, 2, 0, 0, 0, this, "The above copyright notice and this permission notice shall be included in all", false, false);
		License_10 = App->gui->AddElementText(60, 390 + 5, TEXT, 2, 0, 0, 0, this, "copies or substantial portions of the Software.", false, false);

		License_11 = App->gui->AddElementText(60, 450 + 5, TEXT, 2, 0, 0, 0, this, "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR", false, false);
		License_12 = App->gui->AddElementText(60, 470 + 5, TEXT, 2, 0, 0, 0, this, "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,", false, false);
		License_13 = App->gui->AddElementText(60, 490 + 5, TEXT, 2, 0, 0, 0, this, "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE", false, false);
		License_14 = App->gui->AddElementText(60, 510 + 5, TEXT, 2, 0, 0, 0, this, "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER", false, false);
		License_15 = App->gui->AddElementText(60, 530 + 5, TEXT, 2, 0, 0, 0, this, "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,", false, false);
		License_16 = App->gui->AddElementText(60, 550 + 5, TEXT, 2, 0, 0, 0, this, "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS", false, false);
		License_17 = App->gui->AddElementText(60, 570 + 5, TEXT, 2, 0, 0, 0, this, "IN THE SOFTWARE", false, false);


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
		License_text.add(License_17);

		License_window = App->gui->AddElementWindow(300, 200, WINDOWS, this, &License_text, { 1055,160,930,742 }, false);
	}

	
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
	if (active && button_play->show)
	{
		App->render->Blit(sprites_ninja, 870, 340, &(animation->GetCurrentFrame(dt)), -1.6f);
	}

	return exit;
}

bool j1Menu::CleanUp()
{
	App->tex->UnLoad(sprites_ninja);
	animation = nullptr;
	
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
				element->Action();
			}
			if (element == button_continue && element->show)
			{
				element->Action();
			}
			if (element == button_credits && element->show)
			{
				element->Action();
			}
			if (element == button_options && element->show)
			{
				element->Action();
			}
			if (element == button_exit && element->show)
			{
				element->Action();
			}

			break;

		case MOUSE_LEAVE:
			if (element == button_play && element->show)
			{
				element->Action();
			}
			if (element == button_continue && element->show)
			{
				element->Action();
			}
			if (element == button_credits && element->show)
			{
				element->Action();
			}
			if (element == button_options && element->show)
			{
				element->Action();
			}
			if (element == button_exit && element->show)
			{
				element->Action();
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

		case MOUSE_REPEAT:
			if (element == slider_horizontal && element->show)
			{
				
				element->Action();
			}
			break;

		case MOUSE_STOP_CLICK:
			if (element->show == true)
			{
				App->audio->PlayFx(3);
			}
			if (element == button_play && element->show)
			{
				App->gui->startgame = true;
				continue_game = false;
				App->transit->Transition(this, App->scene);
			}
			if (element == button_continue && element->show)
			{
				App->gui->startgame = true;
				continue_game = true;
				App->transit->Transition(this, App->scene);
			}
			if (element == button_options && element->show)
			{
				element->Action();
				OptionsButton();
			}
			if (element == button_exit && element->show)
			{
				exit = false;
			}
			if (element == button_back && element->show)
			{
				element->Action();
				OptionsButton();
			}
			if (element == button_credits && element->show)
			{
				element->Action();
				CreditsButton();
			}
			if (element == button_back_credits && element->show)
			{
				element->Action();
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

	App->scene->Start();
	App->entities->Start();
	
	if (continue_game)
	{
		continue_game = false;
		App->entities->PreUpdate();
		App->LoadGame();
	}
	else
	{
		App->entities->player->lives = 3;
		App->entities->player->score = 0;
		App->entities->player->coins = 0;

		if (App->scene->Map_1)
		{
			App->scene->StartCurrentScene();
		}
		else
		{
			App->scene->ChangeScene(60, 215);
		}
	}
}

void j1Menu::OptionsButton()
{
	if (button_options->show)
	{
		button_exit->show = false;
		button_continue->show = false;
		button_options->show = false;
		button_play->show = false;
		button_credits->show = false;

		text_start->show = false;
		text_option->show = false;
		text_exit->show = false;
		text_credits->show = false;
		text_continue->show = false;

		button_back->show = true;
		button_sound->show = true;
		button_music->show = true;

		text_sound->show = true;
		text_music->show = true;

		slider_horizontal->show = true;
		
	}
	else
	{
		button_exit->show = true;
		button_options->show = true;
		button_play->show = true;
		button_credits->show = true;
		button_continue->show = true;

		text_start->show = true;
		text_option->show = true;
		text_exit->show = true;
		text_credits->show = true;
		text_continue->show = true;

		
		button_back->show = false;
		button_sound->show = false;
		button_music->show = false;

		text_sound->show = false;
		text_music->show = false;
		slider_horizontal->show = false;
	}

}

void j1Menu::CreditsButton()
{
	if (button_options->show)
	{
		button_exit->show = false;
		button_continue->show = false;
		button_options->show = false;
		button_play->show = false;
		button_credits->show = false;

		text_start->show = false;
		text_continue->show = false;
		text_option->show = false;
		text_exit->show = false;
		text_credits->show = false;

		button_back_credits->show = true;
		License_window->show = true;

	}
	else
	{
		button_exit->show = true;
		button_continue->show = true;
		button_options->show = true;
		button_play->show = true;
		button_credits->show = true;

		text_start->show = true;
		text_continue->show = true;
		text_option->show = true;
		text_exit->show = true;
		text_credits->show = true;

		button_back_credits->show = false;
		License_window->show = false;

	}
}