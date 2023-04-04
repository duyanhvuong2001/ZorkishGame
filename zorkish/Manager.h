#pragma once
#include "States.h"

class GameManager
{
public:
	GameManager();
	void update();
	void render();
	~GameManager();

private:
	//Game Entities
	MainMenu mainmenu;
	About about;
	Help help;
	GamePlay* gameplay = new GamePlay();
	Select* select = new Select(gameplay);
	HiScore hiscore;
	HOF hof;
	STATES state;
	State* curr = &mainmenu;
};