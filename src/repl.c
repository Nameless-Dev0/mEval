#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>

#include "repl.h"
#include "lexer.h"
#include "limits.h"

static inline void show_indicator(void){
    printf(">> ");
    fflush(stdout);
}

static inline void show_start(void){
    printf("Welcome to mEval, (Ctrl+D to exit):\n");
}

void repl_loop(){
    char* line = NULL;
    size_t line_buffer_length = 0;
    ssize_t read_size = 0;
    
    show_start();
    show_indicator();

    while(1){
        read_size = getline(&line, &line_buffer_length, stdin);
        if(read_size == -1)
            break;
        if(read_size > MAX_LINE_LENGTH)
            break;
        if(read_size > 0 && line[read_size - 1] == '\n')
            line[read_size - 1] = '\0';
        
        // Call the lexer
        // Call the parser
        // Call the evaluator

        printf("Result: %s\n", line);
        show_indicator();
    }

    free(line);
}