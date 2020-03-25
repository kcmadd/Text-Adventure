#include "stack.h"

typedef struct keyword
{
	char *name;
	char *description;
	struct keyword * next;
}
Keyword;

typedef struct avatar
{
	Item * inventory;	//maximum 2 items in inventory
	Room * position;	//current position of the avatar
	Keyword * list;
	bool omenPass;
}
Character;

Character* createAvater(Item *inventory, Room *position, Keyword *list, bool omenPass);

Keyword* createKeyword(char *name, char *description, Keyword *next);

Keyword* initKeywordList(Keyword *list);
bool isValidInput(char buffer[], Keyword *list);
int printCommands(Keyword *list);
int inputCommand(Character *avatar, char userInput[], Room *startRoom);
int addCommand(Keyword *list);