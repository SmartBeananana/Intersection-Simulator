/**
 * @file testQueue.c
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing implementation of queue unit test
 */
#include "QueueAPI.h"
#include "test.h"

void printData(void *toBePrinted);
void deleteData(void *toBeDeleted);
int compare(const void *first,const void *second);

int main(int argc, char **argv)
{
    int testNumber = 0, testsPassed = 0;
    int *num, *num1, *num2, *num3, *num4;
    int empty = 0;

    printf("*******************Start Testing Section*******************\n\n");

    Queue *q;

    q = creatQueue(printData, deleteData, compare);
    testNumber++;
    printTestInfo(testNumber, "Testing the initialized queue is not null");
    printf("Expect: Not NULL\n");
    printf("Received: %p\n", (void *)q);
    testsPassed += printPassFail(q != NULL);

    num1 = malloc(sizeof(int));
    *num1 = 1;
    testNumber++;
    printTestInfo(testNumber, "Testing insert a node into queue");
    enQueue(q, num1);
    printf("Expect: 1\n");
    printf("Received: %d\n",*((int *)(q->front->data)));
    testsPassed += printPassFail(*((int *)(q->front->data)) == *num1);

    testNumber++;
    printTestInfo(testNumber, "Testing remove a node from queue");
    num = deQueue(q);
    printf("Expect: 1\n");
    printf("Received: %d\n",*((int *)num));
    testsPassed += printPassFail(*num == *num1);

    testNumber++;
    printTestInfo(testNumber, "Testing the queue is not empty.");
    empty = isEmpty(q);
    printf("Except: 1\n");
    printf("Received: %d\n",empty);
    testsPassed += printPassFail(empty == 1);

    num2 = malloc(sizeof(int));
    *num2 = 2;
    enQueue(q, num2);
    num3 = malloc(sizeof(int));
    *num3 = 3;
    enQueue(q, num3);
    num4 = malloc(sizeof(int));
    *num4 = 4;
    enQueue(q, num4);
    testNumber++;
    printTestInfo(testNumber, "Testing to get the data at the front of the queue");
    num = peek(q);
    printf("Except: 2\n");
    printf("Received: %d\n",*num);
    testsPassed += printPassFail(*num == 2);

    printf("Testing destory funtion with valgrind and cppCheck\n");
    printf("The function works well when there is no memory leak reported\n\n");

    printf("The total number of testing: %d\n", testNumber);
    printf("-----The total number of test passed: %d-----\n\n", testsPassed);


    destroy(q);

    return 0;
}

void deleteData(void *toBeDeleted)
{
    free(toBeDeleted);

}

int compare(const void *first,const void *second)
{
    int a,b;

    a = *((int*)first);
    b = *((int*)second);

    return a-b;
}

void printData(void *toBePrinted)
{
    printf("%d ", *((int*)toBePrinted));
}
