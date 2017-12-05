#ifndef __J1MENU_H__
#define __J1MENU_H__

#include "j1Module.h"

class j1Menu:public j1Module
{
public:

	j1Menu();
	virtual ~j1Menu();

	bool Awake(pugi::xml_node&);
	bool Start();
	/*bool PreUpdate();*/
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void StartGame();
	bool GUIEvent(UIEvents eventType, UIElements* element);

private:

};

#endif // __J1MENU_H__

