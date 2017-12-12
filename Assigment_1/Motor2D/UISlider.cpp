#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "UISlider.h"


UISlider::UISlider(int x, int y, UIElementType type, SDL_Rect * rect, j1Module * modul, bool show) :UIElements(x, y, type, modul)
{
	this->show = show;
	rectangle = rect;
	Elementrect = *rect;
}

UISlider::~UISlider()
{

}

void UISlider::Draw()
{
	if (show)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x - rectangle->w / 2, position.y - App->render->camera.y - rectangle->h / 2, rectangle, 0.9f);
		App->render->Blit(App->gui->window, position.x - App->render->camera.x - rectangle->w / 2, position.y - App->render->camera.y - rectangle->h / 2, rectangle, 0.9f);
	}
	
}
