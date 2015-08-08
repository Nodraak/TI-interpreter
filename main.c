
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
    int i, j;

    printf("\ntokens string\n\n");

    while (ptr_code)
    {
        for (i = 0; i < ptr_code->tokens_length; ++i)
        {
            for (j = 0; j < 4; ++j)
            {
                if (ptr_code->tokens[i]->opcode[j] != 0x00)
                    printf("%02x", (unsigned char)ptr_code->tokens[i]->opcode[j]);
            }
            printf(" %s\n", ptr_code->tokens[i]->string);
        }

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
