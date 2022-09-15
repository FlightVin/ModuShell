#ifndef _CMD_H_
#define _CMD_H_

void my_strtok(char**, int*, char*, char*); //tokenizes the char** list

void my_quit(); // exits terminal and saves relevant states

void execute_command(char*); // to parse pipes

void run_command(char*); // runs the command in the foreground

void my_cwd(); // Parses current working directory into cur_dir

char* parse_to_string(char**, int); // converts array of strings into a single space separated string (redundant now)

void ctrl_d_handler(); // handling ^D

void ctrl_c_handler(); // handling ^C

void ctrl_z_handler(); // handling ^Z

#endif