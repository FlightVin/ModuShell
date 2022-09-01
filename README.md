# C-Shell
Making a shell in C programming language

> Made by Vineeth Bhat (2021101103)

***

## Running shell

1. Run the makefile via `$ make`
2. Start executing shell as `$ ./main`
3. Enter commands separted by ; or & just as you would in a unix terminal
    * `$ command1 arguments & command2 arguments`
    * `$ command1 arguments; command2     arguments   ; command3  arguments ...`
    * And so on
4. To remove all .o and main file run `$ make clean`

NOTE - currently, handles & as ;

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
    * _Output_ : Changes current directory to 
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


https://man7.org/linux/man-pages/man5/proc.5.html (Stumbled across it while exploring /proc)