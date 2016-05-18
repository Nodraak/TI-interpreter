#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

#include "token.h"

typedef char pxl;

typedef struct          _s_vm
{
    double              vars[VAR_LAST];
    double              ret;
    pxl                 screen[63][95];
}                       s_vm;

extern s_vm vm;

void ft_vm_execute_code(s_instruction *ptr_code);
void ft_vm_execute_instruction(s_param *ptr);
void ft_vm_refresh_screen(void);

#endif
