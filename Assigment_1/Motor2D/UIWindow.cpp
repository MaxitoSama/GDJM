#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIWindow.h"


UIWindow::UIWindow(int x, int y, UIElementType type, j1Module* modul, p2List<UIElements*>* elementslist) :UIElements(x, y, type, modul)
{
	window = { 32,542,420,452 };

	size_x = window.w;
	size_y = window.h;

	windowelements = elementslist;

	p2List_item<UIElements*>* item = windowelements->start;

	while (item != nullptr)
	{
		item->data->position.x = item->data->position.x + position.x;
		item->data->position.y = item->data->position.y + position.y;

		item = item->next;
	}

	scale = 1.0f;
}


UIWindow::~UIWindow()
{
}

void UIWindow::Draw()
{
	if (show)
	{
		int rect_x = position.x;
		int rect_y = position.y;

		Elementrect = { rect_x,rect_y,(int)size_x*(int)scale,(int)size_y*(int)scale };

		App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y,&window, 1.0f);

		if (debug)
		{
			App->render->DrawQuad(Elementrect, 100, 200, 50, 80, true);
		}

		p2List_item<UIElements*>* item = windowelements->start;

		while (item != nullptr)
		{
			item->data->isWindowElement = false;
			item->data->Draw();

			item = item->next;
		}

		if (action)
		{
			Action();
		}

		App->input->GetMousePosition(mouseend.x, mouseend.y);
	}
	else
	{
		p2List_item<UIElements*>* item = windowelements->start;
		while (item != nullptr)
		{
			item->data->isWindowElement = true;
			item = item->next;
		}
	}
}

void UIWindow::Action()
{

	App->input->GetMousePosition(mousestart.x, mousestart.y);

	if (mousestart.x != mouseend.x || mousestart.y != mouseend.y)
	{
		position.x += mousestart.x - mouseend.x;
		position.y += mousestart.y - mouseend.y;

		p2List_item<UIElements*>* item = windowelements->start;

		while (item != nullptr)
		{
			item->data->position.x += mousestart.x - mouseend.x;
			item->data->position.y += mousestart.y - mouseend.y;

			item = item->next;
		}
	}

}