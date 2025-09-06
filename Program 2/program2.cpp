/***************************************************************************************
    To compile: 	g++ -Wall -fopenmp program2.cpp -o program2

    Filename: 		program2.cpp
    Authors:		Taseen Iqtider
    Date Created:   02/16/2025
    Last Updated:   02/28/2025
    Purpose:		To demonstrate runtime of different sort algorithms
***************************************************************************************/

// Program imports
#include <iostream>
#include <vector>             // used to create and use vectors
#include <fstream>
#include <parallel/algorithm> // used for sort function
#include <omp.h>              // used for __gnu_parallel and figma statements
#include <ctime>              // used for computing runtime
#include <thread>             //used for calculating number of logical processors on computer
#include <cstdlib>            // used for random number generation
#include "program2.h"

using namespace std;

int main()
{
    // Variable Definitions

    vector<int> nums;     // Vector for holding the numbers to be sorted
    vector<string> words; // Vector for holding the words to be sorted

    // variables for calculating runtime
    clock_t tStart, tStop; // Used for computing runtime
    double compute_time_p;

    // determine number of logical processors on your computer
    const auto processor_count = thread::hardware_concurrency();

    // Number of threads OpenMP will use.
    int num_threads;

    // ask the user for the number of threads
    cout << "\nHow many threads do you want OpenMP to use? (Enter 1-500) ";
    cin >> num_threads;

    //*********************LOOK!************************************************
    // add in the code to validate the user's input (like you did for program 1)
    // make sure the user entered in an integer 1 through 500.
    // Validate user input
    while (!cin || (num_threads < 1 || num_threads > 500))
    {
        if (!cin) // stream is in error state
            cout << "\nOops! You didn't enter a number!\n";
        else
            cout << "\nOops! You didn't enter a number between 1-500!\n";
        cin.clear();
        // line below ignores the rest of the current line, up to '\n' or EOF - whichever comes first
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a number 1 - 500: ";
        cin >> num_threads;
    }

    omp_set_dynamic(false);
    omp_set_num_threads(num_threads);

    cout << "\nNumber of Threads Used: " << num_threads << endl;
    cout << "Number of Processors: " << processor_count << endl;

    // Get data from words.txt and place in the words vector
    readFromFile(words, "words.txt");
    // Get data from numbers.txt and place in the nums vector
    readFromFile(nums, "numbers.txt");

    /*********************************************************************************
     * Computing runtime for the C++ built-in sort function in the Algorithm class
     * For more information about this algorithm in particular, take a look at
     * https://www.geeksforgeeks.org/internal-details-of-stdsort-in-c/
     * It uses the IntroSort algorithm, which is a hybrid between Quicksort, Heapsort,
     * and Insertion Sort.
     *********************************************************************************/
    tStart = clock();
    __gnu_parallel::sort(nums.begin(), nums.end());
    tStop = clock();
    compute_time_p = (double)(tStop - tStart) / CLOCKS_PER_SEC;
    cout << "\n\nParallel Sort Algorithm(int): " << compute_time_p << " seconds" << endl;

    tStart = clock();
    __gnu_parallel::sort(words.begin(), words.end());
    tStop = clock();
    compute_time_p = (double)(tStop - tStart) / CLOCKS_PER_SEC;
    cout << "Parallel Sort Algorithm(words): " << compute_time_p << " seconds" << endl;


    /*********************************************************************************
     * Called the bubbleSort function here for both nums and words
     * Computed the runtimes, and then print the runtimes to the screen
     *********************************************************************************/


    tStart = clock();
    bubbleSort(nums);
    tStop = clock();
    cout << "\nBubble Sort(int): " << (double)(tStop - tStart) / CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();
    bubbleSort(words);
    tStop = clock();
    cout << "Bubble Sort(string): " << (double)(tStop - tStart) / CLOCKS_PER_SEC << " seconds" << endl;

    /*********************************************************************************
     * Called the parallelBubbleSort function here for both nums and words
     * Computed the runtimes, and then print the runtimes to the screen
     *********************************************************************************/


    tStart = clock();
    parallelBubbleSort(nums);
    tStop = clock();
    cout << "\nParallel Bubble Sort(int): " << (double)(tStop - tStart) / CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();
    parallelBubbleSort(words);
    tStop = clock();
    cout << "Parallel Bubble Sort(string): " << (double)(tStop - tStart) / CLOCKS_PER_SEC << " seconds" << endl;

    /*********************************************************************************
     * Called the parallelQuickSort function here for both nums and words
     * Computed the runtimes, and then print the runtimes to the screen
     *********************************************************************************/


    tStart = clock();
    parallelQuickSort(nums, 0, (nums.size() - 1), 0);
    tStop = clock();
    cout << "\nParallel Quick Sort(int): " << (double)(tStop - tStart) / CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();
    parallelQuickSort(words, 0, (words.size() - 1), 0);
    tStop = clock();
    cout << "Parallel Quick Sort(string): " << (double)(tStop - tStart) / CLOCKS_PER_SEC << " seconds" << endl;

    /*********************************************************************************
     * Called the parallelMergeSort function here for both nums and words
     * Computed the runtimes, and then print the runtimes to the screen
     *********************************************************************************/


    tStart = clock();
    parallelMergeSort(nums, 0, nums.size() - 1, 0);
    tStop = clock();
    cout << "\nParallel Merge Sort(int): " << compute_time_p << " seconds" << endl;

    tStart = clock();
    parallelMergeSort(words, 0, words.size() - 1, 0);
    tStop = clock();
    cout << "Parallel Merge Sort(string): " << compute_time_p << " seconds" << endl;

    return 0;
}

