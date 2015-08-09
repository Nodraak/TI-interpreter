
#include <stdlib.h>
#include <string.h>

#include "token.h"

s_token tokens_1[] = {
    {{0x04}, 5, TOKEN_OP, "->"},

    {{0x0D}, 30, TOKEN_FUNC, "^2"},

    {{0x10}, 0, TOKEN_OTHER, "("},
    {{0x11}, 0, TOKEN_OTHER, ")"},

    {{0x2A}, 0, TOKEN_OTHER, "\""},
    {{0x2B}, 0, TOKEN_OTHER, ","},

    {{0x2D}, 30, TOKEN_FUNC, "!"},

    {{0x29}, 0, TOKEN_OTHER, "' '"},
    {{0x30}, 0, TOKEN_INT, "0"},
    {{0x31}, 0, TOKEN_INT, "1"},
    {{0x32}, 0, TOKEN_INT, "2"},
    {{0x33}, 0, TOKEN_INT, "3"},
    {{0x34}, 0, TOKEN_INT, "4"},
    {{0x35}, 0, TOKEN_INT, "5"},
    {{0x36}, 0, TOKEN_INT, "6"},
    {{0x37}, 0, TOKEN_INT, "7"},
    {{0x38}, 0, TOKEN_INT, "8"},
    {{0x39}, 0, TOKEN_INT, "9"},

    {{0x3A}, 0, TOKEN_OTHER, "."},

    {{0x3E}, 0, TOKEN_OTHER, ": (maybe)"},
    {{0x3F}, 0, TOKEN_OTHER, ":"},

    {{0x41}, 0, TOKEN_VAR, "A"},
    {{0x42}, 0, TOKEN_VAR, "B"},
    {{0x43}, 0, TOKEN_VAR, "C"},
    {{0x44}, 0, TOKEN_VAR, "D"},
    {{0x45}, 0, TOKEN_VAR, "E"},
    {{0x46}, 0, TOKEN_VAR, "F"},
    {{0x47}, 0, TOKEN_VAR, "G"},
    {{0x48}, 0, TOKEN_VAR, "H"},
    {{0x49}, 0, TOKEN_VAR, "I"},
    {{0x4A}, 0, TOKEN_VAR, "J"},
    {{0x4B}, 0, TOKEN_VAR, "K"},
    {{0x4C}, 0, TOKEN_VAR, "L"},
    {{0x4D}, 0, TOKEN_VAR, "M"},
    {{0x4E}, 0, TOKEN_VAR, "N"},
    {{0x4F}, 0, TOKEN_VAR, "O"},
    {{0x50}, 0, TOKEN_VAR, "P"},
    {{0x51}, 0, TOKEN_VAR, "Q"},
    {{0x52}, 0, TOKEN_VAR, "R"},
    {{0x53}, 0, TOKEN_VAR, "S"},
    {{0x54}, 0, TOKEN_VAR, "T"},
    {{0x55}, 0, TOKEN_VAR, "U"},
    {{0x56}, 0, TOKEN_VAR, "V"},
    {{0x57}, 0, TOKEN_VAR, "W"},
    {{0x58}, 0, TOKEN_VAR, "X"},
    {{0x59}, 0, TOKEN_VAR, "Y"},
    {{0x5A}, 0, TOKEN_VAR, "Z"},
    {{0x5B}, 0, TOKEN_VAR, "0mega"},

    {{0x5D}, 0, TOKEN_INCOMPLETE, "<incomplete>"},

    {{0x63}, 0, TOKEN_INCOMPLETE, "<incomplete>"},

    {{0x6A}, 0, TOKEN_OTHER, "="},
    {{0x6B}, 0, TOKEN_OTHER, "<"},
    {{0x6C}, 0, TOKEN_OTHER, ">"},

    {{0x6F}, 0, TOKEN_OTHER, "!="},
    {{0x70}, 10, TOKEN_OP, "+"},
    {{0x71}, 10, TOKEN_OP, "-"},

    {{0x82}, 20, TOKEN_OP, "*"},
    {{0x83}, 20, TOKEN_OP, "/"},

    {{0x85}, 0, TOKEN_FUNC, "EffDessin"},

    {{0x93}, 0, TOKEN_FUNC_WITH_PARAM, "Texte"},

    {{0x9C}, 0, TOKEN_FUNC_WITH_PARAM, "Ligne"},
    {{0x9E}, 0, TOKEN_FUNC_WITH_PARAM, "Pt-Aff"},
    {{0x9F}, 0, TOKEN_FUNC_WITH_PARAM, "Pt-NAff"},

    {{0xB0}, 0, TOKEN_FUNC, "(-)"},
    {{0xB1}, 0, TOKEN_FUNC_WITH_PARAM, "partEnt("},

    {{0xB5}, 0, TOKEN_OTHER, "dim("},

    {{0xBA}, 0, TOKEN_FUNC_WITH_PARAM, "partDec("},
    {{0xBB}, 0, TOKEN_INCOMPLETE, "<incomplete>"},
    {{0xBC}, 0, TOKEN_FUNC_WITH_PARAM, "sqrt("},

    {{0xCE}, 0, TOKEN_OTHER, "If"},
    {{0xCF}, 0, TOKEN_OTHER, "Then"},

    {{0xD0}, 0, TOKEN_OTHER, "Else"},
    {{0xD1}, 0, TOKEN_OTHER, "While"},

    {{0xD3}, 0, TOKEN_OTHER, "For("},
    {{0xD4}, 0, TOKEN_OTHER, "End"},

    {{0xD6}, 0, TOKEN_OTHER, "Lbl"},
    {{0xD7}, 0, TOKEN_OTHER, "Goto"},

    {{0xDC}, 0, TOKEN_FUNC_WITH_PARAM, "Input("},

    {{0xDE}, 0, TOKEN_FUNC_WITH_PARAM, "Disp"},

    {{0xE1}, 0, TOKEN_FUNC, "EffEcr"},

    {{0xF0}, 30, TOKEN_OP, "^"},

    {{0xFF}, 0, TOKEN_OTHER, "xx Error 1"},
};

