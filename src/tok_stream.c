#include "tok_stream.h"
#include "lexer.h"
#include <stddef.h>
#include <stdlib.h>

stream_t *create_stream(size_t stream_size){
    stream_t *stream = malloc(sizeof(stream_t)); // MUST FREE SECOND

    if(!stream)
        return NULL;
    
    if(stream_size == 0 || stream_size > 4095){
        free(stream);
        return NULL;
    }

    stream->buffer = calloc(stream_size, sizeof(token_t)); // MUST FREE FIRST
    if(!(stream->buffer)){
        free(stream);
        return NULL;
    }

    stream->capacity = stream_size;
    stream->length = 0;

    return stream;
}

void stream_destroy(stream_t** stream){
    if(!(stream) || !(*stream))
        return;

    free((*stream)->buffer);
    free((*stream));
    *stream = NULL;
}


void stream_push_tok(stream_t* stream){
    return;
}

void stream_pop_tok(stream_t* stream){
    return;
}

const token_t *current_token(const stream_t *stream){
    if (!stream || !(stream->length))
        return NULL;

    size_t last_index = stream -> length;
    return &(stream->buffer[last_index]);
}