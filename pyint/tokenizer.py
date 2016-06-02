#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import copy


"""
priorities:
    0 default
    1 if while ... (special too)
    2 != > ... (special)

    5 ->
    6 functions with param
    7 ,
    10 + -
    20 * /
    30 ^ !
"""


class Token(object):
    def __init__(self, priority, string, payload=None):
        self.priority = priority
        self.string = string
        self.payload = payload
        self.children = []

    def clone(self):
        return copy.deepcopy(self)

    def add_children(self, iterable):
        self.children.extend(iterable)

    def __repr__(self):
        return '<%s "%s">' % (self.__class__.__name__, self.string)

class TEndOfInstruction(Token):
    pass

# base types

class TNumber(Token):
    pass

class TVar(Token):
    pass

class TString(Token):
    pass

# functions without params

class TFunc(Token):
    pass

# functions with param

class TFuncWithParam(Token):
    pass

class TOp(TFuncWithParam):
    pass

class TAssign(TFuncWithParam):
    pass

# conditional statements

class TCond(Token):
    def __init__(self, *args, **kwargs):
        super(TCond, self).__init__(*args, **kwargs)
        self.if_true = []
        self.if_false = []

    def add_if_true(self, iterable):
        self.if_true.extend(iterable)

    def add_if_false(self, iterable):
        self.if_false.extend(iterable)

class TIf(TCond):
    pass

class TWhile(TCond):
    pass

class TFor(TCond):
    pass

class TThen(Token):
    pass

class TElse(Token):
    pass

class TEnd(Token):
    pass

# specials

class TDoubleQuotes(Token):
    pass

class TParenthesisOpen(Token):
    pass

class TParenthesisClose(Token):
    pass

class TComma(Token):
    pass

class TOther(Token):
    pass


