/**
 * @file LinkedListImpl.c
 * @author Xiangyuan Lian
 * @date May 2018
 * @brief File containing implementation of doubly linked list
 */
#include "LinkedListAPI.h"

List *initializeList(
    void (*printFunction)(void *toBePrinted),
    void (*deleteFunction)(void *toBeDeleted),
    int (*compareFunction)(const void *first,const void *second))
{
    List *newList;

    newList = malloc(sizeof (List));

    if (newList == NULL)
        return NULL;

    newList->head = NULL;
    newList->tail = NULL;
    newList->printData = printFunction;
    newList->deleteData = deleteFunction;
    newList->compare = compareFunction;

    return newList;
}

Node *initializeNode(void *data)
{
    Node *newNode;

    newNode = malloc(sizeof (Node));

    if (newNode == NULL)
        return NULL;

    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;

    return newNode;
}

void insertFront(List *list, void *toBeAdded)
{

    if (list == NULL)
        return;

    Node *newNode = initializeNode(toBeAdded);

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->next = list->head;
    list->head->previous = newNode;
    list->head = newNode;
}

void insertBack(List *list, void *toBeAdded)
{
    if(list == NULL)
        return;

    Node *newNode = initializeNode(toBeAdded);

    if(list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->previous = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
}

void deleteList(List *list)
{
    if (list == NULL)
        return;

    while (list->head != NULL)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        temp->next = NULL;
        temp->previous = NULL;
        list->deleteData(temp->data);
        free(temp);
    }
    free(list);
    return;
}

void insertSorted(List *list, void *toBeAdded)
{
      if (list == NULL)
         return;

      Node *newNode;

      if (list->head == NULL)
      {
          newNode = initializeNode(toBeAdded);
          list->head = newNode;
          list->tail = newNode;
          return;
      }

      Node *temp = list->head;

      if(temp != NULL && (list->compare(toBeAdded, temp->data)) <= 0 )
      {
          insertFront(list, toBeAdded);
          return;
      }

      while(temp != NULL && (list->compare(toBeAdded, temp->data)) > 0)
      {
           temp = temp->next;
      }

      if(temp == NULL)
      {
          insertBack(list, toBeAdded);
      }
      else
      {
          newNode = initializeNode(toBeAdded);
          newNode->next = temp;
          newNode->previous = temp->previous;
          temp->previous->next = newNode;
          temp->previous = newNode;
      }

}

int deleteDataFromList(List *list, void *toBeDeleted)
{
    if (list == NULL || list->head == NULL || toBeDeleted == NULL)
        return EXIT_FAILURE;

    Node *temp = list->head;

    if(temp->data == toBeDeleted)
    {
        list->head = temp->next;

        if(list->head != NULL)
        {
            list->head->previous = NULL;
        }
        list->deleteData(temp->data);
        free(temp);
        return EXIT_SUCCESS;
    }

    temp = list->tail;
    if(temp->data == toBeDeleted)
    {
        list->tail = temp->previous;

        if(temp->previous != NULL)
        {
            temp->previous->next = NULL;
        }
        list->deleteData(temp->data);
        free(temp);
        return EXIT_SUCCESS;
    }
    while(temp != NULL && temp->data != toBeDeleted)
    {
        temp = temp->next;

        if(temp == toBeDeleted)
        {
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;

            list->deleteData(temp->data);
            free(temp);
            return EXIT_SUCCESS;
        }
    }
    return -1;
}

void *pop(List *list)
{
    void *toBePopped;

    toBePopped = getFromFront(list);

    if(toBePopped == NULL)
    {
        return NULL;
    }

    Node *temp = list->head;
    list->head = list->head->next;

    if(list->head == NULL)
    {
        list->tail = NULL;
    }
    else
    {
        list->head->previous = NULL;
    }
    free(temp);
    return toBePopped;
}

void *getFromFront(List *list)
{
    if(list == NULL || list->head == NULL)
    {
        return NULL;
    }
    return list->head->data;
}

void *getFromBack(List *list)
{
    if(list == NULL || list->head == NULL)
    {
        return NULL;
    }
    return list->tail->data;
}

void printForward(List *list)
{
    if(list == NULL || list->head == NULL)
    {
        return;
    }

    Node *temp = list->head;
    while(temp)
    {
        list->printData(temp->data);
        temp = temp->next;
    }
}

void printBackwards(List *list)
{
    if(list == NULL || list->head == NULL)
    {
        return;
    }

    Node *temp = list->tail;
    while(temp != NULL)
    {
        list->printData(temp->data);
        temp = temp->previous;
    }
}
