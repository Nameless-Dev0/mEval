#include "ast.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

// TODO: convert token shallow copies to deep copies.

static void destroy_node(ast_node_t* node);
static ast_node_t* create_node(void);
static ast_node_t* init_binary_node(ast_node_t* left, ast_node_t* right);
static ast_node_t* init_unary_node(ast_node_t* right);

static void destroy_node(ast_node_t* node){
    if(!node)
        return;
    destroy_node(node->left);
    destroy_node(node->right);
    free(node);
}

static ast_node_t* create_node(void){
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if(!node){
        fprintf(stderr, "fatal: node creation failed... exiting");
        exit(EXIT_FAILURE);
    }
    return node;
}

static ast_node_t* init_binary_node(ast_node_t* left, ast_node_t* right){
    ast_node_t* node = create_node();
    node -> left = left;
    node -> right = right;
    return node;
}

static ast_node_t* init_unary_node(ast_node_t* right){
    ast_node_t* node = create_node();
    node -> left = NULL;
    node -> right = right;
    return node;
}

void create_AST(ast_t* tree){
    tree -> root = create_node();
    tree -> root -> left = NULL;
    tree -> root -> right = NULL;
}

void destroy_AST(ast_t* tree){
    if(!tree)
        return;
    destroy_node(tree->root);
    tree->root = NULL;
}

ast_node_t* create_number_node(const token_t* tok){
    if(!tok){
        fprintf(stderr, "fatal: null token error... exiting");
        exit(EXIT_FAILURE);
    };

    ast_node_t* node;
    node = create_node();
    node -> left = NULL;
    node -> right = NULL;
    node -> token.type = (tok->type);
    node -> token.value = (tok->value);
    strlcpy((node -> token.lexeme), tok->lexeme, sizeof(tok->lexeme));
    return node;
}

ast_node_t* create_negative_node(ast_node_t* child){
    token_t token = {"UNARY MINUS", MINUS, 0};
    ast_node_t* node = init_unary_node(child);
    node->token = token;
    return node;
}

ast_node_t* create_positive_node(ast_node_t* child){
    token_t token = {"UNARY PLUS", PLUS, 0};
    ast_node_t* node = init_unary_node(child);
    node->token = token;
    return node;
}

ast_node_t* create_plus_node(ast_node_t* left, ast_node_t* right){
    token_t token = {"PLUS", PLUS, 0};
    ast_node_t* node = init_binary_node(left, right);
    node->token = token;
    return node;
}

ast_node_t* create_minus_node(ast_node_t* left, ast_node_t* right){
    token_t token = {"MINUS", MINUS, 0};
    ast_node_t* node = init_binary_node(left, right);
    node->token = token;
    return node;
}

ast_node_t* create_multiply_node(ast_node_t* left, ast_node_t* right){
    token_t token = {"MULTIPLY", MULTIPLY, 0};
    ast_node_t* node = init_binary_node(left, right);
    node->token = token;
    return node;
}

ast_node_t* create_divide_node(ast_node_t* left, ast_node_t* right){
    token_t token = {"DIVIDE", DIVIDE, 0};
    ast_node_t* node = init_binary_node(left, right);
    node->token = token;
    return node;
}

ast_node_t* create_power_node(ast_node_t* left, ast_node_t* right){
    token_t token = {"POWER", POWER, 0};
    ast_node_t* node = init_binary_node(left, right);
    node->token = token;
    return node;
}

ast_node_t* create_function_node(token_type_t func_type, ast_node_t* child){
    token_t token = {"MATH FUNCTION", func_type, 0};
    ast_node_t* node = create_node();
    node->left = NULL;
    node->right = child;
    node->token = token;
    return node;
}

