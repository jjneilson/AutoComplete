/*
 * Sorting.hpp
 *
 *  Created on: Nov 16, 2021
 *      Author: jackneilson
 */

#ifndef SORTING_HPP_
#define SORTING_HPP_
#include "wordInfo.hpp"
#include <iostream>
using namespace std;

class Sorting {
	friend class AC;
	
	
public:
	Sorting();
	void insertionSort(wordInfo *arr[], int len);
	void selectionSort(wordInfo *arr[], int len);
	void quickSort(wordInfo *arr[], int beg, int end);
	int partition(wordInfo *arr[],int beg,int end); // used by quickSort
	void mergeSort(wordInfo *arr[],int l1,int l2);
	void merge(wordInfo *arr[], int l, int m, int r); // used by mergeSort
};



#endif /* SORTING_HPP_ */
