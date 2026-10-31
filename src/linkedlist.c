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
        printf("The list is empty, nothing to show\n");
        return;
    }
    while(head != NULL){
        display_one_address(head);
        head = head->next;
    }
};

struct linkedlist *create_address(char *name, char *surname, char *email, char *phone_number){
    if ((strlen(name) >= MAX_STRING) || (strlen(surname) >= MAX_STRING) || (strlen(email) >= MAX_STRING) || (strlen(phone_number) >= MAX_STRING)){
        fprintf(stderr, "The total size exceeds limit\n");
        return NULL;
    }

    struct linkedlist *address = malloc(sizeof(struct linkedlist));

    if (address == NULL){
        fprintf(stderr, "Unable ot allocate memory for the linkedlist\n");
        return NULL;
    }

    strcpy(address->name, name);
    strcpy(address->surname, surname);
    strcpy(address->email, email);
    strcpy(address->phone_number, phone_number);
    address->next = NULL;

    return address;
}

int parse_address(char *line, struct linkedlist **address){
    char *name = strtok(line, ",");
    char *surname = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    char *phone_number = strtok(NULL, ",\n");

    if (name == NULL || surname == NULL ||
        email == NULL || phone_number == NULL) {

        fprintf(stderr, "Error: invalid CSV record\n");
        return -1;
    }

    struct linkedlist *new_address = create_address(name, surname, email, phone_number);
    
    if (new_address == NULL) {
        return 1;
    }
    *address = new_address;

    return 0;
}

int load_address_book(char *path_name, struct linkedlist **head){ 
    FILE *file = fopen(path_name, "r");

    if (file == NULL) {
        perror("Error:");
        return -1;
    }
    char line[512];

    struct linkedlist **tail = head;

    while (*tail != NULL) {
        tail = &(*tail)->next;
    }

    while (fgets(line, sizeof(line), file) != NULL) {

        struct linkedlist *address;
        int status = parse_address(line, &address);
        if (status == -1){
            continue;
        } else if (status == 1){
            fclose(file);
            return 1;
        } else if (status == 0){
            *tail = address;
            tail = &address->next;
        }
    }

    fclose(file);

    return 0;
}

int add_new_address_end(struct linkedlist **head, struct linkedlist *address){ 
    if (address == NULL){
        fprintf(stderr, "Error: the address to be added is empty\n");
        return 1;
    }

    
    if ((*head == NULL)){
        *head = address;
        return 0;
    }
    
    struct linkedlist *temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = address;

    return 0;
}

int add_new_address_position(struct linkedlist **head, struct linkedlist *address, int position){
    if ((*head == NULL) || (address == NULL) || (position < 0)){
        fprintf(stderr, "Error: null values passed\n");
        return 1;
    }

    if (position == 0){
        address->next = *head;
        *head = address;
        return 0;
    }

    struct linkedlist *temp = *head;

    for(int i=0; i<position; i++){

        if (i+1 == position){
            address->next = temp->next;
            temp->next = address;
            return 0;
        }

        if (temp->next == NULL){
            fprintf(stderr, "Error: position exceeds the list length\n");
            return 1;
        }

        temp = temp->next;
    }

    return 1;
}

int delete_address_position(struct linkedlist **head, int position){ 
    if ((*head == NULL) || (position < 0)){
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

    temp->next = temp->next->next;
    
    free(address_to_delete);
    address_to_delete = NULL;

    return 0;
}

int delete_address_book(struct linkedlist **head){
    if (*head == NULL){
        fprintf(stderr, "Error: unable to delete the emply list\n");
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

struct linkedlist *find_address_position(struct linkedlist *head, int position){

    if ((head == NULL) || (position < 0)){
        fprintf(stderr, "Error: null values passed\n");
        return NULL;
    }


    for(int i=0; i< position; i++){
        if (head == NULL){
            return NULL;
        }
        head = head->next;
    }

    return head;
}

struct linkedlist *find_address_feature(struct linkedlist *head, char *feature){
    if ((head == NULL)){
        fprintf(stderr, "Error: empty address book passed\n");
        return NULL;
    }

    struct linkedlist *address_to_find;

    while(head != NULL){
        if(strcmp(feature, head->name) == 0 || strcmp(feature, head->surname) == 0 || strcmp(feature, head->email) == 0 || strcmp(feature, head->phone_number) == 0){
            address_to_find = head;
            return address_to_find;
        }
        head = head->next;
    }

    return NULL;
}