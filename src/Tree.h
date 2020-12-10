#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;



class Tree {

public:
	Tree(int w, char c);
	Tree(int w, Tree* t1, Tree* t2);
	~Tree();
	int getWeight() const;
	void printTree(vector<char>& bitString, vector<char>& input, Tree* root) const;
	char getChar() const;
	int getRightChildWeight();
	int getLeftChildWeight();
	void setParent(Tree* t);
//private:
	Tree* left;
	Tree* right;
	Tree* parent;
	int weight;
	char c;
};



#endif
