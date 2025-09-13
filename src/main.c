#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

// main just executes a simple REPL.

int main(void){
    
    char* line = NULL;
    size_t line_buffer_length = 0;
    ssize_t read_size = 0;

    printf("Welcome to mEval, (Ctrl+D to exit):\n");
    printf(">> ");
    fflush(stdout);

    while(1){
        read_size = getline(&line, &line_buffer_length, stdin);
        if(read_size == -1)
            break;

        if(read_size > 0 && line[read_size - 1] == '\n')
            line[read_size - 1] = '\0';
            
        printf("Result: %s\n", line);
        printf(">> ");
        fflush(stdout);
    }

    free(line);
    return 0;
} 