s_token tokens_2[] = {
    {{0x5d, 0x00}, 0, TOKEN_OTHER, "L1"},
    {{0x5d, 0x01}, 0, TOKEN_OTHER, "L2"},

    {{0x63, 0x02}, 0, TOKEN_OTHER, "Xgrad"},
    {{0x63, 0x03}, 0, TOKEN_OTHER, "Ygrad"},
    {{0x63, 0x0A}, 0, TOKEN_INCOMPLETE, "<incomplete>"},
    {{0x63, 0x0B}, 0, TOKEN_OTHER, "Xmax"},
    {{0x63, 0x0C}, 0, TOKEN_INCOMPLETE, "<incomplete>"},
    {{0x63, 0x0D}, 0, TOKEN_OTHER, "Ymax"},

    {{0xBB, 0x0A}, 0, TOKEN_OTHER, "entAleat("},

    {{0xFF, 0xFF}, 0, TOKEN_OTHER, "xx Error 2"},
};

s_token tokens_3[] = {
    {{0x63, 0x0A, 0x3E}, 0, TOKEN_OTHER, "Xmin"},
    {{0x63, 0x0C, 0x3E}, 0, TOKEN_OTHER, "Ymin"},

    {{0xFF, 0xFF, 0xFF}, 0, TOKEN_OTHER, "xx Error 3"},
};

s_token *tokens_data[] = {
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

        for (i = 0; strcmp(tokens_data[byte_count][i].opcode, "\xFF") != 0; ++i)
        {
            if (strcmp(tokens_data[byte_count][i].opcode, current_opcode) == 0)
                break;
        }
        token = &tokens_data[byte_count][i];

        byte_count ++;
    } while (token->type == TOKEN_INCOMPLETE);

    ret = malloc(sizeof(s_token));
    if (ret == NULL)
        ft_abort("malloc");
    memcpy(ret, token, sizeof(s_token));

    memcpy(ret->opcode, current_opcode, 4);
    ret->string = strdup(token->string);

    return ret;
}
