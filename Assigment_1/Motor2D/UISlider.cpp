#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "UISlider.h"
#include "j1Input.h"


UISlider::UISlider(int x, int y, UIElementType type, SDL_Rect* slider, SDL_Rect* button, j1Module* modul, p2List<UIElements*>* elementslist, bool show) :UIElements(x, y, type, modul)
{
	this->show = show;
	this->slider = slider;
	this->button = button;
	sliderelements = elementslist;
	Elementrect = *slider;
}

UISlider::~UISlider()
{

}

void UISlider::Draw()
{
	if (show)
	{
		//slider
		App->render->Blit(App->gui->window, position.x - App->render->camera.x - slider->w / 2, position.y - App->render->camera.y - slider->h / 2, slider, 1.5f);

		//button
		App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x - button->w / 2, position.y - App->render->camera.y + 55 - button->h / 2, button, 0.5f);
	}
	
}

void UISlider::Action()
{
	App->input->GetMousePosition(mousestart.x, mousestart.y);

	if (mousestart.x != mouseend.x || mousestart.y != mouseend.y)
	{
		position.x += mousestart.x - mouseend.x;
		position.y += mousestart.y - mouseend.y;

		p2List_item<UIElements*>* item = sliderelements->start;

		while (item != nullptr)
		{
			item->data->position.x += mousestart.x - mouseend.x;
			item->data->position.y += mousestart.y - mouseend.y;

			item = item->next;
		}
	}
}
