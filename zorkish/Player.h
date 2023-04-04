#pragma once
#include <iostream>
#include <list>
#include <vector>
using namespace std;

struct Location;
class World;
class Item;
class Attribute;



class Inventory
{
public:
	Inventory();
	~Inventory();
	bool Has(string itm);
	void Add(Item* itm);
	string View(string itm);
	Item* Fetch(string);
	void Remove(string itm);
	string desc();
private:
	list<Item*> _items;
};

class Item
{
public:
	Item(string name, string desc);
	string name();
	virtual string desc();
	string fullDesc();
	Item* SearchFor(string itm);
	Inventory inven;
	void AddAttribute(Attribute*);
	string ShowAttributes();
	vector<Attribute*> attributes;
	~Item();
private:
	string _name;
	string _desc;
};

class Player {
private:
	Location* _location;
	
	Inventory* _inven = new Inventory;
public:
	World* world;
	bool playing;
	Player(World*);
	Location* MyLocation();
	void move(const string& dir);
	Inventory* locateContainerFor(string itm);
	Item* locateItem(string);
	void render();
	Inventory* MyInventory();
	~Player();
};

