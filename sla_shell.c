#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commands.h"
#define MAX_INPUT_SIZE 1024

struct builtin_command {
    char *name;
    void (*func)(char **);
};

struct builtin_command commands[] = {
    {"pwd2", pwd2},
    {"echo2", echo2},
    {"cd2", cd2},
    {"cat2", cat2},
    {"rm2", rm2},
    {"ls2", ls2},
    {NULL, NULL} 
};

int main() {
    char input[MAX_INPUT_SIZE];
    pid_t pid;
    const char *delimiter = " ";
    char *token;
    char *args[10];
    int x = 0;
    int found = 0;

    while(1) {
        found = 0;
        printf("sla_shell> ");
        fflush(stdout);

        x = 0;

        if(fgets(input, MAX_INPUT_SIZE, stdin)){
            input[strcspn(input, "\n")] = '\0';
            args[x] = strtok(input, delimiter);
            while (args[x] != NULL && x < 9){
                x++;
                args[x] = strtok(NULL, delimiter);
            }
            args[x] = NULL;
            pid = fork();

            if(pid == 0){
                execvp(args[0], args);
            }else if (pid > 0){
                wait(NULL);
            }
        }
        if (strcmp(args[0], "exit") == 0) {
            found = 1;
            break;
        }
        for (int i = 0; commands[i].name != NULL; i++){
            if ( strcmp(args[0], commands[i].name) == 0) {
                found = 1;
                commands[i].func(args);
                break;
            }
        }
        if(!found){
            printf("Command not found\n");
        }

    }
    return 0;
}