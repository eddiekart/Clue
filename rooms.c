/*
 * rooms.c
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */
#include "rooms.h"
#include "items.h"
#include "characters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * "Constructor" for room; Takes in name, desc and pointers to adjacent rooms
 * Returns pointer to room structure with data values that were given to function
 * Sets first item and character as default dummy items/characters
 */
struct Room *room(char* name, char* desc, struct Room *north,
					struct Room *east, struct Room* south,
					struct Room*west){
	// Allocating mem for room
	struct Room *temp = (struct Room *) malloc(sizeof(struct Room));
	// MALLOC fail case
	if (temp == NULL){
		printf("MALLOC FAILED\n");
		printf("Attempted to malloc ROOM %s\n", name);
		exit(-1);
	}
	temp->name = name;
	temp->desc = desc;
	temp->north = north;
	temp->east = east;
	temp->south = south;
	temp->west = west;
	temp->item = dummyItem();
	//temp->item = items("dummy", "dummy", NULL);


	temp->character = dummyChar();


	//temp->character = character("dummy", NULL, NULL);
	return temp;
}

/**
 * Takes in pointer to room structure
 * Returns the room's name
 * Returns NULL if room is null
 */
char* room_name(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->name;
}

/**
 * Takes in pointer to room structure
 * returns the room's description
 * Returns NULL if room is null
 */
char* room_desc(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->desc;
}

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's north direction
 * Returns NULL if room is null
 */
struct Room* room_north(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->north;
}

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's east direction
 * Returns NULL if room is null
 */
struct Room* room_east(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->east;
}

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's south direction
 * Returns NULL if room is null
 */
struct Room* room_south(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->south;
}

/**
 * Takes in pointer to room structure
 * returns the pointer to the room in the room's west direction
 * Returns NULL if room is null
 */
struct Room* room_west(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->west;
}

/**
 * Takes in pointer to room structure
 * returns the pointer to the item linkedlist in the room
 * Returns NULL if room is null
 */
struct Item* room_item(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->item;
}

/**
 * Takes in pointer to room structure
 * returns the poitner to the character linkedlist in the room
 * Returns NULL if room is null
 */
struct Character* room_character(struct Room *room){
	if (room == NULL){
		return NULL;
	}
	return room->character;
}


/**
 * Takes in struct pointer and string
 * Sets given structure's name to given string
 */
void room_setName(struct Room *room, char* name){
	// Ensures function only attempts to change data when room is not null
	if (room != NULL){
		room->name = name;
	}
}

/**
 * Takes in struct pointer and string
 * Sets given structure's desc to given string
 */
void room_setDesc(struct Room *room, char* desc){
	// Ensures function only attempts to change data when room is not null
	if (room != NULL){
		room->desc = desc;
	}
}

/**
 * Takes in two struct pointers
 * Sets given struct pointer's north room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setNorth(struct Room *room, struct Room *north){
	// Ensures function only attempts to change data when room is not null
	if (room != NULL){
		room->north = north;
		// IF north room is not null, changes north room's south pointer as this room
		if (north != NULL){
			north->south = room;
		}
	}
}

/**
 * Takes in two struct pointers
 * Sets given struct pointer's east room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setEast(struct Room *room, struct Room *east){
	// Ensures function only attempts to change data when room is not null
	if (room != NULL){
		room->east = east;
		// IF east room is not null, changes east room's west pointer as this room
		if (east != NULL){
			east->west = room;
		}
	}
}

/**
 * Takes in two struct pointers
 * Sets given struct pointer's south room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setSouth(struct Room *room, struct Room *south){
	// Ensures function only attempts to change data when room is not null
	if (room != NULL){
		room->south = south;
		// IF south room is not null, changes south room's north pointer as this room
		if (south != NULL){
			south->north = room;
		}
	}
}

/**
 * Takes in two struct pointers
 * Sets given struct pointer's west room pointer as the second struct pointer given
 * Also changes second room's appropriate pointer to the main room, if second room is not null
 */
void room_setWest(struct Room *room, struct Room *west){
	// Ensures function only attempts to change data when room is not null
	if (room != NULL){
		room->west = west;
		// IF west room is not null, changes west room's east pointer as this room
		if (west != NULL){
			west->east = room;
		}
	}
}

/**
 * Takes in a room struct pointer and an item struct pointer
 * Sets given room pointer's item pointer as the item pointer given
 * Does not do anything if input Room to be operated on is null
 */
void room_setItem(struct Room *room, struct Item *item){
	if (room != NULL){
		room->item = item;
	}
}

/**
 * Takes in a room struct pointer and a character struct pointer
 * Sets given room pointer's character pointer as the character pointer given
 * Does not do anything if input Room to be operated on is null
 */
void room_setCharacter(struct Room *room, struct Character *character){
	if (room != NULL){
		room->character = character;
	}
}

/**
 * Takes in a room pointer and item pointer
 * Adds item pointer directly into the room's item list
 * Doesn't do anything when room is NULL
 */
void room_addItem(struct Room *room, struct Item *item){
	if (room != NULL){
		item_add(room_item(room), item);
	}
}

/**
 * Takes in a room pointer and a name string
 * Takes item with name from room if it exists
 * Returns NULL if room is null
 */
