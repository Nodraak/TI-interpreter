#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include "token.h"

typedef enum _e_param
{
    PARAM_FUNC,
    PARAM_INT,
    PARAM_STR,
    PARAM_VAR,
}           e_param;

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

    VAR_LAST,
}               e_var;

typedef struct _s_param s_param;

typedef struct              _s_function
{
    void*(*callback)(s_param *av[]);
    int                     ac;
    s_param                 **av;
    char                    *name;
}                           s_function;

typedef struct              _s_param
{
    e_param                 type;

    s_function              *function;
    int                     n;
    char                    *str;
    e_var                   var;
}                           s_param;

typedef struct              _s_instruction
{
    s_token                 **tokens;
    int                     tokens_length;
    s_param                 *param;

    struct _s_instruction   *next;
}                           s_instruction;


void *memdup(void *data, int length);
void *ft_get_callback(s_token *token);

s_param *parse_int(s_token **tokens, int length);
s_param *parse_func(s_token *func, s_token **tokens, int length);

int ft_tokens_split_get_index(s_token **tokens, int length);
s_param *ft_tokens_parse_tokens(s_token **tokens, int length);
s_instruction *ft_instruction_parse(s_token **tokens, int length);

#endif
