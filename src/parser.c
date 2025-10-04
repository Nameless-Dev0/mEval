#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static ast_node_t* parse_expr(parser_t* parser);
static ast_node_t* parse_expr_prime(parser_t* parser, ast_node_t* left);
static ast_node_t* parse_term(parser_t* parser);
static ast_node_t* parse_term_prime(parser_t* parser, ast_node_t* left);
static ast_node_t* parse_unary(parser_t* parser);
static ast_node_t* parse_pow(parser_t* parser);
static ast_node_t* parse_pow_prime(parser_t* parser, ast_node_t* left);
static ast_node_t* parse_factor(parser_t* parser);

void parser_init(parser_t* parser, lexer_t* lexer){
    parser->lexer = lexer;
    parser->current_token = lex_peek(lexer);
}

void generate_parser_AST(parser_t* parser){
    parser->tree = parse_expr(parser);
}

void parser_reset(parser_t* parser){
    if(!parser){
        fprintf(stderr, "(parser) fatal error: null parser or tree... exiting\n");
        exit(EXIT_FAILURE);
    }

    if(parser->tree){
        destroy_node(parser->tree);
        parser->tree = NULL;
    }

    parser->lexer = NULL;
    parser->current_token = NULL;
}

// current_token is NULL if at end of token stream
static void next(parser_t* parser){
    parser->current_token = lex_next(parser->lexer);
}

static ast_node_t* parse_expr(parser_t* parser){
    ast_node_t* term = NULL;
    term = parse_term(parser);
    if(!term)
        return NULL;
    return parse_expr_prime(parser, term);
}

static ast_node_t* parse_expr_prime(parser_t* parser, ast_node_t* left){
    ast_node_t* term = NULL;
    ast_node_t* next_left_term = NULL;
    token_type_t type = parser->current_token->type;

    if(!(type == PLUS || type == MINUS))
        return left;

    next(parser);
    term = parse_term(parser);
    if(!term){
        destroy_node(left);
        return NULL;
    }

    if(type == PLUS)
        next_left_term = create_plus_node(left,term);
    if(type == MINUS)
        next_left_term = create_minus_node(left,term);

    return parse_expr_prime(parser, next_left_term);
}

static ast_node_t* parse_term(parser_t* parser){
    ast_node_t* unary = NULL;
    unary = parse_unary(parser);
    if(!unary)
        return NULL;
    return parse_term_prime(parser, unary);
}

static ast_node_t* parse_term_prime(parser_t* parser, ast_node_t* left){
    ast_node_t* unary = NULL;
    ast_node_t* next_left_unary = NULL;
    token_type_t type = parser->current_token->type;

    if(!(type == MULTIPLY || type == DIVIDE))
        return left;

    next(parser);
    unary = parse_unary(parser);
    if(!unary){
        destroy_node(left);
        return NULL;
    }

    if(type == MULTIPLY)
        next_left_unary = create_multiply_node(left,unary);
    if(type == DIVIDE)
        next_left_unary = create_divide_node(left,unary);

    return parse_term_prime(parser, next_left_unary);
}

/*
    Exponentation is right associative, so when adding a new sub-tree we add it to the right.
    The resulting parse tree is a right-leaning tree.
*/

static ast_node_t* parse_pow(parser_t* parser){
    ast_node_t* left_factor = NULL;
    left_factor = parse_factor(parser);
    if(!left_factor)
        return NULL;
    return parse_pow_prime(parser, left_factor);
}
/*
    left here refers to the operand's position in the expression,
    which is also its position in the parse tree.
*/
static ast_node_t* parse_pow_prime(parser_t* parser, ast_node_t* left_factor){
    ast_node_t* right_factor = NULL;

    if(parser->current_token->type != POWER)
        return left_factor;

    next(parser);
    right_factor = parse_pow(parser);
    if(!right_factor){
        destroy_node(left_factor);
        return NULL;
    }

    return create_power_node(left_factor, right_factor);
}

static ast_node_t* parse_unary(parser_t* parser){
    ast_node_t* pow = NULL;
    ast_node_t* result = NULL;
    token_type_t type = parser -> current_token -> type;
    if(!(type == PLUS || type == MINUS))
        return parse_pow(parser);;
    
    next(parser);
    pow = parse_pow(parser);
    if(!pow)
        return NULL;

    if(type == PLUS)
        result = create_positive_node(pow);
    if(type == MINUS)
        result = create_negative_node(pow);
    return result;
}

static ast_node_t* parse_factor(parser_t* parser){
    ast_node_t* result = NULL;
    token_type_t type = parser -> current_token -> type;
    
    if(type == UNKNOWN){
        fprintf(stderr, "unknown token: '%s'\n", parser->current_token->lexeme);
        return NULL;
    }

    if(type == SIN ||type == COS  ||type == TAN){
        next(parser);
        if(parser->current_token->type != LPAREN){
            fprintf(stderr, "syntax error: expected: '('\n");
            return NULL;
        }
        next(parser);

        result = parse_expr(parser);

        if((parser->current_token -> type != RPAREN)){
            fprintf(stderr, "syntax error: expected: ')'\n");
            destroy_node(result);
            return NULL;
        }

        next(parser);
        result = create_function_node(type, result);
        return result;
    }

    if(parser->current_token->type == LPAREN){
        next(parser);
        result = parse_expr(parser);

        if((parser->current_token -> type != RPAREN)){
            fprintf(stderr, "syntax error: expected: ')'\n");
            destroy_node(result);
            return NULL;
        }

        next(parser);
        return result;
    }

    if(parser->current_token->type != NUMBER){
        fprintf(stderr, "syntax error: expected: number\n");
        return NULL;
    }

    result = create_number_node(parser->current_token);
    next(parser);
    return result;
}
