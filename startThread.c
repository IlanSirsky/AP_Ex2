#include "startThread.h"

void *startThread(void *args)
{
    while (1)
    {
        Task *task;
        pthread_mutex_lock(&mutexQueue);
        while (isQueueEmpty(&queue))
        {
            pthread_cond_wait(&condQueue, &mutexQueue);
        }
        task = dequeue(&queue);
        pthread_mutex_unlock(&mutexQueue);
        if (!strcmp(task->data, "terminate"))
        {
            break;
        }
        executeTask(task);
        
        // print the output in the correct order according to taskCount
        while (printCount != *task->taskCount)
        {
            pthread_cond_wait(&condPrint, &mutexQueue);
        };
        printf("%s\n", task->data);
        printCount++;
        pthread_cond_signal(&condPrint);
    }
    return NULL;
}
