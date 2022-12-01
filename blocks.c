#include "blockchain.h"

void add_block(char* bid, int* flags, node** head){
    block* curr;
    int len = strlen(bid);
    if( bid[len-1] == '*'){
        bid[len-1] = '\0';
        bid[len-2] = '\0';
        *flags |= ADBA;
    }
    if( (*head)->block == NULL){
        curr = initialize_block(bid);
        (*head)->block = curr;
    }else if( !(check_bid((*head)->block, bid)) ){
        printf("NOK: This block (%s) already exists...\n",bid);
        return;
    }
    else{
        curr = current_block_state((*head)->block);
        curr->next = initialize_block(bid);
        curr = curr->next;
        if( (*flags &= ADBA) ){
            synchronize_nodes(bid, flags, head);
        }
    }
    *flags |= ADB;
    *flags |= SYN;
    printf("OK-block added!\n");
}

bool check_bid(block* blockchain, char* bid){
while(blockchain != NULL){
    if(strcmp(blockchain->bid, bid) == 0){
        return false;
    }
    blockchain = blockchain->next;
    }
    return true;
}

block* cpy_blockchain(block* head_block){
    block* blockchain_cpy = NULL;
    block* blockchain_cpy_head = NULL;
    while(head_block != NULL){
        if(blockchain_cpy == NULL){
            blockchain_cpy = initialize_block(head_block->bid);
            blockchain_cpy_head = blockchain_cpy;
        }else{
            blockchain_cpy->next = initialize_block(head_block->bid);
            blockchain_cpy = blockchain_cpy->next;
        }
        head_block = head_block->next;
    }
    return blockchain_cpy_head;
}

block* create_block(){
    block* new_block = malloc(sizeof(new_block));
    new_block->bid = NULL;
    new_block->next = NULL;
    return new_block;
}

block* current_block_state(block* head){
    while(head->next != NULL){
        head = head->next;
    }
    return head;
}
void free_block(block* block){
    block->bid = NULL;
    block->next = NULL;
    free(block);
}

block* initialize_block(char* bid){
    block* new_block = create_block();
    new_block->bid = strdup(bid);
    return new_block;
}

void remove_block(char* bid, int* flags, node** head){
    block* block_chain = (*head)->block;
    if( strcmp(block_chain->bid, bid) == 0){//if block to be removed is first in the list
        (*head)->block = block_chain->next;
        free_block(block_chain);
        printf("OK-block (%s) removed!\n",bid);
        *flags |= RMB;
        synchronize_nodes(bid, flags, head);
        return;
    }
    while( block_chain->next != NULL){
        if( strcmp(block_chain->next->bid, bid) == 0){
            block* temp = block_chain->next;
            block_chain->next = block_chain->next->next;
            free_block(temp);
            printf("OK-block (%s) removed!\n",bid);
            *flags |= RMB;
            synchronize_nodes(bid, flags, head);
            return;
        }
        block_chain= block_chain->next;
    }
    printf("NOK: Block (%s) Does Not Exist\n", bid);
}
