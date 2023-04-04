#pragma once
#include <cstdio>
#include <vector>
#include <map>
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;


struct Location
{
	//pair of direction and location
	typedef map<string, Location*> dirs;
	dirs directions;
	string name;
	string desc;
	string Desc();
	Inventory *Inven;
	Location(string, string);
	bool hasDirection(const string&);
	Location* moveTo(const string& direction);
	void render();
	~Location();
};

class World {
public:
	typedef map<string, Location*> lmap;
	lmap locations;
	bool hasLocation(const string&);
	Item* findItem(string);
	void addLocation(const string&, const string&);
	void addDirection(const string& from, const string& to, string direction);
	void render();
	~World();
};