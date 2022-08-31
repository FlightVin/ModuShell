#ifndef _BACK_H_
#define _BACK_H_

void run_cmd_background(char*);

void run_in_background(char**);

struct back_process{
    pid_t process_pid;
    char* process_name;   
};

typedef struct back_process BackProcess;

#endif