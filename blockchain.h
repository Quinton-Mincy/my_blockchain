#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
//libraries
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
//flags
#define ADN  0b1//add node
#define RMN  0b10//remove node
#define ADB  0b100//add block
#define ADBA 0b1000//add block to all nodes
#define RMB  0b10000//remove block
#define LS   0b100000//list nodes by identifiers
#define LSL  0b1000000//list nodes by identifiers w/associated blocks
#define SYN  0b10000000//synchronize all nodes with eachother (identical block chains) 
#define Q    0b100000000//quit. leave blockchain
//user commands
#define ADD_NODE "add node"
#define REMOVE_NODE "remove node"
#define ADD_BLOCK "add block"
#define REMOVE_BLOCK "remove block"
#define LIST_NODES "ls"
#define LIST_NODES_L "ls -l"
#define SYNCHRONIZE "sync"
#define QUIT "quit"

typedef struct s_bids{
    char* bid;
    struct s_bids* next;
}block;

typedef struct s_nids{
    int nid;
    struct s_bids* block;
    struct s_nids* next;    
}node;

typedef struct s_cmd_func
{
  char *cmd; 
  void (*func) (char* id, int* flags, node** head);
}cmd_func;

//formatting (formatting.c)
void display_prompt(char* curr_size, int* flags);
char* itoa(int num);
void list_nodes(char* biff, int* flags, node** head);
void print_chain(node* current_chain);
char* reverse_string(char* str);
//program initialization (init_chain.c)
node* continue_blockchain(node* current_chain, int* n_nodes, int* n_blocks);
node* new_blockchain(int* n_nodes, int* n_blocks);
node* run_program(node* current_chain,char* pathname, int* n_nodes, int* n_blocks);
//user interaction (ui.c)
void get_value(const cmd_func command_functions[], char* buffer, node** head, int* flags);
void parse_flag_counter(int* flags, int* n_nodes, int* n_blocks);
node* read_input(node* node_chain, int* n_nodes, int* n_blocks);
node* user_input_loop(node** head, cmd_func command_functions[], int* n_nodes, int* n_blocks, int* flags);
//node handling (node_handles.c)
void add_node(char* nid, int* flags, node** node_chain);
bool check_nid(node* head, char* nid);
node* create_node();
node* current_node_state(node* head);
void free_chain(node* head);
void free_node(node* node);
node* initialize_node(int nid);
void remove_node(char* nid, int* flags, node** head);
void synchronize_nodes(char* bid, int* flags, node** head);
//block handling (blocks.c)
void add_block(char* bid, int* flags, node** head);
bool check_bid(block* blockchain, char* bid);
block* cpy_blockchain(block* head_block);
block* create_block();
block* current_block_state(block* head);
void free_block(block* block);
block* initialize_block(char* bid);
void remove_block(char* bid,int* flags , node** head);
//file creators/parsers (parsing.c)
block* read_bids(int fd);
void read_block(block* current_block, char* buffer, int* size);
void read_count(int* n_nodes, int* n_blocks, int fd);
node* readfile(char* filename, int* n_nodes, int* n_blocks);
void save_query(char* pathname, node* current_chain, int* n_nodes, int* n_blocks);
void write2file(node* chain, char* filename, int* n_nodes, int* n_blocks);

#endif