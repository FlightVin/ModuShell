#ifndef _BACK_H_
#define _BACK_H_

void run_cmd_background(char*); // tokenizes arguments and presents to run_in_background

void run_in_background(char**); // runs given process in background

void background_process_term(); // run when a child is detected to have terminated

void remove_from_queue(int); // removed a child process from the background exxecution queue

struct back_process{
    pid_t process_pid;
    char* process_name;   
};

typedef struct back_process BackProcess;
typedef struct back_process* ProcessPtr;

#endif