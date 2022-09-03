#ifndef _PATH_H_
#define _PATH_H_

void relative_path(char*, char*); // gives relative path wrt to shell's directory

void absolute_path(char*, char*); // gives absolute path from actual root given a path relative to the shell's directory

void relative_path_to_cwd(char*, char*); // gives relative path wrt to current directory

#endif