#ifndef TOK_STREAM_H
#define TOK_STREAM_H

/*
    Token stream is a dymanic array data structure.
    It is the output/return type of the lexer.
*/

#include <stddef.h>
    
#define STREAM_VALID_CHECK assert(stream && (stream->buffer))

typedef struct token token_t;

typedef enum token_stream_status{
    SUCCESS,
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

stream_t* create_stream(void); // initial capacity is 64 tokens
void stream_destroy(stream_t* stream);

const token_t* stream_curr_token(const stream_t* stream);
const token_t* stream_next_token(const stream_t* stream);
token_stream_status_t stream_iterate_next(stream_t* stream);

token_stream_status_t stream_append_token(stream_t* stream, const token_t* new_token);
void print_stream(const stream_t* stream);

#endif // TOK_STREAM_H
