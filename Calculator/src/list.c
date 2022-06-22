#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
iElement *nextListElement(list *inList)
//Функция для перехода к следующему элементу списка
{
	iElement *next = inList->current->nextElement;
	inList->current =  next;
	return next;
}
int listAppend(list *inList, iElement *newElement)
//Функция для добавления нового элемента в список
{
	if(inList->head == NULL)
	{
		inList->head = newElement;
		inList->current = newElement;
		return 0;
	}
	inList->current->nextElement = newElement;
	inList->current = newElement;
	return 0;
}
int goHeadElement(list *inList)
//Функция для перехода из тукущего элемента списка к первому
{
	inList->current =  inList->head;
	return 0;
}
int deleteElement(list *inList)
//Функция для удаления элемента из списка
{
	iElement *delete = inList->current;
	if(delete == inList->head)
	{
		inList->head = delete->nextElement;
		nextListElement(inList);
	}
	else
	{
		goHeadElement(inList);
		while(inList->current->nextElement != delete) nextListElement(inList);
		inList->current->nextElement = delete->nextElement;
		if(delete->nextElement != NULL) inList->current = delete->nextElement;
	}
	free(delete);
	return 0;
}
