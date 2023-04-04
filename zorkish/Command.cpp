#include "Command.h"
#include "Graph.h"
//Split function
vector<string> SplitCommand(string line, string delim) {
	vector<string> items;
	size_t pos = 0;
	while ((pos = line.find(delim)) != string::npos) {
		items.push_back(line.substr(0, pos));
		line.erase(0, pos + delim.length());
	}
	items.push_back(line.substr(0, pos));
	return items;
}
//Command Processor:
CommandProcessor::CommandProcessor(Player* p) {
	this->p = p;
	//Move command map
	commandMap["move"] = new CommandMove(this->p);
	//Look command map
	commandMap["look"] = new CommandLook(this->p);
	//Alias command map
	commandMap["alias"] = new CommandAlias(this);
	//Inventory command map
	commandMap["inventory"] = new CommandInventory(this->p);
	//Help command map
	commandMap["help"] = new CommandHelp(this);
	//Treeview command map
	commandMap["treeview"] = new CommandTreeview(this->p);
	//Debug command map
	commandMap["debug"] = new CommandDebug(this->p);
	//Quit command map
	commandMap["quit"] = new CommandQuit(this->p);
	//Put command map
	commandMap["put"] = new CommandPut(this->p);
	//Take command map
	commandMap["take"] = new CommandTake(this->p);
}

string CommandProcessor::Process(string arg) {
	vector<string> args = SplitCommand(arg, " ");
	cmdMap::iterator itr = commandMap.find(args[0]);
	if (itr == commandMap.end()) {
		return "No command like that...";
	}
	Command* cmd = (commandMap.find(args[0])->second);
	return cmd->Process(args);
}

CommandProcessor::~CommandProcessor() {
	for (auto cmd : commandMap) {
		if (cmd.second != nullptr) {
			delete (cmd.second);
		}
	}
}

//Look Command
CommandLook::CommandLook(Player* p) {
	this->p = p;
}

string CommandLook::Process(vector<string> args) {
	if (args.size() == 1) {
		Location* loc = p->MyLocation();
		string msg = loc->name + " contains: \n";
		msg += loc->Inven->desc();
		loc->render();
		return msg;
	}
	else if (args.size() == 3) {
		if (args[1] == "at") {
			Item* item = p->MyLocation()->Inven->Fetch(args[2]);
			if (item!=nullptr) {
				string msg;
				msg += item->desc() + "\n";
				msg += item->ShowAttributes();
				return msg;
			}
			else {
				return "Cannot find " + args[2] + " here";
			}
		}
		else if (args[1] == "in") {
			Item* container = p->MyLocation()->Inven->Fetch(args[2]);
			if (container == nullptr) {
				return "Cannot find container";
			}
			else {
				return container->fullDesc();
			}
		}
		else {
			return "Syntax: Look AT something or Look IN something";
		}
	}
	else {
		return "Wrong look command ";
	}
}

//Move Command

CommandMove::CommandMove(Player* p) {
	this->p = p;
}

string CommandMove::Process(vector<string> args) {
	if (args.size() == 2) {
		if (p->MyLocation()->hasDirection(args[1])) {
			p->move(args[1]);
			return "Moved " + args[1];
		}
		else {
			return "Cannot move that way";
		}
	}
	else {
		return "Wrong move command";
	}
}

//Alias Command
CommandAlias::CommandAlias(CommandProcessor* processor) {
	this->processor = processor;
}

string CommandAlias::Process(vector<string> args) {
	if (args.size() != 3) {
		string msg = "Alias";
		msg += "\[OLD COMMAND\] + \[NEW COMMAND\]";
		return msg;
	}
	else {
		cmdMap::iterator itr = processor->commandMap.find(args[1]);
		if (itr != processor->commandMap.end()) {
			return "Command " + args[1] + " already exist";
		}
		itr = processor->commandMap.find(args[2]);
		if (itr == processor->commandMap.end()) {
			return "Command " + args[2] + " not available";
		}
		processor->commandMap[args[1]] = processor->commandMap[args[2]];
		return "Aliased " + args[1] + " to " + args[2];
	}
}

//Inventory Command
CommandInventory::CommandInventory(Player* p) {
	this->p = p;
}

string CommandInventory::Process(vector<string> args) {
	if (args.size() != 1) {
		return "Syntax: inventory";
	}
	else {
		string msg = "You are carrying: \n";
		msg += p->MyInventory()->desc();
		return msg;
	}
}

