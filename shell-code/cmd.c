#include "headers.h"

void my_strtok(char** list, int* num, char* args, char* in_data){
    list[0] = strtok(in_data, args);
    *num = 0;

    while(list[*num]){
        list[++(*num)] = strtok(NULL, args);
    }
}