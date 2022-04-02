/* 
Dario Quiñones - 2022

A simple equation solver, part of the Calculator project. 
Takes a string of operadors and operands and returns the result.

It could have been written in a more C-like way, but it's mostly a Rust port.
I have not yet found a way to get proper function definitions in another C file.

And, by the way, this is BARELY A PROTOTYPE.

Equation_solver.h */
//#ifdef __cplusplus
//extern "C" {
//#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <math.h> // Haven't linked math.h yet

#define F_PRECISION 4

// When we parse the equation, it is stored in the form of tokens.
// The tokens are stored in a linked list.
// The tokens are either operadors or operands.
// Tokens are (for now) +, -, *, /, (, ), and numbers.

/*****************************************************************************
 *                              Type Definitions                             *
 * **************************************************************************/

// The types of token data, either operator or operand.
enum TokenType {
    OPERATOR,
    OPERAND
};

/* The different types of operadors. */
enum OperatorType {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULUS,
    POWER,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS
};

/* An operador or operand.

    * The type is either OPERATOR or OPERAND.
    * The value is either the type of operador or the operand value.
    * The next is a pointer to the next token.
*/
typedef struct Token token;
struct Token {
    enum TokenType type;
    union {
        enum OperatorType operador;
        double value;
    };
    token *next;
    token *prev;
} Token;


/*****************************************************************************
 *                              Fuction prototypes                           *
 * **************************************************************************/

// Constructs a new token.
token *new_token (enum TokenType type, double value);

// Takes a character and returns the corresponding operador type.
// It should not be used for numbers as it does not support more than one digit.
token *char_to_token (char c);

// It takes a float still in string form and 
// returns a token with the value.
token *number_to_token (char *str);

// Returns either the operador type or the operand value as a *char.
char *token_to_string (token *token);

// Returns the length of the token.
int length(token *list);

// Prints the token list.
void print_tokens (token *tokens);

// Appends a token to the end of a linked list.
token *append_token (token *list, token *new_token);

// Removes all whitespace from a string.
// Returns a pointer to a new string.
char *remove_whitespace(char *str);

// // Removes every non-tokenizable character from a string.
// char *clean_string(char *str);

// Parses the string into tokens.
// Returns a pointer to the first token.
token *tokenizer(char *str, token *tokens);

// Inserts the middle token in place of the left and right tokens.
void insert_replace(token *left, token *middle, token *right);

void solve_parenthesis(token *tokens, token *parenthesis);

// Evaluates the tokens.
// Returns the result.
token *evaluate_tokens(token *tokens);

// Returns the pointer to the first token of the type specified.
token *tokenfind(token *tokens, enum OperatorType type);

// Returns the char of the operador type.
char operador_char(enum OperatorType type);

//double pow(double x, double y);

char *solve(char *equation);


