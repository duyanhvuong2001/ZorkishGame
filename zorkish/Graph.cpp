#include "Graph.h"
//Location implementation
bool Location::hasDirection(const string& name) {
	dirs::iterator itr = directions.find(name);
	if (itr == directions.end()) {
		return false;
	}
	return true;
}

Location* Location::moveTo(const string& direction) {
	if (hasDirection(direction)) {
		cout << "Moving " << direction << endl;
		return directions[direction];
	}
	cout << "Cannot move that way!" << endl;
	return this;
}
void Location::render() {
	cout << "A " << name << ", " << desc << endl;
	for (auto dir : directions) {
		cout << " --> " << dir.first << ": " << dir.second->name << ",";
	}
	cout << endl;
}
Location::Location(string inputname, string inputdesc) {
	name = inputname;
	desc = inputdesc;
	Inven = new Inventory();
}
Location::~Location() {
	delete Inven;
}

//World implementation

void World::addLocation(const string& name, const string& desc) {
	if (!hasLocation(name)) {
		Location* l = new Location(name, desc);
		locations[name] = l;
		return;
	}
	cout << "Location named " << name << " already exist!" << endl;
}

bool World::hasLocation(const string& name) {
	lmap::iterator itr = locations.find(name);
	if (itr == locations.end()) {
		return false;
	}
	return true;
}

Item* World::findItem(string itm) {
	lmap::iterator itr;
	for (itr = locations.begin(); itr != locations.end(); itr++) {
		Item* searched = itr->second->Inven->Fetch(itm);
		if (searched != nullptr) {
			return searched;
		}
	}
	return nullptr;
}

void World::addDirection(const string& from, const string& to, string direction) {
	string msg = "";
	if (!hasLocation(from)) {
		msg += "- No location named " + from + " is found\n";
	}

	if (!hasLocation(to)) {
		msg += "- No location named " + to + " is found\n";
	}

	if (msg != "") {
		cout << "Create connection failed as: " << endl;
		cout << msg;
		return;
	}
	Location* f = (locations.find(from)->second);
	Location* t = (locations.find(to)->second);
	f->directions[direction] = t;
}
void World::render() {
	cout << "<< World Information >>" << endl;
	for (auto l : locations) {
		l.second->render();
	}
	cout << endl;
}
World::~World() {
	for (auto l : locations) {
		delete (l.second);
	}
}
