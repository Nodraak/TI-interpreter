
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct  _s_token
{
    char        *opcode;
    int         read_further;
    char        *string;
}               s_token;


s_token tokens_1[] = {
    {"\x00", 0, "[ xx ] XX Unknow (EOP ?)"},

    {"\x04", 0, "[asig] ->"},

    {"\x10", 0, "[    ] ("},
    {"\x11", 0, "[    ] )"},

    {"\x2A", 0, "[    ] \""},
    {"\x2B", 0, "[    ] ,"},

    {"\x30", 0, "[int ] 0"},
    {"\x31", 0, "[int ] 1"},
    {"\x32", 0, "[int ] 2"},
    {"\x33", 0, "[int ] 3"},
    {"\x34", 0, "[int ] 4"},
    {"\x35", 0, "[int ] 5"},
    {"\x36", 0, "[int ] 6"},
    {"\x37", 0, "[int ] 7"},
    {"\x38", 0, "[int ] 8"},
    {"\x39", 0, "[int ] 9"},

    {"\x3F", 0, "[ctrl] :"},

    {"\x41", 0, "[var ] A"},
    {"\x42", 0, "[var ] B"},
    {"\x43", 0, "[var ] C"},
    {"\x44", 0, "[var ] D"},
    {"\x45", 0, "[var ] E"},
    {"\x46", 0, "[var ] F"},
    {"\x47", 0, "[var ] G"},
    {"\x48", 0, "[var ] H"},
    {"\x49", 0, "[var ] I"},
    {"\x4A", 0, "[var ] J"},
    {"\x4B", 0, "[var ] K"},
    {"\x4C", 0, "[var ] L"},
    {"\x4D", 0, "[var ] M"},
    {"\x4E", 0, "[var ] N"},
    {"\x4F", 0, "[var ] O"},
    {"\x50", 0, "[var ] P"},
    {"\x51", 0, "[var ] Q"},
    {"\x52", 0, "[var ] R"},
    {"\x53", 0, "[var ] S"},
    {"\x54", 0, "[var ] T"},
    {"\x55", 0, "[var ] U"},
    {"\x56", 0, "[var ] V"},
    {"\x57", 0, "[var ] W"},
    {"\x58", 0, "[var ] X"},
    {"\x59", 0, "[var ] Y"},
    {"\x5A", 0, "[var ] Z"},

    {"\x5D", 1, "x"},

    {"\x63", 1, "x"},

    {"\x85", 0, "[ io ] EffDessin"},

    {"\x9E", 0, "[ io ] Pt-Aff"},

    {"\xB5", 0, "[func] dim("},

    {"\xBB", 1, "x"},

    {"\xCF", 0, "[ctrl] Then"},

    {"\xD1", 0, "[ctrl] While"},

    {"\xD3", 0, "[ctrl] For("},
    {"\xD4", 0, "[ctrl] End"},

    {"\xDE", 0, "[ io ] Disp"},

    {"\xFF", 0, "[ xx ] xx Error 1"},
};

s_token tokens_2[] = {
    {"\x5d\x00", 0, "[var ] L1"},
    {"\x5d\x01", 0, "[var ] L2"},

    {"\x63\x02", 0, "[win ] Xgrad"},
    {"\x63\x03", 0, "[win ] Ygrad"},
    {"\x63\x0A", 1, "x"},
    {"\x63\x0B", 0, "[win ] Xmax"},
    {"\x63\x0C", 1, "x"},
    {"\x63\x0D", 0, "[win ] Ymax"},

    {"\xBB\x0A", 0, "[func] entAleat("},

    {"\xFF", 0, "[ xx ] xx Error 2"},
};

s_token tokens_3[] = {
    {"\x63\x0A\x3E", 0, "[win ] Xmin"},
    {"\x63\x0C\x3E", 0, "[win ] Ymin"},

    {"\xFF", 0, "[ xx ] xx Error 3"},
};

s_token *tokens[] = {
    tokens_1,
    tokens_2,
    tokens_3,
};


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


s_token *ft_get_next_token(FILE *f)
{
    int i = 0, byte_count = 0;
    char opcode[4] = "";
    s_token *token = NULL, *ret = NULL;

    do
    {
        fread(&opcode[byte_count], 1, 1, f);

        for (i = 0; strcmp(tokens[byte_count][i].opcode, "\xFF") != 0; ++i)
        {
            if (strcmp(tokens[byte_count][i].opcode, opcode) == 0)
                break;
        }
        token = &tokens[byte_count][i];

        byte_count ++;
    } while (token->read_further);

    ret = malloc(sizeof(s_token));
    if (ret == NULL)
        ft_abort("malloc");

    ret->opcode = strdup(opcode);
    ret->read_further = byte_count;
    ret->string = strdup(token->string);

    return ret;
}


int main(void)
{
    // char file[] = "data/AATEST.8Xp";
    char file[] = "data/ABC.8Xp";
    char buf[1024];
    FILE *f = NULL;

    f = fopen(file, "r");
    if (f == NULL)
        ft_abort("fopen");

    ft_fread(buf, 8, f);
    printf("file type: %s\n", buf);

    ft_fread(buf, 3, f); /* unknown */

    ft_fread(buf, 40, f);
    printf("date: %s\n", buf);

    ft_fread(buf, 9, f); /* unknown */

    ft_fread(buf, 6, f);
    printf("name: %s\n", buf);

    ft_fread(buf, 8, f); /* unknown */

    printf("----------\n");

    while (!feof(f))
    {
        s_token *token = ft_get_next_token(f);

        int i;
        for (i = 0; i < token->read_further; ++i)
            printf("%02x", (unsigned char)token->opcode[i]);
        for (; i < 3; ++i)
            printf("  ");
        printf(" %s\n", token->string);

        free(token->opcode);
        free(token->string);
        free(token);
    }

    return 0;
}

