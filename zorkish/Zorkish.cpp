// Zorkish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "States.h"
#include "Player.h"
#include "Graph.h"
#include <fstream>
#include <vector>
#include "Command.h"
#include "Manager.h"
using namespace std;
//function for splitting string


int main(int agvc, char* argv[])
{
	/*Item* bag = new Item("bag", "solid");
	Item* paper = new Item("paper", "soft");
	Item* sword = new Item("sword", "wielded");
	bag->inven.Add(paper);
	paper->inven.Add(sword);
	Item* searched = bag->SearchFor("sword");
	cout << searched->name() << endl;
	delete bag;*/
	GameManager manager;
	while (true) {
		manager.render();
		manager.update();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
