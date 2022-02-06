/*
 * AC.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: jackneilson
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>
#include <sstream>
#include "AC.hpp"
using namespace std;

AC::AC(string f1,bool isverbose) {
	srand(time(NULL));
	verbose = isverbose;
	tree = new bstTree();
	fn = f1;
	curr = "";
	currSize = 0;
	wordarr = NULL;
	predictions = NULL;
	readFile();
	convertToArray();
	if (verbose) {
		printArr();
	}
	ui();
}

void AC::ui() {
	while (curr != "-1") {
	string str;
	getline (cin,str);
	int num = -1;
	if (str >= "0" && str<="9") {
		stringstream si(str);
		si>>num;
		if (num >=0 && num<5) {
			cout << predictions[num]->word<<endl;;
			tree->insert(predictions[num]->word);
			if (verbose) {
				printArr();
			}
			curr = "";
		}
	}
	else if ((str != "\r") && (str != "")&& (str != "-1")) {
		curr += str;
		getPredictions();
	}
	else if (str != "-1"){
		//cout << "here with "<<curr<<endl;
		curr = stripSpace(curr);
		if (curr.length() > 0) {
			if (tree->insert(curr)) {
				//tree->printTreeIO();
					if (verbose) {
						cout << "inserted a new word: " << curr<<endl;
					}
				convertToArray();
				}
				if (verbose) {
					printArr();
				}
			}
			curr = "";
		}
		else {
		curr = "-1";
		}
	}
	cout << "Done!"<< endl;
}

void AC::getPredictions() {
	int x = findBeg();
	int y = findEnd();
	if (verbose) {
		cout << curr << endl;
		cout << x << " is the Beginning " << endl;
		cout << y << " is the Ending " << endl;
	}
	if (x!=-1 && y!= -1) {
		int len = y-x+1;
		//cout << "Len " << len << endl;
		if (predictions != NULL) {
			delete[] predictions;
		}
		predictions = new wordInfo *[len];
		for (int i =0; i < len; i++) {
			predictions[i] = wordarr[i+x];
		}
		if (verbose) {
			for (int i =0; i < len; i++) {
				cout << predictions[i]->word <<":"<<predictions[i]->ct <<" | ";
			}
			cout << endl;
		}
		if (len > 1) {
			int r = rand()%4;
			if (r==0) {
				if (verbose)
					cout << "Selection: "<< endl;
				sorts.selectionSort(predictions,len);
				}
			else if (r==1) {
				if (verbose)
					cout << "Insertion: " << endl;
				sorts.insertionSort(predictions,len);
			}
			else if (r==2) {
				if (verbose)
					cout << "merge: " << endl;
				sorts.mergeSort(predictions,0,len-1);
			}
			else if (r==3) {
				if (verbose)
					cout << "quickSort " << endl;
				sorts.quickSort(predictions,0,len-1);
			}
		}
		if (len>5) 
			len = 5;
		for (int i =0; i < len; i++) {
			cout << i<<":"<<predictions[i]->word <<":"<<predictions[i]->ct <<" | ";
		}
		cout << endl;
	}
}

int AC::findEnd() {
	int b =0;
	int e = currSize -1;
	int m = (e-b)/2;
	while (b<=e) {
		if (verbose) {
			cout << "B is " << b << ", E is " << e <<", "<<" m is "<<m << endl;
			cout << curr << ","<<wordarr[m]->word << ", "<<curr.compare(wordarr[m]->word.substr(0,curr.length()))<<endl;
		}
		if (curr.compare(wordarr[m]->word.substr(0,curr.length()))==0) {
			e = m;
			while (e< currSize &&(curr.compare(wordarr[e]->word.substr(0,curr.length()))==0) ) {
				e++;
			}
			e--;
			return(e);
		}
		if (curr.compare(wordarr[m]->word.substr(0,curr.length()))>0) {
			b = m+1;
		}
		else {
			e = m-1;
		}
		m = (e-b)/2 + b;
	}
	return -1;
}

int AC::findBeg() {
	int b =0;
	int e = currSize -1;
	int m = (e-b)/2;
	while (b<=e ) {
		if (verbose) {
			cout << "b is " << b << ", e is " << e <<", "<<" m is "<<m << endl;
			cout << curr << ","<<wordarr[m]->word << ", "<<curr.compare(wordarr[m]->word.substr(0,curr.length()))<<endl;
		}
		if (curr.compare(wordarr[m]->word.substr(0,curr.length()))==0) {
			b = m;
			while (b >=0 &&(curr.compare(wordarr[b]->word.substr(0,curr.length()))==0) ) {
				b--;
			}
			b++;
			return(b);
		}
		if (curr.compare(wordarr[m]->word.substr(0,curr.length()))>0) {
			b = m+1;
		}
		else {
			e = m-1;
		}
		m = (e-b)/2 + b;
	}
	return -1;
}

void AC::convertToArray() {
	if (tree->root == NULL ) {
		if (verbose)
			cout << "Empty Tree" << endl;
	}
	else {
		if (wordarr != NULL) {
			delete [] wordarr;
		}
		if (verbose)
			cout << "New Size: " << tree->size << endl;
		wordarr= new wordInfo *[tree->size];
		currSize = 0;
		convertToArray(tree->root);
	}
}

void AC::convertToArray(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		convertToArray(n->left);
		wordarr[currSize] = n->w;
		wordarr[currSize]->printWord();
		currSize++;
		convertToArray(n->right);
	}
}

void AC::printArr() {
	//cout << "HERE!! Size is " << tree->size << endl <<endl << endl;
	for (int i = 0; i < tree->size; i++) {
		cout << i << "|";
		wordarr[i]->printWord();
	}
}

string AC::stripSpace(string s) {
	unsigned int i = 0;
	while (i < s.length()) {
		if ((!isalpha(s[i])) && (s[i] != '\'') ){
			s.erase(i);
		}
		else {
			s[i]=tolower(s[i]);
		}
		i++;
	}
	return s;
}

void AC::readFile() {
	ifstream infile(fn.c_str(),ios::in); // open file
	string key = "";
	infile>> key;
	while (infile >> key) { // loop getting single characters
		//cout << key << endl;
		key = stripSpace(key);
		if (verbose)
			cout << key << endl;
		if (key.length() > 0) {
			tree->insert(key);
		}
	}
	if (verbose) {
		tree->printTreeIO();
		cout << endl;
	}
	infile.close();
}


