#include "headers.h"

const size_t command_len = 1e3;
const size_t max_arg_length = 1e3;

int main(){
    char* root_dir_path = getenv("PWD");

    char* input_message;
    char cur_command[command_len];
    char command_name[command_len];

    char* command_list[max_arg_length];
    char* argument_list[max_arg_length];

    while(1){
        prompt(root_dir_path);

        size_t input_len = 1e3;
        getline(&input_message, &input_len, stdin);

        command_list[0] = strtok(input_message, ";\n");
        int num_commands = 0;

        while(command_list[num_commands]){
            command_list[++num_commands] = strtok(NULL, ";\n");
        }

        for (int cmd_index = 0; cmd_index < num_commands; cmd_index++){
            strcpy(cur_command, command_list[cmd_index]);

            // puts(cur_command);

            argument_list[0] = strtok(cur_command, " \n\t");
            int num_arguments = 0;

            while(argument_list[num_arguments]){
                argument_list[++num_arguments] = strtok(NULL, " \n\t");
            }


            char* main_command = strdup(argument_list[0]);

            if (strcmp(main_command, "echo") == 0){
                
            }
        }

        fflush(stdout);
    }
    
    exit(EXIT_SUCCESS);
}