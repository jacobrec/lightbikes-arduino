#include "util.h"
#include <Arduino.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


List_t *createList(int dataSize) {
    List_t *l = (List_t *)malloc(sizeof(List_t));

    l->length   = 0;
    l->dataSize = dataSize;
    l->tail     = NULL;
    l->head     = NULL;
    return(l);
}

void push(List_t *list, const void *data) {
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));

    newNode->data = malloc(list->dataSize);
    memcpy(newNode->data, data, list->dataSize);

    if (list->length == 0) {
        list->tail = newNode;
        list->head = newNode;
    }
    else{
        newNode->previous = list->tail;
        list->tail->next  = newNode;
        list->tail        = newNode;
    }
    list->length++;
}

void *pop(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to pop\n");
    }
    else{
        Node_t *end;
        if (list->length == 1) {
            end        = list->tail;
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            end        = list->tail;
            list->tail = list->tail->previous;
        }
        list->length--;

        void *data = end->data;
        free(end);

        return(data);
    }
    return(NULL);
}

void *peek(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to peek\n");
    }
    else{
        return(list->tail->data);
    }
    return(NULL);
}

void insert(List_t *list, int index, const void *data) {
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));

    newNode->data = malloc(list->dataSize);
    memcpy(newNode->data, data, list->dataSize);

    if (list->length >= index && index >= 0) {
        if (index == 0 && list->length == 0) {
            list->tail = newNode;
            list->head = newNode;
        }
        else{
            if (index == 0) {
                newNode->next        = list->head;
                list->head->previous = newNode;
                list->head           = newNode;
            }
            else if (index == list->length) {
                newNode->previous = list->tail;
                list->tail->next  = newNode;
                list->tail        = newNode;
            }
            else {
                Node_t *prev = list->head;
                for (int i = 0; i < index - 1; i++) {
                    prev = prev->next;
                }

                newNode->previous = prev;
                newNode->next     = prev->next;

                prev->next->previous = newNode;
                prev->next           = newNode;
            }
        }
    }
    else{
        fprintf(stderr, "Error: index out of bounds\n");
        free(newNode->data);
        free(newNode);
        return;
    }
    list->length++;
}

void *pull(List_t *list, int index) {
    if (list->length > index && index >= 0) {
        if (index == 0) {
            return(dequeue(list));
        }
        else if (index == list->length - 1) {
            return(pop(list));
        }
        else{
            Node_t *node = list->head;
            for (int i = 0; i < index; i++) {
                node = node->next;
            }

            node->next->previous = node->previous;
            node->previous->next = node->next;
            list->length--;
            void *data = node->data;
            free(node);

            return(data);
        }
    }
    else{
        fprintf(stderr, "Error: index out of bounds\n");
    }
    return(NULL);
}

void *get(List_t *list, int index) {
    if (list->length > index && index >= 0) {
        Node_t *node = list->head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
        return(node->data);
    }
    else{
        fprintf(stderr, "Error: index out of bounds\n");
    }
    return(NULL);
}

void *dequeue(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to pop\n");
    }
    else{
        Node_t *end;
        if (list->length == 1) {
            end        = list->head;
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            end        = list->head;
            list->head = list->head->next;
        }
        list->length--;

        void *data = end->data;
        free(end);

        return(data);
    }
    return(NULL);
}

void *preview(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to peek\n");
    }
    else{
        return(list->head->data);
    }
    return(NULL);
}

void destroyList(List_t *list) {
    while (list->length > 0) {
        free(pop(list));
    }
    free(list);
}

void SerialPrintf(char *fmt, ...) {
    char    buf[128];  // resulting string limited to 128 chars
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 128, fmt, args);
    va_end(args);
    Serial.print(buf);
}
