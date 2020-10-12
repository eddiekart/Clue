/*
 * characters.c
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */

#include "characters.h"
#include "items.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * "Constructor" for character
 * Takes in a string for character's name
 * Automatically adds dummy item to the inventory
 * Takes in a character pointer for a linkedlist of characters in the same room
 */
struct Character *character(char* name, struct Character *next){
	struct Character *temp = (struct Character *) malloc(sizeof(struct Character));
	if (temp == NULL){
		printf("MALLOC FAILED\n");
		printf("Failed trying to initialize character %s\n", name);
		exit(-1);
	}

	temp->name = name;
	temp->inventory = dummyItem();
	temp->next = next;
	return temp;
}

/**
 * Constructor for a dummy character structure
 * Data values are "dummy", NULL, NULL
 * Dummy's inventory value is NULL
 * Used to hold first position in a character linked list
 */
struct Character *dummyChar(void){
	struct Character *temp = (struct Character *) malloc(sizeof(struct Character));
	if (temp == NULL){
		printf("MALLOC FAILED\n");
		printf("Failed trying to initialize dummy character\n");
		exit(-1);
	}
	temp->name = "dummy";
	temp->inventory = NULL;
	temp->next = NULL;
	return temp;
}

/**
 * Function that takes in a pointer to a Character structure
 * Returns character's name
 * Returns NULL if Character pointer is null
 */
char* char_name(struct Character *piece){
	if (piece == NULL){
		return NULL;
	}
	return piece->name;
}

/**
 * Function that takes in a pointer to a Character structure
 * Returns character's inventory
 * Returns NULL if character is NULL or is a dummy character
 */
struct Item *char_inventory(struct Character *piece){
	if (piece == NULL){
		return NULL;
	}
	return piece->inventory;
}

/**
 * Function that takes in a pointer to a Character structure
 * Returns a pointer to the next character structure in the linkedlist
 * Returns NULL if Character pointer is null
 */
struct Character *char_next(struct Character *piece){
	if (piece == NULL){
		return NULL;
	}
	return piece->next;
}

/**
 * Function that takes in a pointer to a Character struct and a string
 * Sets the character's name as the input string
 * Does not do anything if input Character to be operated on is null
 */
void char_setName(struct Character *piece, char* name){
	if (piece != NULL){
		piece->name = name;
	}
}

/**
 * Function that takes in a pointer to a Character struct and a pointer to a different Character struct
 * Sets the character's next character pointer as the input character pointer
 * Does not do anything if input Character to be operated on is null
 */
void char_setNext(struct Character *piece, struct Character *next){
	if (piece != NULL){
		piece->next = next;
	}
}

/**
 * Function that takes in pointer to a Character struct and a string of item to remove from inventory
 * Removes item from character's inventory and returns pointer to it if found
 * Uses item_take() from items.c
 * If not found, returns NULL
 * This function is an alternative to obtaining character's inventory pointer and operating directly on it
 * ^ Is done for better readability
 */
struct Item *char_takeItem(struct Character *piece, char* name){
	return item_take(char_inventory(piece), name);
}

/**
 * Function that takes in pointer to a Character struct and an Item struct
 * Puts item struct into character's inventory
 * Uses item_add() from items.c
 * This function is an alternative to obtaining character's inventory pointer and operating directly on it
 * ^ Is done for better readability
 */
void char_giveItem(struct Character *piece, struct Item *item){
	item_add(char_inventory(piece), item);
}

/**
 * Function that takes in a Character pointer and name of character to take
 * Returns pointer to character with given name if found
 * Removes the character found from the linkedlist of the input Character
 * If not found, returns NULL
 * Needs to be used with item linked list where the first item is a dummy character, created by dummyChar()
 */
struct Character *char_take(struct Character *piece, char* name){
	if (piece == NULL){
		return NULL;
	}
	// Variable used for current item in loop
	struct Character *currChar = piece;
	// Variable used for next item in loop
	struct Character *nextChar = char_next(currChar);
	// Goes through character linked list until there is no next character
	while (nextChar != NULL){
		// Checking if next character is the character being searched for
		if (strcmp(char_name(nextChar), name) == 0){
			// Removing nextChar from linkedlist and linking currChar with nextChar's next character
			char_setNext(currChar, char_next(nextChar));
			// Removing nextChar from character list
			char_setNext(nextChar, NULL);
			return nextChar;
		}
		// Iterating through next character, as nextChar was not the character being searched for
		currChar = nextChar;
		nextChar = char_next(currChar);
	}
	// Item not found
	return NULL;
}

/**
 * Function that adds given character to a given character list
 * Takes in pointers to item list, and item to add to that item list
 * To take from list and add to another, use char_take to obtain the character to add first
 * Can use like char_add(destination, char_take(source, "name"));
 */
void char_add(struct Character *list, struct Character *toAdd){
	// Only adds when list is not null
	if (list != NULL){
		// Variable used for current character in loop
		struct Character *currChar = list;
		// Variable used for next character in loop
		struct Character *nextChar = char_next(currChar);
		// Iterates until nextChar is NULL, aka reaching end of linkedlist
		while (nextChar != NULL){
			currChar = nextChar;
			nextChar = char_next(currChar);
		}
		// Adding character toAdd to the end of the list
		char_setNext(currChar, toAdd);
	}
}

/**
 * Iterates through linkedList of this character to see if character find is in there
 * Returns 0 if false, 1 if true
 */
int char_has(struct Character *list, char* name){
	if (list != NULL && name != NULL){
		// Variable used for current character in loop
		struct Character *currChar = list;
		// Variable used for next character in loop
		struct Character *nextChar = char_next(currChar);
		while (nextChar != NULL){
			if (strcmp(char_name(nextChar), name) == 0){
				return 1;
			}
			currChar = nextChar;
			nextChar = char_next(currChar);
		}
	}
	return 0;
}

/**
 * Takes in Character pointer and name of item ot search for
 * Returns 1 if character has item, 0 if it does not
 */
int char_hasItem(struct Character *list, char* name){
	return item_has(char_inventory(list), name);
}

/**
 * Function that takes in a pointer to a Character struct
 * Prints out all the characters linked to the character given
 */
void char_print(struct Character *list){
	struct Character *currChar = list;
	struct Character *nextChar = char_next(currChar);
	if (nextChar == NULL){
		printf("No characters\n");
	} else {
		while (nextChar != NULL){
			printf("%s\n", char_name(nextChar));
			currChar = nextChar;
			nextChar = char_next(currChar);
		}
	}
}















