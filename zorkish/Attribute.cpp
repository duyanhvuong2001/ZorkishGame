#include "Attribute.h"
#include <string>

Health::Health(int value) {
	_value = value;
}

string Health::Detail() {
	return "Health: " + to_string(_value);
}
//Mana

Mana::Mana(int value) {
	_value = value;
}

string Mana::Detail() {
	return "Mana: " + to_string(_value);
}