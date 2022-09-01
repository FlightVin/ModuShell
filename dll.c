#include "headers.h"

void insert_dll(DLL que, pid_t pid, char* process_name){
    que->size++;
    DLLNode new_node = make_node(pid, process_name);

    que->last_node->next_node = new_node;
    new_node->prev_node = que->last_node;

    que->last_node = new_node;

}

void deque_dll(DLL que){
    if (que->size == 0) return;

    que->size--;
    DLLNode old_last_node = que->last_node;

    que->last_node = old_last_node->prev_node;
    free_node(old_last_node);

    que->last_node->next_node = NULL;
}

void pop_dll(DLL que){
    if (que->size == 0) return;

    que->size--;
    DLLNode old_first_node = que->start_node->next_node;
    
    que->start_node->next_node = old_first_node->next_node;
    free_node(old_first_node);
}

void delete_from_dll(DLL que, pid_t pid){
    if (que->size == 0) return;

    DLLNode cur_node = que->start_node->next_node;
    while(cur_node != NULL && cur_node->element->process_pid != pid){
        cur_node = cur_node->next_node;
    }

    if (cur_node == NULL){
        printf("ERROR! Lost track of background process %d\n", pid);
        return;
    }

    if (cur_node == que->last_node){
        deque_dll(que);
    } else {
        que->size--;

        DLLNode prev_deleted_node = cur_node->prev_node;
        DLLNode next_deleted_node = cur_node->next_node;

        free_node(cur_node);

        prev_deleted_node->next_node = next_deleted_node;
    }
}

DLLNode make_node(pid_t pid, char* process_name){
    ProcessPtr process = (ProcessPtr) malloc(sizeof(BackProcess));
    process->process_name = strdup(process_name);
    process->process_pid = pid;

    DLLNode ret = (DLLNode) malloc(sizeof(struct dll_node));
    ret->element = process;
    ret->prev_node = NULL;
    ret->next_node = NULL;

    return ret;    
}

DLL make_dll(){
    DLL ret = (DLL) malloc(sizeof(struct dll));
    ret->size = 0;
    ret->start_node = make_node(-1, "\0");
    ret->last_node = ret->start_node;
    return ret;
}

void free_node(DLLNode ptr){
    free(ptr->element->process_name);
    free(ptr);
}