//Help command:

CommandHelp::CommandHelp(CommandProcessor* processor) {
	this->processor = processor;
}

string CommandHelp::Process(vector<string> args) {
	//iterator for command map
	if (args.size() == 1) {
		cmdMap::iterator it;
		cmdMap cmdMap = processor->commandMap;
		//iterator for reverse command map
		map < Command*, vector<string>>::iterator itr;
		map < Command*, vector<string>> rvsMap;
		for (it = cmdMap.begin(); it != cmdMap.end(); it++) {
			itr = rvsMap.find(it->second);
			if (itr != rvsMap.end()) {
				rvsMap[it->second].push_back(it->first);
			}
			else {
				rvsMap[it->second] = vector<string>();
				rvsMap[it->second].push_back(it->first);
			}
		}
		string msg;
		for (itr = rvsMap.begin(); itr != rvsMap.end(); itr++) {
			msg += "** ";
			for (size_t i = 0; i < itr->second.size(); i++) {
				msg += itr->second[i] + ", ";
			}
			msg += "\n";
		}
		return msg;
	}
	else {
		return "Syntax: help";
	}
}

//Tree-view command:
CommandTreeview::CommandTreeview(Player* p) {
	this->p = p;
}

string CommandTreeview::Process(vector<string> args) {
	if (args.size() == 1) {
		string msg;
		//Current Location
		msg += "[Current Location]\n";
		//Edges
		msg += p->MyLocation()->desc+"\n";
		//Location Items
		msg += "[Location contains]: \n";
		msg += p->MyLocation()->Inven->desc();
		//Player Inven
		msg += "[Player's Inventory]: \n";
		msg += p->MyInventory()->desc();
		return msg;
	}
	else {
		return "Syntax: treeview";
	}
	
}
//Debug Command:
CommandDebug::CommandDebug(Player* p) {
	this->p = p;
}

string CommandDebug::Process(vector<string> args) {
	if (args.size() == 1) {
		p->world->render();
		return "";
	}
	else {
		return "Syntax: debug";
	}

}
//Quit command
CommandQuit::CommandQuit(Player* p) {
	this->p = p;
}

string CommandQuit::Process(vector<string> args) {
	if (args.size() == 1) {
		p->playing = false;
		return "Bye have a great time";
	}
	else {
		return "Syntax: quit";
	}
}

//Put Command
CommandPut::CommandPut(Player* p) {
	this->p = p;
}

string CommandPut::Process(vector<string> args) {
	if (args.size() == 4) {
		Inventory* itmInven = p->locateContainerFor(args[1]);
		if (itmInven == nullptr) {
			return "Cannot locate item " + args[1];
		}

		Item* container = p->locateItem(args[3]);

		if (container == nullptr) {
			return "Cannot locate container " + args[3];
		}

		container->inven.Add(itmInven->Fetch(args[1]));
		itmInven->Remove(args[1]);
		return "Moved item " + args[1] + " to " + args[3];
	}
	else {
		return "Syntax: Put SOMETHING in SOMETHING";
	}
}

//Take Command
CommandTake::CommandTake(Player* p) {
	this->p = p;
}

string CommandTake::Process(vector<string> args) {
	if (args.size() == 2) {
		Item* itm = p->MyLocation()->Inven->Fetch(args[1]);
		if (itm == nullptr) {
			return "Cannot find item " + args[1] + " here";
		}
		p->MyInventory()->Add(itm);
		p->MyLocation()->Inven->Remove(args[1]);
		return "Took item " + args[1] + " into my inventory";
	}
	else if (args.size() == 4) {
		if (args[2] != "from") {
			return "Take SOMETHING FROM SOMETHING";
		}
		Item* container = p->MyLocation()->Inven->Fetch(args[3]);
		if (container == nullptr) {
			return "Cannot locate item " + args[3];
		}
		if (!container->inven.Has(args[1])) {
			return "Cannot locate item " + args[1] + " in " + args[3];
		}
		p->MyInventory()->Add(container->inven.Fetch(args[1]));
		container->inven.Remove(args[1]);
		return "Item " + args[1] + " taken from " + args[3];

	}
	else {
		return "Syntax: Take SOMETHING or Take SOMETHING from SOMETHING";
	}
}