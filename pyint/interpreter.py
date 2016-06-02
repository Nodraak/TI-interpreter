#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import string

from tokenizer import (
    TFuncWithParam,
    TNumber,
    TString,
    TVar,
)


class Interpreter(object):
    def __init__(self):
        self.data = {}
        self.data.update({c: 0 for c in string.ascii_uppercase})
        self.data.update({'Omega': 0})
        self.data.update({'ret': 0})

    def run(self, instructions):
        for ins in instructions:
            token = ins.as_token()

            callback = getattr(self, token.payload, None)
            if callback:
                callback(token)
            else:
                raise ValueError('InterpreterError: function not implemented.')

            print('')

    def get_arg_value(self, token):
        if isinstance(token, TNumber):
            return token.payload
        elif isinstance(token, TVar):
            return self.data[token.string]
        # elif isinstance(token, TFuncWithParam):
            # self.run(token.args)
            # return self.data['ret']
            # pass  # todo fix this

        print('')
        print('get_arg_value', token)

        raise ValueError('todo / fixme')

    def ft_vm_functions_effecr(self, token):
        # todo
        print('ft_vm_functions_effecr()')

    def ft_vm_functions_input(self, token):
        print('input', token.children)
        string, var = token.children
        val = input(string.as_token().string)
        self.data[var.as_token().string] = float(val)

    def ft_vm_functions_assign(self, token):
        val, var = token.children
        self.data[var.as_token().string] = val.as_token().payload

