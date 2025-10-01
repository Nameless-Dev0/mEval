#include "ast.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

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

static void print_node_token(const token_t* token){
    if(token->type == NUMBER){
        printf("%lf", token->value);
        return;
    }

    switch (token->type) {
        case PLUS:
            printf(" + ");
            return;
        case MINUS:
            printf(" - ");
            return;
        case MULTIPLY:
            printf(" * ");
            return;
        case DIVIDE:
            printf(" / ");
            return;
        case POWER:
            printf(" ^ ");
            return;
        case SIN:
            printf(" sin ");
            return;
        case COS:
            printf(" cos ");
            return;
        case TAN:
            printf(" tan ");
            return;
        default:
            printf("CONVERSION FAILED");
            return;
    }
}

void show_parser_tree(const ast_node_t* root){ // left, root, right
    if(!root)
        return;
    show_parser_tree(root->left);
    print_node_token(&(root->token)); // the token struct member stores the actual token not a pointer
    show_parser_tree(root->right);
}

ast_node_t* create_node(void){
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if(!node){
        fprintf(stderr, "(ast) fatal error: node creation failed... exiting");
        exit(EXIT_FAILURE);
    }
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

void destroy_node(ast_node_t* root){
    if(!root)
        return;
    destroy_node(root->left);
    destroy_node(root->right);
    free(root);
}


ast_node_t* create_number_node(const token_t* tok){
    if(!tok){
        fprintf(stderr, "(ast) fatal error: null token error... exiting");
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

