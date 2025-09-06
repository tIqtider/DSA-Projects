/***************************************************************************
	Filename: 		Stack.h
	Author: 		Taseen Iqtider
	Date Created: 	2/17/2025
	Date Updated: 	3/26/2025
	Purpose: 		header file for war source file
****************************************************************************/

#ifndef STACK_H
#define STACK_H

#include "Card.h"
using namespace std;

// Stack dynamic class
class Stack
{
private:
	// Declare a structure for the stack linked list
	struct ListNode
	{
		Card card;		// The value in this node
		ListNode *next; // To point to the next node
	};

	ListNode *top; // Stack head pointer "top"

public:
	// Constructor (sets top to NULL)
	Stack()
	{
		top = NULL;
	}

	// Destructor (deletes all nodes left in the stack)
	~Stack()
	{
		ListNode *nodePtr;	// To traverse the list
		ListNode *nextNode; // To point to the next node

		// Position nodePtr at the top of the list.
		nodePtr = top;

		// While nodePtr is not at the end of the list...
		while (nodePtr)
		{
			// Save a pointer to the next node.
			nextNode = nodePtr->next;

			// Delete the current node.
			delete nodePtr;

			// Position nodePtr at the next node.
			nodePtr = nextNode;
		}
	}

	// isEmpty (returns true if stack is empty or false otherwise)
	bool isEmpty()
	{
		if (!top)
			return true;
		else
			return false;
	}

	// getSize (returns the number of nodes in the stack)
	int getSize()
	{
		int counter = 0;
		ListNode *current;

		current = top;

		while (current != NULL)
		{
			counter++;
			current = current->next;
		}
		return counter;
	}

	// push (accepts a card object and places it on top of stack)
	void push(const Card &newCard)
	{
		ListNode *newNode; // To point to a new node

		// Allocate a new list node
		newNode = new ListNode;
		newNode->card = newCard; // set card value
		newNode->next = top;	 // point to top node
		top = newNode;			 // set newNode as the top
	}

	// pop (deletes the top node & returns Card object)
	Card pop()
	{
		ListNode *nodePtr;
		Card tempCard;

		if (!top) // if the stack is empty
		{
			cout << "\nStack is empty\n";
			return Card();
		}
		else
		{
			nodePtr = top;
			if (top->next != NULL) // if there is another item in the stack
			{
				top = top->next; // move the top to the next item in stack
			}
			else
			{
				top = NULL;
			}
			tempCard = nodePtr->card;
			delete nodePtr; // delete the top of the stack

			return tempCard; // return the value that was in the top of the stack
		}
	}
};

#endif