#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item
{
	char *name;
	char *description;
	struct item * next;
}
Item;

Item* createItem(char *name, char *description, Item *next);

void printInventory(Item **tempInv);