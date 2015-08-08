
#include <stdlib.h>
#include <stdio.h>

#include "8xp.h"
#include "token.h"
#include "instruction.h"


void ft_append_instruction(s_instruction **list, s_instruction *elem)
{
    /* if empty instruction, skip it */
    if (elem->tokens_length == 0)
    {
        // todo: free elem
        return;
    }

    /* empty list */
    if (*list == NULL)
    {
        *list = elem;
    }
    /* append instruction */
    else
    {
        s_instruction *ptr = *list;

        while (ptr->next)
            ptr = ptr->next;

        ptr->next = elem;
    }
}


int ft_fread(char *buf, int size, FILE *f)
{
    int ret = fread(buf, 1, size, f);
    buf[ret] = '\0';
    return ret;
}


char *ft_8xp_read_code(char *file, int *code_length)
{
    FILE *f = NULL;
    char buf[1024];
    int header_size = 8+3+40+9+6+8;
    char *raw_code;

    f = fopen(file, "r");
    if (f == NULL)
        ft_abort("fopen");

    /* read header */
    ft_fread(buf, 8, f);
    printf("file type: %s\n", buf);

    ft_fread(buf, 3, f); /* unknown */

    ft_fread(buf, 40, f);
    printf("date: %s\n", buf);

    ft_fread(buf, 9, f); /* unknown */

    ft_fread(buf, 6, f);
    printf("name: %s\n", buf);

    ft_fread(buf, 8, f); /* unknown */

    /* read code */
    fseek(f, 0, SEEK_END);
    *code_length = ftell(f) - header_size - 3; /* 2 bytes control sum + 1 byte null */

    fseek(f, header_size, SEEK_SET);

    raw_code = malloc(sizeof(char)*(*code_length));
    if (raw_code == NULL)
        ft_abort("malloc");
    ft_fread(raw_code, *code_length, f);

    ft_fread(buf, 3, f);
    printf("control sum: %2x%2x\n", (unsigned char)buf[0], (unsigned char)buf[1]);

    return raw_code;
}


s_instruction *ft_8xp_parse_code(char *raw_code, int code_length)
{
    char *code_ptr = raw_code;
    s_token *ci_code[128]; /* current_instruction */
    int ci_index = 0;
    s_instruction *ret = NULL;

    /* loop over the code */
    while (code_ptr < raw_code + code_length)
    {
        s_token *token = ft_token_next(&code_ptr);

        if (token->opcode[0] == 0X3E || token->opcode[0] == 0X3F) /* next instruction */
        {
            ft_append_instruction(&ret, ft_instruction_parse(ci_code, ci_index));
            ci_index = 0;
        }
        else /* regular token */
        {
            ci_code[ci_index] = token;
            ci_index ++;
            // todo: check overflow
        }
    }

    ft_append_instruction(&ret, ft_instruction_parse(ci_code, ci_index));

    return ret;
}
