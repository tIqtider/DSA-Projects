/***************************************************************************************
	To compile: 	g++ -Wall -fopenmp program2.cpp -o program2

	Filename: 		program2.h
	Authors:		Taseen iqtider
	Date Created:	02/16/2025
	Last Updated:	02/28/2025
	Purpose:		To demonstrate runtime of different sort algorithms
***************************************************************************************/

// File guards
#ifndef PROGRAM2_H
#define PROGRAM2_H

// Program imports
#include <iostream>
#include <vector>             // used to create and use vectors
#include <fstream>
#include <parallel/algorithm> // used for sort function
#include <omp.h>              // used for __gnu_parallel and figma statements
#include <ctime>              // used for computing runtime
#include <thread>             //used for calculating number of logical processors on computer
#include <cstdlib>            // used for random number generation

using namespace std;

template <typename T>
void readFromFile(vector<T> &, string);
template <typename T>
void printVector(vector<T> &);
template <typename T>
void scramble(vector<T> &);


/********************************************************
 * Declare the function prototypes below for each sorting
 * function and any required helper functions here
 ********************************************************/
template <typename T>
void bubbleSort(vector<T> &);

template <typename T>
void parallelBubbleSort(vector<T> &);

template <typename T>
void parallelQuickSort(vector<T> &, int, int, int);

template <typename T>
void parallelMergeSort(vector<T> &, int, int, int);

template <typename T>
int partition(vector<T> &, int, int);

template <typename T>
void merge(vector<T> &, int, int, int);

// Close guards
#endif