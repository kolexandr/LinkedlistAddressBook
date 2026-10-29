#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "linkedlist.h"

void display_addresses(struct linkedlist *head){
    if (head == NULL){ 
        fprintf(stderr, "Error: the head is empty, unable to display addresses\n");
        return;
    }
    struct linkedlist *temp;
    temp = head;
    while(temp != NULL){
        printf("Name: %s, Surname: %s, Email: %s, Phone: %s\n\n");
        temp = head->next;
    }
};

void display_one_address(struct linkedlist *address){
    if (address == NULL){ 
        fprintf(stderr, "Error: the address is empty, unable to display address\n");
        return;
    }
    printf("Name: %s, Surname: %s, Email: %s, Phone: %s\n\n");
}

struct linkedlist *create_address(char *name, char *surname, char *email, char *phone_number){
    if (strlen(name) > MAX_STRING | strlen(surname) > MAX_STRING | strlen(email) > MAX_STRING | strlen(phone_number) > MAX_STRING){
        fprintf(stderr, "The total size exceeds limit\n");
        return -1;
    }

    struct linkedlist *address = malloc(sizeof(struct linkedlist));

    if (address == NULL){
        fprintf(stderr, "Unable ot allocate memory for the linkedlist\n");
        return 1;
    }

    strcpy(address->name, name);
    strcpy(address->surname, surname);
    strcpy(address->email, email);
    strcpy(address->phone_number, phone_number);

    return address;
}

struct linkedlist *load_address_book(char *path_name){
    FILE *file;
    file = fopen(path_name, "r");

    if (file = NULL){
        perror("Error: ");
        return -1;
    }

    char name[50], surname[50], email[50], phone_number[50];
    struct linkedlist *head;
    struct linkedlist *next;
    head->next = next;
    while(fscanf(file, "%49s %49s %49s %49s", name, surname, email, phone_number) != NULL){
        struct linkedlist *address;
        if(!(address = create_address(name, surname, email, phone_number))){
            continue;
        }
        next->next = address;
        next = next->next;
    }

    return head->next->next;
}

int add_new_address_end(struct linkedlist *head, struct linkedlist *address){
    if (head == NULL | address == NULL){
        return 1;
    }
    
    while(head->next != NULL){
        head = head->next;
    }

    head->next = address;

    return 0;
}

// FIX
int add_new_address_position(struct linkedlist *head, struct linkedlist *address, int position){
    if (head == NULL | address == NULL | position == NULL){
        fprintf(stderr, "Error: null values passed\n");
        return 1;
    }

    // consider the case that the position might be 0 and we will need to change head, so maybe return linkedlist struct instead of int
    if (position == 0){
        address->next = head;
    }

    // we find the position, insert the address by changing the head next pointer to the address and address pointer is pointing to the head->next->next now  
    for(int i=0; i<position; i++){
        if (head->next == NULL){
            fprintf(stderr, "Error: position exceeds the list length\n");
            return 1;
        }
        

        if (i+1 == position){
            break;
        }

        head = head->next;
    }

    
}

int delete_address_position(struct linkedlist *head, int position){
    if (head == NULL | position == NULL){
        fprintf(stderr, "Error: null values passed\n");
        return 1;
    }

    struct linkedlist *address_to_delete;

    if (position == 0){
        address_to_delete = head;
        goto delete_address;
    }

    // check head->next, once we find position take the address, keep the head. Then connect head->next to head->next->next first and then clean the address to delete
    for(int i=0; i<position; i++){
        if (head->next == NULL){
            fprintf(stderr, "Error: position exceeds the list length\n");
            return 1;
        }
        
        if (i+1 == position){
            address_to_delete = head->next; 
            break;
        }

        head = head->next;
    }

delete_address:
    head->next =head->next->next;
    free(address_to_delete);

    return 0; 
}

int delete_address_book(struct linkedlist *head){
    struct linkedlist *temp = head;
    while (head != NULL){
        temp = head->next;
        free(head);
        head = temp;
    }
    
    return 0;
}

int find_address_position(struct linkedlist * head, int position){

}

int find_address_feature(struct linkedlist *head, struct linkedlist *address, int position){

}