#include "item.h"

typedef struct room
{
	char *name;
	char *description;
	Item * item;
	struct room * north;
	struct room * west;
	struct room * east;
	struct room * up;
	struct room * down;
	bool omen;
	bool Event;
}
Room;

Room* createRoom(char *name, char *description, Item *items, Room *north, Room *west, Room *east, Room *up, Room *down, bool omen, bool Event);

void printArray(int arr[]);
void randArry(int array[]);
void adjRoomLook(Room *adjRoom);