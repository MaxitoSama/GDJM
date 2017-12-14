#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "UISlider.h"
#include "j1Input.h"


UISlider::UISlider(int x, int y, UIElementType type, SDL_Rect* slider, SDL_Rect* button, j1Module* modul, UIElements* element_button, bool show) :UIElements(x, y, type, modul)
{
	this->show = show;
	this->slider = slider;
	this->button = button;
	Elementrect = *button;

	scale = 0.5f;
	collider_size_x = button->w;
	collider_size_y = button->h;

	button_point.x = position.x - App->render->camera.x - button->w / 2;
	button_point.y = position.y - App->render->camera.y + 55 - button->h / 2;



}

UISlider::~UISlider()
{

}

void UISlider::Draw()
{
	if (show)
	{
		int rect_x;
		int rect_y;

		rect_x = button_point.x+45;
		rect_y = button_point.y+40;

		Elementrect = { rect_x-45,rect_y-40,(int)(collider_size_x*scale),(int)(collider_size_y*scale) };

		//slider
		App->render->Blit(App->gui->window, position.x - App->render->camera.x - slider->w / 2, position.y - App->render->camera.y - slider->h / 2, slider, 1.5f);

		//button
		App->render->Blit(App->gui->GetAtlas(), button_point.x, button_point.y, button, 0.5f);

		if (debug == true)
		{
			App->render->DrawQuad(Elementrect, 255, 0, 255, 80);
		}
		
	}

}

void UISlider::Action()
{
	App->input->GetMouseButtonDown(mouse_button);


	if (mouse_button == 0)
	{
		App->input->GetMousePosition(mousestart.x, mousestart.y);
		//button_point.x += mousestart.x - mouseend.x;
	}
	LOG("Mouse initial position %d %d. Mouse final position %d %d", mousestart.x, mousestart.y, mouseend.x, mouseend.y);

	
	
}
