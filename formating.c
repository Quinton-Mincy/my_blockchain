#include "blockchain.h"

void display_prompt(char* curr_size, int* flags){
    char prompt_left[] = "[s";
    char prompt_left_desync[] = "[-";
    char prompt_right[] = "]>";
    int length = strlen(curr_size);

    if( (*flags & SYN) != 0){
        write(1,prompt_left_desync,3);
    }else{
        write(1,prompt_left,3);
    }

    write(1,curr_size,sizeof(char)*length);
    write(1,prompt_right,3);
}

char* itoa(int num){
    char str[1024] = {'\0'};
    int i = 0;
    if(num != 0){
        while(num != 0){
            str[i] = (num%10) + '0';
            num/=10;
            i++;
        }
    }else{
        str[0] = 48;
    }
    char* final = strdup(str);
    if(strlen(final)>1){
        return reverse_string(final);
    }
    return final;
}

void list_nodes(char* buffer, int* flags, node** head){
    if(buffer){//buffer is not needed in ls/ls-l commands, but function pointers in cmd_func array need to have uniform input. Could create a separate array for functions such as these (also synchronize)

    }
    if( (*flags & LSL) !=0 ){
        print_chain(*head);
        *flags &= ~LSL;
    }else{
        node* header = *head;
        while(header != NULL){
            printf("%d\n",header->nid);
            header = header->next;
        }
    }
}

void print_chain(node* head){
    if(head == NULL){
        printf("NOK: Blockchain is empty\n");
        return;
    }
    while(head!=NULL){
        printf("%d:",head->nid);
        if(head->block != NULL){
            block* temp = head->block;
            while(temp != NULL){
                printf(" %s",temp->bid);
                temp = temp->next;
            }
        }
        printf("\n");
        head = head->next;
    }
}

char* reverse_string(char* str){
    int endex = strlen(str) -1;
    int index = 0;
    while(index < endex){
        char temp = str[index];
        str[index] = str[endex];
        str[endex] = temp;
        index++;
        endex--;
    }
    return str;
}