#pragma once
#include <iostream>
#include "Command.h"
enum class STATES {
	MAIN_MENU,
	ABOUT,
	HELP,
	SL_ADVENTURE,
	GAMEPLAY,
	NEW_HI_SCR,
	HALL_OF_FAME,
	CONSTRUCT,
};
class State
{
public:
	State();
	virtual void render() = 0;
	virtual STATES update() = 0;
	~State();

private:

};

class Delete : public State {
public:
	void render() override;
	STATES update() override;
	Delete(Player*, World*);
private:
	void DeleteGame();
	Player* p;
	World* w;
};
class MainMenu : public State
{
public:
	void render() override;
	STATES update() override;
private:

};

class About : public State
{
public:
	void render() override;
	STATES update() override;
private:

};

class Help : public State
{
public:
	void render() override;
	STATES update() override;
private:

};



class GamePlay : public State
{
public:
	GamePlay();
	void render() override;
	STATES update() override;
	Player* p;
	World* w;
	CommandProcessor* processor;
	~GamePlay();
private:
	string callback;
	
};

class Select : public State
{
public:
	void render() override;
	STATES update() override;
	Select(GamePlay*);
private:
	void MakeGame(string line);
	GamePlay* gameplay;
};

class HiScore : public State
{
public:
	void render() override;
	STATES update() override;
private:

};

class HOF : public State
{
public:
	void render() override;
	STATES update() override;
private:

};