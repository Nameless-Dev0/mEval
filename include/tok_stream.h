#ifndef TOK_STREAM_H
#define TOK_STREAM_H

#define MAX_BUFFER_CAPACITY 4096

#include <stddef.h>

/*
    Token stream is a dymanic array data structure.
    It is the output/return type of the lexer.
*/

typedef struct token token_t;

// TODO: Add error handling for tok_stream errors.
typedef enum token_stream_status{
    STREAM_NULL = 1,
    BUFFER_MAX_EXCEEDED,
    REALLOC_BUFFER_FAILED,
    RESIZE_BUFFER_SUCCESS,
    PUSH_TOK_FAILED,
    POP_TOK_FAILED
}token_stream_status_t;

typedef struct stream{
    size_t position;
    size_t length;
    size_t capacity;
    struct token* buffer;
}stream_t;


stream_t* create_stream(size_t stream_size);
void stream_destroy(stream_t** stream);

// const token_t* stream_curr_token(const stream_t* stream, int position); // TODO
// const token_t* stream_next_token(const stream_t* stream, int position); // TODO
token_stream_status_t stream_append_token(stream_t* stream, token_t* new_token);


#endif // TOK_STREAM_H