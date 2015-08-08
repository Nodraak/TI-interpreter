
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


void ft_print_code(s_instruction *ptr_code)
{
    int i;

    printf("\nopcode [type] string\n");

    while (ptr_code)
    {
        s_token *ptr_token = ptr_code->tokens;

        while (ptr_token)
        {
            for (i = 0; i < ptr_token->read_further; ++i)
                printf("%02x", (unsigned char)ptr_token->opcode[i]);
            for (; i < 3; ++i)
                printf("  ");
            printf(" %s\n", ptr_token->string);

            ptr_token = ptr_token->next;
        }

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
