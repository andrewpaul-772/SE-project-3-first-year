
// Struct for an item
typedef struct Item {
    char name[50]; // Name of the item
    struct Item* next; // Pointer to the next item
    struct Item* previous; //pointer to previous argument
} Item;

// Struct for a person
typedef struct Person {
    char name[50]; // Name of the person
    Item* first_item; // Pointer to the first item in the list
    struct Person* next; // Pointer to the next person
    struct Person* previous; //pointer to previous person
} Person;

void menu(struct Person* List, char file[]);
struct Person* readFile(char myFile[]);
void displayFile(struct Person* List, char file[]);
char* loadNewFile();
void editListMenu(struct Person* List, char file[]);
void addItem(struct Person* List, char file[]);
void deleteItem(struct Person* List, char file[]);
void editItem(struct Person* List, char file[]);
void editBoardMenu(struct Person* List, char file[]);
void addList(struct Person* List, char file[]);
void deleteList(struct Person* List, char file[]);
void editList(struct Person* List, char file[]);
void saveBoard(struct Person* List, char file[]);
void printAsciiArt();

