#ifndef startThreads_H
#define startThreads_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "myqueue.h"

void *startThread(void *args);

#endif