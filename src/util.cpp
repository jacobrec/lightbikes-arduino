#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


// from the google drive
int CellQueue::getLength() const {
    return(length);
}

CellQueue::CellQueue() {
    head = NULL;
    tail = NULL;
    length = 0;
}

CellQueue::~CellQueue() {
    while (getLength() > 0) {
        dequeue();
    }
}

void CellQueue::push(Cell c) {
    length++;
    QueueItem *tmp = new QueueItem(); // New **struct**
    tmp->val  = c;               // No ctor.  Init here.
    tmp->next = NULL;

    if (head == NULL) { // Special case
        assert(tail == NULL);
        head = tmp;     // First object in queue
    }
    else {
        tail->next = tmp; // Link in at tail
    }
    tail = tmp;           // New object is tail
}
Cell CellQueue::dequeue() {
    length--;
    Cell res = head->val;

    QueueItem *tmp = head;
    head = tmp->next; // Unlink head
    delete tmp;
    if (head == NULL) {
        tail = NULL;
    }

    return(res);
}

void SerialPrintf(char *fmt, ...) {
    char    buf[128];  // resulting string limited to 128 chars
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 128, fmt, args);
    va_end(args);
    Serial.print(buf);
}
