/**
 * @file main.c
 * @author Xiangyuan Lian
 * @date May 2018
 * @brief File containing the function definitions and implementation of the intersection simulator
 */
#include "carAPI.h"
#include "LinkedListAPI.h"
#include "QueueAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printData(void *toBePrinted);
void deleteData(void *toBeDeleted);
int compare(const void *first,const void *second);
void queueAllocation(List *list, Queue *queueNSWE[],int counter);
int queueIsEmpty(Queue *queueNSWE[]);
Queue *rightofWay(Queue *queueNSWE[]);
double getReachFrontTime(Car *c);
void setReachFrontTime(Car *c, double counter);

int main(int argc, char **argv)
{
    char str[30], *token;
    FILE *fp = NULL;
    List *list = NULL;
    Car *c, *nextInQueue;
    Node *temp;
    Queue *queueNSWE[4];
    int i;
    double counter = 0.0;
    Queue *priorityQueue;
    List *resultList;

    if (argc != 2)
    {
        printf("---Invaild Input---\n");
    }
    else
    {
        fp = fopen(argv[1],"r");
        if(fp == NULL)
        {
            printf("Can't open the file!\n");
            exit(1);
        }
        else
        {
            list = initializeList(printData,deleteData,compare);
            if(list == NULL)
            {
                printf("List is null\n");

                return 0;
            }
            while(fgets(str,20,fp))
            {
                c = initializeCar();
                token = strtok(str," ");
                c->heading = *token;
                token = strtok(NULL," ");
                c->going = *token;
                token = strtok(NULL," ");
                c->approchTime = atof(token);

                insertSorted(list,c);
            }
        }
    }
    fclose(fp);
    temp = list->head;

    for(i=0; i<4; i++)
    {
        queueNSWE[i] = creatQueue(printData,deleteData,compare);
    }

    resultList = initializeList(printData,deleteData,compare);
    while(queueIsEmpty(queueNSWE) == 0 || list->head != NULL)
    {
        queueAllocation(list,queueNSWE,counter);
        for (i=0; i<4; i++)
        {
            c = getFromFront(queueNSWE[i]->theList);

            if(c && getReachFrontTime(c) == -1)
            {
                setReachFrontTime(c,c->approchTime);
            }
        }

        priorityQueue = rightofWay(queueNSWE);
        c = deQueue(priorityQueue);

        if((nextInQueue = peek(priorityQueue)))
        {
            nextInQueue->reachFrontTime = counter + 1;
        }
        if(c != NULL)
        {
            c->waitTime = counter-(c->approchTime);
            if(c->going == 'F')
            {
                counter = counter + 2;
            }
            else if(c->going == 'R')
            {
                counter = counter + 1.5;
            }
            else if(c->going == 'L')
            {
                counter = counter + 3.5;
            }
            insertBack(resultList, c);
        }
        else
        {
            counter++;
        }
    }

    printf("****************************Conclusion**************************\n");

    double maxWaitTime, totWaitTime=0, totAveWaitTime=0;
    int num=0;
    double totWaitTimeNSWE[4], aveWaitTimeNSWE[4];
    int numNSWE[4];

    printf("The order went throught the intersection:\n");
    printForward(resultList);

    for (i=0; i<4; i++)
    {
        totWaitTimeNSWE[i] = 0.0;
        numNSWE[i] = 0;
    }

    temp = resultList->head;
    maxWaitTime = ((Car*)temp->data)->waitTime;

    while(temp)
    {
        if (((Car*)temp->data)->heading== 'N')
        {
           totWaitTimeNSWE[0]+=(((Car*)temp->data)->waitTime);
           numNSWE[0]++;
        }
        else if(((Car*)temp->data)->heading == 'S')
        {
           totWaitTimeNSWE[1]+=(((Car*)temp->data)->waitTime);
           numNSWE[1]++;
        }
        else if(((Car*)temp->data)->heading == 'W')
        {
           totWaitTimeNSWE[2]+=(((Car*)temp->data)->waitTime);
           numNSWE[2]++;
        }
        else if (((Car*)temp->data)->heading == 'E')
        {
           totWaitTimeNSWE[3]+=(((Car*)temp->data)->waitTime);
           numNSWE[3]++;
        }

        if(((Car*)temp->data)->waitTime > maxWaitTime)
        {
           maxWaitTime = ((Car*)temp->data)->waitTime;
        }
        num++;
        temp = temp->next;
    }

    for (i=0; i<4; i++)
    {
        aveWaitTimeNSWE[i] = totWaitTimeNSWE[i]/numNSWE[i];
        totWaitTime += totWaitTimeNSWE[i];
    }
    totAveWaitTime = totWaitTime/num;

    printf("\n");
    printf("Average wait time for cars heading north: %g\n", aveWaitTimeNSWE[0]);
    printf("Average wait time for cars heading south: %g\n", aveWaitTimeNSWE[1]);
    printf("Average wait time for cars heading west: %g\n", aveWaitTimeNSWE[2]);
    printf("Average wait time for cars heading east: %g\n", aveWaitTimeNSWE[3]);
    printf("Maximum wait time for all cars: %g\n", maxWaitTime);
    printf("Average wait time for all cars: %g\n", totAveWaitTime);

    deleteList(list);
    deleteList(resultList);

    for(i=0; i<4; i++)
    {
        destroy(queueNSWE[i]);
    }

    return 0;
}

