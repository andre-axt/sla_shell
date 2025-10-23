#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

int pwd2() {
    char path[1024];
    if(getcwd(path, sizeof(path)) != NULL){
        printf("Current Path: %s\n", path);
    }else {
        printf("error\n");
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
            printf("error\n");
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
            printf("error\n");
        }
    }
    return 0;
}

int rm2 (char **args) {
    if(args[1] != NULL){
        if(remove(args[1]) == 0){
            printf("removed\n");
        }
        else{
            printf("error\n");
        }
    }else{
        printf("missing file argument\n");
    }
    return 0;
}

int ls2 (char **args) {
    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL){
        if(entry->d_name[0] != '.'){
            if(entry->d_type == DT_DIR){
                printf(BLUE "%s  " COLOR_RESET, entry->d_name);
            }else{
                printf(GREEN "%s  " COLOR_RESET, entry->d_name);
            }

        }

    }
    printf("\n");
    closedir(dir);
    return 0;
}