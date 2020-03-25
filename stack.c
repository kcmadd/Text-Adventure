#include "stack.h"

Stack * top;

Stack* createStack(Room *stackRoom, Stack *next)
{
	Stack *newStack = (Stack*) malloc(sizeof(Stack));
	newStack->stackRoom = stackRoom;
	newStack->next = next;
	return newStack;
}


Room* pop()
{
	//removes from top of stack

	Stack * temp;
	temp = top;
	top = top->next;
	temp->next = NULL;
	Room *poppedRoom = temp->stackRoom;
	free(temp);
	return poppedRoom;
}

void push(Room *room)
{
	//pushes to stack
	//printf("%d", a);
	Stack *temp = createStack(NULL, NULL);
	temp->stackRoom = room;
	temp->next = top;
	top = temp;
}