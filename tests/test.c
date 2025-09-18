#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#include "test.h"
#include "lexer.h"
#include "token.h"
#include "tok_stream.h"
#include "lex_limits.h"

static expected_lexer_output_t tests[TESTS_COUNT] = {
    {"1+2",        {{1.0, NUMBER, "1"}, {0.0, PLUS, "+"}, {2.0, NUMBER, "2"}}, 3},
    {"(3*4)",      {{0.0, LPAREN, "("}, {3.0, NUMBER, "3"}, {0.0, TIMES, "*"}, {4.0, NUMBER, "4"}, {0.0, RPAREN, ")"}}, 5},
    {"cos(0)",     {{0.0, COS, "cos"}, {0.0, LPAREN, "("}, {0.0, NUMBER, "0"}, {0.0, RPAREN, ")"}}, 4},
    {"sin(90)",    {{0.0, SIN, "sin"}, {0.0, LPAREN, "("}, {90.0, NUMBER, "90"}, {0.0, RPAREN, ")"}}, 4},
    {"5-3",        {{5.0, NUMBER, "5"}, {0.0, MINUS, "-"}, {3.0, NUMBER, "3"}}, 3},
    {"2^3",        {{2.0, NUMBER, "2"}, {0.0, POWER, "^"}, {3.0, NUMBER, "3"}}, 3},
    {"tan(45)",    {{0.0, TAN, "tan"}, {0.0, LPAREN, "("}, {45.0, NUMBER, "45"}, {0.0, RPAREN, ")"}}, 4},
    {"1+2*3",      {{1.0, NUMBER, "1"}, {0.0, PLUS, "+"}, {2.0, NUMBER, "2"}, {0.0, TIMES, "*"}, {3.0, NUMBER, "3"}}, 5},
    {"(4/2)-1",    {{0.0, LPAREN, "("}, {4.0, NUMBER, "4"}, {0.0, DIVIDE, "/"}, {2.0, NUMBER, "2"}, {0.0, RPAREN, ")"}, {0.0, MINUS, "-"}, {1.0, NUMBER, "1"}}, 7},
    {"3.14+2.71",  {{3.14, NUMBER, "3.14"}, {0.0, PLUS, "+"}, {2.71, NUMBER, "2.71"}}, 3},
    {"(1+(2*3))",  {{0.0, LPAREN, "("}, {1.0, NUMBER, "1"}, {0.0, PLUS, "+"}, {0.0, LPAREN, "("}, {2.0, NUMBER, "2"}, {0.0, TIMES, "*"}, {3.0, NUMBER, "3"}, {0.0, RPAREN, ")"}, {0.0, RPAREN, ")"}}, 9},
    {"42",         {{42.0, NUMBER, "42"}}, 1},
    {"  1 + 2  ",  {{1.0, NUMBER, "1"}, {0.0, PLUS, "+"}, {2.0, NUMBER, "2"}}, 3},
    {"1$2",        {{1.0, NUMBER, "1"}, {0.0, UNKNOWN, "$"}, {2.0, NUMBER, "2"}}, 3},
    {"(1+2",       {{0.0, LPAREN, "("}, {1.0, NUMBER, "1"}, {0.0, PLUS, "+"}, {2.0, NUMBER, "2"}}, 4},
    {"",           {}, 0}
};

static int check_lexer_output(stream_t* lexer_output, expected_token_t* expected_out, size_t expected_out_length){
    if(expected_out_length != lexer_output->length)
        return -1;

    for (size_t i = 0; i < expected_out_length; i++){
        if(
            lexer_output->buffer[i].type != expected_out[i].expected_type ||
            strcmp(lexer_output->buffer[i].lexeme, expected_out[i].expected_lexeme) != 0||
            //fabs(lexer_output->buffer[i].value - expected_out[i].value) > 1e-9
            lexer_output->buffer[i].value != expected_out[i].value
        ){return -1;}
    }
    return 0;
}

int main(void){

    const char* expression;
    expected_token_t* expected_stream;
    size_t expected_stream_length;
    lexer_t lexer;

    for (size_t i = 0; i < TESTS_COUNT; i++)
    {
        expression = tests[i].expression;
        expected_stream = tests[i].expected_out;
        expected_stream_length = tests[i].num_tokens;

        lexer_init(&lexer, expression);
        lex_expression(&lexer);

        if(!check_lexer_output(lexer.stream, expected_stream, expected_stream_length))
            printf("TEST %zu ... PASS ✓ \n", i);
        else
            printf("TEST %zu ... FAIL 𐄂 \n", i);

        lexer_reset(&lexer);
    }
    
    return 0;
}


