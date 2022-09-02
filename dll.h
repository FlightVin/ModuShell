#ifndef _DLL_H_
#define _DLL_H_
#include "headers.h"

typedef struct dll* DLL;
typedef struct dll_node* DLLNode;

struct dll{
    size_t size;
    DLLNode start_node;
    DLLNode last_node;
};

struct dll_node{
    DLLNode prev_node;
    ProcessPtr element;
    DLLNode next_node;
};

void insert_dll(DLL, pid_t, char*); // pushes a new node with given parameters into dll
void deque_dll(DLL); // removes the first node from dll
void pop_dll(DLL); // rmeoves last node from dll

void delete_from_dll(DLL, pid_t); // removes a particular node from dll

void delete_node(DLL, DLLNode); // removed a particular node from dll given pointer

DLLNode make_node(pid_t, char*);

DLL make_dll();

void free_node(DLLNode);

DLLNode find_node(DLL, pid_t);

#endif