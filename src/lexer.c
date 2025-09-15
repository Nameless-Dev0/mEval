#include "lexer.h"
#include "token.h"
#include "tok_stream.h"
#include "limits.h"

#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static token_t* tokenize_number(lexer_t* lexer);
static token_t* tokenize_symbol(lexer_t* lexer); 
static token_t* tokenize_math_func(lexer_t* lexer);

static inline char advance(lexer_t* lexer){
    return (lexer->source[lexer->current++]);
}

static inline char peek(lexer_t* lexer){
    return (lexer->source[lexer->current]);
}

static inline char peek_next(lexer_t* lexer){
    return (lexer->source[(lexer->current) + 1]);
}

static bool is_at_end(lexer_t* lexer) {
    return lexer->source[lexer->current] == '\0';
}

static token_t* tokenize_symbol(lexer_t* lexer){
    token_t* token = NULL;
    char symbol = advance(lexer);
    char lexeme[2] = {symbol, '\0'};

    switch (symbol){
      case '(': token = create_token(LPAREN, lexeme); break;
      case ')': token = create_token(RPAREN, lexeme); break;
      case '+': token = create_token(PLUS,   lexeme); break;
      case '-': token = create_token(MINUS,  lexeme); break;
      case '*': token = create_token(TIMES,  lexeme); break;
      case '/': token = create_token(DIVIDE, lexeme); break;
      case '^': token = create_token(POWER,  lexeme); break;
      default: break;
    }
    return token;
}

static token_t* tokenize_math_func(lexer_t* lexer){
    lexer->start = lexer->current;
    token_t* token = NULL;

    char buffer[4] = {0};
    size_t i = 0;

    while(isalpha(peek(lexer)) && i < 3)
        buffer[i++] = advance(lexer);
    buffer[i] = '\0';

    if(!strncmp(buffer, "sin", 3))
        token = create_token(SIN, buffer);
    else if(!strncmp(buffer, "cos", 3))
        token = create_token(COS, buffer);
    else if(!strncmp(buffer, "tan", 3))
        token = create_token(TAN, buffer);

    return token;
}

static token_t* tokenize_number(lexer_t* lexer){
    lexer->start = lexer->current;

    if(peek(lexer) == '.' && isdigit(peek_next(lexer))) // leading dot
        advance(lexer);

    while(isdigit(peek(lexer))){
        advance(lexer);
    }
    
    if(peek(lexer) == '.' && isdigit(peek_next(lexer))){
        advance(lexer);
        while(isdigit(peek(lexer)))
            advance(lexer);
    }
    
    size_t lexeme_length = (lexer->current) - (lexer->start);
    char lexeme[MAX_LEXEME_LENGTH]; 

    if(!lexeme_length)
        return NULL;

    if(lexeme_length >=  MAX_LEXEME_LENGTH){
        fprintf(stderr,"lexeme length overflow... treated as UNKNOWN\n");
        return NULL; // maybe assert idk yet
    }

    strncpy(lexeme, &(lexer->source[lexer->start]),lexeme_length);
    lexeme[lexeme_length] = '\0';

    double value  = strtod(lexeme, NULL);

    if(lexeme_length == 1 && lexeme[0] == '.') // dot only
        return NULL;
    
    token_t* ret_token = create_token(NUMBER, lexeme, value);
    if(!ret_token){
        fprintf(stderr, "number token creation failed\n"); // proper error handling tbd
        assert(ret_token);
    }
    return ret_token;
}

void lexer_init(lexer_t* lexer, const char* line, size_t line_length){
    if(!lexer)
        return;
    lexer->source = line;
    lexer->start = 0;
    lexer->current = 0;
    lexer->stream = create_stream(line_length);
}

void lex_expression(lexer_t* lexer){
    
    if(!(lexer->stream)){
        fprintf(stderr, "stream creation failed\n");
        assert(lexer->stream);
    }

    while(!is_at_end(lexer)){
        token_t* token = NULL;
        token_stream_status_t status;
        
        token = tokenize_number(lexer);
        if(!token)
            token = tokenize_symbol(lexer);
        if(!token)
            token = tokenize_math_func(lexer);

        if (!token){
            char unknown_symbol[2] = {peek(lexer),'\0'};
            token = create_token(UNKNOWN, unknown_symbol);
            advance(lexer);
        }
        status = stream_append_token(lexer->stream, token);
        if(status != SUCCESS)
            fprintf(stderr, "Appending token to stream failed. Error: %d\n", (int)status);
    }
}

void lexer_reset(lexer_t* lexer){
    if(!lexer)
        return;
    stream_destroy(lexer->stream);
    lexer->stream = NULL; 
    lexer->source = NULL;
    lexer->start = 0;
    lexer->current = 0;
}


