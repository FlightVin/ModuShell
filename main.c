#include "headers.h"
#include "dll.h"

int main(){
    running_background_processes = make_dll();
    history_queue = init_history();

    char* input_message;
    char cur_command[max_str_len];
    char* command_list[max_arg_length];
    char* background_list[max_arg_length];

    getcwd(root_dir_path, max_str_len);

    // redirecting stderr
    freopen(".shell_stderr", "w", stderr);
    fprintf(stderr, "\n\n ---------- start of shell execution at system time ---------- %ld\n\n", time(NULL));

    while(1){
        prompt();
        fflush(stdout);

        size_t input_len = max_str_len;
        getline(&input_message, &input_len, stdin);

        size_t no_space = strlen(input_message) - 1;
        for (no_space = strlen(input_message) - 1; no_space>0; no_space--){
            if (input_message[no_space - 1] != ' ' && input_message[no_space -1] != '\t') break;
        }

        // Handling seg fault for trailing spaces
        input_message[no_space] = '\0';

        if (strlen(input_message) != 0) add_to_history(input_message, default_history_storage_size);

        // starting timer
        time_t process_begin_clock = time(NULL);

        // legacy code which supports things but gives ; more priority than &
        /*
        int num_commands;
        my_strtok(command_list, &num_commands, ";\n", input_message);

        for (int cmd_index = 0; cmd_index < num_commands; cmd_index++){
            strcpy(cur_command, command_list[cmd_index]);
            
            if (detect_amp(command_list[cmd_index])){
                int flag = (cur_command[strlen(cur_command) - 1] == '&') ? 1 : 0;
                int num_background;
                
                my_strtok(background_list, &num_background, "&", cur_command);

                for (int i = 0; i<num_background-1; i++){
                    run_cmd_background(background_list[i]);
                }

                if (flag){
                    run_cmd_background(background_list[num_background - 1]);
                }else{
                    run_command(background_list[num_background - 1]);
                }
            }else{
                run_command(cur_command);
            }
        }
        */

        char command_buffer[max_str_len];
        int command_length = 0;
        strcpy(command_buffer, "");

        for (int i = 0; i<=no_space; i++){
            if (input_message[i] != ';' && input_message[i] != '&'){
                command_buffer[command_length++] = input_message[i];
            } else {
                command_buffer[command_length++] = '\0';

                if (input_message[i] == ';'){
                    run_command(command_buffer);
                } else {
                    run_back_background(command_buffer);
                }

                strcpy(command_buffer, "");
                command_length = 0;
            }
        }

        if (strlen(command_buffer) != 0){
            run_command(command_buffer);
        }

        fflush(stdout);

        // Ending process
        time_t process_end_clock = time(NULL);
        process_exec_time = process_end_clock - process_begin_clock;

        signal(SIGCHLD, background_process_term);
        fflush(stdout);
    }
    
    exit(EXIT_SUCCESS);
}