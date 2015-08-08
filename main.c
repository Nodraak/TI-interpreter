
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "token.h"
#include "instruction.h"

void ft_abort(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    fprintf(stderr, "(Errno: %d %s)\n", errno, strerror(errno));
    exit(1);
}


int ft_fread(char *buf, int size, FILE *f)
{
    int ret = fread(buf, 1, size, f);
    buf[ret] = '\0';
    return ret;
}


s_token *ft_get_next_token(FILE *f, int *c)
{
    int i = 0, byte_count = 0;
    char current_opcode[4] = "";
    s_token *token = NULL, *ret = NULL;

    do
    {
        fread(&current_opcode[byte_count], 1, 1, f);
        (*c) ++;

        for (i = 0; strcmp(tokens[byte_count][i].opcode, "\xFF") != 0; ++i)
        {
            if (strcmp(tokens[byte_count][i].opcode, current_opcode) == 0)
                break;
        }
        token = &tokens[byte_count][i];

        byte_count ++;
    } while (token->read_further);

    ret = malloc(sizeof(s_token));
    if (ret == NULL)
        ft_abort("malloc");

    strcpy(ret->opcode, current_opcode);
    ret->read_further = byte_count;
    ret->string = strdup(token->string);
    ret->next = NULL;

    return ret;
}


char *program[] = {
    "data/AATEST.8Xp",
    "data/ABC.8Xp",
    "data/BASE.8Xp",
    "data/WTC.8Xp",
};


void ft_append_instruction(s_instruction **list, s_instruction *elem)
{
    if (*list == NULL)
    {
        *list = elem;
    }
    else
    {
        s_instruction *ptr = *list;

        while (ptr->next)
            ptr = ptr->next;

        ptr->next = elem;
    }
}

void ft_append_token(s_instruction **list, s_token *elem)
{
    if (*list == NULL)
    {
        *list = malloc(sizeof(s_instruction));
        if (*list == NULL)
            ft_abort("malloc");

        (*list)->tokens = elem;
        (*list)->next = NULL;
    }
    else
    {
        s_token *ptr = (*list)->tokens;

        while (ptr->next)
            ptr = ptr->next;

        ptr->next = elem;
    }
}


int main(void)
{
    char *file = program[3];
    char buf[1024];
    FILE *f = NULL;

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
    int header_size = 8+3+40+9+6+8;
    int code_length = 0, c = 0, i = 0;

    fseek(f, 0, SEEK_END);
    code_length = ftell(f) - header_size - 3; /* 3 = 2 control sum + 1 null */
    fseek(f, header_size, SEEK_SET);

    s_instruction *code = NULL, *cur_instruction = NULL;

    for (c = 0; c < code_length;)
    {
        s_token *token = ft_get_next_token(f, &c);

        if (token->opcode[0] == 0X3E || token->opcode[0] == 0X3F) /* next instruction */
        {
            ft_append_instruction(&code, cur_instruction);
            cur_instruction = NULL;
        }
        else
        {
            ft_append_token(&cur_instruction, token);
        }
    }

    ft_fread(buf, 3, f);
    printf("control sum: %2x%2x\n", (unsigned char)buf[0], (unsigned char)buf[1]);

    printf("\nopcode [type] string\n");

    s_instruction *ptr = code;
    while (ptr)
    {
        s_token *ptr_token = ptr->tokens;

        while (ptr_token)
        {
            //printf("%-4d | ", c);
            for (i = 0; i < ptr_token->read_further; ++i)
                printf("%02x", (unsigned char)ptr_token->opcode[i]);
            for (; i < 3; ++i)
                printf("  ");
            printf(" %s\n", ptr_token->string);

            ptr_token = ptr_token->next;
        }

        ptr = ptr->next;
    }

    return 0;
}
