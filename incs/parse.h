#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

s_param *parse_int(s_token **tokens, int length);
s_param *parse_str(s_token **tokens, int length);
s_param *parse_var(s_token **tokens, int length);
s_param *parse_func(s_token **tokens, int length);
s_param *parse_func_with_param(s_token *func, s_token **tokens, int length);
s_param *parse_op(s_token **tokens, int length, int index);
s_param *parse_make_function(s_token *token, int ac, s_param **av);

#endif
