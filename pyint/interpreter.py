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
            getattr(self, ins.token.callback)(ins)
            print(self.data)
            print('')

    def ft_vm_functions_effecr(self, ins):
        # todo
        print('ft_vm_functions_effecr()')

    def ft_vm_functions_input(self, ins):
        string, var = ins.children
        val = input(string.token.string)
        self.data[var.token.string] = float(val)

    def ft_vm_functions_assign(self, ins):
        val, var = ins.children
        self.data[var.token.string] = val.token.string


