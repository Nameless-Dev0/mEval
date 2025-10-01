#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>

#include "repl.h"
#include "lexer.h"
#include "lex_limits.h"
#include "ast.h"
#include "parser.h"
#include "eval.h"

static void show_start(void){
    printf("Welcome to mEval, (Ctrl+D to exit):\n");
}

static void show_indicator(void){
    printf(">> ");
    fflush(stdout);
}

void repl_loop(void){
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
        
        lexer_t lexer;
        parser_t parser;
        double result;

        lexer_init(&lexer, line);
        lex_expression(&lexer);

        parser_init(&parser, &lexer);
        generate_parser_AST(&parser);

        //show_parser_tree(parse_tree.root);
        result = evaluate_AST(parser.tree);
        printf("%lf\n", result);
        
        parser_reset(&parser);
        lexer_reset(&lexer);

        show_indicator();
    }

    free(line);
}