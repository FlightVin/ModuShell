#include <stdio.h>
#include <sys/utsname.h> // Fr=or uname
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

// using extern for convention
extern size_t max_str_len;
extern size_t command_len;
extern size_t max_arg_length;
extern int pwd_flag;

extern char root_dir_path[1000];
extern char user_name[1000];
extern char old_pwd[1000];
extern char cur_dir[1000];

extern long process_exec_time;

