
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "vm_functions.h"
#include "token.h"

s_token tokens_1[] = {
    {{0x04}, 5,             TOKEN_OP,                   ft_vm_functions_assign, "->"},

    {{0x0D}, 30,            TOKEN_FUNC,                 NULL,               "^2"},

    {{0x10}, 0,             TOKEN_PARENTHESIS_OPEN,     NULL,               "("},
    {{0x11}, 0,             TOKEN_PARENTHESIS_CLOSE,    NULL,               ")"}  ,

    {{0x2A}, 0,             TOKEN_DOUBLE_QUOTES,        NULL,               "\""},
    {{0x2B}, 0,             TOKEN_COMA,                 NULL,               ","},

    {{0x2D}, 30,            TOKEN_FUNC,                 NULL,               "!"},

    {{0x29}, 0,             TOKEN_OTHER,                NULL,               "' '"},
    {{0x30}, 0,             TOKEN_NUMBER,               NULL,               "0"},
    {{0x31}, 0,             TOKEN_NUMBER,               NULL,               "1"},
    {{0x32}, 0,             TOKEN_NUMBER,               NULL,               "2"},
    {{0x33}, 0,             TOKEN_NUMBER,               NULL,               "3"},
    {{0x34}, 0,             TOKEN_NUMBER,               NULL,               "4"},
    {{0x35}, 0,             TOKEN_NUMBER,               NULL,               "5"},
    {{0x36}, 0,             TOKEN_NUMBER,               NULL,               "6"},
    {{0x37}, 0,             TOKEN_NUMBER,               NULL,               "7"},
    {{0x38}, 0,             TOKEN_NUMBER,               NULL,               "8"},
    {{0x39}, 0,             TOKEN_NUMBER,               NULL,               "9"},

    {{0x3A}, 0,             TOKEN_OTHER,                NULL,               "."},

    {{0x3E}, 0,             TOKEN_OTHER,                NULL,               ":"},
    {{0x3F}, 0,             TOKEN_OTHER,                NULL,               ":"},

    {{0x41}, 0,             TOKEN_VAR,                  NULL,               "A"},
    {{0x42}, 0,             TOKEN_VAR,                  NULL,               "B"},
    {{0x43}, 0,             TOKEN_VAR,                  NULL,               "C"},
    {{0x44}, 0,             TOKEN_VAR,                  NULL,               "D"},
    {{0x45}, 0,             TOKEN_VAR,                  NULL,               "E"},
    {{0x46}, 0,             TOKEN_VAR,                  NULL,               "F"},
    {{0x47}, 0,             TOKEN_VAR,                  NULL,               "G"},
    {{0x48}, 0,             TOKEN_VAR,                  NULL,               "H"},
    {{0x49}, 0,             TOKEN_VAR,                  NULL,               "I"},
    {{0x4A}, 0,             TOKEN_VAR,                  NULL,               "J"},
    {{0x4B}, 0,             TOKEN_VAR,                  NULL,               "K"},
    {{0x4C}, 0,             TOKEN_VAR,                  NULL,               "L"},
    {{0x4D}, 0,             TOKEN_VAR,                  NULL,               "M"},
    {{0x4E}, 0,             TOKEN_VAR,                  NULL,               "N"},
    {{0x4F}, 0,             TOKEN_VAR,                  NULL,               "O"},
    {{0x50}, 0,             TOKEN_VAR,                  NULL,               "P"},
    {{0x51}, 0,             TOKEN_VAR,                  NULL,               "Q"},
    {{0x52}, 0,             TOKEN_VAR,                  NULL,               "R"},
    {{0x53}, 0,             TOKEN_VAR,                  NULL,               "S"},
    {{0x54}, 0,             TOKEN_VAR,                  NULL,               "T"},
    {{0x55}, 0,             TOKEN_VAR,                  NULL,               "U"},
    {{0x56}, 0,             TOKEN_VAR,                  NULL,               "V"},
    {{0x57}, 0,             TOKEN_VAR,                  NULL,               "W"},
    {{0x58}, 0,             TOKEN_VAR,                  NULL,               "X"},
    {{0x59}, 0,             TOKEN_VAR,                  NULL,               "Y"},
    {{0x5A}, 0,             TOKEN_VAR,                  NULL,               "Z"},
    {{0x5B}, 0,             TOKEN_VAR,                  NULL,               "0mega"},

    {{0x5D}, 0,             TOKEN_INCOMPLETE,           NULL,               "<incomplete>"},

    {{0x63}, 0,             TOKEN_INCOMPLETE,           NULL,               "<incomplete>"},

    {{0x6A}, 0,             TOKEN_OTHER,                NULL,               "="},
    {{0x6B}, 0,             TOKEN_OTHER,                NULL,               "<"},
    {{0x6C}, 0,             TOKEN_OTHER,                NULL,               ">"},

    {{0x6F}, 0,             TOKEN_OTHER,                NULL,               "!="},
    {{0x70}, 10,            TOKEN_OP,                   NULL,               "+"},
    {{0x71}, 10,            TOKEN_OP,                   NULL,               "-"},

    {{0x82}, 20,            TOKEN_OP,                   NULL,               "*"},
    {{0x83}, 20,            TOKEN_OP,                   NULL,               "/"},

    {{0x85}, 0,             TOKEN_FUNC,                 NULL,               "EffDessin"},

    {{0x93}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "Texte"},

    {{0x9C}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "Ligne"},
    {{0x9E}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "Pt-Aff"},
    {{0x9F}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "Pt-NAff"},

    {{0xB0}, 0,             TOKEN_FUNC,                 NULL,               "(-)"},
    {{0xB1}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "partEnt("},

    {{0xB5}, 0,             TOKEN_OTHER,                NULL,               "dim("},

    {{0xBA}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "partDec("},
    {{0xBB}, 0,             TOKEN_INCOMPLETE,           NULL,               "<incomplete>"},
    {{0xBC}, 0,             TOKEN_FUNC_WITH_PARAM,      NULL,               "sqrt("},

    {{0xCE}, 0,             TOKEN_OTHER,                NULL,               "If"},
    {{0xCF}, 0,             TOKEN_OTHER,                NULL,               "Then"},

    {{0xD0}, 0,             TOKEN_OTHER,                NULL,               "Else"},
    {{0xD1}, 0,             TOKEN_OTHER,                NULL,               "While"},

    {{0xD3}, 0,             TOKEN_OTHER,                NULL,               "For("},
    {{0xD4}, 0,             TOKEN_OTHER,                NULL,               "End"},

    {{0xD6}, 0,             TOKEN_OTHER,                NULL,               "Lbl"},
    {{0xD7}, 0,             TOKEN_OTHER,                NULL,               "Goto"},

    {{0xDC}, 0,             TOKEN_FUNC_WITH_PARAM,      ft_vm_functions_input,  "Input("},

    {{0xDE}, 0,             TOKEN_FUNC_WITH_PARAM,      ft_vm_functions_disp,   "Disp"},

    {{0xE1}, 0,             TOKEN_FUNC,                 ft_vm_functions_effecr, "EffEcr"},

    {{0xF0}, 30,            TOKEN_OP,                   NULL,               "^"},

    {{0xFF}, 0,             TOKEN_OTHER,                NULL,               "xx Error 1"},
};

