#ifndef AST_H
#define AST_H

#include "token.h"

/*
    The AST is implemented as binary tree.
    
    Nodes don't reference tokens they make deep copies, since the having the
    nodes of a heap allocated tree point to a heap allocated token stream
    would be a nightmare to debug.

    The copying isn't really an issue for now, since the token struct is small (with a maximum size of 144 bytes) and the tokens themselves
    only keep accumalating until the expression is parsed then they are freed before parsing the next expression.
*/

typedef struct ast_node{
    struct ast_node* left;
    struct ast_node* right;
    token_t token;
} ast_node_t;

ast_node_t* create_node(void);
void destroy_node(ast_node_t* root);
void show_parser_tree(const ast_node_t* root);

ast_node_t* create_number_node(const token_t* token);
ast_node_t* create_negative_node(ast_node_t* child);
ast_node_t* create_positive_node(ast_node_t* child);

ast_node_t* create_plus_node(ast_node_t* left, ast_node_t* right);
ast_node_t* create_minus_node(ast_node_t* left, ast_node_t* right);

ast_node_t* create_multiply_node(ast_node_t* left, ast_node_t* right);
ast_node_t* create_divide_node(ast_node_t* left, ast_node_t* right);
ast_node_t* create_power_node(ast_node_t* left, ast_node_t* right);

ast_node_t* create_function_node(token_type_t func_type, ast_node_t* child);


#endif // AST_H