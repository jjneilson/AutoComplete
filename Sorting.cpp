/*
 * Sorting.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: jackneilson
 */

/* Sorting Algorithm Questions
 * 
 * 1. The ONLY place new nodes are created is in the Tree code. Equally, you ONLY update the counts in the Tree code, yet
 *    these nodes and their updates show up in my array of predictions. How is this possible?
 *	  The AC class is a friend class of each Tree Node and has access to each attribute of each node and can therefore put
 *	  the counts in the array of predictions.
 *    
 * 2. In findBeg and findEnd, the code follows a certain relatively efficient algorithm. What is the name of the algorithm?
 * 	  Based on a normal find algorithm used in linked lists.
 */



#include "Sorting.hpp"
#include <iostream>
using namespace std;

Sorting::Sorting(){
	
}

void Sorting::insertionSort(wordInfo *arr[], int len){
	wordInfo *current = NULL;
	wordInfo *temp = NULL;
	for(int i = 1; i<len;i++){
		current = arr[i];
		for(int j = 1; i >= j; j++){
			if(current->word < arr[i-j]->word){
				temp = arr[i-j];
				arr[i-j] = current;
				arr[i] = temp;
			}
		}
	}	
}

void Sorting::selectionSort(wordInfo *arr[], int len){
	wordInfo *min = NULL;
	int small = 0;
	for(int i = 0; i < len; i++){
		min = arr[i];
		small = 0;
		for(int j = i+1; j < len; j++){
			if(min->word > arr[j]->word){
				min = arr[j];
				small = j;
			}
		}
		arr[small] = arr[i];
		arr[i] = min;
	}
}

void Sorting::quickSort(wordInfo *arr[], int beg, int end){
	if(beg < end){
		int part = partition(arr, beg, end);	
		quickSort(arr, beg, part-1);
		quickSort(arr, part+1, end);
	}
}

int Sorting::partition(wordInfo *arr[],int beg,int end){ // used by quickSort
	wordInfo *temp = NULL;
	wordInfo *pivot = arr[end];
	int i = beg-1;
	for(int j = beg; j <= end-1; j++)
	{
		if (arr[j]->word < pivot->word)
		{
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[i+1];
	arr[i+1] = arr[end];
	arr[end] = temp;
	return i+1;
}

void Sorting::mergeSort(wordInfo *arr[],int l1,int l2){
	if(l2 > l1){
		int m = l1 + (l2-l1)/2;
		mergeSort(arr,l1,m);
		mergeSort(arr,m+1,l2);
		merge(arr,l1,m,l2);
	}
}

void Sorting::merge(wordInfo *arr[], int l, int m, int r){ // used by mergeSort
	wordInfo *temp[r-l+1];
	int i = l;
	int j = m+1;
	int k = 0;
	while(i <= m && j<= r){ //sorting the values into temp array.
		if(arr[i]->word <= arr[j]->word){
			temp[k] = arr[i];
			i++;
			k++;
		}
		else{
			temp[k] = arr[j];
			i++;
			j++;
		}
	}
	while(i <= m){ // present in case j > r before rest of array is copied
		temp[k] = arr[i];
		i++;
		k++;
	}
	while(j <= r){ // present in case i > m before rest of array is copied
		temp[k] = arr[j];
		i++;
		j++;
	}
	for(int i = l;i <= r;i++){ // readding the value to original array in correct positions
		arr[i] = temp[i-l];
	}
	
	
	
	
}