#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "UIImage.h"


UIImage::UIImage(int x, int y, UIElementType type, SDL_Rect* rect, j1Module* modul) :UIElements(x, y, type, modul)
{
	rectangle = rect;
	Elementrect = *rect;
}


UIImage::~UIImage()
{
}

void UIImage::Draw()
{
	App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x - rectangle->w / 2, position.y - App->render->camera.y - rectangle->h / 2, rectangle, 0.9f);
	LOG("holi");
}
