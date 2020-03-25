#include "room.h"
#include <time.h>

Room* createRoom(char *name, char *description, Item *item, Room *north, Room *west, Room *east, Room *up, Room *down, bool omen, bool Event)
{

	Room *newRoom = (Room*) malloc(sizeof(Room));

	newRoom->name = name;
	newRoom->description = description;
	newRoom->item = item;
	newRoom->north = north;
	newRoom->west = west;
	newRoom->east = east;
	newRoom->up = up;
	newRoom->down = down;
	newRoom->omen = omen;
	newRoom->Event = Event;

	return newRoom;
}

void printArray(int arr[])
{
	for (int i = 0; i < 6; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void randArry(int array[])
{
	//randomizes numbers between 1 and 6 (each number corresponds to a room)
	srand(time(NULL));	//to make sure the same seed isn't used
	for (int i = 1; i < 6; i++)
	{
		int j = rand() % i;	//generate rand number between 1 and 6
		//swapping elements
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

void adjRoomLook(Room *adjRoom)
{
	//prints adj rooms to see if the exist or not
	if (adjRoom->north == NULL) printf("North is an Unexplored Area\n");
	else printf("North is %s\n", adjRoom->north->name);

	if (adjRoom->east == NULL) printf("East is an Unexplored Area\n");
	else printf("East is %s\n", adjRoom->east->name);

	if (adjRoom->west == NULL) printf("West is an Unexplored Area\n");
	else printf("West is %s\n", adjRoom->west->name);

	if (adjRoom->up == NULL) printf("Up is an Unexplored Area\n");
	else printf("Up is %s\n", adjRoom->up->name);

	if (adjRoom->down == NULL) printf("Down is an Unexplored Area\n\n");
	else printf("Down is %s\n\n", adjRoom->down->name);
}