
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "vm_functions.h"
#include "token.h"

s_token tokens_1[] = {
    {{0x04}, 5,             T_TYPE_OP,                   ft_vm_functions_assign,     "->"},

    {{0x0D}, 30,            T_TYPE_FUNC,                 NULL,                       "^2"},

    {{0x10}, 0,             T_TYPE_PARENTHESIS_OPEN,     NULL,                       "("},
    {{0x11}, 0,             T_TYPE_PARENTHESIS_CLOSE,    NULL,                       ")"}  ,

    {{0x2A}, 0,             T_TYPE_DOUBLE_QUOTES,        NULL,                       "\""},
    {{0x2B}, 0,             T_TYPE_COMA,                 NULL,                       ","},

    {{0x2D}, 30,            T_TYPE_FUNC,                 ft_vm_functions_fact,       "!"},

    {{0x29}, 0,             T_TYPE_OTHER,                NULL,                       "' '"},
    {{0x30}, 0,             T_TYPE_NUMBER,               NULL,                       "0"},
    {{0x31}, 0,             T_TYPE_NUMBER,               NULL,                       "1"},
    {{0x32}, 0,             T_TYPE_NUMBER,               NULL,                       "2"},
    {{0x33}, 0,             T_TYPE_NUMBER,               NULL,                       "3"},
    {{0x34}, 0,             T_TYPE_NUMBER,               NULL,                       "4"},
    {{0x35}, 0,             T_TYPE_NUMBER,               NULL,                       "5"},
    {{0x36}, 0,             T_TYPE_NUMBER,               NULL,                       "6"},
    {{0x37}, 0,             T_TYPE_NUMBER,               NULL,                       "7"},
    {{0x38}, 0,             T_TYPE_NUMBER,               NULL,                       "8"},
    {{0x39}, 0,             T_TYPE_NUMBER,               NULL,                       "9"},

    {{0x3A}, 0,             T_TYPE_NUMBER,               NULL,                       "."},

    {{0x3E}, 0,             T_TYPE_OTHER,                NULL,                       ":"},
    {{0x3F}, 0,             T_TYPE_OTHER,                NULL,                       ":"},

    {{0x41}, 0,             T_TYPE_VAR,                  NULL,                       "A"},
    {{0x42}, 0,             T_TYPE_VAR,                  NULL,                       "B"},
    {{0x43}, 0,             T_TYPE_VAR,                  NULL,                       "C"},
    {{0x44}, 0,             T_TYPE_VAR,                  NULL,                       "D"},
    {{0x45}, 0,             T_TYPE_VAR,                  NULL,                       "E"},
    {{0x46}, 0,             T_TYPE_VAR,                  NULL,                       "F"},
    {{0x47}, 0,             T_TYPE_VAR,                  NULL,                       "G"},
    {{0x48}, 0,             T_TYPE_VAR,                  NULL,                       "H"},
    {{0x49}, 0,             T_TYPE_VAR,                  NULL,                       "I"},
    {{0x4A}, 0,             T_TYPE_VAR,                  NULL,                       "J"},
    {{0x4B}, 0,             T_TYPE_VAR,                  NULL,                       "K"},
    {{0x4C}, 0,             T_TYPE_VAR,                  NULL,                       "L"},
    {{0x4D}, 0,             T_TYPE_VAR,                  NULL,                       "M"},
    {{0x4E}, 0,             T_TYPE_VAR,                  NULL,                       "N"},
    {{0x4F}, 0,             T_TYPE_VAR,                  NULL,                       "O"},
    {{0x50}, 0,             T_TYPE_VAR,                  NULL,                       "P"},
    {{0x51}, 0,             T_TYPE_VAR,                  NULL,                       "Q"},
    {{0x52}, 0,             T_TYPE_VAR,                  NULL,                       "R"},
    {{0x53}, 0,             T_TYPE_VAR,                  NULL,                       "S"},
    {{0x54}, 0,             T_TYPE_VAR,                  NULL,                       "T"},
    {{0x55}, 0,             T_TYPE_VAR,                  NULL,                       "U"},
    {{0x56}, 0,             T_TYPE_VAR,                  NULL,                       "V"},
    {{0x57}, 0,             T_TYPE_VAR,                  NULL,                       "W"},
    {{0x58}, 0,             T_TYPE_VAR,                  NULL,                       "X"},
    {{0x59}, 0,             T_TYPE_VAR,                  NULL,                       "Y"},
    {{0x5A}, 0,             T_TYPE_VAR,                  NULL,                       "Z"},
    {{0x5B}, 0,             T_TYPE_VAR,                  NULL,                       "0mega"},

    {{0x5D}, 0,             T_TYPE_INCOMPLETE,           NULL,                       "<incomplete>"},

    {{0x63}, 0,             T_TYPE_INCOMPLETE,           NULL,                       "<incomplete>"},

    {{0x6A}, 2,             T_TYPE_OP,                   ft_vm_functions_equal,      "="},
    {{0x6B}, 2,             T_TYPE_OP,                   ft_vm_functions_lower,      "<"},
    {{0x6C}, 2,             T_TYPE_OP,                   ft_vm_functions_greater,    ">"},

    {{0x6F}, 2,             T_TYPE_OP,                   ft_vm_functions_not_equal,  "!="},
    {{0x70}, 10,            T_TYPE_OP,                   ft_vm_functions_add,        "+"},
    {{0x71}, 10,            T_TYPE_OP,                   ft_vm_functions_add,        "-"},

    {{0x82}, 20,            T_TYPE_OP,                   ft_vm_functions_mul,        "*"},
    {{0x83}, 20,            T_TYPE_OP,                   ft_vm_functions_div,        "/"},

    {{0x85}, 0,             T_TYPE_FUNC,                 ft_vm_functions_effdessin,  "EffDessin"},

    {{0x93}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_text,       "Texte"},

    {{0x9C}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_line,       "Ligne("},
    {{0x9E}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_ptaff,      "Pt-Aff"},
    {{0x9F}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_ptnaff,     "Pt-NAff"},

    {{0xB0}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_neg,        "(-)"},
    {{0xB1}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_partent,    "partEnt("},

    {{0xB5}, 0,             T_TYPE_OTHER,                NULL,                       "dim("},

    {{0xBA}, 0,             T_TYPE_FUNC_WITH_PARAM,      NULL,                       "partDec("},
    {{0xBB}, 0,             T_TYPE_INCOMPLETE,           NULL,                       "<incomplete>"},
    {{0xBC}, 0,             T_TYPE_FUNC_WITH_PARAM,      NULL,                       "sqrt("},

    {{0xCE}, 1,             T_TYPE_TEST,                 ft_vm_functions_if,         "If"},
    {{0xCF}, 1,             T_TYPE_TEST,                 NULL,                       "Then"},

    {{0xD0}, 1,             T_TYPE_TEST,                 NULL,                       "Else"},
    {{0xD1}, 1,             T_TYPE_TEST,                 ft_vm_functions_while,      "While"},

    {{0xD3}, 1,             T_TYPE_TEST,                 ft_vm_functions_for,        "For("},
    {{0xD4}, 1,             T_TYPE_TEST,                 NULL,                       "End"},

    {{0xD6}, 0,             T_TYPE_OTHER,                NULL,                       "Lbl"},
    {{0xD7}, 0,             T_TYPE_OTHER,                NULL,                       "Goto"},

    {{0xDC}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_input,      "Input("},

    {{0xDE}, 0,             T_TYPE_FUNC_WITH_PARAM,      ft_vm_functions_disp,       "Disp"},

    {{0xE1}, 0,             T_TYPE_FUNC,                 ft_vm_functions_effecr,     "EffEcr"},

    {{0xF0}, 30,            T_TYPE_OP,                   NULL,                       "^"},

    {{0xFF}, 0,             T_TYPE_OTHER,                NULL,                       "xx Error 1"},
};