struct Item *room_takeItem(struct Room *room, char* name){
	if (room != NULL){
		return item_take(room_item(room), name);
	}
	return NULL;
}

/**
 * Takes in a room pointer and character pointer
 * Adds character pointer directly into the room's character list
 * Doesn't do anything when room is NULL
 */
void room_addCharacter(struct Room *room, struct Character *character){
	if (room != NULL){
		char_add(room_character(room), character);
	}
}

/**
 * Searches room's items for the item with name
 * Returns 1 if found, 0 if not
 */
int room_hasItem(struct Room *room, char* name){
	return item_has(room_item(room), name);
}

/**
 * Searches room's characters for the character with name
 * Returns 1 if found, 0 if not
 */
int room_hasCharacter(struct Room *room, char* name){
	return char_has(room_character(room), name);
}

/**
 * Takes in two room pointers
 * Switches the item pointers in the two rooms
 * Used for shuffling (randomly placing) items
 * Does not do anything if either Room to be operated on is null
 */
void room_swapItems(struct Room *source, struct Room *dest){
	if (source != NULL && dest != NULL){
		// Temporary variable to save item pointer in dest room
		struct Item *temp = room_item(dest);
		// Setting dest room's item pointer as source room's item pointer
		room_setItem(dest, room_item(source));
		// Setting source room's item pointer as dest room's previous item pointer
		room_setItem(source, temp);
	}
}

/**
 * Takes in two room pointers
 * Switches the character pointers in the two rooms
 * Used for shuffling (randomly placing) characters
 * Does not do anything if input Room to be operated on is null
 */
void room_swapCharacters(struct Room *source, struct Room *dest){
	if (source != NULL && dest != NULL){
		// Temporary variable to save character pointer in dest room
		struct Character *temp = room_character(dest);
		// Setting dest room's character pointer as source room's character pointer
		room_setCharacter(dest, room_character(source));
		// Setting source room's character pointer as dest room's previous character pointer
		room_setCharacter(source, temp);
	}
}

/**
 * Takes in a string to determine direction for function move_character
 * "north": Returns 0
 * "east": Returns 1
 * "south": Returns 2
 * "west": Returns 3
 * Returns 0 in invalid case
 */
int getDirection(char* direction){
	// Case direction is north
	if (strcmp(direction, "north") == 0){
		return 0;
	// Case direction is east
	} else if (strcmp(direction, "east") == 0){
		return 1;
	// Case direction is south
	} else if (strcmp(direction, "south") == 0){
		return 2;
	// Case direction is west
	} else if (strcmp(direction, "west") == 0){
		return 3;
	}
	// Invalid case
	return -1;
}

/**
 * Takes two room structure pointers, name string and direction string
 *
 * Two ways to use:
 * MOVING CHARACTER TO ADJACENT ROOM
 * Destination is NULL: Character in SOURCE room is moved in room in the given direction from SOURCE
 *
 * MOVING CHARACTER TO A GIVEN ROOM
 * Direction is NULL: Character in SOURCE room is moved to DESTINATION room
 *
 * Valid directions: "north", "east", "south", "west", case sensitive
 *
 * Does not do anything if input Room to be operated on is null
 * Returns 0 if no problems
 * Returns -1 if character not found
 * Returns -2 if direction is invalid
 * Returns -3 for other errors
 */
int move_character(struct Room *source, struct Room *destination, char* name, char* direction){
	// Invalid usage of function
	if (source == NULL || name == NULL){
		return -3;
		/*
		 * CODE FOR FIRST USAGE OF THE FUNCTION
		 */
	} else if (destination == NULL){
		// Invalid usage; first usage requires direction
		if (direction == NULL){
			return -3;
		}
		// Temporary pointer to be used to destination room
		struct Room *dest;

		// Switch case to define dest pointer
		switch(getDirection(direction)){
		// Destination is north room
		case 0:
			dest = room_north(source);
			break;
		// Destination is east room
		case 1:
			dest = room_east(source);
			break;
		// Destination is south room
		case 2:
			dest = room_south(source);
			break;
		// Destination is west room
		case 3:
			dest = room_west(source);
			break;
		// Invalid direction string
		default:
			// Returns error code for invalid direction
			return -2;
		}

		// Case where room in direction is null
		if (dest == NULL){
			return -2;
		}

		// Taking character with given name from source room
		struct Character *piece = char_take(room_character(source), name);

		// Checking to see if character was found or not; if piece == NULL, char not found
		if (piece == NULL){
			// Returns error code for invalid character name
			return -1;
		}

		// Adds piece to the character list in dest room
		char_add(room_character(dest), piece);


		/*
		 * CODE FOR SECOND USAGE OF THE FUNCTION
		 */
	} else if (direction == NULL){
		// Invalid usage;
		if (destination == NULL){
			return -3;
		}

		// Taking character with given name from source room
		struct Character *piece = char_take(room_character(source), name);
		// Checking to see if character was found or not; if piece == NULL, char not found
		if (piece == NULL){
			// Returns error code for invalid character name
			return -1;
		}
		// Adds piece to the character list in dest room
		char_add(room_character(destination), piece);
	}
	return 0;
}



