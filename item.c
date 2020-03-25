#include "item.h"

Item* createItem(char *name, char *description, Item *next)
{
	Item *newItem = (Item*) malloc(sizeof(Item));

	newItem->name = name;
	newItem->description = description;
	newItem->next = next;
	return newItem;
}	//item struct

void printInventory(Item **tempInv)
{
	if (*tempInv == NULL)	//if Inventory is empty
		printf("Your Inventory is Empty\n");

	Item *temp = *tempInv;	//copy of list
	while (temp != NULL)
	{
		//iterates to the end of the list
		printf("%s: %s \n", temp->name, temp->description);	//prints each item of the list
		temp = temp->next;	//goes to next item until next item is NULL
	}
}