#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

typedef struct      _s_token
{
    char            opcode[4];
    int             read_further;
    char            *string;
    struct _s_token *next;
}                   s_token;

extern s_token *tokens[];

s_token *ft_token_next(char **code_ptr);

#endif
