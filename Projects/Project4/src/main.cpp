#include <iostream>
#include <string>
#include <map>
using namespace std;

class Stack {
	private:
		struct Node {
				char character;
				int lineNumber;
				int charIndex;
				Node* next;
		};
		Node* top;
	public:
		Stack() {
			top = nullptr;
		}
		~Stack();
		void push(char, int, int);
		void pop(char&, int&, int&);
		bool empty();
};

Stack::~Stack() {
	Node* nodePtr = nullptr, *nextNode = nullptr;

	// Position nodePtr at the top of the stack.
	nodePtr = top;

	// Traverse the list deleting each node.
	while (nodePtr != nullptr) {
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

void Stack::push(char character, int lineNumber, int charIndex) {
	Node* newNode = nullptr; // Pointer to a new node

	// Allocate a new node and store variables there
	newNode = new Node;
	newNode->character = character;
	newNode->lineNumber = lineNumber;
	newNode->charIndex = charIndex;

	if (empty()) { // If there are no nodes in the list make newNode the first node.
		top = newNode;
		newNode->next = nullptr;
	} else { // Otherwise, insert newNode before top.
		newNode->next = top;
		top = newNode;
	}
}

void Stack::pop(char &character, int &lineNumber, int &charIndex) {
	Node *temp = nullptr; // Temporary pointer

	if (!empty()) { // pop values off top of stack
		character = top->character;
		lineNumber = top->lineNumber;
		charIndex = top->charIndex;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool Stack::empty() {
	return top == nullptr;
}

int main() {
	// while text is being read, use stack to test for matching "blocks"
	// while accepting input, keep track of how many lines you have received already
	// to do the test, as you receive a line of text, start processing each line

	// TO PROCESS EACH LINE
	// ignore all non-delimiters
	// if left delimiter received, push it onto stack along with line number and character in that line that the delimiter was found
	// if right delimiter received, pop top of stack and compare the characters. If left matches with a right delimiter, then that is fine and continue processing. If they DO NOT MATCH, output an error message showing the mismatch

	map<char, char> bracketPairs = {	//
			make_pair(')', '('),	//
			make_pair('}', '{'),	//
			make_pair(']', '[')	//
			};

	char referencedCharacter;
	int referencedLineNumber, referencedCharIndex;

	Stack bracketStack;
	string currentLine;
	int lineNumber = 1;
	int charIndex;

	do {
		getline(cin, currentLine);

		charIndex = 0;
		for (auto it = currentLine.begin(); it < currentLine.end(); ++it, ++charIndex) {
			switch (*it) {
				case '(':
				case '{':
				case '[':
					bracketStack.push(*it, lineNumber, charIndex);
					break;
				case ')':
				case '}':
				case ']':
					if (bracketStack.empty()) {
						cout << "Right delimiter " << *it << " had no left delimiter found at line " << lineNumber << ", char " << charIndex << endl;
					}

					bracketStack.pop(referencedCharacter, referencedLineNumber, referencedCharIndex);

					if (referencedCharacter != bracketPairs[*it]) {
						cout << "Mismatched delimiter " << referencedCharacter << " found at line " << referencedLineNumber << ", char " << referencedCharIndex << " does not match " << *it << " found at line " << lineNumber << ", char " << charIndex << endl;
					}

					break;
				default:
					continue;
			}
		}

		++lineNumber;
	} while (currentLine != "DONE");

	while (!bracketStack.empty()) {
		bracketStack.pop(referencedCharacter, referencedLineNumber, referencedCharIndex);
		cout << "Left delimiter " << referencedCharacter << " at line " << referencedLineNumber << ", char " << referencedCharIndex << " had no right delimiter." << endl;
	}

	return 0;
}
