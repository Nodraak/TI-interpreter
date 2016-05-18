#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

typedef enum    _e_t_type_opcode
{
    T_OPCODE_ASSIGN         = 0x04,
    T_OPCODE_POW_2          = 0x0D,
    T_OPCODE_PARENTHESIS_OPEN   = 0x10,
    T_OPCODE_PARENTHESIS_CLOSE  = 0x11,
    T_OPCODE_DOUBLE_QUOTES  = 0x2A,
    T_OPCODE_COMA           = 0x2B,
    T_OPCODE_FACT           = 0x2D,
    T_OPCODE_SPACE          = 0x29,
    T_OPCODE_N_0            = 0x30,
    T_OPCODE_N_1            = 0x31,
    T_OPCODE_N_2            = 0x32,
    T_OPCODE_N_3            = 0x33,
    T_OPCODE_N_4            = 0x34,
    T_OPCODE_N_5            = 0x35,
    T_OPCODE_N_6            = 0x36,
    T_OPCODE_N_7            = 0x37,
    T_OPCODE_N_8            = 0x38,
    T_OPCODE_N_9            = 0x39,
    T_OPCODE_DOT            = 0x3A,
    T_OPCODE_EOI_1          = 0x3E,
    T_OPCODE_EOI_2          = 0x3F,
    T_OPCODE_V_A            = 0x41,
    T_OPCODE_V_B            = 0x42,
    T_OPCODE_V_C            = 0x43,
    T_OPCODE_V_D            = 0x44,
    T_OPCODE_V_E            = 0x45,
    T_OPCODE_V_F            = 0x46,
    T_OPCODE_V_G            = 0x47,
    T_OPCODE_V_H            = 0x48,
    T_OPCODE_V_I            = 0x49,
    T_OPCODE_V_J            = 0x4A,
    T_OPCODE_V_K            = 0x4B,
    T_OPCODE_V_L            = 0x4C,
    T_OPCODE_V_M            = 0x4D,
    T_OPCODE_V_N            = 0x4E,
    T_OPCODE_V_O            = 0x4F,
    T_OPCODE_V_P            = 0x50,
    T_OPCODE_V_Q            = 0x51,
    T_OPCODE_V_R            = 0x52,
    T_OPCODE_V_S            = 0x53,
    T_OPCODE_V_T            = 0x54,
    T_OPCODE_V_U            = 0x55,
    T_OPCODE_V_V            = 0x56,
    T_OPCODE_V_W            = 0x57,
    T_OPCODE_V_X            = 0x58,
    T_OPCODE_V_Y            = 0x59,
    T_OPCODE_V_Z            = 0x5A,
    T_OPCODE_V_OMEGA        = 0x5B,
    T_OPCODE_INCOMPLETE_1   = 0x5D,
    T_OPCODE_INCOMPLETE_2   = 0x63,
    T_OPCODE_EQUAL          = 0x6A,
    T_OPCODE_LOWER          = 0x6B,
    T_OPCODE_GREATER        = 0x6C,
    T_OPCODE_DIFF           = 0x6F,
    T_OPCODE_ADD            = 0x70,
    T_OPCODE_SUB            = 0x71,
    T_OPCODE_MUL            = 0x82,
    T_OPCODE_DIV            = 0x83,
    T_OPCODE_EFFDESSIN      = 0x85,
    T_OPCODE_TEXT           = 0x93,
    T_OPCODE_LINE           = 0x9C,
    T_OPCODE_PTAFF          = 0x9E,
    T_OPCODE_PTNAFF         = 0x9F,
    T_OPCODE_MINUS          = 0xB0,
    T_OPCODE_PARTENT        = 0xB1,
    T_OPCODE_DIM            = 0xB5,
    T_OPCODE_PARTDEC        = 0xBA,
    T_OPCODE_INCOMPLETE_3   = 0xBB,
    T_OPCODE_SQRT           = 0xBC,
    T_OPCODE_IF             = 0xCE,
    T_OPCODE_THEN           = 0xCF,
    T_OPCODE_ELSE           = 0xD0,
    T_OPCODE_WHILE          = 0xD1,
    T_OPCODE_FOR            = 0xD3,
    T_OPCODE_END            = 0xD4,
    T_OPCODE_LBL            = 0xD6,
    T_OPCODE_GOTO           = 0xD7,
    T_OPCODE_INPUT          = 0xDC,
    T_OPCODE_DISP           = 0xDE,
    T_OPCODE_EFFECR         = 0xE1,
    T_OPCODE_POW            = 0xF0
}
                e_t_type_opcode;

/*
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
*/


typedef enum    _e_t_type_type
{
    T_TYPE_NUMBER,               /* 0-9 */
    T_TYPE_VAR,                  /* A-Z + Omega */
    T_TYPE_FUNC,                 /* ex: EffEcr() */
    T_TYPE_FUNC_WITH_PARAM,      /* ex: Input(...) */
    T_TYPE_OP,                   /* ex: +, *, -> */
    T_TYPE_TEST,                 /* if, else, ... (=, >, ... are OP) */
    T_TYPE_INCOMPLETE,

    T_TYPE_PARENTHESIS_OPEN,
    T_TYPE_PARENTHESIS_CLOSE,
    T_TYPE_DOUBLE_QUOTES,
    T_TYPE_COMA,

    T_TYPE_OTHER,
    T_TYPE_UNKNOWN
}               e_t_type_type;


typedef enum    _e_var
{
    VAR_A,
    VAR_B,
    VAR_C,
    VAR_D,
    VAR_E,
    VAR_F,
    VAR_G,
    VAR_H,
    VAR_I,
    VAR_J,
    VAR_K,
    VAR_L,
    VAR_M,
    VAR_N,
    VAR_O,
    VAR_P,
    VAR_Q,
    VAR_R,
    VAR_S,
    VAR_T,
    VAR_U,
    VAR_V,
    VAR_W,
    VAR_X,
    VAR_Y,
    VAR_Z,
    VAR_OMEGA,

    VAR_XMIN,
    VAR_XMAX,
    VAR_XGRAD,
    VAR_YMIN,
    VAR_YMAX,
    VAR_YGRAD,

    VAR_LAST
}               e_var;

typedef struct _s_param s_param; /* prevent circular include */

typedef void (*vm_function) (int ac, s_param *av[]);

typedef struct      _s_token
{
    unsigned char   opcode[4];
    int             priority; /* operator priority */
    e_t_type_type    type;
    vm_function     callback; /* for functions */
    char            *string;
}                   s_token;

/*
priority:
    1 if while (special too)
    2 != > (special)

    5 ->
    10 + -
    20 * /
    30 ^ !
*/

extern s_token *tokens[];

s_token *ft_token_next(unsigned char **code_ptr);

int ft_token_get_number(s_token *token);
e_var ft_token_get_var(s_token *token);
char *ft_var_get_str(e_var var);
s_token *ft_token_get(unsigned char opcode);

#endif
