#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commands.h"
#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];
    pid_t pid;
    const char *delimiter = " ";
    char *token;
    char *args[10];
    int x = 0;

    while(1) {
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
            break;
        }
        if (strcmp(args[0], "pwd2") == 0){
            pwd2();
        }

    }
    return 0;
}