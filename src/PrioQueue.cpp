#include "Tree.h"


struct TreeWrapper {
	TreeWrapper() {
		tree = NULL;
	}

	TreeWrapper(Tree* t) {
		tree = t;
	}

	bool operator<(const TreeWrapper &tw) const {
		return tree->getWeight() > tw.tree->getWeight();
	}

	Tree* tree;
};

Tree::Tree(int w, char c) {
	weight = w;
	this->c = c;
	left = NULL;
	right = NULL;
}

Tree::Tree(int w, Tree* t1, Tree* t2) {
	left = t1;
	right = t2;
	weight = w;
	c = NULL;
}

int Tree::getWeight() const {
	return this->weight;
}

char Tree::getChar() const {
	return this->c;
}

void Tree::printTree(vector<char>& bitString, vector<char>& input) const {

	// Make sure it's breadth first.

	cout << "current node: " << this->getChar() << endl;
	if(this->left != NULL) {
		cout << "left node: " << this->left->getChar() << endl;
		cout << "left weight: " << this->left->getWeight() << endl;
		this->left->printTree(bitString, input);
	}
	if(this->right != NULL) {
		cout << "right node: " << this->right->getChar() << endl;
		cout << "right weight: " << this->right->getWeight() << endl;
		this->right->printTree(bitString, input);
	}






/*
	if(!input.empty()) {
		vector<char> temp = input;

		// True if current node is leaf
		if(this->left == NULL && this->right == NULL) {
			// Check if leaf node is the letter we're searching for
			if(temp.front() == this->c) {
				// Node found! Remove front letter and call printTree for next character
				temp.erase(temp.begin());
				for (char x : bitString) {
					cout << x << endl;
				}
				printTree(bitString, temp);
			}
		}

		// Add 1 to bitString if left child exists
		if (this->left != NULL) {
			cout << "going left..." << endl;
			bitString.push_back(1);
			this->left->printTree(bitString, temp);
		}
		// Add 0 to bitString if right child exists
		if (this->right != NULL) {
			cout << "going right..." << endl;
			bitString.push_back(0);
			this->right->printTree(bitString, temp);
		}
	} else {
		//for (vector<char>::iterator it = bitString.begin(); it != bitString.end(); ++it) {
		for (char out : bitString) {
			//cout << *it;
			cout << out << endl;

		}
		cout << "heureka! " << endl;
	}*/
}

TreeWrapper createTree(vector<char>& input) {

	vector<char> usedElements;
	priority_queue<TreeWrapper> q;

	for (unsigned int i = 0; i < input.size(); i++) {

		char c = input[i];

		if(!(find(usedElements.begin(), usedElements.end(), c) != usedElements.end())) {

			int counter = 1;

			for (unsigned int j = i+1; j < input.size(); j++) {
				char d = input[j];
				if (d == c) counter++;
			}

			usedElements.push_back(c);

			// Create tree for each letter
			q.push(TreeWrapper(new Tree(counter, c)));
		}
	}

	while(q.size() > 1 ){

		// Pick the top 2 elements (retrieve and remove) and create a new tree with weight ele1 + ele2
		Tree *temp1 = new Tree(q.top().tree->getWeight(), q.top().tree->getChar());
		q.pop();
		Tree *temp2 = new Tree(q.top().tree->getWeight(), q.top().tree->getChar());
		q.pop();
		int weightSum = temp1->getWeight() + temp2->getWeight();

		// Put new tree in prio queue
		q.push(TreeWrapper(new Tree(weightSum, temp1, temp2)));
	}

	//Return remaining tree in prio queue
	cout << "Weight of top: " << q.top().tree->getWeight() << endl;
	return q.top();
}

int main() {

	cout << "MAIN START" << endl;

	vector<char> input;
	input.push_back('a');
	input.push_back('b');
	input.push_back('b');
	input.push_back('a');
	input.push_back('c');

	TreeWrapper t = createTree(input);
	vector<char> bitString = {};
	t.tree->printTree(bitString, input);
	cout << "MAIN END" << endl;
	return 0;
}

/*
 * Problem:
 */
