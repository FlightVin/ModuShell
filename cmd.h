#ifndef _CMD_H_
#define _CMD_H_

void my_strtok(char**, int*, char*, char*); //tokenizes the char** list

int detect_amp(char*); // Detects & symbol

void my_quit(); // exits terminal and saves relevant states

void run_command(char*); // runs the command in the foreground

void my_cwd(); // Parses current working directory into cur_dir

char* get_month(int); // returns month name

char* parse_to_string(char**, int); // converts array of strings into a single space separated string (redundant now)

#endif