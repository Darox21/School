/*
Dario Quiñones - 2022

A simple equation solver, part of the Calculator project.
Takes a string of operators and operands and returns the result.

It could have been written in a more C-like way, but it's mostly a Rust port.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eqsolver.h"
#include <math.h> // Haven't linked math.h yet


/*****************************************************************************
 *                          Function implementations                         *
 * **************************************************************************/

token *new_token (enum TokenType type, double value) {
    // If token is operand, value is the operand value.
    // If token is operator, value is the operator type.
    token *t = malloc(sizeof(token));
    t->type = type;
    if (type == OPERAND) {
        t->value = value;
    } else {
        t->operador = value;
    }
    t->next = NULL;
    t->prev = NULL;
    return t;
};

char operator_char(enum OperatorType t) {
    switch (t) {
        case ADD:
            return '+';
        case SUBTRACT:
            return '-';
        case MULTIPLY:
            return '*';
        case DIVIDE:
            return '/';
        case MODULUS:
            return '%';
        case OPEN_PARENTHESIS:
            return '(';
        case CLOSE_PARENTHESIS:
            return ')';
        case POWER:
            return '^';
        default:
            return '\0';
    }
};

token *char_to_token (char c) {
    switch (c)
    {
        case '+':
            return new_token(OPERATOR, ADD);
        case '-':
            return new_token(OPERATOR, SUBTRACT);
        case '*':
            return new_token(OPERATOR, MULTIPLY);
        case '/':
            return new_token(OPERATOR, DIVIDE);
        case '%':
            return new_token(OPERATOR, MODULUS);
        case '^':
            return new_token(OPERATOR, POWER);
        case '(':
            return new_token(OPERATOR, OPEN_PARENTHESIS);
        case ')':
            return new_token(OPERATOR, CLOSE_PARENTHESIS);
        default:
            return NULL;
    }
};

double operation_table(int op, double left, double right){
	double result;
    switch (op)
    {
        case ADD:
            result = left + right;
            break;
        case SUBTRACT:
            result = left - right;
            break;
        case MULTIPLY:
            result = left * right;
            break;
        case DIVIDE:
            result = left / right;
            break;
        case MODULUS:
            result = (long int)left % (long int)right;
            break;
		case POWER:
			result = pow(left, right);
			break;
        default:
            break;
    }
    return result;
}

token *number_to_token (char *str) {
    // It's an operand.
    return new_token(OPERAND, atof(str));
};

char *token_to_string (token *t) {
    if (t->type == OPERATOR) {
        char *c = malloc(sizeof(char));
        c[0] = operator_char(t->operador);
        return c;
    } else {
        // return the value as a string.
        char *str = malloc(sizeof(char) * 20);
        // printf("t->value: %f\n", t->value);
        sprintf(str, "%.3f", t->value);
        return str;
    }
};

int length(token *list) {
    int length = 0;
    token *t = list;
    while (t != NULL) {
        length++;
        t = t->next;
    }
    return length;
};

void print_tokens (token *tokens) {
    token *t = tokens;
    while (t != NULL) {
        printf("%s, ", token_to_string(t));
        t = t->next;
    }
    printf("\n");
};

token *append_token (token *list, token *new_token) {
    if (list == NULL) {
        return new_token;
    }
    token *t = list;
    while (t->next != NULL) {
        t = t->next;
    }
    t->next = new_token;
    new_token->prev = t;
    return list;
};

char *remove_whitespace(char *str){
    char *new_str = malloc(strlen(str) + 1);
    char *new_str_ptr = new_str;
    char *str_ptr = str;
    while (*str_ptr != '\0') {
        if (!isspace(*str_ptr)) {
            *new_str_ptr = *str_ptr;
            new_str_ptr++;
        }
        str_ptr++;
    }
    *new_str_ptr = '\0';
    return new_str;
};

// char *clean_string(char *str) {
//     // Remove whitespace.
//     str = remove_whitespace(str);
//     // Remove all non-tokenizable characters.
//     char *result = malloc(strlen(str) + 1);
//     char *str_ptr = str;
//     while (*str_ptr != '\0') {
//         if (char_to_token(*str_ptr) != NULL || isdigit(*str_ptr)) {
//             *result = *str_ptr;
//             result++;
//         }
//         str_ptr++;
//     }
//     *result = '\0';
//     return result;
// }

token *tokenizer(char *str, token *tokens){
    // Remove whitespace from the string.
    printf("Tokenizing... %s\n", str);
    str = remove_whitespace(str);

    char prev_char = '\0';
    char *curr_num = calloc(100,sizeof(char));
    char *chars = str;
    int i;
    for (i = 0; i<strlen(str); i++) {
        if (isdigit(prev_char) && (isdigit(chars[i]) || chars[i] == '.')) {
            // It's a number. push it to the current number.
            curr_num[strlen(curr_num)] = chars[i];
        } else if (isdigit(prev_char)){
            // It's the end of the number.
            token *t = number_to_token(curr_num);
            tokens = append_token(tokens, t);

            curr_num = calloc(100,sizeof(char));
            // Add the operator to the tokens.
            token *operator = char_to_token(chars[i]);
            tokens = append_token(tokens, operator);

        } else {
            // The last character was an operator, the current can be anything.
            if (isdigit(chars[i]) || chars[i] == '.' || chars[i] == '-') {
                // It's a number.
                curr_num[strlen(curr_num)] = chars[i];
            } else {
                // It's an operator.
                token *t = char_to_token(chars[i]);
                tokens = append_token(tokens, t);
            }
        }
        prev_char = chars[i];
    }
    // Add the last number to the end of the tokens (if it exists).
    if (strlen(curr_num) > 0) {
        token *t = number_to_token(curr_num);
        tokens = append_token(tokens, t);
    }
    // Set the the first token's prev to NULL.
    if (tokens != NULL) {
        tokens->prev = NULL;
    }
    return tokens;
};

