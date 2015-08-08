
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "8xp.h"
#include "token.h"
#include "instruction.h"


void ft_abort(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    fprintf(stderr, "(Errno: %d %s)\n", errno, strerror(errno));
    exit(1);
}


void print_tokens(s_token **tokens, int length)
{
    int i;

    printf("token[]->opcode");
    for (i = 0; i < length; ++i)
        printf(" %02x", tokens[i]->opcode);
    printf("\n");

    printf("token[]->opcode[0]");
    for (i = 0; i < length; ++i)
        printf(" %02x", (unsigned char)tokens[i]->opcode[0]);
    printf("\n");

}


void ft_print_sparam(s_param *param, int level)
{
    int i = 0;

    for (i = 0; i < level*4; ++i)
        printf(" ");

    switch (param->type)
    {
        case PARAM_INT:
            printf("int: \"%d\"\n", param->n);
            break;
        case PARAM_STR:
            printf("str: \"%s\"\n", param->str);
            break;
        case PARAM_FUNC:
            printf("func: \"%s\" (ac=%d)\n", param->function->name, param->function->ac);
            int j;
            for (j = 0; j < param->function->ac; ++j)
                ft_print_sparam(param->function->av[j], level+1);
            break;
        case PARAM_VAR:
            printf("var: <todo>\n");
            break;
        default:
            printf("<unknown todo>\n");
    }
}


void ft_print_code(s_instruction *ptr_code)
{
    int i, j;

    while (ptr_code)
    {
        /* tokens */
        for (i = 0; i < ptr_code->tokens_length; ++i)
        {
            for (j = 0; j < 4; ++j)
            {
                if (ptr_code->tokens[i]->opcode[j] != 0x00)
                    printf("%02x", (unsigned char)ptr_code->tokens[i]->opcode[j]);
            }
            printf(" %s\n", ptr_code->tokens[i]->string);
        }

        /* param */
        ft_print_sparam(ptr_code->param, 0);

        printf("\n");
        ptr_code = ptr_code->next;
    }
}


char *program[] = {
    "data/AATEST.8Xp",
    "data/ABC.8Xp",
    "data/BASE.8Xp",
    "data/WTC.8Xp",
};


int main(void)
{
    char *raw_code = NULL;
    int code_length;
    s_instruction *code = NULL;

    raw_code = ft_8xp_read_code(program[3], &code_length);
    code = ft_8xp_parse_code(raw_code, code_length);
    ft_print_code(code);

    return 0;
}
