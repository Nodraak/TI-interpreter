#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

typedef enum    _e_token
{
    TOKEN_INT,
    TOKEN_VAR,
    TOKEN_FUNC,                 /* ex: EffEcr() */
    TOKEN_FUNC_WITH_PARAM,      /* ex: Input(...) */
    TOKEN_OP,                   /* ex: +, *, -> */
    TOKEN_INCOMPLETE,

    TOKEN_PARENTHESIS_OPEN,
    TOKEN_PARENTHESIS_CLOSE,
    TOKEN_DOUBLE_QUOTES,
    TOKEN_COMA,

    TOKEN_OTHER,
    TOKEN_UNKNOWN
}               e_token;


typedef enum    _e_var
{
    VAR_A,
    VAR_B,
    VAR_C,
    VAR_D,
    VAR_E,
    VAR_F,
    VAR_G,
    VAR_H,
    VAR_I,
    VAR_J,
    VAR_K,
    VAR_L,
    VAR_M,
    VAR_N,
    VAR_O,
    VAR_P,
    VAR_Q,
    VAR_R,
    VAR_S,
    VAR_T,
    VAR_U,
    VAR_V,
    VAR_W,
    VAR_X,
    VAR_Y,
    VAR_Z,
    VAR_OMEGA,

    VAR_LAST
}               e_var;


typedef struct      _s_token
{
    unsigned char   opcode[4];
    int             priority; /* operator priority */
    e_token         type;
    void*           callback; /* for functions */
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

s_token *ft_token_next(unsigned char **code_ptr);

int ft_token_get_int(s_token *token);
e_var ft_token_get_var(s_token *token);
int ft_token_is_var_std(s_token *token);
void *ft_token_get_callback(s_token *token);

#endif
