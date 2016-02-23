/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

const int DEFAULT_SIZE = 3;

VectorPriorityQueue::VectorPriorityQueue() {
    arr = new string[DEFAULT_SIZE];
    numAllocated = DEFAULT_SIZE;
    numUsed = 0;
}

VectorPriorityQueue::~VectorPriorityQueue() {
    delete[] arr;
    numAllocated = numUsed = 0;
}

int VectorPriorityQueue::size() {
    return numUsed;
}

bool VectorPriorityQueue::isEmpty() {
    if (numUsed > 0)
        return false;
    else
        return true;
}

void VectorPriorityQueue::enqueue(string value) {
    if (numUsed == numAllocated)
        doubleCapacity();
    arr[numUsed++] = value;
}

string VectorPriorityQueue::peek() {
    if (isEmpty())
        error("Priority Queue is empty");
    else {
        int minIndex = 0;
        return findMin(minIndex);
    }
}

string VectorPriorityQueue::dequeueMin() {
    if (isEmpty())
        error("Priority Queue is empty");
    else {
        int minIndex = 0;
        string result = findMin(minIndex);
        removeAt(minIndex);
        return result;
    }
}

void VectorPriorityQueue::doubleCapacity()
{
    string *newArr = new string[numAllocated*2];
    for (int i = 0; i < numUsed; i++)
        newArr[i] = arr[i];

    delete[] arr;
    arr = newArr;
    numAllocated *= 2;
}

string VectorPriorityQueue::findMin(int &minIndex)
{
    string minString = arr[0];
    minIndex = 0;
    for (int i = 0; i < numUsed; i++) {
        if (arr[i] < minString) {
            minString = arr[i];
            minIndex = i;
        }
    }
    return minString;
}

void VectorPriorityQueue::removeAt(int index)
{
    if (index < 0 || index >= size())
        error("out of bound");

    for (int i = index; i < numUsed - 1; i++)
        arr[i] = arr[i+1];

    numUsed--;
}

