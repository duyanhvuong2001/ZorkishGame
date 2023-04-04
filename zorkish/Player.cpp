#include "Player.h"
#include "Graph.h"
#include "Attribute.h"
Item::Item(string name, string desc) {
	_name = name;
	_desc = desc;
}

string Item::name() {
	return _name;
}
string Item::desc() {
	return _desc;
}

string Item::fullDesc() {
	string msg = _name + " is " + _desc + " contains:\n" + inven.desc();
	return msg;
}

Item* Item::SearchFor(string itm) {
	if (name().compare(itm) == 0) {
		return this;
	}
	else {
		return inven.Fetch(itm);
	}
}

void Item::AddAttribute(Attribute* attr) {
	attributes.push_back(attr);
}

string Item::ShowAttributes() {
	string msg = "";
	for (auto a : attributes) {
		msg += "- ";
		msg += a->Detail();
		msg += "\n";
	}
	return msg;
}

Item::~Item() {
	for (auto a : attributes) {
		delete a;
	}
}
//inven

Inventory::Inventory() {

}



string Inventory::desc() {
	string dsc;
	for (auto& i : _items) {
		dsc.append("- ");
		dsc.append(i->name());
		dsc.append("\n");
	}
	return dsc;
}
void Inventory::Add(Item* itm) {
	_items.push_back(itm);
}
string Inventory::View(string itm) {
	if (this->Has(itm)) {
		for (auto& i : _items) {
			if (i->name().compare(itm) == 0) {
				return i->name() + " is " + i->desc();
			}
		}
	}
	else {
		return "Found no item named " + itm;
	}
}
void Inventory::Remove(string itm) {
	if (this->Has(itm)) {
		Item* removed = nullptr;
		for (auto& i : _items) {
			if (i->name().compare(itm) == 0) {
				removed = i;
				break;
			}
		}
		_items.remove(removed);
	}
}
bool Inventory::Has(string itm) {
	for (auto& i : _items) {
		if (i->name().compare(itm) == 0) {
			return true;
		}
	}
	return false;
}
Item* Inventory::Fetch(string itm) {
	for (auto& i : _items) {
		Item* searched = i->SearchFor(itm);
		if (searched != nullptr) {
			return searched;
		}
	}
	return nullptr;
}
Inventory::~Inventory() {
	for (auto& i : _items) {
		delete i;
	}
}

//Player implementation

Player::Player(World* w) {
	world = w;
	_location = world->locations["Hall"];
	playing = true;
}

void Player::move(const string& dir) {
	_location = _location->moveTo(dir);
}

void Player::render() {
	cout << "Player ";
	_location->render();
}

Item* Player::locateItem(string itm) {
	Item* item = this->MyInventory()->Fetch(itm);
	if (item != nullptr) {
		return item;
	}
	else {
		return MyLocation()->Inven->Fetch(itm);
	}
}

Inventory* Player::locateContainerFor(string itm) {
	if (this->MyInventory()->Has(itm)) {
		return this->MyInventory();
	}
	else {
		if (MyLocation()->Inven->Has(itm)) {
			return MyLocation()->Inven;
		}
		return nullptr;
	}
}
Inventory* Player::MyInventory() {
	return _inven;
}
Location* Player::MyLocation() {
	return _location;
}
Player::~Player() {
	delete _inven;
}
