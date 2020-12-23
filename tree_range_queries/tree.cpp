#include "tree.h"

namespace trees {
// Standart tree
size_t Standart::getRangeQuerieCount(int first, int second) {
	size_t surplus = 0; 
	
	if(first > second) {
		auto tmp = second;
		second = first;
		first = tmp;
	}
	
	tree_iter fi = tree.lower_bound(first);
	if(*fi == first) {surplus++;}
	
	tree_iter si = tree.upper_bound(second);
	if(*(--si) == second) {surplus++;}
	
	return (std::distance(fi, ++si) - surplus);
}

void AVL::insertKey(int key) {	
	Node* NewNode = new Node(key, nullptr);
	if(!root_) {
		root_ = NewNode;
	}
	else {
		InsertIntoTree(NewNode, root_);
		RecalculateHeights(NewNode);
		RebalanceNode(NewNode->parent);
	}
}

Node* AVL::find(int key) {
	return _find(key, root_);
}

Node* AVL::_find(int key, Node* curNode) {
	if(!curNode) 
		curNode = root_;
	
	if(curNode->value == key) {
		return curNode;
	} 
	else if(key > curNode->value) {
		if(curNode->right)
			return _find(key, curNode->right);
	}
	else if(key < curNode->value) {
		if(curNode->left)
			return _find(key, curNode->left);
	} 
	
	return curNode;
}

void AVL::InsertIntoTree(Node* NewNode, Node* CurrentRoot) {
	if(NewNode->value == CurrentRoot->value) {
		return;
	}
	
	if(NewNode->value > CurrentRoot->value) {
		if(CurrentRoot->right) {
			InsertIntoTree(NewNode, CurrentRoot->right);
		}
		else {
			CurrentRoot->right = NewNode;
			NewNode->parent = CurrentRoot;
		}

		return;
	}
		
	if(NewNode->value < CurrentRoot->value) {
		if(CurrentRoot->left) {
			InsertIntoTree(NewNode, CurrentRoot->left);
		}
		else {
			CurrentRoot->left = NewNode;
			NewNode->parent = CurrentRoot;
		}
		
		return;
	}
}

void AVL::RecalculateHeights(Node* CurNode) {
	if(!(CurNode->parent)) {
		return;
	}
	
	if(CurNode->parent->height == CurNode->height) {
		CurNode->parent->height++;
	} 
	else {
		return;
	}
	
	RecalculateHeights(CurNode->parent);
}

void AVL::RightRotate(Node* CentralNode) {
	if(!CentralNode || !root_)
		return;
		
	Node* leftChild = CentralNode->left;
	Node* parent = CentralNode->parent;
	
	if(!leftChild)
		return;
	
	if(CentralNode == root_)
		root_ = leftChild;
	
	CentralNode->parent = leftChild;
	CentralNode->left = leftChild->right;
	
	if(leftChild->right)
		leftChild->right->parent = CentralNode;
		
	leftChild->right = CentralNode;
	leftChild->parent = parent;
	
	if(parent)
	{
		if(parent->left == CentralNode)
			parent->left = leftChild;
		else
			parent->right = leftChild;
	}
}

void AVL::LeftRotate(Node* CentralNode) {
	if(!CentralNode || !root_)
		return;
		
	Node* rightChild = CentralNode->right;
	Node* parent = CentralNode->parent;
	
	if(!rightChild)
		return;
		
	if(CentralNode == root_)
		root_ = rightChild;
		
	CentralNode->parent = rightChild;
	CentralNode->right = rightChild->left;
	
	if(rightChild->left)
		rightChild->left->parent = CentralNode;	
		
	rightChild->left = CentralNode;
	rightChild->parent = parent;

	if(parent) {
		if(parent->left == CentralNode)
			parent->left = rightChild;
		else
			parent->right = rightChild;
	}
}

void AVL::RebalanceNode(Node* CurNode) {
	if(!CurNode) {
		return;
	} 
	
	Node* old_parent = CurNode->parent;
	
	int b_factor = CurNode->BalanceFactor();
	if(b_factor > 1) {
		if(CurNode->right && CurNode->right->left && 
		   (CurNode->right->left->left || CurNode->right->left->right)) 
		{
			RightRotate(CurNode->right);
			LeftRotate(CurNode);
		}
		else {
			LeftRotate(CurNode);
		}
	} 
	else if(b_factor < -1) {
		if(CurNode->left && CurNode->left->right && 
		   (CurNode->left->right->left || CurNode->left->right->right)) 
		{
			LeftRotate(CurNode->right);
			RightRotate(CurNode);
		}
		else {
			RightRotate(CurNode);
		}
	}
	
	RebalanceNode(old_parent);
}

Node* AVL::next(Node* me) {   
	if(me->right != nullptr){ 
        me = me->right;
        while (me->left != nullptr) {
            me = me->left;
        }
        return me;
	}
	else{
		if (me->parent == nullptr) {
            return nullptr;
        }
        
		if(me->parent->left == me){
			return me->parent;
		}
		else {
			Node* result = me->parent;
			while (result->parent && result != result->parent->left){
				result = result->parent;
			}
			if (result->parent == nullptr){
				return nullptr;
			}
			return result->parent;
		}
	}
}

void AVL::printFromNode(Node* curNode) {	
	std::cout << "{ ";
	while (curNode) {
		std::cout << curNode->value <<  " ";
		curNode = next(curNode);
	}
	
	std::cout << "}" << std::endl;
}

size_t AVL::getRangeQuerieCount(int first, int second) {
	size_t surplus = 0; 
	
	if(first > second) {
		auto tmp = second;
		second = first;
		first = tmp;
	}
	
	Node* fi = find(first);
	if(fi->value < first) {surplus++;}
		
	Node* si = find(second);
	if(si->value > second) {surplus++;}
	
	size_t dist = 1;
	while (fi != si) {
		dist++;
		fi = next(fi);
	}
	
	return (dist - surplus);
}

}
