#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>


#include "cmd.h"
#include "paths.h"
#include "prompt.h"
#include "error_mes.h"
#include "echo.h"
#include "cd.h"
#include "pwd.h"
#include "back_process.h"
#include "ls.h"
#include "fore_process.h"
#include "pinfo.h"
#include "dll.h"
#include "history.h"
#include "discover.h"

// using extern for convention
// Generic variables
extern size_t max_str_len;
extern size_t command_len;
extern size_t max_arg_length;
extern int pwd_flag;

extern char root_dir_path[1000];
extern char* user_name;
extern char old_pwd[1000];
extern char cur_dir[1000];

// For foregorund processes
extern long process_exec_time;

// For background process handling
struct dll* running_background_processes;

// for history
struct dll* history_queue;
extern int default_history_storage_size;
extern int default_history_display_num;
extern char history_storage_file_name[1000];
extern char history_storage_file[2000];