tokens = {
    0x04: TAssign(priority=5, string='->', payload='ft_vm_functions_assign'),
    0x0D: TFunc(priority=30, string='^2', payload='ft_vm_function_square'),

    0x10: TParenthesisOpen(priority=0, string='('),
    0x11: TParenthesisClose(priority=0, string=')'),

    0x2A: TDoubleQuotes(priority=0, string='"'),
    0x2B: TComma(priority=7, string=','),

    0x2D: TFunc(priority=30, string='!', payload='ft_vm_functions_fact'),

    0x29: TOther(priority=0, string=' '),
    0x30: TNumber(priority=0, string='0', payload=0),
    0x31: TNumber(priority=0, string='1', payload=1),
    0x32: TNumber(priority=0, string='2', payload=2),
    0x33: TNumber(priority=0, string='3', payload=3),
    0x34: TNumber(priority=0, string='4', payload=4),
    0x35: TNumber(priority=0, string='5', payload=5),
    0x36: TNumber(priority=0, string='6', payload=6),
    0x37: TNumber(priority=0, string='7', payload=7),
    0x38: TNumber(priority=0, string='8', payload=8),
    0x39: TNumber(priority=0, string='9', payload=9),

    0x3A: TNumber(priority=0, string='.'),

    0x3E: TEndOfInstruction(priority=0, string=':'),
    0x3F: TEndOfInstruction(priority=0, string=':'),

    0x41: TVar(priority=0, string='A'),
    0x42: TVar(priority=0, string='B'),
    0x43: TVar(priority=0, string='C'),
    0x44: TVar(priority=0, string='D'),
    0x45: TVar(priority=0, string='E'),
    0x46: TVar(priority=0, string='F'),
    0x47: TVar(priority=0, string='G'),
    0x48: TVar(priority=0, string='H'),
    0x49: TVar(priority=0, string='I'),
    0x4A: TVar(priority=0, string='J'),
    0x4B: TVar(priority=0, string='K'),
    0x4C: TVar(priority=0, string='L'),
    0x4D: TVar(priority=0, string='M'),
    0x4E: TVar(priority=0, string='N'),
    0x4F: TVar(priority=0, string='O'),
    0x50: TVar(priority=0, string='P'),
    0x51: TVar(priority=0, string='Q'),
    0x52: TVar(priority=0, string='R'),
    0x53: TVar(priority=0, string='S'),
    0x54: TVar(priority=0, string='T'),
    0x55: TVar(priority=0, string='U'),
    0x56: TVar(priority=0, string='V'),
    0x57: TVar(priority=0, string='W'),
    0x58: TVar(priority=0, string='X'),
    0x59: TVar(priority=0, string='Y'),
    0x5A: TVar(priority=0, string='Z'),
    0x5B: TVar(priority=0, string='Omega'),

#0x5D: Token_INCOMPLETE(priority=0, callback='NULL', string='<incomplete>'),

#0x63: Token_INCOMPLETE(priority=0, callback='NULL', string='<incomplete>'),

    0x6A: TOp(priority=2, string='=', payload='ft_vm_functions_equal'),
    0x6B: TOp(priority=2, string='<', payload='ft_vm_functions_lower'),
    0x6C: TOp(priority=2, string='>', payload='ft_vm_functions_greater'),

    0x6F: TOp(priority=2, string='!=', payload='ft_vm_functions_not_equal'),
    0x70: TOp(priority=10, string='+', payload='ft_vm_functions_add'),
    0x71: TOp(priority=10, string='-', payload='ft_vm_functions_add'),

    0x82: TOp(priority=20, string='*', payload='ft_vm_functions_mul'),
    0x83: TOp(priority=20, string='/', payload='ft_vm_functions_div'),

    0x85: TFunc(priority=0, string='EffDessin', payload='ft_vm_functions_effdessin'),

    0x93: TFuncWithParam(priority=6, string='Texte(', payload='ft_vm_functions_text'),

    0x9C: TFuncWithParam(priority=6, string='Ligne(', payload='ft_vm_functions_line'),
    0x9E: TFuncWithParam(priority=6, string='Pt-Aff(', payload='ft_vm_functions_ptaff'),
    0x9F: TFuncWithParam(priority=6, string='Pt-NAff', payload='ft_vm_functions_ptnaff'),

    0xB0: TFuncWithParam(priority=6, string='(-)', payload='ft_vm_functions_neg'),
    0xB1: TFuncWithParam(priority=6, string='partEnt(', payload='ft_vm_functions_partent'),

    0xB5: TFuncWithParam(priority=6, string='dim('),

    0xBA: TFuncWithParam(priority=6, string='partDec(', payload='ft_vm_functions_partdec'),
#0xBB: Token_INCOMPLETE(priority=0, callback='NULL', string='<incomplete>'),
    0xBC: TFuncWithParam(priority=6, string='sqrt(', payload='ft_vm_function_sqrt'),

    0xCE: TIf(priority=1, string='If', payload='ft_vm_functions_if'),
    0xCF: TThen(priority=1, string='Then'),

    0xD0: TElse(priority=1, string='Else'),
    0xD1: TWhile(priority=1, string='While', payload='ft_vm_functions_while'),

    0xD3: TFor(priority=1, string='For(', payload='ft_vm_functions_for'),
    0xD4: TEnd(priority=1, string='End'),

    0xD6: TOther(priority=0, string='Lbl'),
    0xD7: TOther(priority=0, string='Goto'),

    0xDC: TFuncWithParam(priority=6, string='Input(', payload='ft_vm_functions_input'),

    0xDE: TFuncWithParam(priority=6, string='Disp(', payload='ft_vm_functions_disp'),

    0xE1: TFunc(priority=0, string='EffEcr', payload='ft_vm_functions_effecr'),

    0xF0: TOp(priority=30, string='^', payload='ft_vm_function_pow'),

    (0x5d, 0x00): TVar(priority=0, string='L1'),
    (0x5d, 0x01): TVar(priority=0, string='L2'),

    (0x63, 0x02): TVar(priority=0, string='Xgrad'),
    (0x63, 0x03): TVar(priority=0, string='Ygrad'),
    (0x63, 0x0A): TVar(priority=0, string='Xmin'),
    (0x63, 0x0B): TVar(priority=0, string='Xmax'),
    (0x63, 0x0C): TVar(priority=0, string='Ymin'),
    (0x63, 0x0D): TVar(priority=0, string='Ymax'),

    (0xBB, 0x0A): TFuncWithParam(priority=6, string='entAleat('),
}


class Tokenizer(object):
    def __init__(self, code):
        self.code = code

    def __iter__(self):
        generator = iter(self.code)
        for byte in generator:
            # try:
            yield tokens[byte].clone()
            # except KeyError:
            #    yield tokens[(byte, next(generator))]
