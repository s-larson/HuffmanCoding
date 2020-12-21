#include "Tree.h"


struct TreeWrapper {
	TreeWrapper() {
		this->tree = NULL;
	}

	TreeWrapper(Tree* t) {
		this->tree = t;
	}

	bool operator<(const TreeWrapper &tw) const {
		return this->tree->getWeight() > tw.tree->getWeight();
	}

	Tree* tree;
};

Tree::Tree(int w, char c) {
	this->weight = w;
	this->c = c;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}

Tree::Tree(int w, Tree* t1, Tree* t2) {
	this->left = t1;
	this->right = t2;
	this->weight = w;
	this->c = NULL;
	this->parent = NULL;
}

int Tree::getWeight() const {
	return this->weight;
}

char Tree::getChar() const {
	return this->c;
}

void Tree::printTree(vector<char>& bitString) const {

	vector<char> temp;

	// There exists a child to the left. Add 1 and recursively call printTree
	if(this->left != NULL) {
		temp = bitString;
		temp.push_back('1');
		this->left->printTree(temp);
	}

	// There exists a child to the right. Add 0 and recursively call printTree
	if(this->right != NULL) {
		temp = bitString;
		temp.push_back('0');
		this->right->printTree(temp);
	}

	// Leaf node reached. Print out bitString
	if(this->right == NULL && this->left == NULL) {
		temp = bitString;
		string completePath(temp.begin(), temp.end());
		cout << completePath << ": " << this->getChar() << "\n";
	}
}

TreeWrapper createTree(vector<char>& input) {

	// Used for storing trees and already counted characters
	vector<char> usedElements;
	priority_queue<TreeWrapper> q;

	// Count character occurances
	for (unsigned int i = 0; i < input.size(); i++) {

		char c = input[i];
		int counter = 1;

		// Only start counting if the character has not been already counted
		if(!(find(usedElements.begin(), usedElements.end(), c) != usedElements.end())) {

			// Search through the rest of the input string (from current + 1 -> last)
			for (unsigned int j = i+1; j < input.size(); j++) {
				char d = input[j];
				if (d == c) counter++;
			}

			// Mark the character as counted and create a single node tree (weight based on counter)
			usedElements.push_back(c);
			q.push(TreeWrapper(new Tree(counter, c)));
		}
	}

	// Combine the single node trees until only one tree remain in the priority queue
	while (q.size() > 1) {

		// Pick the top 2 elements (retrieve and remove) and create a new tree with combined weights
		Tree* temp1 = q.top().tree;
		q.pop();
		Tree* temp2 = q.top().tree;
		q.pop();
		int weightSum = temp1->getWeight() + temp2->getWeight();

		// Put new tree in the back of the priority queue
		q.push(TreeWrapper(new Tree(weightSum, temp1, temp2)));
	}

	//Return complete tree
	return q.top();
}

int main() {

	// Create input vector and fill with elements
	vector<char> input;
	input.push_back('a');
	input.push_back('b');
	input.push_back('b');
	input.push_back('a');
	input.push_back('c');
	input.push_back('k');
	input.push_back('p');

	// Create tree structure and print content
	TreeWrapper t = createTree(input);
	vector<char> bitString = {};
	t.tree->printTree(bitString);

	return 0;
}
