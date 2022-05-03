#pragma once
#include <string>
#include <iostream>

class Room {
private:
	std::string name,description;
public:
	//constructor
	Room() {

	}

	Room(std::string n,std::string d) {
		//a real room
		name = n;
		description = d;
	}

	//methods

	std::string getName() {
		return name;
	}

	std::string getDescription() {
		return description;
	}
};
