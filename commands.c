#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int pwd2() {
    char path[1024];
    if(getcwd(path, sizeof(path)) != NULL){
        printf("Current Path: %s\n", path);
    }else {
        printf("Error");
        return 1;
    }

    return 0;

}

int echo2(char **args) {
    int i = 1;

    while(args[i] != NULL){
        printf("%s", args);
        i++;
        if (args[i] != NULL) {
            printf(" "); 
        }
    }
    printf("\n");
    return 0;
}

int cd2 (char **args) {
    if(args[1] == NULL){
        chdir(getenv("HOME"));
    }
    else{
        if(args[1] != NULL){
            chdir(getenv(args[1]));
        }
        if (chdir(args[1]) != 0) {
            printf("error");
        }
    }
}

int cat2 (char **args) {
    if(args[1] != NULL){
        FILE *file;
        char line[100];
        if(file = fopen(args[1], "r")){
            while (fgets(line, sizeof(line), file) != NULL){
                printf("%s", line);
            }
            fclose(file);
        }else{
            printf("error");
        }
    }
    return 0;
}
