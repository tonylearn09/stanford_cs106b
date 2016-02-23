/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
    head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    while (head != NULL) {
        Cell *nextCell = head->next;
        delete head;
        head = nextCell;
    }
}

int LinkedListPriorityQueue::size() {
    int count = 0;
    for (Cell *cur = head; cur != NULL; cur = cur->next)
        count++;

	return count;
}

bool LinkedListPriorityQueue::isEmpty() {
    return head == NULL;
}

void LinkedListPriorityQueue::enqueue(string value) {
    Cell *cur, *prev;

    Cell *newCell = new Cell;
    newCell->value = value;

    for (cur = head, prev = NULL; cur != NULL &&
            value > cur->value; prev = cur, cur = cur->next)
        /* null body */ ;
    
    newCell->next = cur;

    if (prev == NULL) {
        head = newCell;
    } else {
        prev->next = newCell;
    }
}

string LinkedListPriorityQueue::peek() {
    if (isEmpty())
        error("Priority Queue is empty");
    return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
    string result = peek();

    Cell* nextHead = head->next;
    delete head;
    head = nextHead;

    return result;
}

