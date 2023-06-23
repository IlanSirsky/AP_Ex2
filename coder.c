#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "codec.h"
#include "readChars.h"
#include "myqueue.h"
#include "startThread.h"

// code taken from 2 videos on youtube
// https://www.youtube.com/watch?v=_n2hE2gyPxU&ab_channel=CodeVault
// https://www.youtube.com/watch?v=7i9z4CRYLAE&ab_channel=CodeVault

// global variables
TaskQueue queue;
int taskCount = 0;
int printCount = 0;
pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;
pthread_cond_t condPrint;
void (*encrypt_decrypt)(char *, int) = NULL;

int main(int argc, char *argv[])
{
    // init mutex, cond variables and queue
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);
    pthread_cond_init(&condPrint, NULL);
    initQueue(&queue);
    
    // check that the amount of arguments is valid
    if (argc < 3)
    {
        printf("error not valid amount of  arguments need a key and a flag\n");
        return 0;
    }

    // check if flag is valid
    if (strcmp(argv[2], "-e") != 0 && strcmp(argv[2], "-d") != 0)
    {
        printf("error not valid flag\n");
        return 0;
    }

    // check if the flag is -e or -d
    if (strcmp(argv[2], "-e") == 0)
    {
        encrypt_decrypt = &encrypt;
    }
    else if (strcmp(argv[2], "-d") == 0)
    {
        encrypt_decrypt = &decrypt;
    }

    int key = atoi(argv[1]);

    // check if key is valid
    if (key == 0 && strcmp(argv[1], "0") != 0)
    {
        printf("error not valid key\n");
        return 0;
    }

    // init the threads
    pthread_t th[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0)
        {
            perror("Failed to create the thread");
        }
    }

    // seperates the input into 1024 char chunks and sumbits tasks to the thread pool
    readChars(key);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join the thread");
        }
    }

    //destroy mutex and cond variables
    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
    pthread_cond_destroy(&condPrint);
    return 0;
}