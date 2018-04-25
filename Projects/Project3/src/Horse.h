#include <string>
using namespace std;

#ifndef HORSE_H
#define HORSE_H

class Horse {
private:
	static const int DISPLAY_RACE_DIST = 50;
	string name;
	string rider;
	int maxRunningDistPerSecond;
	int distanceTraveled;
	int racesWon = 0;
public:
	Horse(string, string);
	~Horse();
	void runASecond();
	void sendToGate();
	void displayHorse(int);
	void win();

	string getName() const {
		return name;
	}

	int getDistanceTraveled() const {
		return distanceTraveled;
	}

	int getRacesWon() const {
		return racesWon;
	}
};

#endif
