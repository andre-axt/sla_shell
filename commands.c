#include <stdio.h>
#include <unistd.h>

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