/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    head = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    while (head != NULL) {
        Cell *next = head->next;
        delete head;
        head = next;
    }
}

int DoublyLinkedListPriorityQueue::size() {
    int count = 0;
    for (Cell *cur = head; cur != NULL; cur = cur->next)
        count++;
	
	return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return head == NULL;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    Cell *newCell = new Cell;
    newCell->value = value;
    newCell->prev = NULL;
    newCell->next = head;

    /* if there is a Cell that head point to, need to update
     * its prev to point to the new Cell
     */
    if (head != NULL)
        head->prev = newCell;

    head = newCell;
}

string DoublyLinkedListPriorityQueue::peek() {
    if (isEmpty())
        error("Priority Queue is empty");

    return getMin()->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if (isEmpty())
        error("Priority Queue is empty");

    Cell *minCell = getMin();
    string result = minCell->value;
    removeCell(minCell);
    return result;
}

DoublyLinkedListPriorityQueue::Cell *DoublyLinkedListPriorityQueue::getMin()
{
    Cell *toRemove = head;
    for (Cell *cur = head; cur != NULL; cur = cur->next) {
        if (cur->value < toRemove->value)
            toRemove = cur;
    }

    return toRemove;
}

void DoublyLinkedListPriorityQueue::removeCell(Cell *removeCell)
{
    if (removeCell->prev == NULL) {
        /* removeCell is the first Cell, and head point to it */
        head = removeCell->next;

        /* if removeCell is not the only Cell in linkList */
        if (removeCell->next != NULL)
            removeCell->next->prev = NULL;
    } else if (removeCell->next == NULL) {
        /* removeCell is the last Cell */
        removeCell->prev->next = NULL;
    } else {
        /* general case that prev and next Cell all exist */
        removeCell->prev->next = removeCell->next;
        removeCell->next->prev = removeCell->prev;
    }

    delete removeCell;
}

