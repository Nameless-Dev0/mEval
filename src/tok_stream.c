#include <stdlib.h>
#include <assert.h>

#include "tok_stream.h"
#include "token.h"
#include "lex_limits.h"

static inline token_stream_status_t stream_buffer_resize(stream_t* stream);

stream_t *create_stream(void){

    stream_t *stream = malloc(sizeof(stream_t)); // free second    
    if(!stream)
        return NULL;

    stream->buffer = calloc(TOKEN_CAPACITY, sizeof(token_t)); // free first
    if(!(stream->buffer)){
        free(stream);
        return NULL;
    }

    stream->capacity = TOKEN_CAPACITY;
    stream->length = 0;
    stream->iterator = 0;
    return stream;
}

void stream_destroy(stream_t *stream){
    if (!stream)
        return;
    free(stream->buffer);
    free(stream);
}

static inline token_stream_status_t stream_buffer_resize(stream_t* stream){
    STREAM_VALID_CHECK;

    size_t new_capacity = (stream->capacity) * 2;
    if(new_capacity > MAX_TOKEN_CAPACITY)
        return BUFFER_MAX_EXCEEDED;

    token_t* temp = realloc((stream->buffer), (sizeof(token_t) * new_capacity));
    if(!temp)
        return REALLOC_BUFFER_FAILED;
    
    stream->buffer = temp;
    stream->capacity = new_capacity;
    return RESIZE_BUFFER_SUCCESS;
}

token_stream_status_t stream_append_token(stream_t* stream, const token_t* new_token){
    STREAM_VALID_CHECK;
    assert(new_token);

    token_stream_status_t status;
    if((stream->capacity) == (stream->length)){
        status = stream_buffer_resize(stream);
        if(status != RESIZE_BUFFER_SUCCESS)
            return status;
    }

    stream -> buffer[(stream -> length)++] = *new_token;
    return SUCCESS;
}

inline const token_t* stream_curr_token(const stream_t* stream){
    STREAM_VALID_CHECK;
    if(stream->length == 0 || stream->iterator >= stream->length)
        return NULL;
    return &(stream->buffer[stream->iterator]);
}

inline const token_t* stream_next_token(const stream_t* stream){
    STREAM_VALID_CHECK;
    if(stream->length == 0 || stream->iterator + 1 >= stream->length)
        return NULL;
    return &(stream->buffer[(stream->iterator)+ 1]);
}

inline token_stream_status_t stream_iterate_next(stream_t* stream){
    STREAM_VALID_CHECK;
    if(stream->iterator + 1 >= stream->length)
        return NO_NEXT_TOKEN;
    stream->iterator++;
    return SUCCESS;
}

void print_stream(const stream_t* stream){
    STREAM_VALID_CHECK;
    size_t current = 0;
    for(; current < stream->length; current++)
        print_token(&stream->buffer[current]);
}
