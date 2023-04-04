#pragma once
#include <iostream>
#include "Player.h"
#include <map>
#include <vector>

using namespace std;

class Command
{
public:
	virtual string Process(vector<string> args) = 0;
private:

};

class CommandLook : public Command
{
public:
	CommandLook(Player* p);
	string Process(vector<string> args) override;
private:
	Player* p;
};

class CommandInventory : public Command {
private:
	Player* p;
public:
	CommandInventory(Player*);
	string Process(vector<string> args) override;
};

class CommandPut : public Command {
private:
	Player* p;
public:
	CommandPut(Player*);
	string Process(vector<string> args) override;
};

class CommandTake : public Command {
private:
	Player* p;
public:
	CommandTake(Player*);
	string Process(vector<string> args) override;
};

class CommandMove : public Command {
private:
	Player* p;
public:
	CommandMove(Player* p);
	string Process(vector<string> args) override;
};

typedef map<string, Command*> cmdMap;

class CommandProcessor {

public:
	CommandProcessor(Player* p);
	string Process(string arg);
	cmdMap commandMap;
	~CommandProcessor();
private:
	Player* p;
};

class CommandAlias : public Command {
private:
	CommandProcessor* processor;
public:
	CommandAlias(CommandProcessor*);
	string Process(vector<string> args) override;
};

class CommandHelp : public Command {
private:
	CommandProcessor* processor;
public:
	CommandHelp(CommandProcessor*);
	string Process(vector<string> args) override;
};

class CommandTreeview : public Command {
private:
	Player* p;
public:
	CommandTreeview(Player* p);
	string Process(vector<string> args) override;
};

class CommandDebug : public Command {
private:
	Player* p;
public:
	CommandDebug(Player* p);
	string Process(vector<string> args) override;
};

class CommandQuit : public Command {
private:
	Player* p;
public:
	CommandQuit(Player*);
	string Process(vector<string> args) override;
};