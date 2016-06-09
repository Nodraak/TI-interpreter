#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from itertools import zip_longest
from math import factorial
import string
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
        self.variables.update({c: 0 for c in string.ascii_uppercase})
        self.variables.update({'Omega': 0})
        self.ret = 0
        self.screan_clear()

    def run(self, instructions, update_screen=True):
        for ins in instructions:
            token = ins.as_token()

            if isinstance(token, TNumber) or isinstance(token, TVar):
                self.ret = self.get_arg_value(ins)
            elif isinstance(token, TFunc) or isinstance(token, TFuncWithParam) or isinstance(token, TCond):
                callback = getattr(self, token.payload)
                callback(token)
            else:
                raise ValueError('InterpreterError: unknown token "%s".' % token.payload)

            if update_screen:
                self.refresh_screen()
                time.sleep(1.0/20)

    def refresh_screen(self):
        tmp_pxl = []
        tmp_pxl.append('+%s+' % ('-'*95))
        for row in self.screen[::-1]:
            tmp_pxl.append('|%s|' % ''.join(['X' if x else ' ' for x in row]))
        tmp_pxl.append('+%s+' % ('-'*95))

        tmp_state = []
        tmp_state.append('')
        for var, val in sorted(self.variables.items()):
            tmp_state.append('%s: %s' % (var, val))

        zipped = zip_longest(tmp_pxl, tmp_state, fillvalue='')
        print('\n'.join([' '.join(tup) for tup in zipped]))

    def screan_clear(self):
        self.screen = [[0 for x in range(95)] for y in range(63)]  # todo define

    def screen_set_pxl(self, x, y, val=1):
        if 0 <= x and x < 95 and 0 <= y and y < 63:
            self.screen[y][x] = val

    def get_arg_value(self, ins):
        token = ins.as_token()

        if isinstance(token, TNumber):
            return token.payload
        elif isinstance(token, TVar):
            return self.variables[token.string]
        elif isinstance(token, TString):
            return token.string
        elif isinstance(token, TFuncWithParam):
            self.run([ins])
            return self.ret

        raise ValueError('InterpreterError: unknown value "%s"' % str(token))

    def ft_vm_functions_effecr(self, token):
        self.screan_clear()

    def ft_vm_functions_input(self, token):
        arg1, arg2 = token.children
        prompt = arg1.as_token().string
        key = arg2.as_token().string
        val = input(prompt)
        self.variables[key] = float(val)

    def ft_vm_functions_effdessin(self, token):
        self.screan_clear()

    def ft_vm_functions_assign(self, token):
        arg1, arg2 = token.children
        var = arg2.as_token().string
        val = self.get_arg_value(arg1)
        self.variables[var] = val

    def ft_vm_functions_if(self, token):
        self.run(token.children, False)
        if self.ret:
            self.run(token.if_true)
        # todo else run(if_false)

    def ft_vm_functions_while(self, token):
        self.run(token.children, False)
        while self.ret:
            self.run(token.if_true)
            self.run(token.children, False)

    def ft_vm_functions_for(self, token):
        var, start, stop, step = token.children

        var = var.as_token().string
        start = self.get_arg_value(start)
        stop = self.get_arg_value(stop)
        step = self.get_arg_value(step)

        self.variables[var] = start
        while (stop - self.variables[var])*step >= 0:
            self.run(token.if_true)
            self.variables[var] += step

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

    def ft_vm_functions_neg(self, token):
        (arg, ) = token.children
        val = self.get_arg_value(arg)
        self.ret = -val

    def ft_vm_functions_pow(self, token):
        arg1, arg2 = token.children
        val1 = self.get_arg_value(arg1)
        val2 = self.get_arg_value(arg2)
        self.ret = val1 ** val2

    def ft_vm_functions_fact(self, token):
        (arg, ) = token.children
        val = self.get_arg_value(arg)
        if val == 69:
            time.sleep(0.100)
            return
        self.ret = factorial(val)

    def ft_vm_functions_disp(self, token):
        if len(token.children) == 0:
            print('')
        else:
            raise ValueError('InterpreterError: not implemented')

    def ft_vm_functions_text(self, token):
        y, x, text = token.children

        x = self.get_arg_value(x)
        y = self.get_arg_value(y)
        text = self.get_arg_value(text)

        for letter in text:
            if letter == ' ':
                x += 1
                continue

            for j in range(5):
                for i in range(3):
                    pxl = text_get_pixel(letter, j, i)
                    self.screen_set_pxl(x+i, 63-1-(y+j), pxl)

            x += 4

    def ft_vm_functions_hline(self, token):
        x1, x2, y = token.children

        x1 = self.get_arg_value(x1)
        x2 = self.get_arg_value(x2)
        y = self.get_arg_value(y)

        for i in range(x1, x2+1):
            self.screen_set_pxl(i, y)

    def ft_vm_functions_vline(self, token):
        x, y1, y2 = token.children

        x = self.get_arg_value(x)
        y1 = self.get_arg_value(y1)
        y2 = self.get_arg_value(y2)

        self._ft_vm_functions_vline(x, y1, y2)

    def _ft_vm_functions_vline(self, x, y1, y2):
        for j in range(y1, y2+1):
            self.screen_set_pxl(x, j)

    def ft_vm_functions_line(self, token):
        x1, y1, x2, y2 = token.children

        x1 = self.get_arg_value(x1)
        y1 = self.get_arg_value(y1)
        x2 = self.get_arg_value(x2)
        y2 = self.get_arg_value(y2)

        if x1 == x2:
            self._ft_vm_functions_vline(x1, y1, y2)
        else:
            if (x1 > x2):
                x1, x2 = x2, x1

            coeff = (y2-y1) / (x2-x1)
            for i in range(x1, x2+1):
                j = y1 + (i-x1)*coeff
                self.screen_set_pxl(i, int(j))


