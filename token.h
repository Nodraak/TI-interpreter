#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

typedef enum    _e_token
{
    TOKEN_INT,
    TOKEN_VAR,
    TOKEN_FUNC,
    // operator
    TOKEN_OTHER,
    TOKEN_INCOMPLETE,
    TOKEN_UNKNOWN,
}               e_token;


typedef struct      _s_token
{
    char            opcode[4];
    int             priority;
    e_token         type;
    char            *string;
}                   s_token;

/*
priority:
    5 ->
    10 + -
    20 * /
    30 ^ !
*/

extern s_token *tokens[];

s_token *ft_token_next(char **code_ptr);

#endif
