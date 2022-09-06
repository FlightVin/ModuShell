#include "headers.h"

void add_to_history(char* command, int storage_size){
    // store upto storage_size commands in history queue
    if (history_queue->size >= 1){
        if (strcmp(command, history_queue->last_node->element->process_name) == 0) return;
    }

    insert_dll(history_queue, -1, command);
    if (history_queue->size > storage_size) deque_dll(history_queue);
}

void history(int display_num){
    // display upto display_num commands
    DLLNode cur_node = history_queue->last_node;
    int output_count = 0;

    // backtracing
    while(output_count < display_num && cur_node != history_queue->start_node){
        cur_node = cur_node->prev_node;
        output_count++;
    }

    cur_node = cur_node->next_node;

    while(cur_node != NULL){
        printf("%s\n", cur_node->element->process_name);
        cur_node = cur_node->next_node;
    }
}

struct dll* init_history(){
    // get data from file if it already exists
    sprintf(history_storage_file, "%s/%s", root_dir_path, history_storage_file_name);

    FILE* storage_file_stream = fopen(history_storage_file, "r");

    if (storage_file_stream == NULL){
        FILE* storage_file_stream = fopen(history_storage_file, "w");
        fprintf(storage_file_stream, "%ld\n", 0l);
        fclose(storage_file_stream);

        return make_dll();
    }
    DLL new_queue = make_dll();

    size_t queue_size;
    fscanf(storage_file_stream, "%ld", &queue_size);
    fscanf(storage_file_stream, "\n");

    char* process_name = NULL;
    for (int i = 0; i<queue_size; i++){
        size_t input_len = 0;
        ssize_t len = getline(&process_name, &input_len, storage_file_stream);
        process_name[len - 1] = '\0';
        insert_dll(new_queue, -1, process_name);
    }

    fclose(storage_file_stream);
    return new_queue;
}

void store_history(){
    DLLNode cur_node = history_queue->start_node->next_node;

    FILE* storage_file_stream = fopen(history_storage_file, "w");
    if (storage_file_stream == NULL){
        perror("Couldn't open history storage file");
        return;
    }

    fprintf(storage_file_stream, "%ld\n", history_queue->size);

    // storing all nodes in file
    while(cur_node != NULL){
        fprintf(storage_file_stream, "%s\n", cur_node->element->process_name);
        cur_node = cur_node->next_node;
    }

    fclose(storage_file_stream);
}