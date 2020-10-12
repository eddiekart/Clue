This is a README file for the detailed implementation of Clue
Author: Yunsik Edwin Lee
Link to demonstration video: https://youtu.be/tUUOmrs-EKI

How the requirements were fulfilled:

1. You must use C structs in your code to represent various game objects.

Rooms were created using rooms.c and rooms.h
Characters (including player avatar) was created using characters.c and characters.h
Items were created using items.c and items.h

Each room contained a character and an item, so the movement of characters and items were implemented within the individual files for room, character, items.

Items did not include any other header files, while Characters included Items due to the player requiring an inventory.

Rooms included both Characters and Items.

Characters and Items were stored in a linked list format, with a dummy variable occupying the first index of the linkedlists.



2. You must use pointers in your code.

All the functions in rooms, characters and items took in pointers and returned pointers, or returned nothing.

The only place pointers were not used was in the adventure.c, and even then, it was only for an integer used for a counter.



3. You must use dynamic allocation in your code using malloc/calloc.

Every single instance of a room, character or item was allocated memory through the usage of malloc.



4. You must deallocate memory in your code using free.

free() was used in the command input processing function, where the input string was stored temporarily. 
This string was freed after the string was processed.

In addition, at the end of the program, all the memories used by structures were freed by free(structure).