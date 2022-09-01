#ifndef _CMD_H_
#define _CMD_H_

void my_strtok(char**, int*, char*, char*); //tokenizes the char** list

int detect_amp(char*); // Detects & symbol

void my_quit();

void run_command(char*);

void my_cwd();

char* get_month(int);

char* parse_to_string(char**, int);

#endif