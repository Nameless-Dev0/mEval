#ifndef TOK_STREAM_H
#define TOK_STREAM_H

/*
    Token stream is a dymanic array data structure.
    It is the output/return type of the lexer.
*/

#include <stddef.h>

typedef struct token token_t;

typedef enum token_stream_status{
    SUCCESS,
    STREAM_NULL,
    TOKEN_NULL,
    NO_NEXT_TOKEN,
    BUFFER_MAX_EXCEEDED,
    REALLOC_BUFFER_FAILED,
    RESIZE_BUFFER_SUCCESS,
}token_stream_status_t;

typedef struct stream{
    size_t iterator;
    size_t length;
    size_t capacity;
    struct token* buffer;
}stream_t;

stream_t* create_stream(size_t stream_size);
void stream_destroy(stream_t* stream);

const token_t* stream_curr_token(const stream_t* stream);
token_stream_status_t stream_iterate_next(stream_t* stream);
token_stream_status_t stream_append_token(stream_t* stream, const token_t* new_token);

void print_stream(const stream_t* stream);
#endif // TOK_STREAM_H