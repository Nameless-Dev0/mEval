#include "benchmark.h"
#include "lexer.h"
#include "parser.h"
#include "eval.h"
#include <stddef.h>
#include <stdio.h>

const char* expressions[] = {
    "1+2",
    "(3*4)",
    "cos(0)",
    "sin(90)",
    "5-3",
    "2^3",
    "tan(45)",
    "1+2*3",
    "(4/2)-1",
    "3.14+2.71",
    "(1+(2*3))",
    "42",
    "  1 + 2  ",
    "1$2",
    "(1+2",
    "",
    "sin(30)+cos(60)",
    "tan(45)*2",
    "(2+3)^2",
    "((1+2)*3)/4"
};

int main(void){

    size_t expressions_count = sizeof(expressions)/sizeof(expressions[0]);

    lexer_t lexer;
    parser_t parser;
    double result;

    for(int j = 0; j < 1; j++){
        for(size_t i = 0; i < expressions_count; i++){

            lexer_init(&lexer, expressions[i]);
            lex_expression(&lexer);

            parser_init(&parser, &lexer);
            generate_parser_AST(&parser);
            result = evaluate_AST(parser.tree);

            parser_reset(&parser);
            lexer_reset(&lexer);
            
        }
    }

    return 0;
}