#ifndef UTIL_H
#define UTIL_H
#include <Arduino.h>
#include <stdarg.h>

void SerialPrintf(char *fmt, ...);

typedef struct {
    uint16_t loc;
    uint8_t  colour;
} Cell;

typedef struct item {
    Cell         val;
    struct item *next;
} QueueItem;

class CellQueue {
private:
    int        length;
    QueueItem *head;
    QueueItem *tail;
public:
    int getLength() const;

    CellQueue();
    ~CellQueue();

    Cell dequeue();
    void push(Cell c);
};

#endif
