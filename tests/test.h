#ifndef TEST_H
#define TEST_H

#include "lex_limits.h"
#include "token.h"

#define TESTS_COUNT 16

typedef struct expected_token{
    double value;
    token_type_t expected_type;
    char expected_lexeme[MAX_LEXEME_LENGTH];
} expected_token_t;

typedef struct {
    const char* expression;
    expected_token_t expected_out[MAX_TOKEN_CAPACITY]; 
    size_t num_tokens;
} expected_lexer_output_t;

#endif // TEST_H

