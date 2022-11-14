#include "blockchain.h"

node* continue_blockchain(node* current_chain, int* n_nodes, int* n_blocks){
    printf("Backup Found: Starting Blockchain\n");
    node* head_ref = NULL;

    head_ref = read_input(current_chain, n_nodes, n_blocks);
    printf("Backing Up Blockchain...\n");
    return head_ref;
}

node* new_blockchain(int* n_nodes, int* n_blocks){
    printf("No Backup Found: Starting New Blockchain\n");
    node* node_chain = NULL;
 
    node* head_ref = NULL;

    head_ref = read_input(node_chain, n_nodes, n_blocks);
    printf("Backing Up Blockchain...\n");
    return head_ref;
}

node* run_program(node* current_chain,char* pathname, int* n_nodes, int* n_blocks){
    struct stat* sb = malloc(sizeof(struct stat));
    if((lstat(pathname,sb)) == -1){
        current_chain = new_blockchain(n_nodes, n_blocks);
    }else{
        current_chain = readfile(pathname, n_nodes, n_blocks);
        current_chain = continue_blockchain(current_chain, n_nodes, n_blocks );
    }
    return current_chain;
}