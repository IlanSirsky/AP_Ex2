#include "readChars.h"

void readChars(int key)
{
    char c;
    int counter = 0;
    int dest_size = 1024;
    char data[dest_size];

    while ((c = getchar()) != EOF)
    {
        data[counter] = c;
        counter++;

        if (counter == MAX_BUFFER_SIZE)
        {
            Task *t = (Task *)malloc(sizeof(Task));
            t->taskFunction = (void (*)(char *, int))malloc(sizeof(void (*)(char *, int)));
            t->taskFunction = encrypt_decrypt;
            t->data = (char *)malloc(sizeof(char) * dest_size);
            strcpy(t->data, data);
            t->key = (int *)malloc(sizeof(int));
            *t->key = key;
            t->taskCount = (int *)malloc(sizeof(int));
            *t->taskCount = taskCount++;
            submitTask(t);
            memset(data, 0, dest_size);
            counter = 0;
        }
    }

    if (counter > 0)
    {
        char lastData[counter];
        lastData[0] = '\0';
        strncat(lastData, data, counter);
        Task *t = (Task *)malloc(sizeof(Task));
        t->taskFunction = (void (*)(char *, int))malloc(sizeof(void (*)(char *, int)));
        t->taskFunction = encrypt_decrypt;
        t->data = (char *)malloc(sizeof(char) * counter);
        strcpy(t->data, lastData);
        t->key = (int *)malloc(sizeof(int));
        *t->key = key;
        t->taskCount = (int *)malloc(sizeof(int));
        *t->taskCount = taskCount++;
        submitTask(t);
        memset(data, 0, dest_size);
        counter = 0;
    }

    // insert terminating tasks
    for (int i = 0; i < THREAD_NUM; i++)
    {
        Task *t = (Task *)malloc(sizeof(Task));
        t->taskFunction = (void (*)(char *, int))malloc(sizeof(void (*)(char *, int)));
        t->taskFunction = encrypt_decrypt;
        t->data = (char *)malloc(sizeof(char) * dest_size);
        strcpy(t->data, "terminate");
        t->key = (int *)malloc(sizeof(int));
        *t->key = key;
        t->taskCount = (int *)malloc(sizeof(int));
        *t->taskCount = taskCount++;
        submitTask(t);
    }
}
