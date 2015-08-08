
#include <stdlib.h>
#include <string.h>

#include "token.h"

s_token tokens_1[] = {
    {{0x04}, 0, "[asig] ->", NULL},

    {{0x0D}, 0, "[math] ^2", NULL},

    {{0x10}, 0, "[    ] (", NULL},
    {{0x11}, 0, "[    ] )", NULL},

    {{0x2A}, 0, "[    ] \"", NULL},
    {{0x2B}, 0, "[    ] ,", NULL},

    {{0x2D}, 0, "[    ] !", NULL},

    {{0x29}, 0, "[    ] ' '", NULL},
    {{0x30}, 0, "[int ] 0", NULL},
    {{0x31}, 0, "[int ] 1", NULL},
    {{0x32}, 0, "[int ] 2", NULL},
    {{0x33}, 0, "[int ] 3", NULL},
    {{0x34}, 0, "[int ] 4", NULL},
    {{0x35}, 0, "[int ] 5", NULL},
    {{0x36}, 0, "[int ] 6", NULL},
    {{0x37}, 0, "[int ] 7", NULL},
    {{0x38}, 0, "[int ] 8", NULL},
    {{0x39}, 0, "[int ] 9", NULL},

    {{0x3A}, 0, "[    ] .", NULL},

    {{0x3E}, 0, "[ctrl] maybe : <<---", NULL},
    {{0x3F}, 0, "[ctrl] :", NULL},

    {{0x41}, 0, "[var ] A", NULL},
    {{0x42}, 0, "[var ] B", NULL},
    {{0x43}, 0, "[var ] C", NULL},
    {{0x44}, 0, "[var ] D", NULL},
    {{0x45}, 0, "[var ] E", NULL},
    {{0x46}, 0, "[var ] F", NULL},
    {{0x47}, 0, "[var ] G", NULL},
    {{0x48}, 0, "[var ] H", NULL},
    {{0x49}, 0, "[var ] I", NULL},
    {{0x4A}, 0, "[var ] J", NULL},
    {{0x4B}, 0, "[var ] K", NULL},
    {{0x4C}, 0, "[var ] L", NULL},
    {{0x4D}, 0, "[var ] M", NULL},
    {{0x4E}, 0, "[var ] N", NULL},
    {{0x4F}, 0, "[var ] O", NULL},
    {{0x50}, 0, "[var ] P", NULL},
    {{0x51}, 0, "[var ] Q", NULL},
    {{0x52}, 0, "[var ] R", NULL},
    {{0x53}, 0, "[var ] S", NULL},
    {{0x54}, 0, "[var ] T", NULL},
    {{0x55}, 0, "[var ] U", NULL},
    {{0x56}, 0, "[var ] V", NULL},
    {{0x57}, 0, "[var ] W", NULL},
    {{0x58}, 0, "[var ] X", NULL},
    {{0x59}, 0, "[var ] Y", NULL},
    {{0x5A}, 0, "[var ] Z", NULL},
    {{0x5B}, 0, "[var ] Omage", NULL},

    {{0x5D}, 1, "x", NULL},

    {{0x63}, 1, "x", NULL},

    {{0x6A}, 0, "[test] =", NULL},
    {{0x6B}, 0, "[test] <", NULL},
    {{0x6C}, 0, "[test] >", NULL},

    {{0x6F}, 0, "[test] !=", NULL},
    {{0x70}, 0, "[math] +", NULL},
    {{0x71}, 0, "[math] -", NULL},

    {{0x82}, 0, "[math] *", NULL},
    {{0x83}, 0, "[math] /", NULL},

    {{0x85}, 0, "[ io ] EffDessin", NULL},

    {{0x93}, 0, "[ io ] Texte", NULL},

    {{0x9C}, 0, "[ io ] Ligne", NULL},
    {{0x9E}, 0, "[ io ] Pt-Aff", NULL},
    {{0x9F}, 0, "[ io ] Pt-NAff", NULL},

    {{0xB0}, 0, "[math] (-)", NULL},
    {{0xB1}, 0, "[func] partEnt(", NULL},

    {{0xB5}, 0, "[func] dim(", NULL},

    {{0xBA}, 0, "[func] partDec(", NULL},
    {{0xBB}, 1, "x", NULL},
    {{0xBC}, 0, "[func] sqrt(", NULL},

    {{0xCE}, 0, "[ctrl] If", NULL},
    {{0xCF}, 0, "[ctrl] Then", NULL},

    {{0xD0}, 0, "[ctrl] Else", NULL},
    {{0xD1}, 0, "[ctrl] While", NULL},

    {{0xD3}, 0, "[ctrl] For(", NULL},
    {{0xD4}, 0, "[ctrl] End", NULL},

    {{0xD6}, 0, "[ctrl] Lbl", NULL},
    {{0xD7}, 0, "[ctrl] Goto", NULL},

    {{0xDC}, 0, "[ io ] Input", NULL},

    {{0xDE}, 0, "[ io ] Disp", NULL},

    {{0xE1}, 0, "[ io ] EffEcr", NULL},

    {{0xF0}, 0, "[    ] ^", NULL},

    {{0xFF}, 0, "[ xx ] xx Error 1", NULL},
};

s_token tokens_2[] = {
    {{0x5d, 0x00}, 0, "[var ] L1", NULL},
    {{0x5d, 0x01}, 0, "[var ] L2", NULL},

    {{0x63, 0x02}, 0, "[win ] Xgrad", NULL},
    {{0x63, 0x03}, 0, "[win ] Ygrad", NULL},
    {{0x63, 0x0A}, 1, "x", NULL},
    {{0x63, 0x0B}, 0, "[win ] Xmax", NULL},
    {{0x63, 0x0C}, 1, "x", NULL},
    {{0x63, 0x0D}, 0, "[win ] Ymax", NULL},

    {{0xBB, 0x0A}, 0, "[func] entAleat(", NULL},

    {{0xFF, 0xFF}, 0, "[ xx ] xx Error 2", NULL},
};

s_token tokens_3[] = {
    {{0x63, 0x0A, 0x3E}, 0, "[win ] Xmin", NULL},
    {{0x63, 0x0C, 0x3E}, 0, "[win ] Ymin", NULL},

    {{0xFF, 0xFF, 0xFF}, 0, "[ xx ] xx Error 3", NULL},
};

s_token *tokens[] = {
    tokens_1,
    tokens_2,
    tokens_3,
};


s_token *ft_token_next(char **code_ptr)
{
    int i = 0, byte_count = 0;
    char current_opcode[4] = "";
    s_token *token = NULL, *ret = NULL;

    do
    {
        current_opcode[byte_count] = **code_ptr;
        (*code_ptr) ++;

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

