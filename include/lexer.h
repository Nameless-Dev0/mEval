#ifndef LEXER_H
#define LEXER_H
#include <stddef.h>

typedef struct stream stream_t;

typedef struct lexer{
    stream_t* stream;
    const char* source;
}lexer_t;

#endif // LEXER_H

