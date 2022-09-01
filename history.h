#ifndef _HISTORY_H_
#define _HISTORY_H_

void add_to_history(char*, int);

void history(int);

struct dll* init_history();

void store_history();

#endif