#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "UIText.h"


UIText::UIText(int x, int y, UIElementType type, const char* text, j1Module* modul, bool actualize, bool _show) :UIElements(x, y, type, modul)
{
	show = _show;
	actualizable = actualize;

	string = text;

	texture = App->font->Print(string, { 255,255,0 }, App->gui->fonts[1]);

	BlackBackground = App->font->Print(string, { 0,0,0 }, App->gui->fonts[1]);

	App->tex->GetSize(texture, size_x, size_y);

	scale = 2.0f;

	int rect_x = position.x - (size_x / 2);
	int rect_y = position.y;

	Elementrect = { rect_x,rect_y,(int)size_x,(int)size_y };
}

UIText::~UIText()
{
}

void UIText::Draw()
{
	if (show)
	{
		if (!actualizable)
		{
			App->render->Blit(BlackBackground, position.x - App->render->camera.x - size_x / 2 + 2, position.y - App->render->camera.y + 2);
			App->render->Blit(texture, position.x - App->render->camera.x - size_x / 2, position.y - App->render->camera.y);
		}
		else
		{
			string = App->scene->score_string.GetString();
			texture = App->font->Print(string, { 255,255,0 }, App->gui->fonts[1]);
			BlackBackground = App->font->Print(string, { 0,0,0 }, App->gui->fonts[1]);

			App->render->Blit(BlackBackground, position.x - App->render->camera.x + 2, position.y - App->render->camera.y + 2);
			App->render->Blit(texture, position.x - App->render->camera.x, position.y - App->render->camera.y);
			SDL_DestroyTexture(texture);
			SDL_DestroyTexture(BlackBackground);
		}		

		if (debug == true)
		{
			App->render->DrawQuad(Elementrect, 0, 255, 255, 80);
		}
	}
}