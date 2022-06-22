#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
iElement *nextElement(queue *inQueue)
//Функция для получения первого элемента из очереди(головы)
{
	iElement *next = inQueue->head;
	inQueue->head = inQueue->head->nextElement;
	return next;
}
int queueAppend(queue *inQueue, iElement *newElement)
//Функция для добавления нового элемента в начало очереди
{
	if(inQueue->head == NULL) inQueue->head = newElement;
	if(inQueue->last != NULL) inQueue->last->nextElement = newElement;
	inQueue->last = newElement;
	return 0;
}
