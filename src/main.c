#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "ui_utils.h"
#include "signal_utils.h"

struct linkedlist *head = NULL;

int main(void){
    char path[512];
    int choice, position;
    char feature[MAX_STRING];

    setup_signals();

    while (!is_interrupted()){
        if (display_options(&choice) != 0){

            if (is_interrupted()){
                break;
            }

            printf("Please try again\n");
            continue;
        }

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
            case 0:
                cleanup_memory(head);
                return 0;
            default:
                printf("Invalid input, try again\n");
                break;
        }
        wait_for_enter();
    }

    printf("\nSignal was received, safe exit\n");
    cleanup_memory(head);
    

    return 0;
}