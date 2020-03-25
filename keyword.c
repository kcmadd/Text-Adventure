#include "keyword.h"

int commandCount = 0;//counter to prevent user from adding command more than once
Keyword* createKeyword(char *name, char *description, Keyword *next)
{
	Keyword *newKeyword = (Keyword*) malloc(sizeof(Keyword));	//allocating memory
	newKeyword->name = name;	//name of command
	newKeyword->description = description;	//description of command
	newKeyword->next = next;	//next node
	return newKeyword;
}

Character* createAvater(Item *inventory, Room *position, Keyword *list, bool omenPass)
{
	Character *user = (Character*) malloc(sizeof(Character));	//allocating memory
	user->inventory = NULL;	//inventory of avatar
	user->position = NULL;	//position of avatar on "map"
	user->omenPass = false;	//checks if user passed an omen room
	user->list = NULL;	//list of commands user can use
	return user;
}	// Avatar struct

Keyword* initKeywordList(Keyword *list)
{
	//created "nodes" for LL containing commands
	//"creates" each respective command (all unlinked)
	Keyword *goE = createKeyword("go east", "moves in east direction", NULL);
	Keyword *goW = createKeyword("go west", "moves in west direction", NULL);
	Keyword *goU = createKeyword("go up", "moves in up direction", NULL);
	Keyword *goD = createKeyword("go down", "moves in down direction", NULL);
	Keyword *takeF = createKeyword("take flashlight", "takes flashlight from room", NULL);
	Keyword *takeC = createKeyword("take crowbar", "takes crowbar from room", NULL);
	Keyword *dropF = createKeyword("drop flashlight", "drops flashlight from inventory", NULL);
	Keyword *dropC = createKeyword("drop crowbar", "drops crowbar from inventory", NULL);
	Keyword *inven = createKeyword("inventory", "views inventory", NULL);
	Keyword *see = createKeyword("look", "command for look", NULL);
	Keyword *add = createKeyword("add command", "add command to list of commands", NULL);
	Keyword *help = createKeyword("help", "valid input menu", NULL);

	//commands above are linked together to create a linked list of commands
	help->next = NULL;
	add->next = help;
	see->next = add;
	inven->next = see;
	dropC->next = inven;
	dropF->next = dropC;
	takeC->next = dropF;
	takeF->next = takeC;
	goD->next = takeF;
	goU->next = goD;
	goW->next = goU;
	goE->next = goW;
	list->next = goE;
	return list;
}

bool isValidInput(char buffer[], Keyword *list)
{
	//checks if user input 
	Keyword *temp = list;	//temporary list
	while (temp != NULL)
	{
		//checks node is NULL
		if (strcmp(buffer, temp->name) == 0)
		{
			//compares user input to node
			return true;	//if true returns 0
			break;	//breaks out of loop
		}
		temp = temp->next;	//goes to next node of command LL
	}
	return false;	//if command not found, retun false
}

int printCommands(Keyword *list)
{
	//used for "help" command
	Keyword *temp = list;	//temp list
	printf("\nList of commands:\n\n");
	while (temp != NULL)
	{
		//while node isn't null
		printf("%s: %s\n", temp->name, temp->description);	//prints name and descption
		temp = temp->next;	//goes to next node
	}
	printf("\n");
	return 0;
}

int addCommand(Keyword *list)
{
	//used for "add command" command
	Keyword *temp = createKeyword(NULL, NULL, NULL);
  temp = list;	//temp list
	while (temp != NULL)
	{
		//while node isn't null
		if (temp->next != NULL)	//checks if next node isn't null
			temp = temp->next;	//goes to next node
		else break;	//if next node is null, then we're at last node of LL
	}
	char tempName[1000] = "";	//stores inputed name for new command
	char tempDes[1000] = "";	//stores inputed description for new command
	tempName[0] = '\0';	//clears any garbage value
	tempDes[0] = '\0';	//clears any garbage value
	printf("\nwhat's the name of the command you want to add:\n");
	fgets(tempName, 1000, stdin);	//puts inputed name to char array
	tempName[strlen(tempName) - 1] = '\0';	//replaces "\n" in array with "\0"
	printf("\nwhat's the description of the command you want to add:\n");
	fgets(tempDes, 1000, stdin);	//puts inputed des. to char array
	tempDes[strlen(tempDes) - 1] = '\0';	//replaces "\n" in array with "\0"
	Keyword *temp2 = createKeyword(tempName, tempDes, NULL);	//creates new node with name and description inputted
	temp->next = temp2;	//sets next node in LL to new node with inputted info
	return 0;
}