/*********************************************************
 * HELPER FUNCTIONS
 * These functions help read in the data from the files
 * scramble the data, and print the data to the console.
 * You should not have to touch these.
 **********************************************************/

template <typename T>
void readFromFile(vector<T> &v, string filename)
{
    ifstream file;
    T tmp;
    file.open(filename);
    while (file >> tmp)
    {
        v.push_back(tmp);
    }
    file.close();
}

template <typename T>
void printVector(vector<T> &v)
{
    for (int i = 0; i < 20; i++)
    {
        cout << v[i] << endl;
    }
}

template <typename T>
void scramble(vector<T> &v)
{
    srand(time(0));
    int randomIndex;
    for (int i = 0; i < v.size(); i++)
    {
        randomIndex = rand() % v.size();
        swap(v[i], v[randomIndex]);
    }
}

/*************************************************
 * SORTING FUNCTIONS
 * These functions implement the sorting algorithms
 *************************************************/

// Implemented the Bubble Sort algorithm here.
template <typename T>
void bubbleSort(vector<T> &v)
{
    T tempForSwap;
    int size = v.size();
    bool sorted = false;
    // maxElement will hold the subscript of the last element
    // that is to be compared to its immediate neighbor
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < size; i++) // using i for "index"
        {
            // swap the two adjacent elements if the one on the left is greater than the one on the right
            if (v[i] > v[i + 1])
            {
                tempForSwap = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tempForSwap;
            }
        }
    }
}

/*
 * Implemented the parallel Bubble Sort algorithm here.
 * To parallelize bubble sort, you will need to have algorithm
 * run in parallel for the even and odd indices of the vector
 * You will need to use the following pragma statements:
 * pragma omp parallel private(<some temporary variable>)
 * pragma omp for reduction(&&:<some boolean that checks for sorted>)
 */
