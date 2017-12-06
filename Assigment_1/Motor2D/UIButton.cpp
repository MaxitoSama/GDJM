#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIButton.h"


UIButton::UIButton(int x, int y, UIElementType type, SDL_Rect* RecTex, const char* text, j1Module* modul) :UIElements(x, y, type, modul)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText = App->font->Print(buttontext, { 255, 255, 0 }, App->gui->fonts[1]);
		App->tex->GetSize(ButtonText, sizeTx, sizeTy);
	}

	RectTexture = RecTex;
	ElementTexture = App->gui->GetAtlas();

	scale = 0.7f;
	
	size_x = RectTexture->w;
	size_y = RectTexture->h;
	
}


UIButton::~UIButton()
{
}


void UIButton::Draw()
{
	if (!isWindowElement)
	{
		int rect_x;
		int rect_y;

		rect_x = position.x - (size_x / 2)*scale - App->render->camera.x;
		rect_y = position.y - App->render->camera.y;

		Elementrect = { rect_x,rect_y,(int)(size_x*scale),(int)(size_y*scale)};
		App->render->Blit(ElementTexture, rect_x, rect_y,RectTexture, scale);

		if (buttontext != nullptr)
		{
			App->render->Blit(ButtonText, position.x - App->render->camera.x - sizeTx / 2, position.y - App->render->camera.y + sizeTy / 2);
		}

		if (debug == true)
		{
			App->render->DrawQuad(Elementrect, 255, 0, 255, 80);
		}

		if (light)
		{
			App->render->Blit(App->gui->buttons[1], position.x - App->render->camera.x - size_x - 12, position.y - App->render->camera.y - 12, RectTexture, scale);
		}
	}
}

void UIButton::Action()
{

	if (!light)
	{
		light = true;
	}
	else
	{
		light = false;
	}
	
}