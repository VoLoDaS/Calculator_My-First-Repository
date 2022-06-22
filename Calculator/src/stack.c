#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
int pushElement(stack *thisStack, stackElement *thisElement)
//Функция для добавления нового элемента в стек
{
	thisElement->next = thisStack->head;
	thisStack->head = thisElement;
	return 0;
}
stackElement *popElement(stack *thisStack)
//Функция для извлечения элемента из стека
{
	stackElement *st = thisStack->head;
	thisStack->head = thisStack->head->next;
	return st;
}
