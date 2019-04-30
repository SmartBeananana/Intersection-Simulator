/**
 * @file QueueImpl.c
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing the function definitions of a queue
 */
#include "QueueAPI.h"

Queue *creatQueue(void (*printFunction)(void *toBePrinted),
                 void (*deleteFunction)(void *toBeDeleted),
                 int (*compareFunction)(const void *first,const void *second))
{
    Queue *q;
    q = malloc(sizeof(Queue));

    if(!q)
    {
        return NULL;
    }

    q->theList = initializeList(printFunction, deleteFunction, compareFunction);

    q->front = q->theList->head;

    q->length = 0;

    return q;
}

void destroy(Queue *q)
{
    if (q == NULL)
    {
        return;
    }
    deleteList(q->theList);

    free(q);
}

void enQueue(Queue *q, void *toBeAdded)
{
    if(q == NULL)
    {
        return;
    }
    insertBack(q->theList, toBeAdded);
    q->front = q->theList->head;
    q->length++;
}

void *deQueue(Queue *q)
{
    if(q == NULL || q->theList == NULL)
    {
        return NULL;
    }

    void *data;

    data = pop(q->theList);

    q->front = q->theList->head;
    if(data != NULL)
    {
        q->length--;
    }

    return data;
}
int isEmpty(Queue *queue)
{
    if(queue == NULL)
    {
        return 1;
    }
    else if(queue->front == NULL || queue->length == 0)
    {
        return 1;
    }
    return 0;
}

void *peek(Queue *queue)
{
    if (queue == NULL)
    {
        return NULL;
    }

    return getFromFront(queue->theList);
}
