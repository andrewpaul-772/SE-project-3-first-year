#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


void menu(struct Person* List, char file[]){
	int choice; // variable to hold the users input choice
	do {

			printf("\nWhat would you like to do?\n");
			fflush(stdout);

			printf("1 - Display a Board\n");
			fflush(stdout);

			printf("2 - Load a Board from a File\n");
			fflush(stdout);

			printf("3 - Edit a List\n");
			fflush(stdout);

			printf("4 - Edit a Board\n");
			fflush(stdout);

			printf("5 - Save a Board to a File\n");
			fflush(stdout);

			printf("6 - Quit\n");
			fflush(stdout);

			printf("\nEnter your Choice => ");
			fflush(stdout);

			// error handling for if user enters a non-integer
			if (scanf("%d", &choice) != 1) {
				// clear the input buffer if non-integer input is entered
				while (getchar() != '\n');
				choice = 0; // set choice to an invalid value so the user can re-enter
			}

			// error handling for if user enters incorrect number
			if (choice < 1 || choice > 6) {
				printf("\nInvalid choice! Please try again.\n\n");
				fflush(stdout);
			}

		} while (choice < 1 || choice > 6);

		switch (choice)
		{
			case 1:
				displayFile(List, file);
				menu(List, file);
				break;
				// display the board
			case 2:
				strcpy(file, loadNewFile());
				List = readFile(file);
				menu(List, file);
				break;
				// load the board
			case 3:
				editListMenu(List, file);
				break;
				// edit the list
			case 4:
				editBoardMenu(List, file);
				break;
				// edit the board
			case 5:
				saveBoard(List, file);
				break;
				// save board to a file
			case 6:
				printf("Exiting programme");
				fflush(stdout);
				printAsciiArt();
				break; // quit program
}
}

struct Person* readFile(char myFile[]){
	 FILE* fp;

	    // Initialize the structs for linked list
	    Person* startPerson;
	    Person* currentPerson;
	    Item* currentItem ;



	    // Open the file for reading
	    fp = fopen(myFile , "r");
	    if (fp == NULL) {
	        printf("Error opening file\n");
	        return NULL;
	    }
	    //initialise first person
	    startPerson = malloc(sizeof(Person));
	    startPerson->first_item = malloc(sizeof(Item));
	    startPerson->previous = NULL;


	    //get name of first person and intialise items for first person
	    if(startPerson != NULL){
	    	fgets(startPerson->name, sizeof(startPerson->name), fp);
		    currentItem = startPerson->first_item;
		    currentItem->previous = NULL;
	    }
	    //if a colon is found at the end of the word then it becomes the name of the next person
	    while(fgets(currentItem->name, sizeof(currentItem->name), fp) != NULL){
	    	if(currentItem->name[strlen(currentItem->name)- 3] == ':'){
	    		startPerson->next = malloc(sizeof(Person));
	    		currentPerson = startPerson->next;
	    		currentPerson->previous = startPerson;
	    		strcpy(currentPerson->name, currentItem->name);
	    		currentItem->previous->next = NULL;
	    		goto out;
	    	}
	    	//get names and initialise pointers to next and previous for items for first person
	    	else{
	    		currentItem->next = malloc(sizeof(Item));
	    		currentItem->next->previous = currentItem;
	    		currentItem = currentItem->next;
	    	}
	    }
	    out:
		//do the same for the rest of the people
		currentPerson->first_item = malloc(sizeof(Item));
	    currentItem = currentPerson->first_item;
	    while(fgets(currentItem->name, sizeof(currentItem->name), fp) != NULL){
	    	if(currentItem->name[strlen(currentItem->name)- 3] == ':'){
	    		currentPerson->next = malloc(sizeof(Person));
	    		currentPerson->next->previous = currentPerson;
	    		currentPerson = currentPerson->next;
	    	    strcpy(currentPerson->name, currentItem->name);
	    	    currentItem->previous->next = NULL;
	    	    currentPerson->first_item = malloc(sizeof(Item));
	    	    currentItem = currentPerson->first_item;
	    	}
	    	else{
	    		currentItem->next = malloc(sizeof(Item));
	    		currentItem->next->previous = currentItem;
	    		currentItem = currentItem->next;
	    	}
	    }

