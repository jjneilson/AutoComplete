/*
 * bst.hpp
 *
 *  Created on: Oct 13, 2021
 *      Author: 13027
 */

#ifndef bstTree_HPP_
#define bstTree_HPP_

#include <iostream>
#include "NodeT.hpp"
#include <stdlib.h>

using namespace std;

class bstTree {
	friend class NodeT;
	friend class AC;
	NodeT *root;
	int size;

public:

	bstTree();
	bstTree(string f);
	bool insert(string s);
	NodeT* find(string l, string f);
	void printTreeIO();
	void printTreeIO(NodeT *n);
	void printTreePre();
	void printTreePre(NodeT *n);
	void printTreePost();
	void printTreePost(NodeT *n);
	void clearTree();
	void clearTree(NodeT *tmp);
	NodeT* removeNoKids(NodeT *tmp);
	NodeT* removeOneKid(NodeT *tmp, bool leftFlag);
	NodeT* remove(string f, string l);
	void setHeight(NodeT *n);
	~bstTree();
	/******************New for AVL ***************************/
	//int getBalance(bstNode *tmp);
	//NodeT *rotateRight(TNode *tmp);
	//NodeT *rotateLeft(TNode *tmp);
};

#endif /* bst_HPP_ */
