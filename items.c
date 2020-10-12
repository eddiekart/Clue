/*
 * items.c
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */

#include "items.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Takes in name and description strings and a pointer to item to link to
 * Creates items with given data and returns pointer to item
 */
struct Item * items(char* name, char* desc, struct Item *next){
	// Allocating memory for Item being created
	struct Item *temp = (struct Item *) malloc(sizeof(struct Item));

	// Case where malloc fails
	if (temp == NULL){
		// Print message for exact location/item being created when malloc failed
		printf("MALLOC FAILED\n");
		printf("Location: items()\nName: %s\nDesc: %s\n", name, desc);
		exit(-1);
	}

	// Malloc succeeded; defining data for new Item
	temp->name = name;
	temp->desc = desc;
	temp->next = next;
	return temp;
}

/**
 * Creates dummy item designed to be the first item of an item linked list
 * Returns pointer to dummy item
 * Params are:
 * name: "dummy"
 * desc: "dummy"
 * next: "NULL"
 */
struct Item *dummyItem(void){
	// Allocating memory for Item being created
	struct Item *temp = (struct Item *)malloc(sizeof(struct Item));
	// Case where malloc fails
	if (temp == NULL){
		// Print message for exact location/item being created when malloc failed
		printf("MALLOC FAILED\n");
		printf("Location: Dummy Item Creation\n");
		exit(0);
	}

	// Malloc success; defining data for new item
	temp->name = "dummy";
	temp->desc = "dummy";
	temp->next = NULL;
	return temp;
}

/**
 * Function that takes in an item and returns the name of the item
 * Returns NULL if item is null
 */
char* item_name(struct Item *item){
	if (item == NULL){
		return NULL;
	}
	return item->name;
}

/**
 * Function that takes in an item and returns the description of the item
 * Returns NULL if item is null
 */
char* item_desc(struct Item *item){
	if (item == NULL){
		return NULL;
	}
	return item->desc;
}

/**
 * Function that takes in an item and returns the next item
 * Returns NULL if item is null
 */
struct Item* item_next(struct Item *item){
	if (item == NULL){
		return NULL;
	}
	return item->next;
}

/**
 * Function to set the name data of an item
 */
void item_setName(struct Item *item, char* name){
	// Does not function if item is null
	if (item != NULL){
		item->name = name;
	}
}

/**
 * Function to set the desc data of an item
 */
void item_setDesc(struct Item *item, char* desc){
	// Does not function if item is null
	if (item != NULL){
		item->desc = desc;
	}
}

/**
 * Function to set the next data of an item
 */
void item_setNext(struct Item *item, struct Item *next){
	// Does not function if item is null
	if (item != NULL){
		item->next = next;
	}
}

/**
 * Function that takes in an item and name of item to search for
 * Returns pointer to item with given name if found
 * If not found, returns NULL
 * Needs to be used with item linked list where the first item is a dummy item
 */
struct Item* item_take(struct Item *item, char* name){
	if (item == NULL){
		return NULL;
	}
	// Variable used for current item in loop
	struct Item *currItem = item;
	// Variable used for next item in loop
	struct Item *nextItem = item_next(currItem);
	// Goes through item linked list until there is no next item
	while (nextItem != NULL){
		// Checking for if next item is the item function is looking for
		if (strcmp(item_name(nextItem), name) == 0){
			// Removing nextItem from linked list and linking curr item with nextItem's next item
			item_setNext(currItem, item_next(nextItem));
			// Removing nextItem's link to the list
			item_setNext(nextItem, NULL);
			return nextItem;
		}
		// Iterating through linked list of item
		currItem = nextItem;
		nextItem = item_next(currItem);
	}
	// Item name not found
	return NULL;
}

/**
 * Function that adds given item to a given item list
 * Takes in pointers to item list, and item to add to that item list
 *
 * HOW TO USE
 *
 * When adding items to BACKPACK from ROOM:
 * item_take(item from room), and then item_add(backpack, pointer from item_take)
 *
 * When adding items to ROOM from BACKPACK:
 * item_take(item from backpack), and then item_add(room, pointer from item_take)
 */
void item_add(struct Item *list, struct Item *toAdd){
	// Only adds when list is not null
	if (list != NULL){
		// Variable used for current item in loop
		struct Item *currItem = list;
		// Variable used for next item in loop
		struct Item *nextItem = item_next(list);
		// Iterates until nextItem is NULL, aka reaching end of linkedlist
		while (nextItem != NULL){
			currItem = nextItem;
			nextItem = item_next(currItem);
		}
		// Adding item toAdd to the end of the list
		item_setNext(currItem, toAdd);
	}
}

/**
 * Iterates through linkedList of this item to see if item find is in there
 * Returns 0 if false, 1 if true
 */
int item_has(struct Item *list, char* name){
	if (list != NULL && name != NULL){
		// Variable used for current item in loop
		struct Item *currItem = list;
		// Variable used for next item in loop
		struct Item *nextItem = item_next(list);
		while (nextItem != NULL){
			if (strcmp(item_name(nextItem), name) == 0){
				return 1;
			}
			currItem = nextItem;
			nextItem = item_next(currItem);
		}
	}
	return 0;
}

/**
 * Function that takes in a pointer to an Item struct
 * Prints out all the items linked to the Item given
 */
void item_print(struct Item *list){
	struct Item *currItem = list;
	struct Item *nextItem = item_next(currItem);
	if (nextItem == NULL){
		printf("No items\n");
	} else {
		while (nextItem != NULL){
			printf("%s\n", item_name(nextItem));
			currItem = nextItem;
			nextItem = item_next(currItem);
		}
	}
}

