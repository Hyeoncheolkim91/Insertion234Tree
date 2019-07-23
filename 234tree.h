#ifndef __234TREE__
#define __234TREE__
#include"Node.h"

class Tree {
	Node* root;

public:
	Tree() {
		root = NULL;			//constructor: set root as NULL
	}
	void insert(Entry* entry) {			//if root is null, make a node and set it as root
		if (root == NULL) {
			root = new Node();
		}

		Node* current = root;				//current is root
		while (!current->isLeaf()) {					
			current = current->drop(entry);
		}

		current->insert(entry);
		if (root->parent != NULL) {
			root = root->parent;
		}
	}
	void print() {
		root->printInorder();
		cout << endl;
	}
};

#endif