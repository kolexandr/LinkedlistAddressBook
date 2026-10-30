#ifndef LINKEDLIST
#define LINKEDLIST

#define MAX_STRING 50
#define FILE_SIZE 512

struct linkedlist{
    char name[MAX_STRING];
    char surname[MAX_STRING];
    char email[MAX_STRING];
    char phone_number[MAX_STRING];
    struct linkedlist *next;
};

void display_one_address(struct linkedlist *address);

void display_addresses(struct linkedlist *head);

struct linkedlist *create_address(char *name, char *surname, char *email, char *phone_number);

int load_address_book(char *path_name, struct linkedlist **head);

int add_new_address_end(struct linkedlist **head, struct linkedlist *address);

int add_new_address_position(struct linkedlist **head, struct linkedlist *address, int position);

int delete_address_position(struct linkedlist **head, int position);

int delete_address_book(struct linkedlist **head);

struct linkedlist *find_address_position(struct linkedlist *head, int position);

struct linkedlist *find_address_feature(struct linkedlist *head, char *feature);

#endif