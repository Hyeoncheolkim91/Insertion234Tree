#ifndef __NODE__
#define __NODE__

#include<iostream>
#include"entry.h"

using namespace std;



#define NULL 0

const int MAX_SIZE = 3; 


class Node {
	Node* child[MAX_SIZE + 1];			// make child node size 4
	Entry* entries[MAX_SIZE];				// entry size is 3
	int size;

	void init(Node* parent, Entry* entry) {
		this->parent = parent;				//initialize parent of node and set first entry
		if (entry != NULL) {
			entries[0] = entry;
			size = 1;
		}
	}
	int find(Entry* entry) {			//find position of entry
		int i = 0;
		while (i < size && entries[i]->getKey() < entry->getKey()) {
			i++;				
		}
		return i;
	}
	void promote(Entry* middle, Node* left, Node* right) {
		if (this->isFull()) {			// if node is full(3keys), then promote middle.
			Entry* middleTree = this->entries[1];
			Node* leftTree = new Node(entries[0]);		// make new node of left 
			Node* rightTree = new Node(entries[2]);		// and right to split

			leftTree->child[0] = child[0];
			leftTree->child[1] = child[1];
			rightTree->child[0] = child[2];
			rightTree->child[1] = child[3];

			Node* node = middleTree->getKey() > middle->getKey() ? leftTree : rightTree;
			node->promote(middle, left, right);

			if (this->parent == NULL) {
				this->parent = new Node();
			}
			this->parent->promote(middleTree, leftTree, rightTree);
		}
		else {
			int insertPosition = find(middle);		// after split and promote
			left->parent = this;						
			right->parent = this;					//find position and insert
			for (int j = size; j > insertPosition; j--) {
				child[j + 1] = child[j];
			}
			this->child[insertPosition] = left;
			this->child[insertPosition + 1] = right;

			put(insertPosition, middle);
		}
	}

	void put(int insertPosition, Entry* entry) {
		for (int j = size; j > insertPosition; j--) {
			entries[j] = entries[j - 1];
		}
		entries[insertPosition] = entry;
		size++;
	}

public:
	Node* parent;
	Node() {
		init(NULL, NULL);
	}
	Node(Entry* entry) {
		init(NULL, entry);
	}
	Node(Node* parent, Entry* entry) {
		init(parent, entry);
	}
	void insert(Entry* entry) {
		if (this->isFull()) {
			Entry* middle = this->entries[1];
			Node* left = new Node(entries[0]);
			Node* right = new Node(entries[2]);

			left->child[0] = child[0];
			left->child[1] = child[1];
			right->child[0] = child[2];
			right->child[1] = child[3];

			Node* node = middle->getKey() > entry->getKey() ? left : right;
			node->insert(entry);

			if (this->parent == NULL) {
				this->parent = new Node();
			}
			this->parent->promote(middle, left, right);
		}
		else {
			int insertPosition = find(entry);
			put(insertPosition, entry);
		}
	}

	bool isFull() {						// check node is full or not
		return this->size == 3;
	}
	bool isLeaf() {
		return child[0] == NULL;			//check if it is a leaf node
	}
	Node* drop(Entry* entry) {
		if (isLeaf()) {								//if it is not leaf node keep descent
			return NULL;							// to find right key
		}
		for (int i = 0; i < size; i++) {
			if (entries[i]->getKey() > entry->getKey()) {
				return child[i];
			}
		}
		return child[size];
	}
	void printInorder() {				//print values inorderly
		cout << "[";
		for (int i = 0; i < size; i++) {
			if (!isLeaf()) {
				this->child[i]->printInorder();
			}
			cout << "." << entries[i]->getKey() << ".";
		}
		if (!isLeaf()) {
			this->child[size]->printInorder();
		}
		cout << "]";
	}
};

#endif