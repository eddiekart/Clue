/*
 * adventure.c
 *
 *  Created on: Sep 26, 2020
 *      Author: eddie
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "items.h"
#include "rooms.h"
#include "characters.h"

#define LINEBREAK printf("#################################\n");
#define SMALLBREAK printf("--------------------\n");

/**
 * Struct to store the answer of the game
 */
struct answer{
	struct Room *room;
	struct Item *item;
	struct Character *character;
};

struct answer *ans;

/*
 * Array used to hold map
 * Map layout with indexes is:
 * 0 1 2
 * 3 4 5
 * 6 7 8
 */
struct Room *map[9];
// Array used to hold all items in game
struct Item *itemList[6];
// Array used to hold all characters in game
struct Character *characterList[6];
// Pointer to room the player is located in
struct Room *playerLoc;
// Counter to count number of times guessed
int counter;
// String to print for HELP command
char* help = "--COMMANDS--\n"\
			"list: Lists all rooms/items/characters\n"\
			"look: Lists current room, rooms in all valid directions, characters in the room and items in the room\n"\
			"go DIRECTION: Moves player character to the direction specified. Valid directions: north, south, east, west\n"\
			"take ITEM: Takes item with name ITEM from the current room and puts it into player's inventory, if it exists\n"\
			"drop ITEM: Drops item with name ITEM from the player's inventory to the room, if it exists\n"\
			"inventory: Lists items in the player's inventory\n"\
			"clue CHARACTER: Makes a guess with the current room, character name given and items in the room/inventory for win condition\n"\
			"quit: Exits the game\n";

/**
 * Admin command that prints out the answers
 * Primarily used to test win condition and to shorten demo of win condition
 */
void getAnswers(){
	printf("Room: %s\n", room_name(ans->room));
	printf("Item: %s\n", item_name(ans->item));
	printf("Character: %s\n", char_name(ans->character));
	LINEBREAK
}
/**
 * NOTE:
 * characterList[0] is ALWAYS the player (avatar)
 */

/**
 * Function that takes in a character name
 * Returns room pointer to the room the character is in
 * Returns NULL if character not found (check character name)
 */
struct Room *findCharacter(char* name){
	for (int i = 0; i < 9; i++){
		if (room_hasCharacter(map[i], name)){
			return map[i];
		}
	}
	return NULL;
}

/**
 * Initializes map array, itemList array and characterList array with following room/item/characters
 * Room list:
 * Kitchen, Living Room, Dining Room, Bedroom, Bathroom, Storage, Pantry, Garage, Game Room
 * Item List:
 * Pen, Knife, Notebook, Diary, Toy, Phone
 * Character List:
 * Player (avatar), Abe, Bob, Carl, Diana, Elise
 */
void initializeBoard(){
	ans = (struct answer *) malloc(sizeof(struct answer));
	map[0] = room("Kitchen", "Kitchen", NULL, NULL, NULL, NULL);
	map[1] = room("Living Room", "Living Room", NULL, NULL, NULL, NULL);
	map[2] = room("Dining Room", "Dining Room", NULL, NULL, NULL, NULL);
	map[3] = room("Bedroom", "Bedroom", NULL, NULL, NULL, NULL);
	map[4] = room("Bathroom", "Bathroom", NULL, NULL, NULL, NULL);
	map[5] = room("Storage", "Storage", NULL, NULL, NULL, NULL);
	map[6] = room("Pantry", "Pantry", NULL, NULL, NULL, NULL);
	map[7] = room("Garage", "Garage", NULL, NULL, NULL, NULL);
	map[8] = room("Game Room", "Game Room", NULL, NULL, NULL, NULL);

	itemList[0] = items("Pen", "Pen", NULL);
	itemList[1] = items("Knife", "Knife", NULL);
	itemList[2] = items("Notebook", "Notebook", NULL);
	itemList[3] = items("Diary", "Diary", NULL);
	itemList[4] = items("Toy", "Toy", NULL);
	itemList[5] = items("Phone", "Phone", NULL);

	characterList[0] = character("Player", NULL);
	characterList[1] = character("Abe", NULL);
	characterList[2] = character("Bob", NULL);
	characterList[3] = character("Carl", NULL);
	characterList[4] = character("Diana", NULL);
	characterList[5] = character("Elise", NULL);


}

/**
 * Randomly places the rooms, items and characters onto the map
 * Links map to each other as appropriate (north, west, etc etc)
 */
