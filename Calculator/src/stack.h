#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef STACK_H_
#define STACK_H_
int pushElement(stack *thisStack, stackElement *thisElement);
stackElement *popElement(stack *thisStack);
#endif