	    // Close the file
	    fclose(fp);
	    //return a pointer to the head of the list for use in all other functions
	    return startPerson;
}

	//gets the name of the file user wants to use
	//return a pointer to the first element of the string
char* loadNewFile(){
	static char newFile[30];
	printf("enter new file name:\n");
	fflush(stdout);
	scanf("%s", newFile);
	//if cant be opened return erro messgae
	if (fopen(newFile , "r") == NULL) {
		printf("Error opening file\n");
		return NULL;
		    }
	else{
		return &newFile[0];
	}
}

//use while loops to iterate through the lists and print each name followed by their items
void displayFile(struct Person* List, char file[]){
	struct Item* item;
	//if its empty return error message
	if(List == NULL){
		printf("Nothing to print");
	}
	while(List != NULL){
		printf("\n%s", List->name);
		fflush(stdout);
		item = List->first_item;
		while(item != NULL){
			printf("\t%s", item->name);
			fflush(stdout);
			item = item->next;
		}
		List = List->next;
	}
	printf("\n\nList printed\n");
	fflush(stdout);
}

void editBoardMenu(struct Person* List, char file[]){
	int choice;
	//print menu
	do {
			printf("\n1 - Edit name of a list\n"
				   "2 - Add a new list\n"
				   "3 - Delete a list \n"
				   "4 - Return to main menu\n"
				   "\nEnter your choice => ");
			fflush(stdout);
			// error handling if user enters a letter
			if (scanf("%d", &choice) != 1) {
				while (getchar() != '\n');
				choice = 0;
			}
			// if user enters an incorrect integer
			if (choice < 1 || choice > 4) {
				printf("\nInvalid choice! Please try again.\n");
				fflush(stdout);
			}

		} while(choice > 4 || choice < 1);

	//return function based on choice of user
	switch (choice)
	{
	case 1:
		editList(List, file);
		//edit name
		break;
	case 2:
		addList(List, file);
		//add new
		break;
	case 3:
		deleteList(List, file);
		//delete list
		break;
	case 4:
		menu(List, file);
		//back to menu
		break;
	}

}

void addList(struct Person* List, char file[]){
	//get name
	char newList[50];
	printf("\nEnter name for new list => ");
	fflush(stdout);
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	fgets(newList, sizeof(newList), stdin);
	//initialise all of the new structs variables
	List->previous = malloc(sizeof(Person));
	List->previous->next = List;
	List->previous->previous = NULL;
	strcpy(List->previous->name, newList);
	List = List->previous;
	List->first_item = NULL;
	//back to menu
	return menu(List, file);
}

void deleteList(struct Person* List, char file[]){
	 char listToDelete[50];
	 //flag to determine if list is found
	 int found = 0;

	 printf("\nEnter name of list to delete => ");
	 fflush(stdout);
	 //get name to delete
	 int c;
	 while ((c = getchar()) != '\n' && c != EOF) { }
	 fgets(listToDelete, sizeof(listToDelete), stdin);

	 struct Person* current = List;
	 //iterate through list till node is found
	 while(current != NULL){
	 //when it's found change the pointers around it
	 if(strcmp(current->name, listToDelete) == 0){
		 if (current->previous == NULL){
			current->next->previous = NULL;
			List = current->next;
			//free the space in memory where it was
			free(current);
			//set flag to found
			found = 1;
			break;
		 }
		 else if(current->next == NULL){
			 current->previous->next = NULL;
			 free(current);
			 found = 1;
			 break;
		 }
		 else{
			 current->previous->next = current->next;
			 current->next->previous = current->previous;
			 free(current);
			 found = 1;
			 break;
		 }

	 }
	 else{
		 current = current->next;
	 }
	 }
	 //if list not found print error message
	 if (found == 0){
		 printf("\nNo List of this name found");
		 fflush(stdout);
	 }
	 return menu(List, file);
}

