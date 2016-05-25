#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class VM(object):
    def __init__(self, instructions):
        self.instructions = instructions

    def run(self):
        for ins in self.instructions:
            ins.dump(0)
            getattr(self, ins.token.callback)(ins)

    def ft_vm_functions_effecr(self, ins):
        print 'ft_vm_functions_effecr()'
        print ins

    def ft_vm_functions_input(self, ins):
        string, var = ins.children
        print 'ft_vm_functions_input()'
        print ins
        print string
        print var

    def ft_vm_functions_assign(self, ins):
        val, var = ins.children
        exit(0)
