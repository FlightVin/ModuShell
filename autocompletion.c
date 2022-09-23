#include "headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void get_input(){
    char cur_char;

    setbuf(stdout, NULL);
    enableRawMode();
    memset(input_message, '\0', max_str_len);
    int pt = 0;

    while (read(STDIN_FILENO, &cur_char, 1) == 1) {
        if (iscntrl(cur_char)){

            // ^D handling
            if (cur_char == 4){ // EOT
                printf("\n");
                ctrl_d_handler();
            } else if (cur_char == 10){ // linefeed -> \n
                input_message[pt++] = cur_char;
                printf("\n");
                break;
            } else if (cur_char == 127){ // backspace
                if (pt > 0){
                    input_message[--pt] ='\0';
                    printf("\b \b");
                }
            } else if (cur_char == 9) { // tab character
                
            } else {
                printf("%d\n", cur_char);
            }

        } else {

            input_message[pt++] = cur_char;
            printf("%c", cur_char);

        }
    }

    disableRawMode();
}