#include "headers.h"
#include "dll.h"

int main(){
    getcwd(root_dir_path, max_str_len); 
    running_background_processes = make_dll();
    history_queue = init_history();
    shell_pid = getpid();

    char* input_message;
    char cur_command[max_str_len];
    char* command_list[max_arg_length];
    char* background_list[max_arg_length];

    // redirecting stderr
    // freopen(".shell_stderr", "w", stderr);
    // fprintf(stderr, "\n\n ---------- start of shell execution at system time ---------- %ld\n\n", time(NULL));

    // signal
    signal(SIGCHLD, background_process_term);
    signal(SIGINT, ctrl_c_handler);
    signal(SIGTSTP, ctrl_z_handler);

    while(1){
        prompt();
        fflush(stdout);

        size_t input_len = max_str_len;
        int getline_ret = getline(&input_message, &input_len, stdin);

        // handling ^D
        if (getline_ret == EOF){
            ctrl_d_handler();
        }

        size_t no_space = strlen(input_message) - 1;
        for (no_space = strlen(input_message) - 1; no_space>0; no_space--){
            if (input_message[no_space - 1] != ' ' && input_message[no_space -1] != '\t') break;
        }

        // Handling seg fault for trailing spaces
        input_message[no_space] = '\0';

        if (strlen(input_message) != 0) add_to_history(input_message, default_history_storage_size);

        char command_buffer[max_str_len];
        int command_length = 0;
        strcpy(command_buffer, "");

        // getting individual commands and cheking whether background of foreground
        for (int i = 0; i<=no_space; i++){
            if (input_message[i] != ';' && input_message[i] != '&'){
                command_buffer[command_length++] = input_message[i];
            } else {
                command_buffer[command_length++] = '\0';

                if (input_message[i] == ';'){
                    execute_command(command_buffer);
                } else {
                    run_back_background(command_buffer);
                }

                strcpy(command_buffer, "");
                command_length = 0;
            }
        }

        if (strlen(command_buffer) != 0){
            execute_command(command_buffer);
        }

        fflush(stdout);
    }
    
    exit(EXIT_SUCCESS);
}