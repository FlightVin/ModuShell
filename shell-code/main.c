#include "headers.h"

const size_t command_len = 1e3;
const size_t max_arg_length = 1e3;
size_t input_len = 1e3;


int main(){
    char* root_dir_path = getenv("PWD");

    char* input_message;
    char cur_command[command_len];
    char command_name[command_len];

    char* command_list[max_arg_length];
    char* argument_list[max_arg_length];

    while(1){
        prompt(root_dir_path);

        getline(&input_message, &input_len, stdin);

        int num_commands;
        my_strtok(command_list, &num_commands, ";\n", input_message);

        for (int cmd_index = 0; cmd_index < num_commands; cmd_index++){
            strcpy(cur_command, command_list[cmd_index]);

            int num_arguments;
            my_strtok(argument_list, &num_arguments, " \n\t", cur_command);

            char* main_command = strdup(argument_list[0]);

            if (strcmp(main_command, "echo") == 0){
                echo(&argument_list[1], num_arguments - 1);
            } else if (strcmp(main_command, "cd") == 0){
                cd(&argument_list[1], num_arguments - 1, root_dir_path);
            } else if (strcmp(main_command, "pwd") == 0){
                pwd(&argument_list[1], num_arguments - 1, root_dir_path); //NOTE - HOME is pseudo home, home is actual home
            } else {
                printf("Invalid command: %s\n", main_command);
            }
        
        }

        fflush(stdout);
    }
    
    exit(EXIT_SUCCESS);
}