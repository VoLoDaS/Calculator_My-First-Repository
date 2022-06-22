#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef LIST_H_
#define LIST_H_
iElement *nextListElement(list *inList);
int listAppend(list *inList, iElement *newElement);
int goHeadElement(list *inList);
int deleteElement(list *inList);
#endif