s_token tokens_2[] = {
    {{0x5d, 0x00}, 0,       T_TYPE_OTHER,                NULL,                       "L1"},
    {{0x5d, 0x01}, 0,       T_TYPE_OTHER,                NULL,                       "L2"},

    {{0x63, 0x02}, 0,       T_TYPE_VAR,                  NULL,                       "Xgrad"},
    {{0x63, 0x03}, 0,       T_TYPE_VAR,                  NULL,                       "Ygrad"},
    {{0x63, 0x0A}, 0,       T_TYPE_VAR,                  NULL,                       "Xmin"},
    {{0x63, 0x0B}, 0,       T_TYPE_VAR,                  NULL,                       "Xmax"},
    {{0x63, 0x0C}, 0,       T_TYPE_VAR,                  NULL,                       "Ymin"},
    {{0x63, 0x0D}, 0,       T_TYPE_VAR,                  NULL,                       "Ymax"},

    {{0xBB, 0x0A}, 0,       T_TYPE_OTHER,                NULL,                       "entAleat("},

    {{0xFF, 0xFF}, 0,       T_TYPE_OTHER,                NULL,                       "xx Error 2"},
};

s_token *tokens_data[] = {
    tokens_1,
    tokens_2,
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
    } while (token->type == T_TYPE_INCOMPLETE);

    ret = ft_calloc(sizeof(s_token));
    memcpy(ret, token, sizeof(s_token));
    memcpy(ret->opcode, current_opcode, 4);
    ret->string = strdup(token->string);

    return ret;
}


