#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct parser{
    lexer_t* lexer;
    token_t* current_token;
    ast_t* tree;
} parser_t;

void init_parser(parser_t* parser, lexer_t* lexer);
void generate_parser_AST(ast_t* tree, parser_t* parser);


#endif // PARSER_H
