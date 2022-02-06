/*
 * wordInfo.hpp
 *
 *  Created on: Nov 16, 2021
 *      Author: jackneilson
 */

#ifndef WORDINFO_HPP_
#define WORDINFO_HPP_


#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class wordInfo {
	friend class NodeT;
	friend class bstTree;
	friend class Sorting;
	friend class AC;
	string word;
	int ct;
	
public:
	wordInfo(string w, int x);
	wordInfo(string w);
	wordInfo();
	void printWord();
};

#endif /* WORDINFO_HPP_ */
