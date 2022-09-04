# C-Shell
Making a shell in C programming language

> Made by Vineeth Bhat (2021101103)

> To see timeline of progress : https://github.com/FlightVin/C-Shell (NOTE - private directory, so, please email vineeth.bhat@students.iiit.ac.in for accessing rights)

***

## Running shell

1. Run the makefile via `$ make`
2. Start executing shell as `$ ./main`
3. Enter commands separted by ; or & just as you would in a unix terminal
    * `$ command1 arguments & command2 arguments`
    * `$ command1 arguments; command2     arguments   ; command3  arguments ...`
    * A command ending with a ; will be executed in the foreground while a command ending in & will executed in background. If no such character is present at the end, then the command is run in foreground.
4. To remove all .o and main file run `$ make clean`

---

## Commands

1. **`echo`**
    * _Output_ : Prints the entered arguments by excluding extra spaces and tabspaces.
    * _Syntax_ : 
    
        `$ echo <arguments>`

    * _Example_ : 

        `$ echo hello     there!`

        `>>> hello     there!`
    
2. **`cd`**
    * _Output_ : Changes current directory to given directory
    * _Syntax_ :

        `$ cd` : changes to home directory

        `$ cd ~` : changes to home directory

        `$ cd file_path` : changes to path based on characters such as `.` (current directory) and `..` (parent directory)

        `$ cd -`

    * _Example_ : 

        `$ cd ~`
    
3. **`pwd`**
    * _Output_ : Prints the present working directory
    * _Syntax_ : 
    
        `$ pwd`

    * _Example_ : 

        `$ pwd` prints /HOME/username/... if the present working directory is a descendant of the directory from which the shell was executed

        `$ pwd` prints /home/username/... otherwise

4. **`exit`**
    * _Output_ : Quits shell
    * _Syntax_ :

        `$ exit`

5. **`ls`**
    * _Output_ : 

        * Paths - 
        
            * If no path is given, lists files and directories in current directory.

            * If path of a directory is given, lists files and directories in given directory.

            * If path of a file is given, lists information about the file

            * If the path is invalid, throws an error

        * Flags - 

            * -l lists all relevant information about path

            * -a lists all the hidden files and folders too

    * _Syntax_ :

        `$ ls -<flags> <dir_name>` : changes to home directory

6. **`pinfo`**
    * _Output_ : Prints the relevant information about the given pid (taken as shell's pid if no pid is provided):

        * process id

        * process status (R for running, S for sleeping, Z for zombie; Append '+' if process is run in foreground)

        * memory usage

        * executable path

    * _Syntax_ : 
    
        `$ pinfo <pid>`

7. **`history`**
    * _Output_ : Displays upto 10 previously executed commands in terminal. Included commands from previous runs of the shell as well.
    * _Syntax_ :

        `$ history`

8. **`discover`**
    * _Output_ : 

        * Paths - 
        
            * If no directory path is given, uses current directory

            * If no search path is given, lists files and directories in given directory based on flags

            * If the path is invalid, throws an error

        * Flags - 

            * -f lists/searches only files

            * -d lists/searches only directories

    * _Syntax_ :

        `$ discover -<flags> <dir_name>` : changes to home directory

9. Any other process is run as in linux terminal using `execvp`