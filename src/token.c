#include <stdlib.h> // malloc, free
#include <assert.h> // assert
#include <stdarg.h> // varidiac function
#include <stdio.h>  // snprintf
#include "token.h"

token_t* create_token(token_type_t type, const char* lexeme, ...){
    token_t* new_token = malloc(sizeof(token_t));
    if(!new_token) 
        return NULL;

    new_token->type = type;
    snprintf(new_token->lexeme, MAX_LEXEME_LENGTH, "%s", lexeme);

    new_token->value = 0;
    
    va_list args;
    va_start(args, lexeme);
    if(type == NUMBER)
        new_token -> value = va_arg(args, double);
    va_end(args);

    return new_token;
}

void free_token(token_t* token){ // dont forget to call
    assert(token);
    free(token);
}

static inline const char* token_type_to_string(token_type_t type){
    switch (type) {
        case NUMBER: return "NUMBER";
        case PLUS:   return "PLUS";
        case MINUS:  return "MINUS";
        case MULTIPLY:  return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case POWER:  return "POWER";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case SIN:    return "SIN";
        case COS:    return "COS";
        case TAN:    return "TAN";
        case UNKNOWN:return "UNKNOWN";
        case END:    return "END";
        default:     return "CONVERSION FAILED";
    }
}

void print_token(const token_t* token){
    if(!token)
        return;
        
    printf(
        "TOKEN: { %s | %s | %lf }\n",
        token->lexeme,
        token_type_to_string(token->type),
        token->value
    );
}

