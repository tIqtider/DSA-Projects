/***************************************************************************
	Filename: 		GraphMatrix.h
	Author: 		Taseen Iqtider
	Date Created: 	04/07/2025
	Date Updated: 	04/19/2025
	Purpose: 		Header file for porgram 4
****************************************************************************/

#pragma once

// include libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// class declaration
class GraphMatrix
{
private:
	int **vertexMatrix;
	int numVertices;
	int numEdges;

public:
	// constructor
	GraphMatrix(int numV)
	{
		numVertices = numV;
		numEdges = 0;

		// dynamically allocate a 2D array
		vertexMatrix = new int *[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			vertexMatrix[i] = new int[numVertices];

			// initialize all elements to zero
			for (int j = 0; j < numVertices; j++)
			{
				vertexMatrix[i][j] = 0;
			}
		}
	}

	// destructor
	~GraphMatrix()
	{
		// delete allocated 2D array
		for (int i = 0; i < numVertices; i++)
		{
			delete vertexMatrix[i];
		}
		delete[] vertexMatrix;
	}

	// getter function
	int getNumVertices()
	{
		return numVertices;
	}

	/*************************************************************
	Function: 	addEdge()
	Input:  	two adjacent vertices, which are integers
	Purpose:  	to create an edge between v1 to v2
	**************************************************************/
	void addEdge(int v1, int v2)
	{
		// if the element is zero, increment numEdges & set element to 1
		if (vertexMatrix[v1][v2] == 0) // no edge created yet
		{
			numEdges++;
		}
		vertexMatrix[v1][v2] = 1;
	}

	/*******************************************************
	Function: 	printGraph()
	Purpose:	Pring the the values of graph in a 2D array
	********************************************************/
	void printGraph()
	{
		// designing and formatting rows & columns
		cout << setw(4) << "";
		for (int j = 0; j < numVertices; j++)
		{
			cout << setw(2) << j << " ";
		}
		cout << endl;

		cout << setw(4) << " ";
		for (int j = 0; j < numVertices; j++)
		{
			cout << "---";
		}
		cout << endl;

		for (int i = 0; i < numVertices; i++)
		{
			cout << i << "|   ";
			for (int j = 0; j < numVertices; j++)
			{
				if (vertexMatrix[i][j] == 0)
				{
					cout << ".  "; // replace 0s with dots(.)
				}
				else
				{
					cout << vertexMatrix[i][j] << "  ";
				}
			}
			cout << endl;
		}
	}

	/******************************************************************
	Function: 	isThereAnEdge()
	Purpose:	returns true if there is an edge between vertex r & c
	*******************************************************************/
	bool isThereAnEdge(int row, int col)
	{
		if (vertexMatrix[row][col] == 1)
			return true;
		else
			return false;
	}
};
