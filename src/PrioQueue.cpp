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

int Tree::getLeftChildWeight() {
	return left->getWeight();
}
int Tree::getRightChildWeight() {
	return right->getWeight();
}

int Tree::getWeight() const {
	return this->weight;
}

char Tree::getChar() const {
	return this->c;
}

void Tree::setParent(Tree* t) {
	this->parent = t;
}

void Tree::printTree(vector<char>& bitString, vector<char>& input, Tree* root) const {

	/*
	 * metod för att returnera 0/1
	 * vector.push_back (function) // if(function)... == 1, push_back 1.
	 * --- Hur returneras alla nivåer?'
	 * PRINT AS YOU GO!
	 *
	 * Make sure it's breadth first !!!!!!!
	 */

	bool found = false;
	vector<char> temp = input;

	cout << "node " << this->c << " parent is " << this->parent->weight << endl;

	while(!temp.empty()) {

		if(found) {
			temp.erase(temp.begin());
			found = false;
		}



		if(this->left != NULL) {
			bitString.push_back('1');
			this->left->printTree(bitString, temp, root);
		}

		if(this->right != NULL) {
			bitString.push_back('0');
			this->right->printTree(bitString, temp, root);
		}

		if(this->right == NULL && this->left == NULL) {
			// Character found!
			if(temp.front() == this->c) {

				// Print out bitString
				for(char c : bitString) {
					cout << c;
				}

				found = true;
			}
		}
		if(this->parent != NULL) break;
		cout << "stuck on node " << this->c << endl;
	}

/*
	if(!input.empty()) {
		vector<char> temp = input;

		// True if current node is leaf
		if(this->left == NULL && this->right == NULL) {
			// Check if leaf node is the letter we're searching for
			if(temp.front() == this->c) {
				// Node found! Remove front letter and call printTree for next character
				cout << "node"<< this->c << "found!" << endl;
				temp.erase(temp.begin());
				root->printTree(bitString, temp, root);
			}
		}

		// Add 1 to bitString if left child exists
		if (this->left != NULL) {
			cout << "going left with node " << this->c << endl;
			bitString.push_back('1');
			this->left->printTree(bitString, temp, root);
		}
		// Add 0 to bitString if right child exists
		if (this->right != NULL) {
			cout << "going right..." << endl;
			bitString.push_back('0');
			this->right->printTree(bitString, temp, root);
		}
	} else {
		for (char out : bitString) {

			cout << out << endl;

		}
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

	while (q.size() > 1) {

			// Pick the top 2 elements (retrieve and remove) and create a new tree with weight ele1 + ele2
			Tree* temp1 = q.top().tree;
			q.pop();
			Tree* temp2 = q.top().tree;
			q.pop();
			int weightSum = temp1->getWeight() + temp2->getWeight();

			// Put new tree in prio queue
			TreeWrapper parent = new Tree(weightSum, temp1, temp2);
			q.push(parent);
			//q.push(TreeWrapper(new Tree(weightSum, temp1, temp2)));
			temp1->setParent(parent.tree);
			temp2->setParent(parent.tree);
			cout << parent.tree->getWeight();
		}


	//Return remaining tree in prio queue
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
	t.tree->printTree(bitString, input, t.tree);

	cout << "MAIN END" << endl;
	return 0;
}
