/**
 * @file QueueAPI.h
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing function definitions of queue
 */
#ifndef _QUEUE_API_
#define _QUEUE_API_

#include "LinkedListAPI.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct queueStruct{
    List *theList;
    Node *front;
    int length;
}Queue;

/**Function to point the head of list inside queue front to the appropriate functions. Allocates memory to the list.
*@return pointer to the queue
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/

Queue *creatQueue(void (*printFunction)(void *toBePrinted),
                  void (*deleteFunction)(void *toBeDeleted),
                  int (*compareFunction)(const void *first,const void *second));

/** Deletes the entire list inside queue starting with the nodes, followed by the list itself.
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param queue pointer to the Queue-type dummy node
**/
void destroy(Queue *q);

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param queue pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list insode queue
**/
void enQueue(Queue *q, void *toBeAdded);

/**Function to return the data at the front of the list.
 *@pre The list inside the queue exists and has memory allocated to it
 *@param queue pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *deQueue(Queue *q);

/**Function to check the queue is empty or not.
 *@pre 'Queue' type must exist and be used inorder to keep track of the linked list.
 *@param queue poniter to the dummy head of the list containing the head pf the list
 *@return integer 1 on empty; interger 0 on not empty
**/
int isEmpty(Queue *queue);

/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param queue pointer to the dummy front of the queue containing the head of the list..
 *@return void pointer to the data in the first node.
 **/
void *peek(Queue *queue);

#endif
