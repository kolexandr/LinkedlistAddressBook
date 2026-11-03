#ifndef UI_UTILS
#define UI_UTILS

#include "linkedlist.h"

int display_options(int *choice);

void wait_for_enter(void);

void cleanup_memory(struct linkedlist *head);

void handle_deleting_address_position(struct linkedlist **head, int *position);

void handle_deleting_address_book(struct linkedlist **head);

void handle_add_address_end(struct linkedlist **head);

void handle_add_address_position(struct linkedlist **head, int *position);

void handle_load_address_book(char *path, struct linkedlist **head);

void handle_find_address_position(struct linkedlist *head, int *position);

void handle_find_address_feature(struct linkedlist *head, char *feature);

#endif