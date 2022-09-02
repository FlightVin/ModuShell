#ifndef _HISTORY_H_
#define _HISTORY_H_

void add_to_history(char*, int); // adds a stribg to the history queue

void history(int); // displays the history 

struct dll* init_history(); // initializes history queue with history from last run (if any)

void store_history(); // stores history queue contents into a hidden file

#endif