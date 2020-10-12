/*
 * characters.h
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */


#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include "items.h"

/**
 * Structure for Character
 * Contains a string: name, used for name
 * Contains item: a pointer to an item linkedlist, used as inventory (probably of the player)
 * Contains character: a pointer to a character struct, for other characters located in the same room
 */
struct Character{
	char* name;
	struct Item *inventory;
	struct Character *next;
};

/**
 * "Constructor" for character
 * Takes in a string for character's name
 * Takes in a character pointer for a linkedlist of characters in the same room
 * Automatically adds dummy item to the inventory
 */
struct Character *character(char* name, struct Character *next);

/**
 * Constructor for a dummy character structure
 * Data values are "dummy", NULL, NULL
 * Used to hold first position in a character linked list
 */
struct Character *dummyChar(void);

/**
 * Function that takes in a pointer to a Character structure
 * Returns character's name
 * Returns NULL if Character pointer is null
 */
char* char_name(struct Character *piece);

/**
 * Function that takes in a pointer to a Character structure
 * Returns character's inventory
 * Returns NULL if character is NULL or is a dummy character
 */
struct Item *char_inventory(struct Character *piece);

/**
 * Function that takes in a pointer to a Character structure
 * Returns a pointer to the next character structure in the linkedlist
 * Returns NULL if Character pointer is null
 */
struct Character *char_next(struct Character *piece);

/**
 * Function that takes in a pointer to a Character struct and a string
 * Sets the character's name as the input string
 * Does not do anything if input Character to be operated on is null
 */
void char_setName(struct Character *piece, char* name);

/**
 * Function that takes in a pointer to a Character struct and a pointer to a different Character struct
 * Sets the character's next character pointer as the input character pointer
 * Does not do anything if input Character to be operated on is null
 */
void char_setNext(struct Character *piece, struct Character *next);

/**
 * Function that takes in pointer to a Character struct and a string of item to remove from inventory
 * Removes item from character's inventory and returns pointer to it if found
 * Uses item_take() from items.c
 * If not found, returns NULL
 * This function is an alternative to obtaining character's inventory pointer and operating directly on it
 */
struct Item *char_takeItem(struct Character *piece, char* name);

/**
 * Function that takes in pointer to a Character struct and an Item struct
 * Puts item struct into character's inventory
 * Uses item_add() from items.c
 * This function is an alternative to obtaining character's inventory pointer and operating directly on it
 */
void char_giveItem(struct Character *piece, struct Item *item);

/**
 * Function that takes in a Character pointer and name of character to take
 * Returns pointer to character with given name if found
 * Removes the character found from the linkedlist of the input Character
 * If not found, returns NULL
 * Needs to be used with item linked list where the first item is a dummy character, created by dummyChar()
 */
struct Character *char_take(struct Character *piece, char* name);

/**
 * Function that adds given character to a given character list
 * Takes in pointers to item list, and item to add to that item list
 * To take from list and add to another, use char_take to obtain the character to add first
 * Can use like char_add(destination, char_take(source, "name"));
 */
void char_add(struct Character *list, struct Character *toAdd);

/**
 * Iterates through linkedList of this character to see if character find is in there
 * Returns 0 if false, 1 if true
 */
int char_has(struct Character *list, char* name);

/**
 * Takes in Character pointer and name of item ot search for
 * Returns 1 if character has item, 0 if it does not
 */
int char_hasItem(struct Character *list, char* name);

/**
 * Function that takes in a pointer to a Character struct
 * Prints out all the characters linked to the character given
 */
void char_print(struct Character *list);




#endif /* CHARACTERS_H_ */

