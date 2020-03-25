#include <stdio.h>
#include <ctype.h>
#include "keyword.h"
#define BUFFER 20

int initializeGameboard(Character *avatar)	//creates all the rooms and items and adds items to their respective rooms
{
	Item *flashlight = createItem("flashlight", "is a light source in the dark, but there are no batteries in it", NULL);
	Item *crowbar = createItem("crowbar", "a tool and a weapon, but it's integrity is weak", NULL);

	Room *garage = createRoom("Garage", "it's dirty, there are tools everywhere", crowbar, NULL, NULL, NULL, NULL, NULL, false, false);

	Room *livingRoom = createRoom("Living Room", "Windows are broken, Couches are torn, and blood splatter on the walls", NULL, NULL, NULL, NULL, NULL, NULL, false, true);

	Room *kitchen = createRoom("Kitchen", "moldy food everywhere", flashlight, NULL, NULL, NULL, NULL, NULL, false, false);

	Room *bedroom = createRoom("bedroom", "windows were boarded up, deadbolts on the door, canned food in the corner, and an empty gun on the shelf\nSomeone was hiding in here", NULL, NULL, NULL, NULL, NULL, NULL, true, false);

	Room *bathroom = createRoom("Bathroom", "Blood is everywhere", NULL, NULL, NULL, NULL, NULL, NULL, true, false);

	Room *secretRoom = createRoom("Hidden Room", "There was a secret room that was walled up", NULL, NULL, NULL, NULL, NULL, NULL, false, true);

	Room *dummy = createRoom("DUMMY", "DUMMY", NULL, NULL, NULL, NULL, NULL, NULL, false, false);	//NOT to be used in game, used to check if user runs out of rooms in "pile"
	push(dummy);	//first room in stack
	int arr[6] = { 1, 2, 3, 4, 5, 6 };	//6 remaining rooms correspond to a number
	randArry(arr);	//shuffles int array of 6 elements
	//printArray(arr);	//temporary (prints order of stack backwards as i forgot stacks are LIFO)

	Keyword *list = createKeyword("go north", "moves in north direction", NULL);	//first command for list of commands
	list = initKeywordList(list);	//this creates remaining commands and linkes them together
	avatar->list = list;	//sets the list of commands the avatar can use to avatar

	for (int i = 0; i < 6; i++)	//6 numbers in arr above(numbers in random order)
		switch (arr[i])	//goes through each element of arr and pushes respective room to stack
	{
		case 1:
			push(garage);
		  break;
		case 2:
			push(bathroom);
		  break;
		case 3:
			push(bedroom);
		  break;
		case 4:
			push(secretRoom);
		  break;
		case 5:
			push(kitchen);
		  break;
		case 6:
			push(livingRoom);
	  	break;
	}
	return 0;
}

int commandInput(Character *avatar, Room *startRoom)	//takes input of User
{
	printf("\nInput your command: ");
	char userInput[BUFFER] = "";	//where input is stored
	userInput[0] = '\0';	//clears any garbage in buffer
	fgets(userInput, BUFFER, stdin);	//store input to char array
	for (int i = 0; userInput[i]; i++)
		userInput[i] = tolower(userInput[i]);	//convert inputed command to lower case
	userInput[strlen(userInput) - 1] = '\0';	//replaces \n in char array to \0

	if (isValidInput(userInput, avatar->list) == true)	//checks if user input is valid by going through command LL
		inputCommand(avatar, userInput, startRoom);	//function call to actually play the game
	else if (isValidInput(userInput, avatar->list) == false) printf("\ninvalid command\n");	//if invalid command
	return 0;
}

int main(void)
{
	bool endgameState = false;	//checks if game has ended

	Room *startRoom = createRoom("Creepy Room", "Where am I? It's Dark", NULL, NULL, NULL, NULL, NULL, NULL, false, false);	//creates starting room

	Character *user = createAvater(NULL, NULL, NULL, false);	//creates avatar

	initializeGameboard(user);	//creates 'gameboard'
	user->position = startRoom;	//sets users sarting pos
	printf("Welcome to Word Adventure\n");
	printCommands(user->list);
	while (endgameState == false)	//if user hasn't died or won
	{
		if (user->omenPass == true && user->position == startRoom && user->inventory != NULL && user->inventory->next != NULL)	//checks for win condition
		{
			printf("\n You Win!\n");
			break;	//breaks from if user wins
		}
		if (strncmp(user->position->name, "DUMMY", 5) == 0 && strncmp(user->position->description, "DUMMY", 5) == 0)	//checks for no more valid rooms left in stack (DUMMY is invalid room)
		{
			printf("you fell down and burned to death\n");	//death statement
			break;	//breaks from loop because death
		}
		fflush(stdin);	//clears any garbage value in input buffer
		commandInput(user, startRoom);	//takes user input
		fflush(stdin);	//clears any garbage value in input buffer
	}
	printf("Game over");
	//deallocates memory below
  free(user->position);
	free(user->inventory);
	free(user->list);
	free(user);
	free(startRoom);
	return 0;
}