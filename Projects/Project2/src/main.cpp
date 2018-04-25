#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct Word {
	string english;
	string piglatin;
};

Word * splitSentence(const string words, int &size);
void convertToPigLatin(Word wordArr[], int size);
void displayPigLatin(const Word wordArr[], int size);

/**
 * Returns Word structure pointer with every English member set to a word in words parameter.
 *
 * @param words String to be seperated into words.
 * @param size Size of Word structure array.
 * @return Returns Word structure pointer.
 * */
Word * splitSentence(const string words, int &size) {
	string s = words; // create a new string that isn't constant

	transform(s.begin(), s.end(), s.begin(), ::tolower); // convert string s to lowercase

	string buffer;
	stringstream ss(s); // insert string into stream
	vector<string> tokens; // create vector to hold words

	// fill tokens vector with words
	while (ss >> buffer) {
		tokens.push_back(buffer);
	}

	size = tokens.size(); // return vector size using reference parameter
	int i; // buffer index
	unsigned int j; // unsigned buffer index

	// erase non alphabet characters from each word in tokens vector
	for (i = 0; i < size; i++) {
		for (j = 0; j < tokens[i].size(); j++) {
			if (!((tokens[i][j] >= 'a' && tokens[i][j] <= 'z') || (tokens[i][j] >= 'A' && tokens[i][j] <= 'Z'))) {
				tokens[i].erase(j, j + 1);
			}
		}
	}

	Word * array = new Word[size]; // allocate dynamic Word structure array of size equal to number of words

	// store each word to English field in Word structure
	for (i = 0; i < size; i++) {
		array[i].english = tokens[i];
	}

	return array;
}

/**
 * Sets piglatin member for each Word structure in wordArr parameter.
 *
 * @param wordArr Word structure array.
 * @param size Size of wordArr parameter.
 * */
void convertToPigLatin(Word wordArr[], int size) {
	char c; // buffer character
	for (int i = 0; i < size; i++) {
		c = wordArr[i].english[0]; // get first character of English word at current index of wordArr
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') { // check if character c is a vowel
			wordArr[i].piglatin = wordArr[i].english + "way";
		} else { // if character c is a consonant
			wordArr[i].piglatin = wordArr[i].english.substr(1, wordArr[i].english.size()) + c + "ay";
		}
	}
}

/**
 * Outputs piglatin member for each Word structure in wordArr parameter.
 *
 * @param wordArr Word structure array.
 * @param size Size of wordArr parameter.
 * */
void displayPigLatin(const Word wordArr[], int size) {
	// output each word plus a space
	for (int i = 0; i < size; i++) {
		cout << wordArr[i].piglatin << " ";
	}
}

int main() {
	string sentence; // start with a string

	cout << "Please enter a string to convert to PigLatin: " << endl;
	getline(cin, sentence); // get users string they inputed
	cout << "Output: " << endl;

	int size; // initialize size variable to be used for splitSentence's parameter return
	Word * words = splitSentence(sentence, size); // obtain Word structure array

	convertToPigLatin(words, size);

	displayPigLatin(words, size);

	return 0;
}