s_token tokens_2[] = {
    {{0x5d, 0x00}, 0,       TOKEN_OTHER,                NULL,               "L1"},
    {{0x5d, 0x01}, 0,       TOKEN_OTHER,                NULL,               "L2"},

    {{0x63, 0x02}, 0,       TOKEN_OTHER,                NULL,               "Xgrad"},
    {{0x63, 0x03}, 0,       TOKEN_OTHER,                NULL,               "Ygrad"},
    {{0x63, 0x0A}, 0,       TOKEN_INCOMPLETE,           NULL,               "<incomplete>"},
    {{0x63, 0x0B}, 0,       TOKEN_OTHER,                NULL,               "Xmax"},
    {{0x63, 0x0C}, 0,       TOKEN_INCOMPLETE,           NULL,               "<incomplete>"},
    {{0x63, 0x0D}, 0,       TOKEN_OTHER,                NULL,               "Ymax"},

    {{0xBB, 0x0A}, 0,       TOKEN_OTHER,                NULL,               "entAleat("},

    {{0xFF, 0xFF}, 0,       TOKEN_OTHER,                NULL,               "xx Error 2"},
};

s_token tokens_3[] = {
    {{0x63, 0x0A, 0x3E}, 0, TOKEN_OTHER,                NULL,               "Xmin"},
    {{0x63, 0x0C, 0x3E}, 0, TOKEN_OTHER,                NULL,               "Ymin"},

    {{0xFF, 0xFF, 0xFF}, 0, TOKEN_OTHER,                NULL,               "xx Error 3"},
};

s_token *tokens_data[] = {
    tokens_1,
    tokens_2,
    tokens_3,
};


s_token *ft_token_next(unsigned char **code_ptr)
{
    int i = 0, byte_count = 0;
    unsigned char current_opcode[4] = "";
    s_token *token = NULL, *ret = NULL;

    do
    {
        current_opcode[byte_count] = **code_ptr;
        (*code_ptr) ++;

        for (i = 0; memcmp(tokens_data[byte_count][i].opcode, "\xFF", 1) != 0; ++i)
        {
            if (memcmp(tokens_data[byte_count][i].opcode, current_opcode, byte_count+1) == 0)
                break;
        }
        token = &tokens_data[byte_count][i];

        byte_count ++;
    } while (token->type == TOKEN_INCOMPLETE);

    ret = ft_calloc(sizeof(s_token));
    memcpy(ret, token, sizeof(s_token));
    memcpy(ret->opcode, current_opcode, 4);
    ret->string = strdup(token->string);

    return ret;
}


int ft_token_get_number(s_token *token)
{
    return token->opcode[0]-0x30;
}

e_var ft_token_get_var(s_token *token)
{
    return (token->opcode[0] - 0x41);
}

int ft_token_is_var_std(s_token *token)
{
    return ((token->opcode[0] >= 0x41) && (token->opcode[0] <= 0x5B));
}