int inputCommand(Character *avatar, char userInput[], Room *startRoom)
{
	//takes user input, avatar, and startroom
	if (strncmp(userInput, "look", 4) == 0)	// letters of input is exactly "look". if user inputs "looke", will get caught by isValidInput function
	{
		//views what is in room
		printf("\n%s\n", avatar->position->description);	//prints description of room
		printf("You're in a %s\n\n", avatar->position->name);	//prints name of room
		adjRoomLook(avatar->position);	//prints adjacent room (if they have been explored or not)
		//printInventory(&(avatar->position->item));

		if (avatar->position->item != NULL)	//checks if and prints room contain(s) item(s)
		{
			printf("there's a %s in the room\nThe item is %s\n\n", avatar->position->item->name, avatar->position->item->description);
			if (avatar->position->item->next != NULL) printf("there's a %s in the room\nThe item is %s\n\n", avatar->position->item->next->name, avatar->position->item->next->description);
		}
	}
	else if (strncmp(userInput, "go", 2) == 0)	//if user input starts with go
	{

		if (strncmp(userInput, "go north", 8) == 0)	//if user input is go north
		{
			if (avatar->position->north != NULL)	//checks if north is explored
				avatar->position = avatar->position->north;	//if it is, then user moves to that direction
			else
			{
				Room *temp = pop();	//if unexplored, then pops room from stack ("pile") of rooms
				if (temp->Event == true)	//checks if event room
				{
					avatar->position = temp;	// position changes to event room
					printf("\nan event has occurred\n");
					avatar->position->north = startRoom;	//event room points north
				}
				else
				{
					avatar->position->north = temp;	//if not event, sets popped room north
					avatar->position = avatar->position->north;	//position becomes north
				}
			}
		}
		else if (strncmp(userInput, "go west", 7) == 0)	//same as north but with "west" direction
		{
			if (avatar->position->west != NULL)
				avatar->position = avatar->position->west;
			else
			{
				Room *temp = pop();
				if (temp->Event == true)
				{
					avatar->position = temp;
					printf("\nan event has occurred\n");
					avatar->position->north = startRoom;
				}
				else
				{
					avatar->position->west = temp;
					avatar->position->west->east = avatar->position;
					avatar->position = avatar->position->west;
				}
			}
		}
		else if (strncmp(userInput, "go east", 7) == 0)	//same as north, but with "east" direction 
		{

			if (avatar->position->east != NULL)
				avatar->position = avatar->position->east;
			else
			{
				Room *temp = pop();
				if (temp->Event == true)
				{
					avatar->position = temp;
					printf("\nan event has occurred\n");
					avatar->position->north = startRoom;
				}
				else
				{
					avatar->position->east = temp;
					avatar->position->east->west = avatar->position;
					avatar->position = avatar->position->east;
				}
			}
		}
		else if (strncmp(userInput, "go down", 7) == 0)	//same as north, but with "down" direction
		{
			if (avatar->position->down != NULL)
				avatar->position = avatar->position->down;
			else
			{
				Room *temp = pop();
				if (temp->Event == true)
				{
					avatar->position = temp;
					printf("\nan event has occurred\n");
					avatar->position->north = startRoom;
				}
				else
				{
					avatar->position->down = temp;
					avatar->position->down->up = avatar->position;
					avatar->position = avatar->position->down;
				}
			}
		}
		else if (strncmp(userInput, "go up", 5) == 0)	//same as north, but with "up" direction
		{
			if (avatar->position->up != NULL)
				avatar->position = avatar->position->up;
			else
			{
				Room *temp = pop();
				if (temp->Event == true)
				{
					avatar->position = temp;
					printf("\nan event has occurred\n");
					avatar->position->north = startRoom;
				}
				else
				{
					avatar->position->up = temp;
					avatar->position->up->down = avatar->position;
					avatar->position = avatar->position->up;
				}
			}
		}
		else
		{
			if (isValidInput(userInput, avatar->list) == false)	//checks if user added a command starting with "go" to list 
				printf("\ninvalid directional command\n");
		}

		if (avatar->position->omen == true)
		{
			//checks if avatar passed an Omen room
			printf("\nit feels ominous in here\n");
			avatar->omenPass = true;	//if true, changes omen flag to true
		}
	}
	else if (strncmp(userInput, "take", 4) == 0)	//checks if userInput starts with take
	{
		Item * tempR;	//temp item (most cases used to remove first item in room if user drops item in room and there are two items)

		//takes item from room
		if (strncmp(userInput, "take flashlight", 15) == 0)	//checks if input is "take flashlight"
		{
			if (avatar->position->item == NULL)	//checks if item exists in room
				printf("item not in room\n");
			else if (strncmp(avatar->position->item->name, "flashlight", 10) == 0 && avatar->position->item->next == NULL)	//checks if flashlight is the only item in the room
			{
				if (avatar->inventory == NULL)	//if avatar inventory doesn't have anything
				{
					avatar->inventory = avatar->position->item;	//"copies" item to inventory
					avatar->position->item = NULL;	//deletes item from room
				}
				else if (avatar->inventory != NULL && avatar->inventory->next == NULL && strncmp(avatar->position->item->name, "flashlight", 10) == 0)	//checks if avatar is already carrying another item
				{
					avatar->inventory->next = avatar->position->item;	//next item in inventory becomes flashlight 
					avatar->position->item = NULL;	//sets item in room to null
				}
			}
			else if (strncmp(avatar->position->item->next->name, "flashlight", 10) == 0)	//if both items are in room and second item is flashlight
			{
				avatar->inventory = avatar->position->item->next;	//sets flashlight(second item) to first item in inventory
				avatar->position->item->next = NULL;	//second item in room set to null
			}
			else if (strncmp(avatar->position->item->name, "flashlight", 10) == 0 && avatar->position->item->next != NULL)	//if both items are in room and first item is flashlight
			{

				tempR = avatar->position->item->next;	//copies second item in room to temp
				avatar->position->item->next = NULL;	//removes it
				avatar->inventory = avatar->position->item;	//sets first item in inventory to remaining item
				avatar->position->item = tempR;	//sets copied second item as first item in room
			}
		}
		else if (strncmp(userInput, "take crowbar", 12) == 0)	//same as flashlight but with crowbar instead
		{
			if (avatar->position->item == NULL)
				printf("item not in room\n");
			else if (strncmp(avatar->position->item->name, "crowbar", 7) == 0 && avatar->position->item->next == NULL)
			{
				if (avatar->inventory == NULL)
				{
					avatar->inventory = avatar->position->item;
					avatar->position->item = NULL;
				}
				else if (avatar->inventory != NULL && avatar->inventory->next == NULL && strncmp(avatar->position->item->name, "crowbar", 7) == 0)
				{
					avatar->inventory->next = avatar->position->item;
					avatar->position->item = NULL;
				}
			}
			else if (strncmp(avatar->position->item->next->name, "crowbar", 7) == 0)
			{
				avatar->inventory = avatar->position->item->next;
				avatar->position->item->next = NULL;
			}
			else if (strncmp(avatar->position->item->name, "crowbar", 7) == 0 && avatar->position->item->next != NULL)
			{
				tempR = avatar->position->item->next;
				avatar->position->item->next = NULL;
				avatar->inventory = avatar->position->item;
				avatar->position->item = tempR;
			}
		}
	}
	else if (strncmp(userInput, "drop", 4) == 0)	//checks if first part of iuser input is "drop"
	{
		//drops item from inventory
		Item * temp;	//temp item (most cases used to remove first item in room if user drops item in room and there are two items)
		if (strncmp(userInput, "drop flashlight", 15) == 0)	//if user input is drop flashlight
		{
			if (avatar->inventory == NULL || (strcmp(avatar->inventory->name, "crowbar") == 0 && avatar->inventory->next == NULL))	//checks if item exists in Inventory
				printf("item not in inventory\n");
			else if (strncmp(avatar->inventory->name, "flashlight", 10) == 0)	//if item is first item in inventoy
			{
				if (avatar->position->item == NULL && avatar->inventory->next == NULL)	//if second item doesn't exist in inventory 
				{ 
					avatar->position->item = avatar->inventory;	//copies item from inventory to room
					avatar->inventory = NULL;	//sets item to null
				}
				else if (avatar->position->item == NULL && strncmp(avatar->inventory->next->name, "crowbar", 7) == 0)	//if crowbar is the second item in the inventory and user wants to remove the first item(flashlight)
				{
					temp = avatar->inventory->next;	//copies second item to temp
					avatar->inventory->next = NULL;	//sets second item in inventory to null
					avatar->position->item = avatar->inventory;	//copies first item in inventory to room
					avatar->inventory = temp;	//users inventory is now second item
				}
				else if (avatar->position->item != NULL && avatar->inventory->next == NULL)	//if room already has item
				{
					avatar->position->item->next = avatar->inventory;	//sets next item in room to inventory
					avatar->inventory = NULL;	//inventory set to null
				}
			}
			else if (strncmp(avatar->inventory->next->name, "flashlight", 10) == 0)	//flashlight is second item in inventory
			{
				if (avatar->position->item == NULL && strncmp(avatar->inventory->next->name, "flashlight", 10) == 0)	//no item exist in room
				{
					avatar->position->item = avatar->inventory->next;	//sets first item in room to second item in inventory
					avatar->inventory->next = NULL;	//second item in inventory is set to null
				}
				else if (avatar->position->item != NULL && strncmp(avatar->inventory->next->name, "flashlight", 10) == 0)	//item exist in room
				{
					avatar->position->item->next = avatar->inventory->next;	//sets second item in inventory to null and copies over to room
					avatar->inventory->next = NULL;	//second item in room set to NULL
				}
			}
		}
		else if (strncmp(userInput, "drop crowbar", 12) == 0)	//same as flashlight but with crowbar instead
		{
			if (avatar->inventory == NULL || (strcmp(avatar->inventory->name, "flashlight") == 0 && avatar->inventory->next == NULL))
				printf("item not in inventory\n");
			else if (strncmp(avatar->inventory->name, "crowbar", 7) == 0)
			{
				if (avatar->position->item == NULL && avatar->inventory->next == NULL)
				{
					avatar->position->item = avatar->inventory;
					avatar->inventory = NULL;
				}
				else if (avatar->position->item == NULL && strncmp(avatar->inventory->next->name, "flashlight", 10) == 0)
				{
					temp = avatar->inventory->next;
					avatar->inventory->next = NULL;
					avatar->position->item = avatar->inventory;
					avatar->inventory = temp;
				}
				else if (avatar->position->item != NULL && avatar->inventory->next == NULL)
				{
					avatar->position->item->next = avatar->inventory;
					avatar->inventory = NULL;
				}
				else if (avatar->position->item != NULL && strncmp(avatar->inventory->next->name, "flashlight", 10) == 0)
				{
					temp = avatar->inventory->next;
					avatar->position->item = avatar->inventory;
					avatar->inventory = avatar->inventory->next;
					avatar->inventory->next = NULL;
				}
			}
			else if (strncmp(avatar->inventory->next->name, "crowbar", 7) == 0)
			{
				if (avatar->position->item == NULL && strncmp(avatar->inventory->next->name, "crowbar", 7) == 0)
				{
					avatar->position->item = avatar->inventory->next;
					avatar->inventory->next = NULL;
				}
				else if (avatar->position->item != NULL && strncmp(avatar->inventory->next->name, "crowbar", 7) == 0)
				{
					avatar->position->item->next = avatar->inventory->next;
					avatar->inventory->next = NULL;
				}
			}
		}
	}
	else if (strncmp(userInput, "inventory", 9) == 0)	//prints inventory of user
	{
		printInventory(&(avatar->inventory));	//see comments to see how this works
	}
	else if (strncmp(userInput, "help", 4) == 0)	//help command-- Lists all the possible commands a user can input(inluding ones that have been manually added)
		printCommands(avatar->list);
	else if (strncmp(userInput, "add command", 4) == 0)
	{
		//adds command to list
    if(commandCount != 1){
		addCommand(avatar->list);	//see comments above to see how this works
    commandCount = 1;//user can only add a command as per instructions
    }
    else printf("you've already added a command\n");
	}
	return 0;
}