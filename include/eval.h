#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
typedef struct ast_node ast_node_t;
double evaluate_AST(ast_node_t* root);

#endif // EVAL_H