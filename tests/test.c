#include "token.h"
#include <stdlib.h>

int main(void){

    for (int i = 0; i < 25; i++){  // NON-NUMBER TOKENS 
        int enum_val = rand() % (13 - 1 + 1) + 1;
        token_type_t type = enum_val;
        token_t* token = create_token(type, "", 0);
    }

    for (int i = 0; i < 25; i++){
        token_type_t type = NUMBER;
        double value = rand();
        char* lexeme;
        snprintf();
        token_t* token = create_token(type, "", );
    }

    return 0;
}