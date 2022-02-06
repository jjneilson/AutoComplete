/*
 * wordInfo.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: jackneilson
 */

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "wordInfo.hpp"
using namespace std;

wordInfo::wordInfo(string w, int x) {
	word = w;
	ct = x;
}

wordInfo::wordInfo(string w) {
	word = w;
	ct = 1;
}

wordInfo::wordInfo() {
	word = "";
	ct =0;
}

void wordInfo::printWord() {
	cout << word << ":" << ct << endl;
}


