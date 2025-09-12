#ifndef TOK_STREAM_H
#define TOK_STREAM_H

#include "lexer.h"
#include <stddef.h>

/*
    Token stream is a dymanic array data structure.
    It is the output/return type of the lexer.
*/

// TODO: Add enum ERRORS for handling tok_stream errors.

stream_t *create_stream(size_t stream_size);
void stream_destroy(stream_t **stream);

void stream_push_tok();
void stream_pop_tok();
const token_t *current_token(const stream_t *stream);


#endif // TOK_STREAM_H