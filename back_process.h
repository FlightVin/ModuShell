#ifndef _BACK_H_
#define _BACK_H_

void run_cmd_background(char*);

void run_in_background(char**);

void background_process_term();

void remove_from_queue(int);

struct back_process{
    pid_t process_pid;
    char* process_name;   
};

typedef struct back_process BackProcess;
typedef struct back_process* ProcessPtr;

#endif