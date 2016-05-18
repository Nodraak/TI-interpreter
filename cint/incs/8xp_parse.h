#ifndef EIGHTXP_PARSE_H_INCLUDED
#define EIGHTXP_PARSE_H_INCLUDED

s_param *ft_8xp_parse_number(s_token **tokens, int length);
s_param *ft_8xp_parse_str(s_token **tokens, int length);
s_param *ft_8xp_parse_var(s_token **tokens, int length);
s_param *ft_8xp_parse_func(s_token **tokens, int length);
s_param *ft_8xp_parse_func_with_param(s_token *func, s_token **tokens, int length);
s_param *ft_8xp_parse_op(s_token **tokens, int length, int index);
s_param *ft_8xp_parse_make_function(s_token *token, int ac, s_param **av);

#endif
