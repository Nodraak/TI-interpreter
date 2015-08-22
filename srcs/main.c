
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "8xp.h"
#include "utils.h"
#include "token.h"
#include "instruction.h"
#include "vm.h"
#include "debug.h"



char *program[] = {
    "data/AATEST.8Xp",
    "data/ABC.8Xp",
    "data_save/BASE.8Xp",
    "data/WTC.8Xp",
};


int main(void)
{
    unsigned char *raw_code = NULL;
    int code_length;
    s_instruction *code = NULL;

    printf("\n---------------------------------------- Read code:\n\n");
    raw_code = ft_8xp_read_code(program[2], &code_length);

    printf("\n---------------------------------------- Parse code:\n\n");
    code = ft_8xp_parse_code(raw_code, code_length);

    printf("\n---------------------------------------- Printf1 code:\n\n");
    ft_print_code(code, 0);

    printf("\n---------------------------------------- Parse conditions:\n\n");
    code = ft_8xp_parse_conditions(&code);

    printf("\n---------------------------------------- Printf2 code:\n\n");
    ft_print_code(code, 0);

    printf("\n---------------------------------------- Execute code:\n\n");
    ft_vm_execute_code(code);

    return 0;
}
