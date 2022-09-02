#ifndef _LS_H_
#define _LS_H_

void ls(char**, int); // interprets flags and other arguments and calls do_ls

void do_ls(char*, int, int); // does ls

void color_print(struct dirent*, char*); // prints according to file type

#endif