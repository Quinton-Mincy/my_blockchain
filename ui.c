#include "blockchain.h"

void get_value(const cmd_func command_functions[], char* buffer, node** head, int* flags){
    int i = 0;
    while(command_functions[i].cmd != NULL){
        int cmd_size = strlen(command_functions[i].cmd);
        if(strncmp(buffer, command_functions[i].cmd, cmd_size) == 0){
            if( strcmp(buffer, LIST_NODES_L) == 0){
                *flags |= LSL;
            }
            char* value = strdup(&buffer[cmd_size+1]);
            command_functions[i].func(value, flags, head);
            return;
        }
        i++;
    }
    if(*buffer != 0 && strcmp(buffer, QUIT) != 0){
        printf("NOK: Command (%s) not found...\n",buffer);
    }
}

void parse_flag_counter(int* flags, int* n_nodes, int* n_blocks){
    if( (*flags & ADN) != 0){//node added
        *n_nodes+=1;
        *flags &= ~ADN;
    }
    else if( (*flags & RMN) != 0){//node removed
        *n_nodes-=1;
        *flags &= ~RMN;
    }
    else if( (*flags & ADB) !=0){
        *n_blocks+=1;
        *flags &= ~ADB;
    }
    else if( (*flags & RMB) !=0){
        *n_blocks-=1;
        *flags &= ~RMB;
    }
}

node* read_input(node* node_chain, int* n_nodes, int* n_blocks){
    int flags = 0b00000000;

    //list of valid commands and their corresponding functions
    cmd_func command_functions[] = { 
                                    {ADD_NODE, &add_node}, \
                                    {ADD_BLOCK, &add_block}, \
                                    {LIST_NODES, &list_nodes} , \
                                    {LIST_NODES_L, &list_nodes}, \
                                    {SYNCHRONIZE, &synchronize_nodes}, \
                                    {REMOVE_NODE, &remove_node}, \
                                    {REMOVE_BLOCK, &remove_block}, \
                                    {NULL, NULL}
                                   };
    node* head = node_chain;
    head = user_input_loop(&head,command_functions, n_nodes, n_blocks, &flags);
    return head;
}

node* user_input_loop(node** head, cmd_func command_functions[], int* n_nodes, int* n_blocks, int* flags){
    printf("Please Limit Block Names to 14, Alpha-Numeric Characters\n");
    char buffer[25] = {'\0'};
    while(strncmp(buffer,QUIT,sizeof(QUIT)-1) != 0){
        bzero(buffer,25);
        char* str_n_nodes = itoa(*n_nodes);
        display_prompt(&str_n_nodes[0], flags);
        int bytes = read(0,buffer,24);
        if(bytes == -1){ 
            printf(" %s \n", strerror(errno));
            free_chain(*head);
            return NULL;
        }
        if(bytes == 0){
            return *head;
        }
        buffer[bytes -1] = '\0';//replaces newline character added to end of buffer when user presses 'enter'
        // parse_commands(buffer, &current_chain, &size, &head,&current_block, &flags);
        get_value(command_functions, buffer,head, flags);
        parse_flag_counter(flags, n_nodes, n_blocks);
    }
    return *head;
}