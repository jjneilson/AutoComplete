/*
 * AC.hpp
 *
 *  Created on: Nov 16, 2021
 *      Author: jackneilson
 */

#ifndef AC_HPP_
#define AC_HPP_
#include "bstTree.hpp" // You update
#include "wordInfo.hpp"
#include "Sorting.hpp" // You write
#include <iostream>
using namespace std;

class AC {
	bool verbose;
	bstTree *tree;
	string fn;
	wordInfo **wordarr;
	wordInfo **predictions;
	int currSize;
	string curr;
	Sorting sorts;

public:
	AC(string f1,bool isverbose=false);
	void readFile();
	void convertToArray();
	void convertToArray(NodeT *n);
	void printArr();
	string stripSpace(string s);
	void ui();
	void getPredictions();
	int findBeg();
	int findEnd();
};
#endif /* AC_HPP_ */
