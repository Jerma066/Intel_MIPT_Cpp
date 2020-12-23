#pragma once

#include <set>
#include <iostream>

namespace trees {
	
class Standart {
public:
	Standart() = default;
	
public:
	void insertKey(int key) {
		tree.insert(key);
	}
	
	size_t getRangeQuerieCount(int first, int second);
	
private:
	using tree_iter = typename std::set<int>::iterator;
	std::set<int> tree;
};



struct Node {
	Node(int v, Node* p) : 
		value(v),
		parent(p)
	{
	}
	
	~Node() {
		delete left;
		delete right;
		//std::cout << "Node with value " << value << " had been deleted ..." << std::endl;
	}
	
	int BalanceFactor() {
		size_t lh = left ? left->height : -1;
		size_t rh = right ? right->height : -1;
		return rh - lh;
	}
	
	int value;
	Node* parent;
	Node* left = nullptr;
	Node* right = nullptr;
	size_t height = 0;
};

class AVL {
public:
	AVL() : 
		root_(nullptr) 
	{
	}
	
	~AVL() {
		delete root_;
	}
	
public:
	void insertKey(int key);
	Node* find(int key);
	size_t getRangeQuerieCount(int first, int second);
	void printFromNode(Node* curNode);
	
private:
	void InsertIntoTree(Node* NewNode, Node* CurrentRoot);
	void RecalculateHeights(Node* CurNode);
	void RightRotate(Node* CentralNode);
	void LeftRotate(Node* CentralNode);
	void RebalanceNode(Node* CurNode);
	Node* _find(int key, Node* curNode);
	Node* next(Node* me);
	
private:
	Node* root_;
};

}
