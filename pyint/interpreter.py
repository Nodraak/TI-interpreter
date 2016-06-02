#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from string import ascii_uppercase

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
        self.data = {}
        self.data.update({c: 0 for c in ascii_uppercase})
        self.data.update({'Omega': 0})
        self.data.update({'ret': 0})

    def run(self, instructions):
        for ins in instructions:
            token = ins.as_token()


            if isinstance(token, TNumber) or isinstance(token, TVar):
                self.data['ret'] = self.get_arg_value(token)
            elif isinstance(token, TFunc) or isinstance(token, TFuncWithParam) or isinstance(token, TCond):
                callback = getattr(self, token.payload)
                callback(token)
            else:
                raise ValueError('InterpreterError: unknown token "%s".' % token.payload)


    def get_arg_value(self, token):
        if isinstance(token, TNumber):
            return token.payload
        elif isinstance(token, TVar):
            return self.data[token.string]
        elif isinstance(token, TString):
            return token.string
        elif isinstance(token, TFuncWithParam):
            self.run(token.children)
            return self.data['ret']

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
        self.data[key] = float(val)

    def ft_vm_functions_assign(self, token):
        arg1, arg2 = token.children
        var = arg2.as_token().string
        val = self.get_arg_value(arg1.as_token())
        self.data[var] = val