void insert_replace(token *left, token *middle, token *right) {
    if (left->prev != NULL) {
        left->prev->next = middle;
    } else {
        middle->prev = NULL;
    }

    if (right->next != NULL) {
        right->next->prev = middle;
    } else {
        middle->next = NULL;
    }
    middle->prev = left->prev;
    middle->next = right->next;
};

void solve_parenthesis(token *tokens, token *parenthesis){
    int paren_count = 0;
    token *t = parenthesis;
    int unsolved = 1;
    while (unsolved == 1) {
        if (t->operador == OPEN_PARENTHESIS) {
            paren_count++;
        } else if (t->operador == CLOSE_PARENTHESIS) {
            paren_count--;
        }
        if (paren_count == 0) {
            // We found the matching parenthesis.
            // We need to evaluate the tokens between the parenthesis.
            token *opening_paren = parenthesis;
            token *closing_paren = t;

            // Cut the tokens inside the parenthesis.
            token *sub_tokens = opening_paren->next;
            closing_paren->prev->next = NULL;

            printf("Solving parenthesis... ");
            print_tokens(sub_tokens);
            // Evaluate the tokens inside the parenthesis.
            token *result = evaluate_tokens(sub_tokens);
            // make the result value to a new token.
            token *output = new_token(OPERAND, result->value);

            // Insert the token in place of the parenthesis.
            insert_replace(opening_paren, output, closing_paren);




            unsolved = 0;

            // // Free the removed tokens.
            // free(sub_tokens);
        }
        t = t->next;
    }
    if (paren_count != 0) {
        printf("Error: Parenthesis mismatch.\n");
    }
}

token *evaluate_tokens(token *tokens) {
    // if we have a parenthesis, we solve it recursively.
    token *paren = tokenfind(tokens, OPEN_PARENTHESIS);
    if (paren != NULL) {
        solve_parenthesis(tokens, paren);
    }

    // Now we have a list of tokens that are not parenthesis.
    // We need to find the place of highest precedence.
    while (length(tokens) > 2) {
        // Find the highest precedence operator.
        token *op = NULL;
        token *t = tokens;
//		int i;
        for (int i = 0; i < length(tokens)-1; i++) {
            if (t->type == OPERATOR) {
                if (op == NULL) {
                    op = t;
                } else if (op->operador < t->operador) {
                    op = t;
                }
            }
            t = t->next;
        }

        if (op == NULL) {
            // There are no operators left.
            break;
        }

        // We need to evaluate the tokens before and after it.
        double left = op->prev->value;
        double right = op->next->value;
        double result = 0;
        printf("Evaluating: %.2f %s %.2f", left, token_to_string(op), right);
		
		result = operation_table(op->operador, left, right);

        printf(" = %.2f\n", result);
        // Insert the result in the list.
        token *output = new_token(OPERAND, result);
        if (length(tokens) >= 3) {
            insert_replace(op->prev, output, op->next);
            if (output->prev == NULL || output->prev->operador == OPEN_PARENTHESIS) {
                tokens = output;
            }
        } else {
            if (op->prev->operador == OPEN_PARENTHESIS) {
                printf("Error: Parenthesis mismatch.\n");
                tokens = output;
            }
            // This was the operation of the last 3 tokens.
            // We can just replace the last 3 tokens with the result.
            op->prev->next = NULL;
            op->next->prev = NULL;
            tokens = output;
        }
        free(op);
    }
    print_tokens(tokens);
    // Return the result.
    return tokens;
};

token *tokenfind(token *tokens, enum OperatorType type) {
    token *t = tokens;
    while (t != NULL) {
        if (t->type == OPERATOR && t->operador == type) {
            return t;
        }
        t = t->next;
    }
    return NULL;
};




/*****************************************************************************
 *                                  Main                                     *
 * **************************************************************************/

char *solve(char *equation){
    // The equation is stored in a string.
    // The string is parsed into tokens.
    // The tokens are then evaluated.
//    char *equation = (char *)"(2 + 6 * (-3 + 140) / 3)";
//	char *equation[80];
//	scanf("%s", equation);
//	printf("OH...");
    equation = remove_whitespace(equation);
    printf("%s\n", equation);
    token *tokens = tokenizer(equation, NULL);
    print_tokens(tokens);
    token *result = evaluate_tokens(tokens);
    printf("Result: %s\n", token_to_string(result));
    printf("\n");
    return token_to_string(result);
}

