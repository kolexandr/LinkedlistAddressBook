#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "linkedlist.h"


void display_one_address(struct linkedlist *address){
    if (address == NULL){ 
        fprintf(stderr, "Error: the address is empty, unable to display address\n");
        return;
    }
    printf("Name: %s, Surname: %s, Email: %s, Phone: %s\n\n", address->name, address->surname, address->email, address->phone_number);
}


void display_addresses(struct linkedlist *head){
    if (head == NULL){ 
        fprintf(stderr, "Error: the head is empty, unable to display addresses\n");
        return;
    }
    while(head != NULL){
        display_one_address(head);
        head = head->next;
    }
};

struct linkedlist *create_address(char *name, char *surname, char *email, char *phone_number){
    if ((strlen(name) > MAX_STRING) | (strlen(surname) > MAX_STRING) | (strlen(email) > MAX_STRING) | (strlen(phone_number) > MAX_STRING)){
        fprintf(stderr, "The total size exceeds limit\n");
        return NULL;
    }

    struct linkedlist *address = malloc(sizeof(struct linkedlist));

    if (address == NULL){
        fprintf(stderr, "Unable ot allocate memory for the linkedlist\n");
        return NULL; // handle it
    }

    strcpy(address->name, name);
    strcpy(address->surname, surname);
    strcpy(address->email, email);
    strcpy(address->phone_number, phone_number);
    address->next = NULL;

    return address;
}

int load_address_book(char *path_name, struct linkedlist **head){
    FILE *file = fopen(path_name, "r");

    if (file == NULL) {
        perror("Error:");
        return -1;
    }

    char name[50], surname[50], email[50], phone_number[50];

    struct linkedlist **tail = head;

    // find the position where the next node should be inserted
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }

    while (fscanf(file, "%49s %49s %49s %49s", name, surname, email, phone_number) == 4) {

        struct linkedlist *address =
            create_address(name, surname, email, phone_number);

        if (address == NULL) {
            fclose(file);
            return 1;
        }

        *tail = address;
        tail = &address->next;
    }

    fclose(file);

    return 0;
}

int add_new_address_end(struct linkedlist **head, struct linkedlist *address){ 
    if (address == NULL){
        fprintf(stderr, "Error: the address to be added is empty\n");
        return 1;
    }

    struct linkedlist *temp = *head;
    
    if ((temp == NULL) && (address != NULL)){
        temp = address;
        return 0;
    }
    
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = address;

    return 0;
}

int add_new_address_position(struct linkedlist **head, struct linkedlist *address, int position){
    if ((address == NULL) | (position < 0)){
        fprintf(stderr, "Error: null values passed\n");
        return 1;
    }

    if (position == 0){
        address->next = *head;
        *head = address;
        return 0;
    }

    struct linkedlist *temp = *head;

    // we find the position, insert the address by changing the head next pointer to the address and address pointer is pointing to the head->next->next now  
    for(int i=0; i<position; i++){
        if (temp->next == NULL){
            fprintf(stderr, "Error: position exceeds the list length\n");
            return 1;
        }

        if (i+1 == position){
            address->next = temp->next;
            temp->next = address;
            return 0;
        }

        temp = temp->next;
    }

    return 1;
}

int delete_address_position(struct linkedlist **head, int position){ // FIX the last member is not removed 
    if ((*head == NULL) | (position < 0)){
        fprintf(stderr, "Error: null values passed\n");
        return 1;
    }

    struct linkedlist *address_to_delete;

    if (position == 0){
        address_to_delete = *head;
        *head = (*head)->next;
        free(address_to_delete);
        return 0;
    }

    struct linkedlist *temp = *head;
    for(int i=0; i<position; i++){
        if (temp->next == NULL){
            fprintf(stderr, "Error: position exceeds the list length\n");
            return 1;
        }
        
        if (i+1 == position){
            address_to_delete = temp->next; 
            break;
        }

        temp = temp->next;
    }

    if (temp->next->next != NULL){
        temp->next = temp->next->next;
    }
    free(address_to_delete);

    return 0;
}

int delete_address_book(struct linkedlist **head){
    if (*head == NULL){
        fprintf(stderr, "Error: unable to delete the emply list");
        return 1;
    }

    struct linkedlist *temp = *head;
    while (*head != NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    
    return 0;
}

// int find_address_position(struct linkedlist *head, int position){
    
//     if ((head == NULL) | (position < 0)){
//         fprintf(stderr, "Error: null values passed\n");
//         return 1;
//     }

//     struct linkedlist *address_to_find;

//     if (position == 0){
        
//     }

//     return 0;
// }

// int find_address_feature(struct linkedlist *head, struct linkedlist *address, int position){
//     return 0;
// }