template <typename T>
void parallelBubbleSort(vector<T> &v)
{
    T tempForSwap;
    int size = v.size();
    bool sorted = true;
    do
    {
#pragma omp parallel private(tempForSwap)
        {
// For loop for even indexes
#pragma omp for reduction(&& : sorted)
            for (int i = 0; i < (size - 1); i += 2)
            {
                if (v[i] > v[i + 1])
                {
                    tempForSwap = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = tempForSwap;
                    sorted = false;
                }
            }
// For loop for odd indexes
#pragma omp for reduction(&& : sorted)
            for (int i = 1; i < (size - 1); i += 2)
            {
                if (v[i] > v[i + 1])
                {
                    tempForSwap = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = tempForSwap;
                    sorted = false;
                }
            }
        }
    } while (!sorted);
}
// Implemented the partition function for Quick Sort here.
template <typename T>
int partition(vector<T> &v, int low, int high)
{
    T tempforSwap;
    int left = low - 1;
    int right = high + 1;
    T pivot = v[high]; // Pivot starts at the last element

    while (left < right)
    {
        do
        {
            right--; // right is larger than pivot, decrement right
        } while (v[right] > pivot);

        do
        {
            left++; // left is smaller than pivot, increment left
        } while (v[left] < pivot);

        if (left < right)
        {
            tempforSwap = v[left];
            v[left] = v[right];
            v[right] = tempforSwap;
        }
    }
    return right;
}

/**
 * Implement the parallel Quick Sort algorithm here.
 * But when you call the parallelQuickSort function recursively,
 * you will have to use this statement above it to parallelize the calls:
 * #pragma omp task shared(v) if(depth < 4)
 * After the recursive calls, put this statement to synchronize the tasks:
 * #pragma omp taskwait
 */
template <typename T>
void parallelQuickSort(vector<T> &v, int low, int high, int depth)
{
    int pivot_location = 0;
    /* Base case: If there are 1 or 0 elements to sort,
    partition is already sorted */
    
    if (low <= high)
    {
        return;
    }
    /* Partition the data within the array */
    pivot_location = partition(v, low, high); // returns location of last element in low partition
    
    // recursively sort low partition
    #pragma omp task shared(v) if (depth < 4)
    
    parallelQuickSort(v, low, pivot_location - 1, depth + 1);
    
    // recursively sort high partition
    #pragma omp task shared(v) if (depth < 4)
    parallelQuickSort(v, pivot_location + 1, high, depth + 1);
    
    #pragma omp taskwait
}

/**
 * Implemented the parallel Merge Sort algorithm here.
 * But when you call the parallelMergeSort function recursively,
 * you will have to use this statement above it to parallelize the calls:
 * #pragma omp task shared(v) if(depth < 4)
 * After the recursive calls, put this statement to synchronize the tasks:
 * #pragma omp taskwait
 * Then do a final merge of the two sorted halves.
 */
template <typename T>
void parallelMergeSort(vector<T> &v, int beg, int end, int depth)
{
    int mid = 0;
 
    // recursive case (when beginning == end then that is base case)
    if (beg < end)
    {
        mid = beg + (end - beg) / 2; // Find the midpoint in the partition

        // recursively sort left partition
        #pragma omp task shared(v) if (depth < 4)
       
        parallelMergeSort(v, beg, mid, depth + 1);

        // recursively sort right partition
        #pragma omp task shared(v) if (depth < 4)
        parallelMergeSort(v, mid + 1, end, depth + 1);

        #pragma omp taskwait
        // Merge two sorted halves
        merge(v, beg, mid, end);
    }
}
// Implemented the merge function here for Merge Sort.
template <typename T>
void merge(vector<T> &v, int beg, int mid, int end)
{
    int mergedSize = end - beg + 1; // Size of merged partition
    int mergePos = 0;               // Position to insert merged number
    int leftPos = beg;              // Initialize left partition position
    int rightPos = mid + 1;         // Initialize right partition position
    vector<T> mergedNumbers(mergedSize);

    // Add smallest element from left or right partition
    while (leftPos <= mid && rightPos <= end)
    {
        if (v[leftPos] < v[rightPos])
        {
            mergedNumbers[mergePos] = v[leftPos];
            ++leftPos;
        }
        else
        {
            mergedNumbers[mergePos] = v[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= mid)
    {
        mergedNumbers[mergePos] = v[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= end)
    {
        mergedNumbers[mergePos] = v[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to the vector
    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
    {
        v[beg + mergePos] = mergedNumbers[mergePos];
    }
}
