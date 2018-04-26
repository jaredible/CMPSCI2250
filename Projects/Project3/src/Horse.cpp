#include "Horse.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Horse::Horse(string name, string rider) {
	this->name = name;
	this->rider = rider;

	srand((unsigned) time(NULL));
	sendToGate();
}

Horse::~Horse() {
}

void Horse::runASecond() {
	distanceTraveled += maxRunningDistPerSecond;
}

void Horse::sendToGate() {
	maxRunningDistPerSecond = 1 + rand() % 101;
	distanceTraveled = 0;
}

void Horse::displayHorse(int goalLength) {
	cout << "|";
	for (int i = 0; i < DISPLAY_RACE_DIST; i++) {
		if (i == (distanceTraveled * DISPLAY_RACE_DIST) / goalLength) {
			cout << ">";
		} else {
			cout << " ";
		}
	}
	cout << "|";

	if (distanceTraveled >= goalLength) {
		cout << ">";
	} else {
		cout << " ";
	}

	cout << " " << name << ", " << "ridden by " << rider << endl;
}

void Horse::win() {
	racesWon++;
}
