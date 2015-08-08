#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include "token.h"

typedef struct              _s_instruction
{
    s_token                 *tokens;
    struct _s_instruction   *next;
}                           s_instruction;

#endif
