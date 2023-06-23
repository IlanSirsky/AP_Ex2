#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 6
#define MAX_BUFFER_SIZE 1024

typedef struct Task
{
    void (*taskFunction)(char *s, int);
    char *data;
    int *key;
    int *taskCount;
} Task;

typedef struct TaskNode
{
    Task *task;
    struct TaskNode *next;
} TaskNode;

typedef struct TaskQueue
{
    TaskNode *head;
    TaskNode *tail;
} TaskQueue;

void initQueue(TaskQueue *queue);

int isQueueEmpty(TaskQueue *queue);

void enqueue(TaskQueue *queue, Task *task);

Task *dequeue(TaskQueue *queue);

extern TaskQueue queue;
extern int taskCount;
extern int printCount;
extern pthread_mutex_t mutexQueue;
extern pthread_cond_t condQueue;
extern pthread_cond_t condPrint;

extern void (*encrypt_decrypt)(char *, int);

void executeTask(Task *task);

void submitTask(Task *task);

#endif