void deleteData(void *toBeDeleted)
{
    free(toBeDeleted);
}

int compare(const void *first,const void *second)
{
    Car *a,*b;

    a = (Car*)first;
    b = (Car*)second;

    return (a->approchTime)-(b->approchTime);
}

void printData(void *toBePrinted)
{
    printf("%c %c %g\n", ((Car*)toBePrinted)->heading,
                         ((Car*)toBePrinted)->going,
                         ((Car*)toBePrinted)->approchTime);
}

void queueAllocation(List *list, Queue *queueNSWE[],int counter)
{
    Car *car = getFromFront(list);
    while(car != NULL &&  car->approchTime <= counter)
    {
        if(car->heading == 'N')
        {
            enQueue(queueNSWE[0],car);
        }
        else if(car->heading == 'S')
        {
            enQueue(queueNSWE[2],car);
        }
        else if(car->heading == 'W')
        {
            enQueue(queueNSWE[3],car);
        }
        else
        {
            enQueue(queueNSWE[1],car);
        }
        pop(list);
        car = getFromFront(list);
        if(!car)
        {
            return;
        }
    }
    if(!car)
    {
        return;
    }
}

int queueIsEmpty(Queue *queueNSWE[])
{
    int i = 0;

    for(i=0; i<4; i++)
    {
        if (isEmpty(queueNSWE[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
Queue *rightofWay(Queue *queueNSWE[])
{
    int i = 0, numofCar = 0, flagE = 0;
    Car *car, *carA, *carB, *carN, *carS, *carW, *carE;
    Queue *priorityQueue = NULL;

    carA = peek(queueNSWE[0]);
    priorityQueue = queueNSWE[0];

    for(i=0; i<4; i++)
    {
        car = peek(queueNSWE[i]);
        if(car != NULL)
        {
            numofCar++;
            if(car->heading == 'E')
            {
                flagE = 1;
            }
        }
    }

    for(i=1; i<4; i++)
    {
        carB = peek(queueNSWE[i]);
        if (carA == NULL && carB == NULL)
        {
            priorityQueue = NULL;
        }
        else if (carA == NULL && carB != NULL)
        {
            carA = carB;
            priorityQueue = queueNSWE[i];
        }
        else if (carA != NULL && carB == NULL)
        {
            continue;
        }
        else if ((carA->reachFrontTime)>(carB->reachFrontTime))
        {
            carA = carB;
            priorityQueue = queueNSWE[i];
        }
        else if ((carA->reachFrontTime)<(carB->reachFrontTime))
        {
            continue;
        }
    }

    carN = peek(queueNSWE[2]);
    carE = peek(queueNSWE[1]);
    carS = peek(queueNSWE[0]);
    carW = peek(queueNSWE[3]);
    if(numofCar == 2)
    {
        if(carN != NULL && carS != NULL && (carN->reachFrontTime) == (carS->reachFrontTime))
        {
            if((carN->going)=='F' || (carN->going)=='R')
            {
                priorityQueue = queueNSWE[2];
            }
            else
            {
                priorityQueue = queueNSWE[0];
            }

        }
        if(carE != NULL && carW != NULL && (carE->reachFrontTime) == (carW->reachFrontTime))
        {
            if((carE->going)=='F' || (carE->going)=='R')
            {
                priorityQueue = queueNSWE[3];
            }
            else
            {
                priorityQueue = queueNSWE[1];
            }
        }
        if(carS != NULL && carE != NULL && (carS->reachFrontTime) == (carE->reachFrontTime))
        {
            priorityQueue = queueNSWE[3];
        }
    }
    if(numofCar == 3 && flagE == 0)
    {
        priorityQueue = queueNSWE[2];
    }
    return priorityQueue;
}

double getReachFrontTime(Car *c)
{
    if(c != NULL)
    {
        return c->reachFrontTime;
    }
    return -1;
}

void setReachFrontTime(Car *c, double counter)
{
    if(c != NULL)
    {
        c->reachFrontTime = counter;
    }
    return;
}
