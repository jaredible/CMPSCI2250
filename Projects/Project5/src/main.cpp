#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

static unsigned int K; // Occurrences of subsequences

class BinaryTree {
	private:
		struct TreeNode {
				string str;
				int count;
				TreeNode *left;
				TreeNode *right;
		};

		TreeNode *root;

		void insert(TreeNode *&, TreeNode *&);
		void destroySubTree(TreeNode *);
		void displayInOrder(TreeNode *) const;
	public:
		BinaryTree() {
			root = nullptr;
		}

		~BinaryTree() {
			destroySubTree(root);
		}

		void insertNode(string);
		bool searchNode(TreeNode *&, string);

		void displayInOrder() {
			displayInOrder(root);
		}
};

void BinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
	if (nodePtr == nullptr) {
		nodePtr = newNode; // Insert the node
	} else if (newNode->str < nodePtr->str) {
		insert(nodePtr->left, newNode); // Search the left branch
	} else {
		insert(nodePtr->right, newNode); // Search the right branch
	}
}

void BinaryTree::destroySubTree(TreeNode *nodePtr) {
	if (nodePtr) {
		if (nodePtr->left) destroySubTree(nodePtr->left);
		if (nodePtr->right) destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

void BinaryTree::displayInOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
		cout << nodePtr->str << ": " << setw(K - (nodePtr->str.length() - 1)) << nodePtr->count << endl;
		displayInOrder(nodePtr->right);
	}
}

void BinaryTree::insertNode(string str) {
	TreeNode *node = root;

	if (searchNode(node, str)) { // Check if node exists
		node->count++; // Increment node's count
	} else { // If node not found, create new node
		// Create a new node and store str in it
		node = new TreeNode;
		node->str = str;
		node->count = 1;
		node->left = node->right = nullptr;

		insert(root, node); // Insert the node
	}
}

bool BinaryTree::searchNode(TreeNode *&nodePtr, string str) {
	while (nodePtr) {
		if (nodePtr->str == str) return true;
		else if (str < nodePtr->str) nodePtr = nodePtr->left;
		else nodePtr = nodePtr->right;
	}

	return false;
}

int main() {
	string filename; // To hold the file name
	cout << "Text file name: ";
	getline(cin, filename); // Get the file name
	// TODO checking
	filename += ".txt"; // Append .txt to show this is a text file

	cout << "k=";
	cin >> K;
	while (K < 1 || K > UINT_MAX) { // Ensure bounds are met
		cout << "Please try again. k=";
		cin >> K;
	}
	cin.get(); // TODO

	ifstream file; // File stream object. File will contain only alphabetical characters and spaces. Ignore spaces and endlines.
	string word; // Word buffer
	string chars; // Will contain all alphabetic characters, excluding spaces, in file

	file.open(filename); // Open the file

	if (file) { // If the file was successfully opened, continue
		while (file >> word) // Get every word in file
			chars += word; // Append character group, A.K.A. a word, onto string

		file.close(); // Close the file
	} else {
		cout << filename << " could not be opened." << endl; // This is not good
	}

	if (K > chars.length()) K = chars.length(); // Ensure K is never above total amount of characters to prevent unnecessary iterations

	BinaryTree binaryTree;

	int length = chars.length();
	string s; // Node value buffer
	for (unsigned int l = 0; l < K; l++) {
		for (unsigned int i = 0; i < length - l; i++) {
			for (unsigned int j = i; j <= i + l; j++)
				s += chars[j]; // Append char onto buffer
			binaryTree.insertNode(s);
			s = ""; // Clear buffer
		}
	}

	binaryTree.displayInOrder();

	return 0;
}
