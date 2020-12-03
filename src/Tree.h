#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <queue>
#include <string>
#include <iostream>
using namespace std;



class Tree {
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
public:
	Tree(int w, char c);
	Tree(int w, Tree* t1, Tree* t2);
	~Tree();
	int getWeight() const;
	void printTree(priority_queue<TreeWrapper> tree) const;
	char getChar() const;
private:
	Tree* left;
	Tree* right;
	int weight;
	char c;
};



#endif
