#include "blockchain.h"

int main(int ac, char* argv[]){
    //check if the name of a new/existing file has been provided via CLI arguments
    //...returns -1 and error message if no file is provided by the user
    if(ac > 2){
        printf("Error: Too many arguments. Recieved %d, expected 1.",(ac-1));
        return -1;
    }
    else if(ac == 1){
        printf("Error: Too few arguments. Recieved 0, expected 1.");
        return -1;
    }
    //checks whether file is new or already exists, and runs program accodingly
    node* current_chain = NULL;
    int n_nodes, n_blocks = 0;
    char* pathname = argv[1];
    current_chain = run_program(current_chain,pathname, &n_nodes, &n_blocks);
    //save blockchain to text file, if user chooses, and free nodes of linked list
    if(current_chain != NULL){
        save_query(pathname, current_chain, &n_nodes, &n_blocks);
        free_chain(current_chain);
    }
    return 0;
}