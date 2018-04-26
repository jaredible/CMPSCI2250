#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

/**
 * Sets param arr with param SIZE then fills it with
 * sequential whole numbers (0, 1, 2,..., SIZE - 1).
 * @param arr Array to initialize.
 * @param SIZE Size of param arr.
 */
void initialize_array(int arr[], int SIZE) {
	for (int i = 0; i < SIZE; i++)
		arr[i] = i;
}

/**
 * Swaps two integers.
 * @param a First integer.
 * @param b Second integer.
 */
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * Generates a random permutation of param arr in a new array then returns it.
 * @param arr Array to shuffle.
 * @param SIZE Size of param arr.
 * @return New shuffled array.
 */
int *shuffle_array(const int arr[], int SIZE) {
	if (SIZE <= 0)
		return nullptr;

	// Allocate a new array.
	int *newArray = new int[SIZE];
	int i, j;

	// Copy arr into newArray
	for (i = 0; i < SIZE; i++)
		newArray[i] = arr[i];

	// Use a different seed value so that we don't get same result each time we run this program
	srand((unsigned) time(NULL));

	for (i = SIZE - 1; i >= 0; i--) {
		// Pick a random index from 0 to i
		j = rand() % (i + 1);
		// Swap arr[i] with the element at random index
		swap(&newArray[i], &newArray[j]);
	}

	// Return a pointer to the new array.
	return newArray;
}

/**
 * Dislay every index in param arr.
 * @param arr Array to display.
 * @param SIZE Size of param arr.
 */
void print_array(const int arr[], int SIZE) {
	cout << "[ ";
	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << " ";
	cout << "]";
}

/**
 * Create new array with param arr's odd valued elements.
 * @param arr
 * @param SIZE Size of param arr.
 * @param newSize New size of newly created odd array.
 * @return New array with odd values.
 */
int *createOddArray(const int arr[], int SIZE, int &newSize) {
	if (SIZE <= 0)
		return nullptr;

	int i, j = 0;

	for (i = 0; i < SIZE; i++)
		if (arr[i] % 2 != 0)
			newSize++;

	// Allocate a new array.
	int *oddArray = new int[newSize];

	for (i = 0; i < SIZE; i++)
		if (arr[i] % 2 != 0)
			oddArray[j++] = arr[i];

	// Return a pointer to the new array.
	return oddArray;
}

/**
 * Create new array with param arr's even valued elements.
 * @param arr
 * @param SIZE Size of param arr.
 * @param newSize New size of newly created odd array.
 * @return New array with even values.
 */
int *createEvenArray(const int arr[], int SIZE, int &newSize) {
	if (SIZE <= 0)
		return nullptr;

	int i, j = 0;

	for (i = 0; i < SIZE; i++)
		if (arr[i] % 2 == 0)
			newSize++;

	// Allocate a new array.
	int *evenArray = new int[newSize];

	for (i = 0; i < SIZE; i++)
		if (arr[i] % 2 == 0)
			evenArray[j++] = arr[i];

	// Return a pointer to the new array.
	return evenArray;
}

/**
 * Sorts param arr.
 * @param arr Array to sort.
 * @param SIZE Size of param arr.
 */
void sort_array(int *arr, int SIZE) {
	int i, j, min;

	for (i = 0; i < SIZE - 1; i++) {
		min = i;
		for (j = i + 1; j < SIZE; j++)
			if (arr[j] < arr[min])
				min = j;

		swap(&arr[min], &arr[i]);
	}

	cout << "\n\nSorted ArrayFight winners were: ";
	print_array(arr, SIZE);
}

/**
 * Allocates new array with same size of largest of two param arrays. Compares
 * values at each index then puts highest in new array. 0 if nothing exists.
 * Displays the new array then sorts the array.
 * @param arr1 First array.
 * @param arr1size First array size.
 * @param arr2 Second array.
 * @param arr2size Second array size.
 */
void array_war(int *arr1, int arr1size, int *arr2, int arr2size) {
	int size = max(arr1size, arr2size);
	int *largest = new int[size];

	for (int i = 0; i < size; i++) {
		if (i >= arr1size)
			largest[i] = arr2[i];
		else if (i >= arr2size)
			largest[i] = arr1[i];
		else
			largest[i] = max(arr1[i], arr2[i]);
	}

	cout << "\n\nArrayFight winners were: ";
	print_array(largest, size);

	sort_array(largest, size);
}

int main() {
	int size;

	// Ask the user for the size of the array then loop if out of bounds
	while (true) {
		cout << "Please enter the size of the array: ";
		cin >> size;
		cout << "\n";
		if (size >= 1 && size <= 52)
			break;
		else
			cout << "Try again!\n\n";
	}

	int *array = nullptr;
	array = new int[size];
	initialize_array(array, size);

	int *shuffleArray = shuffle_array(array, size);

	cout << "Original array is: ";
	print_array(array, size);
	cout << "\n\nShuffled array is: ";
	print_array(shuffleArray, size);

	int oddArraySize = 0;
	int *oddArray = createOddArray(shuffleArray, size, oddArraySize);
	cout << "\n\nAfter call to createOddArray, oddArray is: ";
	print_array(oddArray, oddArraySize);

	int evenArraySize = 0;
	int *evenArray = createEvenArray(shuffleArray, size, evenArraySize);
	cout << "\n\nAfter call to createEvenArray, evenArray is: ";
	print_array(evenArray, evenArraySize);

	array_war(oddArray, oddArraySize, evenArray, evenArraySize);

	// free memory
	oddArray = NULL;
	delete[] oddArray;
	evenArray = NULL;
	delete[] evenArray;

	return 0;
}
