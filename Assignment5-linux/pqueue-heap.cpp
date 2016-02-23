/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

const int DEFAULT_SIZE = 3;

HeapPriorityQueue::HeapPriorityQueue() {
    numAllocated = DEFAULT_SIZE + 1; /* add 1 for dummy cells */
    elems = new string[numAllocated];
    elems[0] = ""; /* dummy cells for easy arithmathtic */
    numUsed = 1; /* there is one element--dummy cell in the array */
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] elems;
}

int HeapPriorityQueue::size() {
    return numUsed - 1; /* minus 1 for dummy cell */
}

bool HeapPriorityQueue::isEmpty() {
    return size() == 0;
}

void HeapPriorityQueue::enqueue(string value) {
    if (numUsed == numAllocated)
        doubleCapcity();
    elems[numUsed++] = value;
    bubbleUp(numUsed - 1);
}
    
string HeapPriorityQueue::peek() {
    if (isEmpty())
        error("Priority Queue is empty");

    /* elems[1] is the smallest one */
    return elems[1];
}

string HeapPriorityQueue::dequeueMin() {
    /* peek() will check if it is empty */
    string result = peek();

    /* swap the last element to the beginning of elems
     * remember the first one is dummy cells
     */
    elems[1] = elems[numUsed-1];

    numUsed--;
    bubbleDown(1);

    return result;
}

void HeapPriorityQueue::doubleCapcity()
{
    numAllocated *= 2;
    string *newElems = new string[numAllocated];
    for (int i = 0; i < numUsed; i++)
        newElems[i] = elems[i];

    delete[] elems;
    elems = newElems;
}

// recursive
void HeapPriorityQueue::bubbleUp(int index)
{
    /* 
     * base case: index = 1
     * There is only one dummy elements and this index elements, so
     * we don't need to compare with its parent.
     */

    /*
     * recursive step
     */
    if (index > 1) {
        int parentIndex = index / 2;
        if (elems[parentIndex] > elems[index]) {
            string temp = elems[parentIndex];
            elems[parentIndex] = elems[index];
            elems[index] = temp;
            bubbleUp(parentIndex);
        }
    }
}

void HeapPriorityQueue::bubbleDown(int index)
{
    int leftChildIndex = 2 * index;
    int rightChildIndex = 2 * index + 1;

    /* 
     * base case: no any child index
     */
    if (leftChildIndex >= numUsed)
        return;

    /*
     * recursive step
     */
    int minChildIndex = leftChildIndex;

    /* if rightChild exist, then need to check with leftchild,
     * in order to decide which one is smaller
     */
    if (rightChildIndex < numUsed) {
        minChildIndex = elems[leftChildIndex] < elems[rightChildIndex]
            ? leftChildIndex : rightChildIndex;
    }

    if (elems[index] > elems[minChildIndex]) {
        string temp = elems[index];
        elems[index] = elems[minChildIndex];
        elems[minChildIndex] = temp;
        bubbleDown(minChildIndex);
    }
}