void editList(struct Person* List, char file[]){
	//same concept as above
	char listToEdit[50];
	char newName[50];
		 int found = 0;

		 printf("\nEnter name of list to edit => ");
		 fflush(stdout);

		 int c;
		 while ((c = getchar()) != '\n' && c != EOF) { }
		 fgets(listToEdit, sizeof(listToEdit), stdin);

		 printf("\nEnter new name => ");
		 fflush(stdout);

		 fgets(newName, sizeof(newName), stdin);

		 struct Person* current = List;

		 while(current != NULL){
			 if(strcmp(current->name, listToEdit) == 0){
				 strcpy(current->name, newName);
				 found = 1;
				 break;
			 }
			 else{
				 current = current->next;
			 }
		 }
		 if(found == 0){
			 printf("\nList of this name not found\n");
			 fflush(stdout);
		 }
		 return menu(List, file);
}

void editListMenu(struct Person* List, char file[]) {
	//same concepts as above but the list has to be found first to enter the items nested list
    int choice;
    do {
       	printf("\n1 - Edit an item\n"
                  "2 - Add an item\n"
                  "3 - Delete an item\n"
                  "4 - Return to main menu\n"
                  "\nEnter your choice => ");
           fflush(stdout);
           // error handling if user enters a letter
           if (scanf("%d", &choice) != 1) {
   			while (getchar() != '\n');
   			choice = 0;
   		}
           // error handling if user enters wrong integer
   		if (choice < 1 || choice > 4) {
   			printf("\nInvalid choice! Please try again.\n");
   			fflush(stdout);
   		}
       } while (choice > 4 || choice < 1);


    switch (choice) {
        case 1:
        	editItem(List, file);
            break;
        case 2:
            addItem(List, file);
            break;
        case 3:
        	deleteItem(List, file);
            break;
        case 4:
            menu(List, file);
            break;
    }
}

void editItem(struct Person* List, char file[]) {
    char listName[50], itemName[50], newItemName[50];
    struct Person* currentList = List;
    struct Item* currentItem;
    int found = 0;

    printf("\nEnter the list name to edit an item => ");
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(listName, sizeof(listName), stdin);

    while (currentList != NULL) {
        if (strcmp(currentList->name, listName) == 0) {
            printf("Enter the name of the item to edit => ");
            fflush(stdout);
            fgets(itemName, sizeof(itemName), stdin);

            currentItem = currentList->first_item;
            while (currentItem != NULL) {
                if (strcmp(currentItem->name, itemName) == 0) {
                    printf("Enter the new name for the item => ");
                    fflush(stdout);
                    fgets(newItemName, sizeof(newItemName), stdin);
                    strcpy(currentItem->name, newItemName);
                    found = 1;
                    break;
                }
                currentItem = currentItem->next;
            }
            break;
        }
        currentList = currentList->next;
    }

    if (!found) {
        printf("\nList or item not found\n");
        fflush(stdout);
    }

    menu(List, file);
}


void addItem(struct Person* List, char file[]) {
    char listName[50], itemName[50];
    struct Person* currentList = List;
    struct Item* newItem;

    printf("\nEnter the list name to add an item => ");
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(listName, sizeof(listName), stdin);

    while (currentList != NULL) {
        if (strcmp(currentList->name, listName) == 0) {
            printf("Enter the name of the new item => ");
            fflush(stdout);
            fgets(itemName, sizeof(itemName), stdin);

            newItem = malloc(sizeof(struct Item));
            strcpy(newItem->name, itemName);
            newItem->next = currentList->first_item;
            newItem->previous = NULL;
            if (currentList->first_item != NULL) {
                currentList->first_item->previous = newItem;
            }
            currentList->first_item = newItem;
            break;
        }
        currentList = currentList->next;
    }

    if (currentList == NULL) {
        printf("\nList not found\n");
        fflush(stdout);
    }

    menu(List, file);
}

