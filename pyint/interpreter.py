#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import string


class Interpreter(object):
    def __init__(self):
        self.data = {}
        self.data.update({c: 0 for c in string.ascii_uppercase})
        self.data.update({'Omega': 0})

    def run(self, instructions):
        for ins in instructions:
            ins.dump(0)
            token = ins.as_token()
            getattr(self, token.callback)(token.children)
            print(self.data)
            print('')

    def ft_vm_functions_effecr(self, args):
        # todo
        print('ft_vm_functions_effecr()')

    def ft_vm_functions_input(self, args):
        string, var = args
        val = input(string.as_token().string)
        self.data[var.as_token().string] = float(val)

    def ft_vm_functions_assign(self, args):
        val, var = args
        self.data[var.as_token().string] = val.as_token().string

