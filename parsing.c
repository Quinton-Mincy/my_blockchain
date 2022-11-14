#include "blockchain.h"

block* read_bids(int fd){
    int i_bid = 0;
    char bid[255] = {'\0'};
    char buffer = '\0';
    read(fd, &buffer,1);
    block* curr_block = NULL;
    block* block_ref = NULL;
    while(buffer != '\n'){//read bids
        if(buffer != '-'){
            bid[i_bid] = buffer;
            i_bid++;
        }
        else{
            if(curr_block == NULL){
                curr_block= initialize_block(bid);
                block_ref = curr_block;
            }else{
                curr_block->next = initialize_block(bid);
                curr_block = curr_block->next;
            }
            bzero(bid,255);
            i_bid = 0;
        }
        read(fd, &buffer,1);//catch last bid
        if(buffer == '\n'){
            curr_block->next = initialize_block(bid);
            curr_block = curr_block->next;
            bzero(bid,255);
        }
    }
    return block_ref;
}

void read_block(block* temp, char* buffer, int* size){
    char* dash = "-";
    char* nl = "\n";
    while(temp != NULL){
        char* bid = strdup(temp->bid);
        *size+= strlen(bid);
        strcat(buffer,bid);//make sure that naming size is limited
        if(temp->next != NULL){
            strcat(buffer,dash);
            *size+=1;
        }
        free(bid);
        temp = temp->next;
    }
    strcat(buffer,nl);
    *size+=1;
}

void read_count(int* n_nodes, int* n_blocks, int fd){
    int index = 0;
    char count_buffer;

    char str_n_node_count[255] = {'\0'};
    char str_n_block_count[255] = {'\0'};

    while(index < 13){//burn through "Node Count: text"
        read(fd,&count_buffer,1);
        index++;
    }
    index = 0;
    while(count_buffer!= ' '){//copy n_nodes number
        str_n_node_count[index] = count_buffer;
        read(fd,&count_buffer,1);
    }
    index = 0;
    while(index < 14){//burn through "Block Count: text"
        read(fd,&count_buffer,1);
        index++;
    }
    index = 0;
    while(count_buffer != '\n'){//copy n_blocks number
        str_n_block_count[index] = count_buffer;
        read(fd,&count_buffer,1);
    }
    *n_nodes = atoi(str_n_node_count);
    *n_blocks = atoi(str_n_block_count);
}

node* readfile(char* filename, int* n_nodes, int* n_blocks){
    int fd = open(filename,S_IRUSR, 0644);
    read_count(n_nodes, n_blocks, fd);
    int i_node = 0;
    node* chain = NULL;
    node* chain_ref = NULL;
    while(i_node < *n_nodes){
        char buffer = '\0';
        char nid[255] = {'\0'};
        int i_nid = 0;
        read(fd, &buffer,1);
        while(buffer != ' '){//read nids
            nid[i_nid] = buffer;
            i_nid++;
            read(fd, &buffer,1);
        }
        if(chain == NULL){//initialize node in chain
            chain = initialize_node(atoi(nid));
            chain_ref = chain;
        }else{
            chain->next = initialize_node(atoi(nid));
            chain = chain->next;
        }
        bzero(nid, 255);

        chain->block = read_bids(fd);
        i_node++;
    }
    return chain_ref;
}

void save_query(char* pathname, node* current_chain, int* n_nodes, int* n_blocks){
    char buffer[2];
    char* yes = "y";
    write(1, "Would You Like To Save The Changes You've Made? [y/n]: ", 56);
    read(0,buffer,2);
    if( strncasecmp(&buffer[0],yes,1) == 0 ){
        write2file(current_chain, pathname, n_nodes, n_blocks);
        write(1, "Saved!\n",8);
    }
}

void write2file(node* chain, char* filename, int* n_nodes, int* n_blocks){
    int fd = open(filename,O_CREAT | O_RDWR | O_TRUNC, 0644);
    char* space = " ";

    char str_n_nodes[255] = "Node Count: ";
    char str_n_blocks[255] = "Block Count: ";
    strcat(str_n_nodes,itoa(*n_nodes));
    strcat(str_n_blocks,itoa(*n_blocks));
  
    write(fd,str_n_nodes,strlen(str_n_nodes));
    write(fd, " ",1);
    write(fd,str_n_blocks,strlen(str_n_blocks));
    write(fd, "\n",1);
    while(chain != NULL){
        block* curr_block = chain->block;
        int size = 0;
        char buffer[1024] = {'\0'};
        int nid = chain->nid;
        char* str_nid = itoa(nid);
        strcat(buffer, str_nid);
        strcat(buffer, space);
        size+=strlen(buffer);

        read_block(curr_block,buffer,&size);
    
        write(fd,buffer,size);
        chain = chain->next;
    }
    close(fd);
}