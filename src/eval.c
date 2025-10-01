#include "ast.h"
#include "token.h"
#include "math.h"

double evaluate_AST(ast_node_t* root){
    if(!root)
        return 0;

    double result;
    switch (root->token.type){
        case NUMBER:
            result = root->token.value;
            return result;
        case PLUS:
            result = evaluate_AST(root->left) + evaluate_AST(root->right);
            return result;
        case MINUS:
            result = evaluate_AST(root->left) - evaluate_AST(root->right);
            return result;
        case MULTIPLY:
            result = evaluate_AST(root->left) * evaluate_AST(root->right);
            return result;
        case DIVIDE:
            result = evaluate_AST(root->left) / evaluate_AST(root->right);
            return result;
        case POWER:
            result = pow(evaluate_AST(root->left), evaluate_AST(root->right));
            return result;
        case SIN:
            result = sin(evaluate_AST(root->right));
            return result;
        case COS:
            result = cos(evaluate_AST(root->right));
            return result;
        case TAN:
            result = tan(evaluate_AST(root->right));
            return result;
        default:
            result = 0;
            return result;
    }

    return result;
}