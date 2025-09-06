/***************************************************************************
    Filename: 		Queue.h
    Author: 		Taseen Iqtider
    Date Created: 	2/17/2025
    Date Updated: 	3/26/2025
    Purpose: 		header file for war source file
****************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "Card.h"
using namespace std;

// Queue dynamic class
class Queue
{
private:
    // Declare a structure for the queue linked list
    struct ListNode
    {
        Card card;      // The value in this node
        ListNode *next; // To point to the next node
    };

    ListNode *front; // queue head pointer
    ListNode *back;  // queue tail pointer
    int size;

public:
    // Constructor (sets front & rear to NULL & size to 0)
    Queue()
    {
        front = NULL;
        back = NULL;
        size = 0;
    }

    // Destructor (deletes all nodes left in the queue)
    ~Queue()
    {
        ListNode *nodePtr;  // To traverse the list
        ListNode *nextNode; // To point to the next node

        // Position nodePtr at the front of the list.
        nodePtr = front;

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

    // isEmpty (returns true if queue is empty or false otherwise)
    bool isEmpty()
    {
        {
            if (!front)
                return true;
            else
                return false;
        }
    }

    // getSize (returns the number of nodes in the queue)
    int getSize()
    {
        int counter = 0;
        ListNode *nodePtr;

        nodePtr = front;

        while (nodePtr)
        {
            counter++;
            nodePtr = nodePtr->next;
        }
        return counter;
    }

    // enqueue (accepts a card object and appends to the back of queue)
    void enqueue(const Card &newCard)
    {
        ListNode *newNode; // To point to a new node

        // Allocate a new node and store card there.
        newNode = new ListNode;
        newNode->card = newCard;
        newNode->next = NULL;

        if (!front)
        {
            front = newNode;
            back = newNode;
        }
        else
        {
            back->next = newNode;
            back = newNode;
        }
        size++; // increment the size of the queue (card deck)
    }

    // dequeue (deletes the front node & returns Card object)
    Card dequeue()
    {
        ListNode *nodePtr = front;
        Card tempCard;

        if (!front) // if the queue is empty
        {
            cout << "\nQueue is empty\n";
            return Card();
        }
        else
        {
            tempCard = nodePtr->card;
            front = front->next; // move the front pointer to the next node
            if (!front)
            {
                back = NULL;
            }
        }
        delete nodePtr; // delete the front of the stack
        size--;         // decrement the size of the queue (card deck)

        return tempCard; // return the value that was in the front of the stack
    }
};

#endif