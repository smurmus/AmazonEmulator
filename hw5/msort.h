#ifndef MSORT_H
#define MSORT_H
#include <string>
#include <cstring>
#include "derived_datastore.h"

using namespace std;

template <class T, class Comparator>
	void mergeSort (vector<T>& myArray, Comparator comp){
		msort(myArray, comp, 0, myArray.size() - 1);
	}

template<class T, class Comparator>
void msort(vector<T>& v, Comparator c, int start, int end){ 
	int mid; 

	if(start < end){
		mid = (start + end)/2;

	//if(!c(v[left], v[mid])){	
		msort(v, c, start, mid);
		msort(v, c, mid + 1, end);		
		merge(v, c, start, end, mid);
	}
}

template<class T, class Comparator>
void merge(vector<T>& a, Comparator c, int s, int e, int m) {
	int i = s, j = m+1, k =0;
	//vector<T> temp;
	T *temp = new T[e-s+1]; //theta(1)
	while(i <= m || j <= e) { //theta(r-l)
		if(i <= m && (j > e || c(a[i], a[j]))) { //makes stable
			//temp.push_back(a[i]);
			temp[k] = a[i];
			i++;
			k++;
		}
		else {
			//temp.push_back(a[j]);
			temp[k] = a[j];
			j++;
			k++;
		}//theta(1)
	}
	for(int k = 0; k < e - s + 1; k++)
		a[k+s] = temp[k]; //theta(r-l)
}

#endif