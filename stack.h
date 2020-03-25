#include "room.h"

typedef struct StackNodeLL
{
	Room * stackRoom;
	struct StackNodeLL * next;
}
Stack;

Stack* createStack(Room *stackRoom, Stack *next);

Room* pop();
void push(Room *room);