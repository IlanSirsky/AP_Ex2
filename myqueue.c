#include "myqueue.h"

void initQueue(TaskQueue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

int isQueueEmpty(TaskQueue *queue)
{
    return queue->head == NULL;
}

void enqueue(TaskQueue *queue, Task *task)
{
    TaskNode *node = (TaskNode *)malloc(sizeof(TaskNode));
    node->task = task;
    node->next = NULL;

    if (isQueueEmpty(queue))
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
}

Task *dequeue(TaskQueue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    TaskNode *node = queue->head;
    Task *task = node->task;

    queue->head = node->next;
    // free(node);

    return task;
}

void executeTask(Task *task)
{
    // print all task properties
    task->taskFunction(task->data, *task->key);
}

void submitTask(Task *task)
{
    pthread_mutex_lock(&mutexQueue);
    enqueue(&queue, task);
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}
