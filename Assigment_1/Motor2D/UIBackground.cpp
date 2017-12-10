#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "UIBackground.h"


UIBackground::UIBackground(int x, int y, UIElementType type, j1Module* modul) :UIElements(x, y, type, modul)
{
}

UIBackground::~UIBackground()
{
}

void UIBackground::Draw()
{
	App->render->Blit(App->gui->GetBackground(), position.x, position.y, {},1.1f);
}