void shuffleMap(){
	// Randomly selecting a room from map to add items and characters to
	time_t t;
	srand((unsigned) time(&t));
	for (int i = 0; i < 6; i++){
		// Adding item
		room_addItem(map[rand()%9], itemList[i]);
		// Adding character
		room_addCharacter(map[rand()%9], characterList[i]);
	}

	playerLoc = findCharacter("Player");

	// Shuffling map array around
	// Temp index variable
	int loc = 0;
	// Temp room pointer
	struct Room *temp = NULL;
	// Swaps map[0] and map[random, 1-8] 30 times
	for (int i = 0; i < 30; i++){
		temp = map[0];
		loc = (rand()%8) + 1;
		map[0] = map[loc];
		map[loc] = temp;
	}

	// Linking rooms on map to each other according to map layout
	room_setEast(map[0], map[1]);
	room_setSouth(map[0], map[3]);
	room_setEast(map[1], map[2]);
	room_setSouth(map[1], map[4]);
	room_setSouth(map[2], map[5]);
	room_setEast(map[3], map[4]);
	room_setSouth(map[3], map[6]);
	room_setEast(map[4], map[5]);
	room_setSouth(map[4], map[7]);
	room_setSouth(map[5], map[8]);
	room_setEast(map[6], map[7]);
	room_setEast(map[7], map[8]);

	// Randomly choosing answer
	ans->room = map[rand()%9];
	ans->item = itemList[rand()%6];
	ans->character = characterList[(rand()%5)+1];

	counter = 0;
}

/**
 * Function for testing purposes
 */
void printMap(){
	for(int i = 0; i < 3; i++){
		printf("%10s %10s %10s\n", room_name(map[3*i]), room_name(map[3*i+1]), room_name(map[3*i+2]));
	}
	LINEBREAK
	printf("---\n");
	for (int i = 0; i < 9; i++){
		item_print(room_item(map[i]));
		printf("---\n");
	}
	LINEBREAK
	printf("---\n");
	for(int i = 0; i < 9; i++){
		char_print(room_character(map[i]));
		printf("---\n");
	}
}

/**
 * Prints out list of rooms, items and characters not including "Player"
 */
void list(){
	// Printing out rooms
	SMALLBREAK
	printf("--Room List--\n");
	for (int i = 0; i < 9; i++){
		printf("%s\n", room_name(map[i]));
	}
	SMALLBREAK
	// Printing out items
	printf("--Item List--\n");
	for (int i = 0; i < 6; i++){
		printf("%s\n", item_name(itemList[i]));
	}
	SMALLBREAK
	/*
	 * Printing out characters
	 * Does NOT print "Player"
	 */
	printf("--Character List--\n");
	for (int i = 1; i < 6; i++){
		printf("%s\n", char_name(characterList[i]));
	}
}

/**
 * Function used for command "look"
 * Prints out current room name, characters in room and items in room
 */
void look(){
	// Printing out room name
	printf("[Current Room]\n");
	printf("%s\n", room_name(playerLoc));
	SMALLBREAK
	// Printing rooms in directions
	printf("[Rooms in direction]\n");

	char* roomNames[4];
	// Printing out north room's name; "None" printed if north room is null
	roomNames[0] = room_north(playerLoc) == NULL ? "None" : room_name(room_north(playerLoc));
	printf("north: %s\n", roomNames[0]);

	// Printing out east room's name; "None" printed if east room is null
	roomNames[1] = room_east(playerLoc) == NULL ? "None" : room_name(room_east(playerLoc));
	printf("east: %s\n", roomNames[1]);

	// Printing out South room's name; "None" printed if South room is null
	roomNames[2] = room_south(playerLoc) == NULL ? "None" : room_name(room_south(playerLoc));
	printf("south: %s\n", roomNames[2]);

	// Printing out west room's name; "None" printed if west room is null
	roomNames[3] = room_west(playerLoc) == NULL ? "None" : room_name(room_west(playerLoc));
	printf("west: %s\n", roomNames[3]);

	// Printing out characters in room
	printf("[Characters in Room]\n");
	char_print(room_character(playerLoc));
	SMALLBREAK
	// Printing out items in room
	printf("[Items in Room]\n");
	item_print(room_item(playerLoc));
	LINEBREAK
}

/**
 * Function used to move player avatar to an adjacent room
 * Use: go DIRECTION
 * valid directions: "north", "south", "east", "west"
 * CASE SENSITIVE
 * If direction is invalid, will print message saying so
 */
void go(char* direction){
	// Int is to check for error codes
	// FIRST usage of move_character
	int message = move_character(playerLoc, NULL, char_name(characterList[0]), direction);

	// Taking actions based on err codes
	switch(message){
	case (0):
		// Switch case to update playerLoc
		switch(getDirection(direction)){
		// Destination is north room
		case 0:
			playerLoc = room_north(playerLoc);
			break;
			// Destination is east room
		case 1:
			playerLoc = room_east(playerLoc);
			break;
			// Destination is south room
		case 2:
			playerLoc = room_south(playerLoc);
			break;
			// Destination is west room
		case 3:
			playerLoc = room_west(playerLoc);
			break;
			// Invalid direction string
		default:
			break;
		}
		break;
	case(-1):
		printf("Invalid character!\n");
		break;
	case(-2):
		printf("Invalid direction!\n");
		break;
	case(-3):
		printf("Unknown error!\n");
		break;
	default:
		break;
	}
}

/**
 * Prints out list of items in the player's inventory
 */
void inventory(){
	printf("--Items in inventory--\n");
	item_print(char_inventory(characterList[0]));
	LINEBREAK
}

