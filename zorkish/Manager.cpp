#include "States.h"
#include "Manager.h"

GameManager::GameManager()
{
	state = STATES::MAIN_MENU;
}
void GameManager::update() {
	state = curr->update();
	if (state == STATES::MAIN_MENU) { curr = &mainmenu; }
	else if (state == STATES::GAMEPLAY) { curr = gameplay; }
	else if (state == STATES::ABOUT) { curr = &about; }
	else if (state == STATES::HELP) { curr = &help; }
	else if (state == STATES::SL_ADVENTURE) { curr = select; }
	else if (state == STATES::NEW_HI_SCR) { curr = &hiscore; }
	else if (state == STATES::HALL_OF_FAME) { curr = &hof; }
}
void GameManager::render() {
	curr->render();
}
GameManager::~GameManager()
{
	delete gameplay;
	delete select;
	curr = nullptr;
}