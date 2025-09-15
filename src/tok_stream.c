#include <stddef.h>
#include <stdlib.h>
#include "tok_stream.h"
#include "token.h"
#include "limits.h"

static inline token_stream_status_t stream_buffer_resize(stream_t* stream){
    if(!stream || !(stream->buffer))
        return STREAM_NULL;

    size_t new_capacity = (stream->capacity) * 2;
    if(new_capacity > MAX_BUFFER_CAPACITY)
        return BUFFER_MAX_EXCEEDED;

    token_t* temp = realloc((stream->buffer), (sizeof(token_t) * new_capacity));
    if(!temp)
        return REALLOC_BUFFER_FAILED;
    
    stream->buffer = temp;
    stream->capacity = new_capacity;
    return RESIZE_BUFFER_SUCCESS;
}

stream_t *create_stream(size_t stream_size){
    stream_t *stream = malloc(sizeof(stream_t)); // free second

    if(!stream)
        return NULL;
    if(stream_size == 0 || stream_size > MAX_BUFFER_CAPACITY){
        free(stream);
        return NULL;
    }

    stream->buffer = calloc(stream_size, sizeof(token_t)); // free first
    if(!(stream->buffer)){
        free(stream);
        return NULL;
    }

    stream->capacity = stream_size;
    stream->length = 0;
    stream->iterator = 0;
    return stream;
}

void stream_destroy(stream_t *stream){
    if (!stream) return;
    free(stream->buffer);
    free(stream);
}

token_stream_status_t stream_append_token(stream_t* stream, const token_t* new_token){
    if(!stream || !(stream->buffer))
        return STREAM_NULL;
    if(!new_token)
        return TOKEN_NULL;

    token_stream_status_t status;
    if((stream->capacity) == (stream->length)){
        status = stream_buffer_resize(stream);
        if(status != RESIZE_BUFFER_SUCCESS)
            return status;
    }

    stream -> buffer[(stream -> length)++] = *new_token;
    return SUCCESS;
}

const token_t* stream_curr_token(const stream_t *stream){
    if(
        !stream ||
        !(stream->buffer) ||
        (stream->length) == 0 ||
        stream->iterator >= stream->length
    ) { return NULL; }

    size_t current = stream->iterator;
    return &(stream->buffer[current]);
}

token_stream_status_t stream_iterate_next(stream_t *stream){
    if(!stream || !(stream->buffer))
        return STREAM_NULL;

    if(stream->iterator + 1 >= stream->length)
        return NO_NEXT_TOKEN;

    stream->iterator++;
    return SUCCESS;
}

void print_stream(const stream_t* stream){
    if(!stream)
        return;

    size_t current = 0;
    for (;current < (stream -> length); current++)
        print_token(&(stream->buffer[current]));
    
}
