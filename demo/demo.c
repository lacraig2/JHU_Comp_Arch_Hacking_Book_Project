#include <stdio.h>
#include <string.h>

void handle_argument(char *argument){
    char buf_internal[10];
    strcpy(buf_internal, argument);
}

int main(int argc, char* argv[]){
    if (argc > 1){
        handle_argument(argv[1]);
        printf("Hi %s! Nice to meet you!\n", argv[1]);
    }else{
        printf("Your first argument should be your name!\n");
        printf("For example: ./program Jim\n");
    }
}