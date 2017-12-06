#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UIElements.h"
#include "UIBackground.h"
#include "UIText.h"
#include "UIImage.h"
#include "UIButton.h"
#include "UITextBox.h"
#include "UIWindow.h"
#include "j1Menu.h"
#include "j1Options.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	background = App->tex->Load("gui/BG.png");

	fonts.PushBack(App->font->Load("fonts/ninja_naruto/njnaruto.ttf", 60));
	fonts.PushBack(App->font->Load("fonts/ninja_naruto/njnaruto.ttf", 50));

	buttons.PushBack(App->tex->Load("gui/UIButton.png"));
	buttons.PushBack(App->tex->Load("gui/UIButton_light.png"));
	textbox = App->tex->Load("gui/UITextBox.png");

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

bool j1Gui::PostUpdate()
{
	p2List_item<UIElements*>* element = elements.start;
	p2List_item<UIElements*>* element2 = elements.start;

	while (element != nullptr)
	{
		element->data->Draw();

		if (CheckMouse(element->data) == true)
		{
			if (element->data->mousein == false)
			{
				element->data->callback->GUIEvent(MOUSE_ENTER, element->data);
				element->data->mousein = true;
				element->data->mouseout = false;
			}
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				element->data->callback->GUIEvent(MOUSE_CLICK, element->data);
			}
			if (App->input->GetMouseButtonDown(1) == KEY_UP)
			{
				element->data->callback->GUIEvent(MOUSE_STOP_CLICK, element->data);
			}
		}
		
		if (element != nullptr)
		{
			if (CheckMouse(element->data) == false && element->data->mouseout == false)
			{
				element->data->callback->GUIEvent(MOUSE_LEAVE, element->data);
				element->data->mousein = false;
				element->data->mouseout = true;
			}

			element = element->next;
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		while (element2 != nullptr)
		{
			if (!element2->data->debug)
			{
				element2->data->debug = true;
			}
			else
			{
				element2->data->debug = false;
			}

			element2 = element2->next;
		}
	}

	if (startgame)
	{
		startgame = false;
		CleanUp();
		App->menu->StartGame();
	}
	if (startoptions)
	{
		startoptions = false;
		CleanUp();
		App->menu->StartOptions();
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<UIElements*>* item;
	item = elements.start;

	while (item != nullptr)
	{
		DeleteElements(item->data);
		item=item->next;
	}

	elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

SDL_Texture* j1Gui::GetBackground() const
{
	return background;
}

// class Gui ---------------------------------------------------

void j1Gui::AddBackground(int x, int y, UIElementType type, j1Module* modul)
{
	UIElements* element_created;
	element_created = new UIBackground(x, y, type, modul);
	elements.add(element_created);
}

UIElements* j1Gui::AddElementText(int x, int y, UIElementType type, j1Module* modul, const char* text)
{
	UIElements* element_created;
	element_created = new UIText(x, y, type, text, modul);
	elements.add(element_created);

	return element_created;

}

void j1Gui::AddElementImage(int x, int y, UIElementType type, SDL_Rect* rect, j1Module* modul)
{
	UIElements* element_created;
	element_created = new UIImage(x, y, type, rect, modul);
	elements.add(element_created);
}

UIElements* j1Gui::AddElementButton(int x, int y, UIElementType type, SDL_Rect* RecTex, j1Module* modul, const char* text, bool iswinelem)
{
	UIElements* element_created;
	element_created = new UIButton(x, y, type, RecTex, text, modul);
	element_created->isWindowElement = iswinelem;
	elements.add(element_created);

	return element_created;
}

UIElements* j1Gui::AddElementTextBox(int x, int y, UIElementType type, j1Module* modul, const char* text)
{
	UIElements* element_created;
	element_created = new UITextBox(x, y, type, text, modul);
	elements.add(element_created);

	return element_created;
}

UIElements* j1Gui::AddElementWindow(int x, int y, UIElementType type, j1Module* modul, p2List<UIElements*>* elementslist)
{
	UIElements* element_created;
	element_created = new UIWindow(x, y, type, modul, elementslist);
	elements.add(element_created);

	return element_created;
}

void j1Gui::DeleteElements(UIElements* element)
{
	RELEASE(element);
}

bool j1Gui::CheckMouse(UIElements* element)const
{
	bool ret = false;
	int x, y;

	App->input->GetMousePosition(x, y);

	x = x - App->render->camera.x;
	y = y - App->render->camera.y;

	if (x>element->Elementrect.x && x<element->Elementrect.x + element->Elementrect.w)
	{
		if (y > element->Elementrect.y && y <element->Elementrect.y + element->Elementrect.h)
		{
			ret = true;
		}
	}

	return ret;
}