#include "blockchain.h"

void add_node(char* nid, int* flags, node** node_chain){
    if( !(check_nid((*node_chain), nid)) ){
        printf("NOK: This node (%s) already exists...\n",nid);
        return;
    }
    if(*nid == 48){
        printf("NOK: Node (0) is Forbidden\n");
        return;
    }
    if( (atoi(nid)) == 0 ){
        printf("Please Initialize Nodes To Numeric Values\n");
        return;
    }
    int nid_ = atoi(nid);
    node* curr;
    if((*node_chain) == NULL){
        curr = initialize_node(nid_);
        (*node_chain) = curr;
    }else{
        curr = current_node_state(*node_chain);
        curr->next = initialize_node(nid_);
        curr = curr->next;
    }
    *flags |= ADN;
    printf("OK-node added!\n");
}

bool check_nid(node* head, char* nid){
    int nid_ = atoi(nid);
    while(head != NULL){
        if(head->nid == nid_){
            return false;
        }
        head = head->next;
    }
    return true;
}

node* create_node(){
    node* new_node = malloc(sizeof(node));
    new_node->nid = 0;
    new_node->block = NULL;
    new_node->next = NULL;
    return new_node;
}

node* current_node_state(node* head){
    while(head->next != NULL){
        head = head->next;
    }
    return head;
}

void free_chain(node* head){
    while(head != NULL){
        node* temp = head;
        head = head->next;
        free_node(temp);
    }
}

void free_node(node* node){
    if(node->block != NULL){
        block* blockchain = node->block;
        while(blockchain != NULL){
            block* temp = blockchain;
            blockchain = blockchain->next;
            free_block(temp);
        }
        node->block = NULL;
    }
    node->nid = 0;
    node->next = NULL;
    free(node);
}

node* initialize_node(int nid){
    node* new_node = create_node();
    new_node->nid = nid;
    return new_node;
}

void remove_node(char* nid, int* flags, node** head){
    node* ref = (*head);
    int nid_ = atoi(nid);
    if( (ref)->nid == nid_){
        printf("NOK-Cannot remove the genesis node\n");
        return;
    }
    while( (ref)->next != NULL){
        if( (ref)->next->nid == nid_){
            node* temp = (ref)->next;
            (ref)->next = (ref)->next->next;
            free_node(temp);
            *flags |= RMN;
            printf("OK-Node (%d) removed!\n",nid_);
            return;
        }
        (ref) = (ref)->next;
    }
    printf("NOK: Node (%d) Does Not Exist\n", nid_);
}

void synchronize_nodes(char* bid, int* flags, node** head){
    if(bid){//buffer is not needed in synchronize_nodes command, but function pointers in cmd_func array need to have uniform input. Could create a separate array for functions such as these (also ls/ls-l)

    }
    block* block_head = (*head)->block;
    if(block_head == NULL){
        printf("No blocks to synchronize!\n");
        return;
    }
    node* temp = (*head);
    while(temp != NULL){
        temp->block = cpy_blockchain(block_head);//optimize to not overwrite data unnecessarily 
        temp = temp->next;
    }
    if( (*flags &= ADBA) != 0 ){
        *flags &= ~ADBA;
        return;
    }
    *flags &= ~SYN;
    printf("OK-Synchronized!\n");
}