#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from string import ascii_uppercase
import time

from tokenizer import (
    TCond,
    TFunc,
    TFuncWithParam,
    TNumber,
    TString,
    TVar,
)


class Interpreter(object):
    def __init__(self):
        self.variables = {}
        self.variables.update({c: 0 for c in ascii_uppercase})
        self.variables.update({'Omega': 0})
        self.ret = 0

    def run(self, instructions):
        for ins in instructions:
            token = ins.as_token()

            if isinstance(token, TNumber) or isinstance(token, TVar):
                self.ret = self.get_arg_value(ins)
            elif isinstance(token, TFunc) or isinstance(token, TFuncWithParam) or isinstance(token, TCond):
                callback = getattr(self, token.payload)
                callback(token)
            else:
                raise ValueError('InterpreterError: unknown token "%s".' % token.payload)


    def get_arg_value(self, ins):
        token = ins.as_token()

        if isinstance(token, TNumber):
            return token.payload
        elif isinstance(token, TVar):
            return self.variables[token.string]
        elif isinstance(token, TString):
            return token.string
        elif isinstance(token, TFuncWithParam):
            self.run(token.children)
            return self.ret

        print('')
        print('get_arg_value', token)

        raise ValueError('todo / fixme')

    def ft_vm_functions_effecr(self, token):
        # todo
        print('ft_vm_functions_effecr()')

    def ft_vm_functions_input(self, token):
        arg1, arg2 = token.children
        prompt = arg1.as_token().string
        key = arg2.as_token().string
        val = input(prompt)
        self.variables[key] = float(val)

    def ft_vm_functions_assign(self, token):
        arg1, arg2 = token.children
        var = arg2.as_token().string
        val = self.get_arg_value(arg1)
        self.variables[var] = val

    def ft_vm_functions_if(self, token):
        self.run(token.children)
        if self.ret:
            self.run(token.if_true)
        # todo else run(if_false)

    def ft_vm_functions_while(self, token):
        self.run(token.children)
        while self.ret:
            self.run(token.if_true)
            self.run(token.children)

    def ft_vm_functions_equal(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 == val2

    def ft_vm_functions_not_equal(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 != val2

    def ft_vm_functions_greater(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 > val2

    def ft_vm_functions_lower(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 < val2

    def ft_vm_functions_add(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 + val2

    def ft_vm_functions_sub(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 + val2

    def ft_vm_functions_mul(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 * val2

    def ft_vm_functions_div(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 / val2

    def ft_vm_functions_partent(self, token):
        (arg1, ) = token.children
        val1 = self.get_arg_value(arg1)
        self.ret = int(val1)

    def ft_vm_functions_partdec(self, token):
        (arg1, ) = token.children
        val1 = self.get_arg_value(arg1)
        self.ret = val1-int(val1)

    def ft_vm_functions_pow(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 ** val2

    def ft_vm_functions_disp(self, token):
        if len(token.children) == 0:
            print('')
        else:
            raise ValueError('InterpreterError: not implemented')
