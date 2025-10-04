#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"
#include "tok_stream.h"
#include "lex_limits.h"

static token_t* tokenize_number(lexer_t* lexer);
static token_t* tokenize_symbol(lexer_t* lexer); 
static token_t* tokenize_math_func(lexer_t* lexer);

static char advance(lexer_t* lexer){
    return (lexer->source[lexer->current++]);
}
static char peek(lexer_t* lexer){
    return (lexer->source[lexer->current]);
}

static char peek_next(lexer_t* lexer){
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
      case '*': token = create_token(MULTIPLY,  lexeme); break;
      case '/': token = create_token(DIVIDE, lexeme); break;
      case '^': token = create_token(POWER,  lexeme); break;
      default: break;
    }
    if(!token)
        lexer->current = lexer->start;
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

    if(!token)
        lexer->current = lexer->start;

    return token;
}

static token_t* tokenize_number(lexer_t* lexer){
    lexer->start = lexer->current;
    bool dot_found = false;

    if(peek(lexer) == '.'){
        dot_found = true;
        if(!isdigit(peek_next(lexer)))
            return NULL;
        advance(lexer);
    }

    while(isdigit(peek(lexer)))
        advance(lexer);
    
    if(peek(lexer) == '.' && isdigit(peek_next(lexer)) && !dot_found){
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

    token_t* ret_token = create_token(NUMBER, lexeme, value);
    if(!ret_token){
        fprintf(stderr, "(lexer) fatal error: number token creation failed... exiting");
        exit(EXIT_FAILURE);
    } 
    return ret_token;
}

void lexer_init(lexer_t* lexer, const char* line){
    if(!lexer)
        return;
    lexer->source = line;
    lexer->start = 0;
    lexer->current = 0;
    lexer->stream = create_stream();
}

void lex_expression(lexer_t* lexer){
    
    if(!(lexer->stream)){
        fprintf(stderr, "(lexer) fatal error: stream null error... exiting\n");
        exit(EXIT_FAILURE);
    }

    while(!is_at_end(lexer)){
        while(peek(lexer) == ' ')
            advance(lexer);
        if (is_at_end(lexer))
            break;

        token_t* token = NULL;
        token_stream_status_t status;

        token = tokenize_number(lexer);
        if(!token)
            token = tokenize_symbol(lexer);
        if(!token)
            token = tokenize_math_func(lexer);
        
        size_t unknown_string_size = 0;
        char unknown_symbol[MAX_LEXEME_LENGTH];
        while(!token && unknown_string_size < MAX_LEXEME_LENGTH - 1 && peek(lexer) != '\0' && peek(lexer) != ' '){
            unknown_symbol[unknown_string_size] = peek(lexer);
            advance(lexer);
            unknown_string_size++;
        }

        if(unknown_string_size != 0){
            unknown_symbol[unknown_string_size] = '\0';
            token = create_token(UNKNOWN, unknown_symbol);
        }

        status = stream_append_token(lexer->stream, token);
        free_token(token);
        if(status != SUCCESS)
            fprintf(stderr, "Appending token to stream failed. Error: %d\n", (int)status);
    }

    token_t* last_token = NULL;
    last_token = create_token(END,"");
    token_stream_status_t last_tok_status = stream_append_token(lexer->stream, last_token);
    free_token(last_token);
    if(last_tok_status != SUCCESS)
        fprintf(stderr, "Appending END token to stream failed. Error: %d\n", (int)last_tok_status);
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

token_t* lex_peek(const lexer_t* lexer){
    return stream_curr_token(lexer->stream);
}

token_stream_status_t lex_advance(lexer_t* lexer){
    return stream_iterate_next(lexer->stream);
}

token_t* lex_next(lexer_t* lexer){
    token_stream_status_t status = lex_advance(lexer);
    if(status == NO_NEXT_TOKEN)
        return NULL;
    return lex_peek(lexer);
}

