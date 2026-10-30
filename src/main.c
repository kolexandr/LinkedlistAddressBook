#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "utils.h"

// TODO csv should have commas, change it

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
    read_int(choice);
}

struct linkedlist *handle_create_address(void){
    char name[MAX_STRING], surname[MAX_STRING], email[MAX_STRING], phone_number[MAX_STRING];

    printf("Enter the the name for the address: ");
    if (read_string(name, MAX_STRING) != 0)
        return NULL;
    printf("Enter the the surname for the address: ");
    if (read_string(surname, MAX_STRING) != 0)
        return NULL;
    printf("Enter the the email for the address: ");
    if (read_string(email, MAX_STRING) != 0)
        return NULL;
    printf("Enter the the phone number for the address: ");
    if (read_string(phone_number, MAX_STRING) != 0)
        return NULL;
    printf("\n");

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
    if(read_int(position) != 0){
        fprintf(stderr, "Error: invalid integer was entered\n");
        return;
    }
    
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

void handle_add_address_position(struct linkedlist **head, int *position){
    printf("Please enter the position for adding new address: ");
    
    if(read_int(position) != 0){
        fprintf(stderr, "Error: invalid integer was entered\n");
        return;
    }

    struct linkedlist *address = handle_create_address();
    
    if (address == NULL) return;

    if (add_new_address_position(head, address, *position) != 0){
        fprintf(stderr, "Error: adding the address on the position failed\n");
        free(address);
        return;
    }
    
    printf("New address was added successfully!\n");
}

void handle_load_address_book(char *path, struct linkedlist **head){
    
    if (get_file_path(path, FILE_SIZE) != 0) {
        fprintf(stderr, "Error: unable to get file path\n");
        return;
    }
    if (load_address_book(path, head) != 0){
        fprintf(stderr, "Error: loading from the file failed");
        return;
    }

    printf("The file was loaded successfully!\n");
}

void handle_find_address_position(struct linkedlist *head, int *position){
    if (head == NULL){
        fprintf(stderr, "Error: head is empty\n");
        return;
    }
    printf("Please enter the position for finding the address: ");
    if(read_int(position) != 0){
        fprintf(stderr, "Error: invalid integer was entered\n");
        return;
    }
    struct linkedlist *address_to_find;
    if ((address_to_find=find_address_position(head, *position)) == NULL){ // TODO check position pointer for others
        fprintf(stderr, "Error: unable to find the address in the list\n");
        return;
    }
    printf("The node that was found:\n");
    display_one_address(address_to_find);
}

void handle_find_address_feature(struct linkedlist *head, char *feature){
    if (head == NULL){
        fprintf(stderr, "Error: head is empty\n");
        return;
    }
    printf("Please enter the feature to find the address: ");
    if (read_string(feature, MAX_STRING) != 0){
        fprintf(stderr, "Error: invalid string was entered\n");
        return;
    }
    struct linkedlist *address_to_find;
    if ((address_to_find=find_address_feature(head, feature)) == NULL){
        fprintf(stderr, "Error: unable to find the address in the list\n");
        return;
    }
    printf("The node that was found:\n");
    display_one_address(address_to_find);
}

int main(void){

    char path[512];
    int choice, position;
    char feature[MAX_STRING];
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
            case 4: 
                handle_add_address_position(&head, &position);
                break;
            case 5:
                handle_deleting_address_position(&head, &position);
                break;
            case 6:
                handle_deleting_address_book(&head);
                break;
            case 7:
                handle_find_address_position(head, &position);
                break;
            case 8:
                handle_find_address_feature(head, feature);
                break;
            default:
                printf("Invalid input, try again\n");
                break;
        }
    }
    

    return 0;
}