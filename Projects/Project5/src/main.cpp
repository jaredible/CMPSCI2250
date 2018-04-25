#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

static int K;

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
		bool searchNode(string);
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

bool BinaryTree::searchNode(string str) {
	return searchNode(root, str);
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
	cout << "k=";
	cin >> K;

	ifstream file; // File stream object
	string filename = "chars.txt"; // To hold the file name
	string line; // Buffer
	string chars;

	file.open(filename); // Open the file

	if (file) { // If the file was successfully opened, continue
		while (file >> line)
			chars += line;

		file.close(); // Close the file
	} else {
		cout << filename << " could not be opened." << endl;
	}

	BinaryTree binaryTree;

	int length = chars.length();
	string s;
	for (auto l = 0; l < K; l++) {
		for (auto i = 0; i < length - l; i++) {
			for (auto j = i; j <= i + l; j++)
				s += chars[j];
			binaryTree.insertNode(s);
			s = "";
		}
	}

	binaryTree.displayInOrder();

	return 0;
}
