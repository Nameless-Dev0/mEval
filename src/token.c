#include <stdlib.h> // malloc, free
#include <assert.h> // assert
#include <stdarg.h> // varidiac function
#include <stdio.h>  // sprintf
#include "token.h"

token_t* create_token(token_type_t type, const char* lexeme, ...){
    token_t* new_token = malloc(sizeof(token_t));
    if(!new_token) 
        return NULL;

    new_token->type = type;
    snprintf(new_token->lexeme, MAX_LEXEME_LENGTH, "%s", lexeme);

    va_list args;
    va_start(args, lexeme);
    if(type == NUMBER)
        new_token -> value = va_arg(args, double);
    va_end(args);

    return new_token;
}

void free_token(token_t** token){
    assert(token);
    free(*token);
    *token = NULL;
}