def text_get_pixel(letter, j, i):
    if letter in string.ascii_uppercase:
        return text_get_letter_pixel(letter, j, i)
    elif letter in string.digits:
        return text_get_number_pixel(letter, j, i)
    else:
        raise ValueError('InterpreterError')


def text_get_letter_pixel(letter, j, i):
    letters = [
        [  # A
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
        ],
        [  # B
            [1, 1, 0],
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 1],
            [1, 1, 0],
        ],
        [  # C
            [1, 1, 1],
            [1, 0, 0],
            [1, 0, 0],
            [1, 0, 0],
            [1, 1, 1],
        ],
        [  # D
            [1, 1, 0],
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 0],
        ],
        [  # E
            [1, 1, 1],
            [1, 0, 0],
            [1, 1, 0],
            [1, 0, 0],
            [1, 1, 1],
        ],
        [  # F
            [1, 1, 1],
            [1, 0, 0],
            [1, 1, 0],
            [1, 0, 0],
            [1, 0, 0],
        ],
        [  # G
            [1, 1, 1],
            [1, 0, 0],
            [1, 0, 0],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # H
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
        ],
        [  # I
            [1, 1, 1],
            [0, 1, 0],
            [0, 1, 0],
            [0, 1, 0],
            [1, 1, 1],
        ],
        [  # J
            [1, 1, 1],
            [0, 1, 0],
            [0, 0, 0],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # K
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 1],
            [1, 0, 1],
        ],
        [  # L
            [1, 0, 0],
            [1, 0, 0],
            [1, 0, 0],
            [1, 0, 0],
            [1, 1, 1],
        ],
        [  # M
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
        ],
        [  # N
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
        ],
        [  # 0
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # P
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 0],
            [1, 0, 0],
        ],
        [  # Q
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 1, 1],
        ],
        [  # R
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 1, 0],
            [1, 0, 1],
        ],
        [  # S
            [1, 1, 1],
            [1, 0, 0],
            [1, 1, 1],
            [0, 0, 1],
            [1, 1, 1],
        ],
        [  # T
            [1, 1, 1],
            [0, 1, 0],
            [0, 1, 0],
            [0, 1, 0],
            [0, 1, 0],
        ],
        [  # U
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # V
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [0, 1, 0],
            [0, 1, 0],
        ],
        [  # W
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 1, 1],
        ],
        [  # X
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
        ],
        [  # Y
            [1, 0, 1],
            [1, 0, 1],
            [0, 1, 0],
            [0, 1, 0],
            [0, 1, 0],
        ],
        [  # Z
            [1, 1, 1],
            [0, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
            [1, 1, 1],
        ],
    ]

    return letters[ord(letter)-ord('A')][j][i]


def text_get_number_pixel(number, j, i):
    numbers = [
        [  # 0
            [1, 1, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # 1
            [0, 0, 1],
            [0, 1, 1],
            [1, 0, 1],
            [0, 0, 1],
            [0, 0, 1],
        ],
        [  # 2
            [1, 1, 1],
            [1, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
            [1, 1, 1],
        ],
        [  # 3
            [1, 1, 1],
            [0, 0, 1],
            [0, 1, 1],
            [0, 0, 1],
            [1, 1, 1],
        ],
        [  # 4
            [0, 1, 0],
            [1, 0, 0],
            [1, 1, 1],
            [0, 0, 1],
            [0, 0, 1],
        ],
        [  # 5
            [1, 1, 1],
            [1, 0, 0],
            [1, 1, 1],
            [0, 0, 1],
            [1, 1, 1],
        ],
        [  # 6
            [0, 1, 0],
            [1, 0, 0],
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # 7
            [1, 1, 1],
            [0, 0, 1],
            [0, 1, 0],
            [0, 1, 0],
            [0, 1, 0],
        ],
        [  # 8
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
        ],
        [  # 9
            [1, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [0, 0, 1],
            [1, 1, 1],
        ],
    ]

    return numbers[ord(number)-ord('0')][j][i]
