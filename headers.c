#include "headers.h"

size_t max_str_len = 1e3;
size_t command_len = 1e3;
size_t max_arg_length = 1e3;
int pwd_flag = 0;

char root_dir_path[1000] = "\0";
char user_name[1000] = "\0";
char old_pwd[1000] = "\0";
char cur_dir[1000] = "\0";

long process_exec_time = 0;

size_t background_process_num = 0;