#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct parser{
    lexer_t* lexer;
    token_t* current_token;
    ast_node_t* tree;
} parser_t;

void parser_init(parser_t* parser, lexer_t* lexer);
void generate_parser_AST(parser_t* parser);
void parser_reset(parser_t* parser);

#endif // PARSER_H
