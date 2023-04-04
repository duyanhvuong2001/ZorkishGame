#pragma once
#include <iostream>
#include "Player.h"
using namespace std;
class Attribute
{
public:
	virtual string Detail() = 0;
protected:
};

class Health : public Attribute {
public:
	string Detail() override;
	Health(int value);
private:
	int _value;
};

class Mana : public Attribute {
public:
	string Detail() override;
	Mana(int value);
private:
	int _value;
};