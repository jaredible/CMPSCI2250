#include <iostream>
#include "Horse.h"

#define MIN_NUM_HORSES 2
#define MIN_RACE_DIST 100

// driver program
int main() {
	int i;

	// input # of horses and validate is # and >= MIN_NUM_HORSES
	int numHorses;
	cout << "How many horses are in the race: ";
	while (!(cin >> numHorses && numHorses >= MIN_NUM_HORSES)) {
		cin.clear();
		cin.ignore(512, '\n');
		// re-prompt user
		cout << "Need at least " << MIN_NUM_HORSES << " horses to begin a race: ";
	}

	// allocate horse objects
	Horse *horses[numHorses];

	// input horse name and rider name for all horses
	string name;
	string rider;
	for (i = 0; i < numHorses; i++) {
		cout << "Please give me the name of horse " << (i + 1) << ": ";
		cin >> name;
		cout << "Please give me the name of rider " << (i + 1) << ": ";
		cin >> rider;
		horses[i] = new Horse(name, rider);
	}

	// input race distance and validate is # and >= MIN_RACE_DIST
	int raceDist;
	cout << "Please enter the distance of the race: ";
	while (!(cin >> raceDist && raceDist >= MIN_RACE_DIST)) {
		cin.clear();
		cin.ignore(512, '\n');
		// re-prompt user
		cout << "Race distance needs to be a minimum of " << MIN_RACE_DIST << ": ";
	}

	// current # of races
	int numRaces = 0;
	bool someHorseWon = false;

	// races loop
	do {
		// reset all horses
		for (i = 0; i < numHorses; i++) {
			horses[i]->sendToGate();
		}

		// display all horses starting position
		cout << "\nThe start!" << endl;
		for (i = 0; i < numHorses; i++) {
			horses[i]->displayHorse(raceDist);
		}
		cout << "\nAre you ready for the next second(y/n)?: ";
		cin.ignore();

		// check if user wants to start race
		if (cin.get() == 'y') {
			// seconds loop
			do {
				// run a second, check if any horse won, display horse, ask user to update race by 1 second
				Horse *h;
				for (i = 0; i < numHorses; i++) {
					h = horses[i];

					// run second for horse
					h->runASecond();

					// check if any horse won
					if (h->getDistanceTraveled() >= raceDist) {
						someHorseWon = true;
					}

					// display horse on track and horse info.
					h->displayHorse(raceDist);
				}

				if (someHorseWon) {
					break;
				}

				// ask user to update another second
				cout << "\nAre you ready for the next second(y/n)?: ";
				cin.ignore();
			} while (cin.get() == 'y');
		}

		if (someHorseWon) {
			// TODO: check for ties
			// get horse that actually won
			int horseWinnerIndex = 0;
			int maxDistance = 0;
			Horse *h;
			for (i = 0; i < numHorses; i++) {
				h = horses[i];

				if (h->getDistanceTraveled() > maxDistance) {
					maxDistance = h->getDistanceTraveled();
					horseWinnerIndex = i;
				}
			}

			horses[horseWinnerIndex]->win();
		}

		if (someHorseWon) {
			someHorseWon = false;
			numRaces++;
		}

		// display race info.
		for (i = 0; i < numHorses; i++) {
			cout << horses[i]->getName() << " has won " << horses[i]->getRacesWon() << "/" << numRaces << " races." << endl;
		}

		// ask user for another race
		cout << "Do you wish to continue(y/n)?: ";
		cin.ignore();
	} while (cin.get() == 'y');

	// deallocate all horse objects
	for (i = 0; i < numHorses; i++) {
		delete horses[i];
	}

	return 0;
}
