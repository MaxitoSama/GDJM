#include "UIElements.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Fonts.h"



UIElements::UIElements(int x, int y, UIElementType type, j1Module* modul) :position(x, y), type(type), callback(modul)
{
}


UIElements::~UIElements()
{
}
