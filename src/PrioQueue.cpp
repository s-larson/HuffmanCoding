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

void Tree::printTree(priority_queue<TreeWrapper> tree) const {
	cout << tree.top().tree->getWeight();
}

priority_queue<TreeWrapper> createTree(unsigned char input[]) {

	priority_queue<TreeWrapper> q;

	// Count character occurance and save in array 'count'
	int count[256] = {0};
	for(int i = 0; input[i] != '\0'; i++) {
		count[input[i]]++;
	}
	// Create tree for each character and insert in priority queue
	for(int i = 0; i < sizeof(count); i++){
		if(count[i] > 0) q.push(TreeWrapper(new Tree(count[i], input[i])));
	}

	while(q.size() > 1 ){

		// Pick the top 2 elements (retrieve and remove) and create a new tree with weight ele1 + ele2
		Tree *temp1 = new Tree(q.top().tree->getChar(), q.top().tree->getWeight());
		q.pop();
		Tree *temp2 = new Tree(q.top().tree->getChar(), q.top().tree->getWeight());
		q.pop();
		int weightSum = temp1->getWeight()+temp2->getWeight();

		// Put new tree in prio queue
		q.push(TreeWrapper(new Tree(weightSum, temp1, temp2)));
	}

	//Return remaining tree in prio queue
	return q;
}

int main() {

	unsigned char input[] = "aabc";

	priority_queue<TreeWrapper> result = createTree(input);

	result.top().tree->printTree(result);


	return 0;
}

/*
 * Problem:
 * - createTree och printTree tar emot felaktiga(?) parametrar. Vad exakt ska matas in/ut ur funktionerna?
 * Idéer: flytta så mkt som möjligt till Tree klassen och håll queuen lokalt
 *
 * To-do:
 * -ta bort struct ur Tree klassen
 * -skapa print funktionen - encoda trädet med 0 = vänster, 1 = höger
 */
