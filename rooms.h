/*
 * rooms.h
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */


#ifndef ROOMS_H_
#define ROOMS_H_

#include "items.h"
#include "characters.h"

/**
 * Structure for room
 * Contains two strings: room name and room description
 * Contains four room pointers, pointing to rooms in that direction from this room
 * Room pointers may be null if there are no rooms in that direction
 * Contains item pointer, pointing to a item linkedlist that contains the items in this room
 * Contains chracter pointer, pointing to a chracter linkedlist that contains the characters in this room
 */
struct Room{
	char* name;
	char* desc;
	struct Room *north;
	struct Room *east;
	struct Room *south;
	struct Room *west;
	struct Item *item;
	struct Character *character;
};

/**
 * "Constructor" for room; Takes in name, desc and pointers to adjacent rooms
 * Returns pointer to room structure with data values that were given to function
 * Sets first item and character as default dummy items/characters
 */
struct Room *room(char* name, char* desc, struct Room *north, struct Room *east, struct Room* south, struct Room *west);

/**
 * Takes in pointer to room structure
 * Returns the room's name
 * Returns NULL if room is null
 */
char* room_name(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the room's description
 * Returns NULL if room is null
 */
char* room_desc(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's north direction
 * Returns NULL if room is null
 */
struct Room* room_north(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's east direction
 * Returns NULL if room is null
 */
struct Room* room_east(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's south direction
 * Returns NULL if room is null
 */
struct Room* room_south(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's west direction
 * Returns NULL if room is null
 */
struct Room* room_west(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the pointer to the item linkedlist in the room
 * Returns NULL if room is null
 */
struct Item* room_item(struct Room *room);

/**
 * Takes in pointer to room structure
 * returns the poitner to the character linkedlist in the room
 * Returns NULL if room is null
 */
struct Character* room_character(struct Room *room);

/**
 * Takes in struct pointer and string
 * Sets given structure's name to given string
 */
void room_setName(struct Room *room, char* name);

/**
 * Takes in struct pointer and string
 * Sets given structure's desc to given string
 */
void room_setDesc(struct Room *room, char* desc);

/**
 * Takes in two struct pointers
 * Sets given struct pointer's north room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setNorth(struct Room *room, struct Room *north);

/**
 * Takes in two struct pointers
 * Sets given struct pointer's east room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setEast(struct Room *room, struct Room *east);

/**
 * Takes in two struct pointers
 * Sets given struct pointer's south room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setSouth(struct Room *room, struct Room *south);

/**
 * Takes in two struct pointers
 * Sets given struct pointer's west room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setWest(struct Room *room, struct Room *west);

/**
 * Takes in a room struct pointer and an item struct pointer
 * Sets given room pointer's item pointer as the item pointer given
 * Does not do anything if input Room to be operated on is null
 */
void room_setItem(struct Room *room, struct Item *item);

/**
 * Takes in a room struct pointer and a character struct pointer
 * Sets given room pointer's character pointer as the character pointer given
 * Does not do anything if input Room to be operated on is null
 */
void room_setCharacter(struct Room *room, struct Character *character);

/**
 * Takes in a room pointer and item pointer
 * Adds item pointer directly into the room's item list
 * Doesn't do anything when room is NULL
 */
void room_addItem(struct Room *room, struct Item *item);

/**
 * Takes in a room pointer and a name string
 * Takes item with name from room if it exists
 * Returns NULL if room is null
 */
struct Item *room_takeItem(struct Room *room, char* name);

/**
 * Takes in a room pointer and character pointer
 * Adds character pointer directly into the room's character list
 * Doesn't do anything when room is NULL
 */
void room_addCharacter(struct Room *room, struct Character *character);

/**
 * Searches room's items for the item with name
 * Returns 1 if found, 0 if not
 */
int room_hasItem(struct Room *room, char* name);

/**
 * Searches room's characters for the character with name
 * Returns 1 if found, 0 if not
 */
int room_hasCharacter(struct Room *room, char* name);

/**
 * Takes in two room pointers
 * Switches the item pointers in the two rooms
 * Used for shuffling (randomly placing) items
 * Does not do anything if input Room to be operated on is null
 */
void room_swapItems(struct Room *source, struct Room *dest);

/**
 * Takes in two room pointers
 * Switches the character pointers in the two rooms
 * Used for shuffling (randomly placing) characters
 * Does not do anything if input Room to be operated on is null
 */
void room_swapCharacters(struct Room *source, struct Room *dest);

/**
 * Takes in a string to determine direction for function move_character
 * "north": Returns 0
 * "east": Returns 1
 * "south": Returns 2
 * "west": Returns 3
 * Returns 0 in invalid case
 */
int getDirection(char* direction);

/**
 * Takes two room structure pointers, name string and direction string
 *
 * Two ways to use:
 * Only source pointer, name and direction strings are given: Character IN source pointer room moves in given direction
 * source, destination and name are given: Moves character IN source room to destination room
 *
 * Valid directions: "north", "east", "south", "west", case sensitive
 *
 * Does not do anything if input Room to be operated on is null
 * Returns 0 if no problems
 * Returns -1 if character not found
 * Returns -2 if direction is invalid
 */
int move_character(struct Room *source, struct Room *destination, char* name, char* direction);


#endif /* ROOMS_H_ */
