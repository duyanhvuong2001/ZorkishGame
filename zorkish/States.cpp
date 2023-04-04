#include "States.h"
#include <fstream>
#include <vector>
#include "Graph.h"
#include "Attribute.h"
using namespace std;
vector<string> Split(string line, string delim) {
	vector<string> items;
	size_t pos = 0;
	while ((pos = line.find(delim)) != string::npos) {
		items.push_back(line.substr(0, pos));
		line.erase(0, pos + delim.length());
	}
	items.push_back(line.substr(0, pos));
	return items;
}
void MainMenu::render() {
	cout << "____________________________________" << endl;
	cout << "<< Welcome to Zorkish! Fun awaits >>" << endl;
	cout << "1. About" << endl;
	cout << "2. Help" << endl;
	cout << "3. Select Adventure" << endl;
	cout << "4. Gameplay" << endl;
	cout << "5. New High Score" << endl;
	cout << "6. Hall of Fame" << endl;
	cout << "<< Please enter: 1-6>>";
}
State::State()
{
}

State::~State()
{
}
STATES MainMenu::update() {
	string line;
	while (getline(cin, line)) {
		int cmd;
		cmd = stoi(line);
		if (cmd >= 1 || cmd < 7) {
			return (STATES)cmd;
		}
		else {
			return STATES::MAIN_MENU;
		}
	}
}

void About::render() {
	cout << "Name: Duy Anh Vuong" << endl;
	cout << "ID: 102603197" << endl;
	cout << "Unit: COS30031 - Games Programming" << endl;
}

STATES About::update() {
	return STATES::MAIN_MENU;
}

void Help::render() {
	cout << "<< List of commands >>" << endl;
	cout << "1. W to go up" << endl;
	cout << "1. S to go down" << endl;
	cout << "1. A to go left" << endl;
	cout << "1. D to go right" << endl;
}

STATES Help::update() {
	return STATES::MAIN_MENU;
}
//Select Implementation
Select::Select(GamePlay* gameplay) {
	this->gameplay = gameplay;
}
void Select::render() {
	cout << "<< Zorkish Stages >>" << endl;
	const int SIZE = 4;
	string name[SIZE] = { "Radiant Valley","City","Metro","Riverlands"};
	int index = 1;
	for (int i = 0; i < SIZE; i++) {
		cout << index << ". " << name[i] << endl;
		index++;
	}
}

STATES Select::update() {
	string line;
	while (getline(cin, line)) {
		ifstream file;
		line += ".txt";
		file.open(line);
		if (file.fail()) {
			cout << "Failed in opening the file" << endl;
			file.close();
		}
		else {
			file.close();
			MakeGame(line);
			cout << "<<Successfully read game file>>" << endl;
			return STATES::GAMEPLAY;
		}
		//Close file
		
	}
	return STATES::MAIN_MENU;
}
void Select::MakeGame(string line) {
	//if file could be opened
	ifstream file;
	file.open(line);
	gameplay->w = new World();
	//add location
	while (getline(file, line) && line != "#") {
		vector<string> splitted = Split(line, ":");
		gameplay->w->addLocation(splitted[0], splitted[1]);
	}
	//add connection
	while (getline(file, line) && line != "-") {
		vector<string> splitted = Split(line, ":");
		if (splitted.size() != 3) {
			cout << "Wrong file format!" << endl;
			exit(1);
		}
		else {
			gameplay->w->addDirection(splitted[0], splitted[1], splitted[2]);
		}
	}
	//add entities into world
	while (getline(file, line)&&line!="+") {
		vector<string> splitted = Split(line, ":");
		if (splitted.size() != 3) {
			cout << "Wrong file format!" << endl;
			exit(1);
		}
		else {
			//If the container is a location
			if (gameplay->w->hasLocation(splitted[2])) {
				gameplay->w->locations[splitted[2]]->Inven->Add(new Item(splitted[0], splitted[1]));
			}
			else {//If the container is potentially an item
				Item* searched = gameplay->w->findItem(splitted[2]);
				if (searched == nullptr) {
					cout << "No item named " + splitted[2] << endl;
				}
				else {
					searched->inven.Add(new Item(splitted[0], splitted[1]));
				}
			}
		}
	}
	gameplay->p = new Player(gameplay->w);
	while (getline(file, line)&&line!="-Attribute") {
		vector<string> splitted = Split(line, ":");
		if (splitted.size() != 2) {
			cout << "Wrong file format for Player Item" << endl;
			exit(1);
		}
		else {
			gameplay->p->MyInventory()->Add(new Item(splitted[0], splitted[1]));
		}
	}

	while (getline(file,line))
	{
		vector<string> splitted = Split(line, ":");
		if (splitted.size() != 3) {
			cout << "Wrong file format for Attributes" << endl;
			exit(1);
		}
		else {
			Attribute* a;
			if (splitted[0] == "H") {
				a = new Health(stoi(splitted[1]));
				
			}
			else {
				a = new Mana(stoi(splitted[1]));
			}
			Item* gained = gameplay->w->findItem(splitted[2]);
			gained->AddAttribute(a);
		}

	}
	file.close();
	gameplay->processor = new CommandProcessor(gameplay->p);
}
//GamePlay Implementation
GamePlay::GamePlay() {
	this->callback = "";
}
void GamePlay::render() {
	cout << callback << endl;
}
GamePlay::~GamePlay() {
	delete processor;
	delete p;
	delete w;
}

STATES GamePlay::update() {
	if (!p->playing) {
		delete p;
		delete w;
		return STATES::MAIN_MENU;
	}
	cout << "Command:--->";
	string line;
	if (getline(cin,line)&&line != "q") {
		callback = processor->Process(line);
		return STATES::GAMEPLAY;
	}
}

//

void HiScore::render() {
	cout << "<< Please enter your name >>" << endl;
}

STATES HiScore::update() {
	string n;
	cin >> n;
	return STATES::MAIN_MENU;
}

void HOF::render() {
	cout << "1. Never: " << "10000" << endl;
	cout << "2. Gonna: " << "1000" << endl;
	cout << "3. Give: " << "100" << endl;
	cout << "4. You: " << "10" << endl;
	cout << "5. Up: " << "1" << endl;
}

STATES HOF::update() {
	return STATES::MAIN_MENU;
}

//Construct Implementation

