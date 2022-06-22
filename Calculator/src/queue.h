#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef QUEUE_H_
#define QUEUE_H_
iElement *nextElement(queue *inQueue);
int queueAppend(queue *inQueue, iElement *newElement);
#endif