int ft_token_get_number(s_token *token)
{
    if ((token->opcode[0] >= T_OPCODE_N_0) && (token->opcode[0] <= T_OPCODE_N_9))
        return token->opcode[0] - T_OPCODE_N_0;
    else if (token->opcode[0] == T_OPCODE_DOT)
        return -1;

    ft_abort("int not found");
    return 0; /* silent waarning */
}

e_var ft_token_get_var(s_token *token)
{
    if ((token->opcode[0] >= T_OPCODE_V_A) && (token->opcode[0] <= T_OPCODE_V_OMEGA))
       return (token->opcode[0] - T_OPCODE_V_A);
    else if (token->opcode[0] == T_OPCODE_INCOMPLETE_2)
    {
        switch (token->opcode[1])
        {
            case 0x02:
                return VAR_XGRAD;
                break;
            case 0x03:
                return VAR_YGRAD;
                break;
            case 0x0A:
                return VAR_XMIN;
                break;
            case 0x0B:
                return VAR_XMAX;
                break;
            case 0x0C:
                return VAR_YMIN;
                break;
            case 0x0D:
                return VAR_YMAX;
                break;
        }
    }

    ft_abort("var not found");
    return VAR_A; /* silent waarning */
}

char *letters[] = {
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z"
};

char *ft_var_get_str(e_var var)
{
    if ((var >= VAR_A) && (var <= VAR_Z))
        return letters[var];
    else if (var == VAR_OMEGA)
        return "Omega";
    else
    {
        switch (var)
        {
            case VAR_XGRAD:
                return "Xgrad";
                break;
            case VAR_YGRAD:
                return "Ygrad";
                break;
            case VAR_XMIN:
                return "Xmin";
                break;
            case VAR_XMAX:
                return "Xmax";
                break;
            case VAR_YMIN:
                return "Ymin";
                break;
            case VAR_YMAX:
                return "Ymax";
                break;
            default:
                /* silent warning */
                break;
        }
    }

    ft_abort("var not found");
    return ""; /* silent waarning */
}


s_token *ft_token_get(unsigned char opcode)
{
    int i = 0;

    do {
        i ++;
    } while(tokens_data[0][i].opcode[0] != opcode);

    return &tokens_data[0][i];
}
