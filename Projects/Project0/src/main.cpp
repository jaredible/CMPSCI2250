#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <climits>
using namespace std;

#define NUM_SOLUTIONS 5
#define MIN 1
#define MAX 1000

/**
 * Returns the smallest absolute difference between parameter
 * guess and any member of the solutions array.
 *
 * @param solutions The array filled with random integers.
 * @param SIZE The size of the array.
 * @param guess The users current guess.
 * @return Closest absolute distance
 * */
int distanceToClosest(const int solutions[], int SIZE, int guess) {
	int smallest = INT_MAX;
	int distance;
	for (int i = 0; i < SIZE; i++) {
		distance = abs(solutions[i] - guess);
		if (distance < smallest)
			smallest = distance;
	}
	return smallest;
}

/**
 * Fills the specified array with random values from MIN to MAX inclusively.
 *
 * @param arr The array to fill.
 * @param SIZE The size of the array.
 * */
void fillRand(int arr[], int SIZE) {
	srand((unsigned) time(NULL));
	for (int i = 0; i < SIZE; i++)
		arr[i] = MIN + rand() % (MAX - MIN + 2);
}

/**
 * Sorts the specified array in ascending order.
 *
 * @param arr The array to sort.
 * @param SIZE The size of the array.
 * */
void sortArr(int arr[], int SIZE) {
	// Implements bubble sort
	int i, j, temp;
	for (i = 0; i < SIZE - 1; i++) {

		// Last i elements are already in place
		for (j = 0; j < SIZE - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/**
 * Returns true when specified guess is inclusively within MIN and MAX
 *
 * @param guess The users current guess.
 * @return Guess is between MIN and MAX inclusively.
 * */
bool inRange(int guess) {
	if (guess < MIN || guess > MAX) {
		cout << "Sorry but your guess is out of range, try again!\n\n";
		return false;
	}
	return true;
}

int main() {
	int solutions[NUM_SOLUTIONS];
	bool first = true;
	int guess;
	int distance;
	int prevDistance;
	bool guessedSameNumber = false;

	fillRand(solutions, NUM_SOLUTIONS);
	sortArr(solutions, NUM_SOLUTIONS);

	cout << "Hello, please try to guess one of my numbers from " << MIN << " to " << MAX << ".\n\n";

	while (true) {
		cout << "Please make a";
		if (guessedSameNumber)
			cout << "nother";
		guessedSameNumber = false;
		cout << " guess: ";

		// Assuming is an integer
		cin >> guess;
		cout << "\n";

		if (!inRange(guess))
			continue;

		if (first) {
			distance = distanceToClosest(solutions, 5, guess);

			if (distance == 0)
				break;
			else
				cout << "I am sorry, that is incorrect!";

			cout << "\n\n";
		} else {
			prevDistance = distance;
			distance = distanceToClosest(solutions, 5, guess);

			if (distance == 0)
				break;
			else if (prevDistance == distance) {
				guessedSameNumber = true;
				continue;
			} else if (prevDistance > distance)
				cout << "Getting warmer!";
			else
				cout << "Getting colder!";

			cout << "\n\n";
		}

		first = false;
	}

	cout << "Success!";

	return 0;
}