/**
 * Function that checks guesses to see if it's the answer
 * Moves character with charName to player location, if name is valid
 * Returns 1 if guess is correct
 * Returns 0 if guess is incorrect
 *
 * Prints ROOM MATCH/CHARACTER MATCH/ITEM MATCH inside function
 * Prints other messages (e.g. character not found) if applicable within function
 */
int clue(char* charName){
	// Increments guess counter
	counter++;
	// Boolean for correct/incorrect
	int success = 1;

	/**
	 * CODE TO CHECK ROOM MATCH
	 */
	if (strcmp(room_name(ans->room), room_name(playerLoc)) == 0){
		printf("ROOM MATCH\n");
	} else {
		// Sets correct/incorrect as false
		success = 0;
	}

	/**
	 * CODE TO CHECK CHARACTER MATCH
	 */
	struct Room *charLocation = findCharacter(charName);
	// Checks if player name is valid
	if (charLocation == NULL){
		printf("Invalid character name!\n");
	} else {
		// Moves character with given name to player location
		// SECOND usage of move_character
		move_character(charLocation, playerLoc, charName, NULL);
		// Case where character with the right name is in the player's room
		if (room_hasCharacter(playerLoc, char_name(ans->character))){
			printf("CHARACTER MATCH\n");
		} else {
			// Sets correct/incorrect as false
			success = 0;
		}
	}

	/**
	 * CODE TO CHECK ITEM MATCH
	 */
	// Checking to see if room has the item
	if (room_hasItem(playerLoc, item_name(ans->item))){
		printf("ITEM MATCH\n");
	// Checking to see if character inventory has item
	} else if (char_hasItem(characterList[0], item_name(ans->item))){
		printf("ITEM MATCH\n");
	// Neither room or inventory has item
	} else {
		// Sets correct/incorrect to false
		success = 0;
	}

	return success;
}

/**
 * Command that takes user input and stores it to first index of input array
 */
void inputCommand(char* inputOne, char* inputTwo){
	// Command input
	printf("Enter command: ");

	// Implementation using strtok
	char* line = (char *) malloc(128);
	char* token;
	size_t nbytes = 127;
	if (getline(&line, &nbytes, stdin) == -1){
		// Getting rid of warning for unused return on getline
	}
	token = strtok(line, " \n");
	if (token != NULL){
		strncpy(inputOne, token, 256);
		token = strtok(NULL, " \n");
	}
	if (token != NULL){
		strncpy(inputTwo, token, 256);
	}
	free(line);
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);

	// Initializing game state
	initializeBoard();
	shuffleMap();

	// String array to store command inputs
	char input[2][256];


	look();
	// Game loop
	while (1){
		// Asking for user command
		inputCommand(input[0], input[1]);

		/*
		 * CMD: help
		 */
		if (strcmp(input[0], "help") == 0){
			printf("%s",help);
			LINEBREAK
		/*
		 * CMD: list
		 */
		} else if (strcmp(input[0], "list") == 0){
			list();
			LINEBREAK
		/*
		 * CMD: look
		 */
		} else if (strcmp(input[0], "look") == 0){
			look();
		/*
		 * CMD: go
		 */
		} else if (strcmp(input[0], "go") == 0){
			go(input[1]);
			LINEBREAK
		/*
		 * CMD: take ITEM
		 */
		} else if (strcmp(input[0], "take") == 0){
			// Checking if room has item
			if (room_hasItem(playerLoc, input[1])){
				// Moving item to inventory
				char_giveItem(characterList[0], room_takeItem(playerLoc, input[1]));
			} else {
				printf("Item not found!\n");
			}
			LINEBREAK
		/*
		 * CMD: drop ITEM
		 */
		} else if (strcmp(input[0], "drop") == 0){
			// Checking if character's inventory has item
			if (char_hasItem(characterList[0], input[1])){
				// Moving item to room
				room_addItem(playerLoc, char_takeItem(characterList[0], input[1]));
			}
			LINEBREAK
		/*
		 * CMD: inventory
		 */
		} else if (strcmp(input[0], "inventory") == 0){
			inventory();
		/*
		 * CMD: clue CHARACTER
		 */
		} else if (strcmp(input[0], "clue") == 0){
			if (clue(input[1])){
				printf("Congratulations! You won in %d tries.\n", counter);
				break;
			} else if (counter >= 10){
				printf("You lost the game! Try again next time.\n");
				break;
			}
			printf("Number of times attempted: %d\n", counter);
			LINEBREAK
		/*
		 * CMD: answer
		 */
		} else if (strcmp(input[0], "answer") == 0){
			getAnswers();
		/*
		 * CMD: quit
		 */
		} else if (strcmp(input[0], "quit") == 0){
			break;
		// Invalid command
		} else {
			printf("Unrecognized command. Use command \"help\" to get a list of commands.\n");
			LINEBREAK
		}
	}


	// Freeing memory used up by structures, as game is over
	for (int i = 0; i < 9; i++){
		free(map[i]);
	}
	for (int i = 0; i < 6; i++){
		free(characterList[i]);
		free(itemList[i]);
	}
	return 0;
}
