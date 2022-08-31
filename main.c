#include "headers.h"

int main(){
    char* input_message;
    char cur_command[command_len];
    char command_name[command_len];

    char* command_list[max_arg_length];
    char* background_list[max_arg_length];

    getcwd(root_dir_path, max_str_len);

    while(1){
        prompt(root_dir_path);

        size_t input_len = 1e3;
        getline(&input_message, &input_len, stdin);

        size_t no_space = strlen(input_message) - 1;
        for (no_space = strlen(input_message) - 1; no_space>0; no_space--){
            if (input_message[no_space - 1] != ' ' && input_message[no_space -1] != '\t') break;
        }

        // Handling seg fault for trailing spaces
        input_message[no_space] = '\0';

        int num_commands;
        my_strtok(command_list, &num_commands, ";\n", input_message);

        for (int cmd_index = 0; cmd_index < num_commands; cmd_index++){
            strcpy(cur_command, command_list[cmd_index]);
            
            if (detect_amp(command_list[cmd_index])){
                int flag = (cur_command[strlen(cur_command) - 1] == '&') ? 1 : 0;
                int num_background;
                
                my_strtok(background_list, &num_background, "&", cur_command);

                for (int i = 0; i<num_background-1; i++){
                    puts(background_list[i - 1]);
                    run_cmd_background(background_list[i - 1]);
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

        fflush(stdout);
    }
    
    exit(EXIT_SUCCESS);
}