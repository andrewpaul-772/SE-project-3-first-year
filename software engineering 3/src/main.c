#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main(void) {

	char myFile[] = "KanbanBoardFile.txt";

	 Person* List = readFile(myFile);

	// print the menu for the user and take input
	printf(" -=- Kanban Board Generator -=-\n\n");
	fflush(stdout);

	menu(List, myFile);


    return 0;
}
