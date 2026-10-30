#include <stdio.h>
#include "linkedlist.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>

char path[30] = "addresses.csv"; // TODO change to handle user home directory
// TODO csv should have commas, change it

void remove_newline(char *str){
    str[strcspn(str, "\n")] = '\0';
}

void ask_int_input(int *choice){
    if(scanf("%d", choice) != 1){
        fprintf(stderr,"Invalid input, please enter the valid choice\n");
        while(getchar() != '\n');
    }
}

void display_options(int *choice){
    printf("\n---ADDRESS BOOK MENU---\n");
    printf("Enter 1 for displaying current list of addresses\n");
    printf("Enter 2 for loading the addresses from the file (default is ~home/ directory)\n");
    printf("Enter 3 for adding new address to the end of the list\n");
    printf("Enter 4 for adding new address to the specific position of the list\n");
    printf("Enter 5 for deleting the address on the specific position\n");
    printf("Enter 6 for deleting the whole address book\n");
    printf("Enter 7 for finding the address on the specific position\n");
    printf("Enter 8 for finding the address by the feature (name, surname, email, phone)\n\n");

    printf("Enter the desired option: ");
    ask_int_input(choice);
}

// make general create address
struct linkedlist *handle_create_address(void){
    char name[MAX_STRING], surname[MAX_STRING], email[MAX_STRING], phone_number[MAX_STRING];

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter the the name for the address: ");
    fgets(name, MAX_STRING, stdin);  // TODO remove \0 from the variables
    printf("Enter the the surname for the address: ");
    fgets(surname, MAX_STRING, stdin);
    printf("Enter the the email for the address: ");
    fgets(email, MAX_STRING, stdin);
    printf("Enter the the phone number for the address: ");
    fgets(phone_number, MAX_STRING, stdin);
    printf("\n");

    remove_newline(name);
    remove_newline(surname);
    remove_newline(email);
    remove_newline(phone_number);
    struct linkedlist *address = NULL;
    address = create_address(name, surname, email, phone_number);
    if (address == NULL){
        fprintf(stderr, "Error: the address initialization failed\n");
        return NULL;
    }

    return address;
}

void handle_deleting_address_position(struct linkedlist **head, int *position){
    printf("Please enter the position for deleting the address: ");
    ask_int_input(position);
    
    if (delete_address_position(head, *position) != 0){
        fprintf(stderr, "Error: the address deletion failed\n");
        return;
    }
    printf("The address was deleted successfully!");
}

void handle_deleting_address_book(struct linkedlist **head){
    if (delete_address_book(head) != 0){
        fprintf(stderr, "Error: the address book deletion failed\n");
        return;
    }
    printf("The address book was deleted successfully!\n");
}

// TODO handle adding to the end
void handle_add_address_end(struct linkedlist **head){
    struct linkedlist *address = handle_create_address();
    
    if (address == NULL) return;

    if (add_new_address_end(head, address) != 0){
        fprintf(stderr, "Error: adding the address to the end failed\n");
        free(address);
        return;
    }

    printf("New address was added successfully!\n");
}

// TODO handle adding to the specific location
void handle_add_address_position(struct linkedlist **head, int *position){
    printf("Please enter the position for adding new address: "); // FIX if number entered is character, it will ask again, and then infinite list containing only one struct 
    ask_int_input(position);


    struct linkedlist *address = handle_create_address();
    
    if (address == NULL) return;

    if (add_new_address_position(head, address, *position) != 0){
        fprintf(stderr, "Error: adding the address to the end failed\n");
        free(address);
        return;
    }
    
    printf("New address was added successfully!\n");
}
// TODO handle to load addresses from the file of the user directory
void handle_load_address_book(char *path, struct linkedlist **head){
    if (load_address_book(path, head) != 0){
        fprintf(stderr, "Error: loading from the file failed");
        return;
    }

    printf("The file was loaded successfully!\n");
}

// TODO handle to find the address on specific location
// void handle_find_address_position(struct linkedlist *head){
//     ask_int_input(position);
//     return;
// }

// TODO handle to find the address by the feature
// void handle_find_

int main(void){

    int choice;
    struct linkedlist *head = NULL;

    while (1){
        display_options(&choice);

        switch(choice){
            case 1:
                display_addresses(head);
                break;
            case 2:
                handle_load_address_book(path, &head);
                break;
            case 3:
                handle_add_address_end(&head);
                break;
            case 4: {
                int position;
                handle_add_address_position(&head, &position);
                break;
            }
            case 5:{
                int position;
                handle_deleting_address_position(&head, &position);
                break;
            }
            case 6:
                handle_deleting_address_book(&head);
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                printf("Invalid input, try again\n");
                break;
        }
    }
    

    return 0;
}