void deleteItem(struct Person* List, char file[]) {
    char listName[50], itemName[50];
    struct Person* currentList = List;
    struct Item* currentItem, *prevItem;
    int found = 0;

    printf("\nEnter the list name to delete an item => ");
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(listName, sizeof(listName), stdin);

    while (currentList != NULL) {
        if (strcmp(currentList->name, listName) == 0) {
            printf("Enter the name of the item to delete => ");
            fflush(stdout);
            fgets(itemName, sizeof(itemName), stdin);

            currentItem = currentList->first_item;
            prevItem = NULL;
            while (currentItem != NULL) {
                if (strcmp(currentItem->name, itemName) == 0) {
                    if (prevItem == NULL) {
                        currentList->first_item = currentItem->next;
                        if (currentList->first_item != NULL) {
                            currentList->first_item->previous = NULL;
                        }
                    } else {
                        prevItem->next = currentItem->next;
                        if (currentItem->next != NULL) {
                            currentItem->next->previous = prevItem;
                        }
                    }
                    free(currentItem);
                    found = 1;
                    break;
                }
                prevItem = currentItem;
                currentItem = currentItem->next;
            }
            break;
        }
        currentList = currentList->next;
    }

    if (!found) {
        printf("\nList or item not found\n");
        fflush(stdout);
    }

    menu(List, file);
}

void saveBoard(struct Person* List, char file[]){
	struct Item* item = NULL;
	struct Person* person;
	//initialise head of list
	person = List;

	printf("Enter file name => ");
				fflush(stdout);
				scanf("%s", file);
	FILE* fp;
	//open in write mode
	fp = fopen(file, "w");
	if(fp == NULL){
		//if cant be opened, print error message
		printf("Error opening/creating file");
		fflush(stdout);
		return;
	}
	//print names followed by their items to file
	while(person != NULL){
		if(person->first_item != NULL){
				item = person->first_item;
			}
		fprintf(fp, "%s", person->name);
		while(item != NULL){
			fprintf(fp, "%s", item->name);
			item = item->next;
		}
		person = person->next;
		}
	//close file
	 fclose(fp);
	 printf("Board saved to file");
	 fflush(stdout);
	 return menu(List, file);
}


void printAsciiArt() {
    printf("                                 @               \n");
    printf("                                @@@@             \n");
    printf("                    @@@@@@@@    @@@              \n");
    printf("                  @@*::::::*@@ @@                \n");
    printf("                @@*::::::::::***@                \n");
    printf("               @*::::::::::::::-*@@@             \n");
    printf("               @:::::::::::::::::::*@            \n");
	printf("               @::::::::::::::::::::@            \n");
	printf("              @*::::::::::*@@@@@@*::*@           \n");
	printf("              @::::::::::*@      @*:@            \n");
	printf("             @*::::::::::@        @*@            \n");
	printf("            @@:::::::::::@        @              \n");
	printf("             @@@@@@*-::::*@                      \n");
	printf("                   @@@@@@@@*                     \n");

	printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿\n"          /*lightning mcqueen!!!*/
	                          "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣉⣁⣤⣤⣶⣾⣿⣿⣶⡄⢲⣯⢍⠁⠄⢀⢹⣿\n"
	                          "⣿⣿⣿⣿⣿⣿⣿⣿⣿⢯⣾⣿⣿⣏⣉⣹⠿⠇⠄⠽⠿⢷⡈⠿⠇⣀⣻⣿⡿⣻\n"
	                          "⣿⣿⡿⠿⠛⠛⠛⢛⡃⢉⢣⡤⠤⢄⡶⠂⠄⠐⣀⠄⠄⠄⠄⠄⡦⣿⡿⠛⡇⣼\n"
	                          "⡿⢫⣤⣦⠄⠂⠄⠄⠄⠄⠄⠄⠄⠄⠠⠺⠿⠙⠋⠄⠄⠄⠢⢄⠄⢿⠇⠂⠧⣿\n"
	                          "⠁⠄⠈⠁⠄⢀⣀⣀⣀⣀⣠⣤⡤⠴⠖⠒⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⢠⡞⠄⣸\n"
	                          "⡀⠄⠄⠄⠄⠄⠤⠭⠦⠤⠤⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣂⣿\n"
	                          "⣷⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢳⠄⠄⢀⠈⣠⣤⣤⣼⣿\n"
	                          "⣿⣿⣷⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣴⣶⣶⣶⣄⡀⠄⠈⠑⢙⣡⣴⣿⣿⣿⣿⣿\n"
	                          "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
	                          );

}
