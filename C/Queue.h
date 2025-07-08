#ifndef QUEUE_H
#define QUEUE_H

#include "data_types_config.h"
#include <stdbool.h>
#include "POD_Utils.h"

#ifndef Queue_DATA_TYPE
#define Queue_DATA_TYPE int
#endif


typedef struct {
    Queue_DATA_TYPE* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* Queue_Create(int capacity);
void Queue_Free(Queue* q);
bool Queue_Enqueue(Queue* q, Queue_DATA_TYPE value);
bool Queue_Dequeue(Queue* q, Queue_DATA_TYPE* value);
bool Queue_Peek(Queue* q, Queue_DATA_TYPE* value);
bool Queue_IsEmpty(Queue* q);
bool Queue_IsFull(Queue* q);
int Queue_GetSize(Queue* q);
int Queue_GetCapacity(Queue* q);

#endif // QUEUE_H
