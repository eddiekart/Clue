/*
 * items.h
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */

#ifndef ITEMS_H_
#define ITEMS_H_

/**
 * Struct for items
 * Contains two strings: Name and Description
 * Contains data for a pointer to next item linked to this item
 * LinkedList of items are used to "contain" multiple items in a room/backpack
 */
struct Item{
	// Name of item
	char* name;

	// Desc of item
	char* desc;

	// Next item in linkedlist

	struct Item* next;
};

/**
 * Takes in name and description strings and a pointer to item to link to
 * Creates items with given data and returns pointer to item
 */
struct Item * items(char* name, char* desc, struct Item *next);

/**
 * Creates dummy item designed to be the first item of an item linked list
 * Params are:
 * name: "dummy"
 * desc: "dummy"
 * next: "NULL"
 */
struct Item * dummyItem(void);

/**
 * Function that takes in an item and returns the name of the item
 */
char* item_name(struct Item *item);

/**
 * Function that takes in an item and returns the description of the item
 */
char* item_desc(struct Item *item);

/**
 * Function that takes in an item and returns the next item
 */
struct Item* item_next(struct Item *item);

/**
 * Function to set the name data of an item
 */
void item_setName(struct Item *item, char* name);

/**
 * Function to set the desc data of an item
 */
void item_setDesc(struct Item *item, char* desc);

/**
 * Function to set the next data of an item
 */
void item_setNext(struct Item *item, struct Item *next);

/**
 * Function that takes in an item and name of item to search for
 * Returns pointer to item with given name if found
 * Removes the item found from the linkedlist of the given Item
 * If not found, returns NULL
 * Needs to be used with item linked list where the first item is a dummy item
 */
struct Item* item_take(struct Item *item, char* name);

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
void item_add(struct Item *list, struct Item *toAdd);

/**
 * Iterates through linkedList of this item to see if item find is in there
 * Returns 0 if false, 1 if true
 */
int item_has(struct Item *list, char* name);

/**
 * Function that takes in Item struct
 * Prints out all the items linked to the Item given
 */
void item_print(struct Item *list);

#endif /* ITEMS_H_ */
