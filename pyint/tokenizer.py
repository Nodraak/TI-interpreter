#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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
    def __init__(self, priority, callback, string):
        self.priority = priority
        self.callback = callback
        self.string = string

    def __repr__(self):
        return '<%s "%s">' % (self.__class__.__name__, self.string)


class TFunc(Token):
    pass

class TNumber(Token):
    pass

class TVar(Token):
    pass

class TString(Token):
    pass

class TOp(Token):
    pass

class TAssign(Token):
    pass

class TEndOfInstruction(Token):
    pass

class TFuncWithParam(Token):
    pass

class TTest(Token):
    pass

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
    0x04: TAssign(priority=5, callback='ft_vm_functions_assign', string='->'),
    0x0D: TFunc(priority=30, callback='ft_vm_function_square', string='^2'),

    0x10: TParenthesisOpen(priority=0, callback='NULL', string='('),
    0x11: TParenthesisClose(priority=0, callback='NULL', string=')'),

    0x2A: TDoubleQuotes(priority=0, callback='NULL', string='"'),
    0x2B: TComma(priority=7, callback='NULL', string=','),

    0x2D: TFunc(priority=30, callback='ft_vm_functions_fact', string='!'),

    0x29: TOther(priority=0, callback='NULL', string=' '),
    0x30: TNumber(priority=0, callback='NULL', string='0'),
    0x31: TNumber(priority=0, callback='NULL', string='1'),
    0x32: TNumber(priority=0, callback='NULL', string='2'),
    0x33: TNumber(priority=0, callback='NULL', string='3'),
    0x34: TNumber(priority=0, callback='NULL', string='4'),
    0x35: TNumber(priority=0, callback='NULL', string='5'),
    0x36: TNumber(priority=0, callback='NULL', string='6'),
    0x37: TNumber(priority=0, callback='NULL', string='7'),
    0x38: TNumber(priority=0, callback='NULL', string='8'),
    0x39: TNumber(priority=0, callback='NULL', string='9'),

    0x3A: TNumber(priority=0, callback='NULL', string='.'),

    0x3E: TEndOfInstruction(priority=0, callback='NULL', string=':'),
    0x3F: TEndOfInstruction(priority=0, callback='NULL', string=':'),

    0x41: TVar(priority=0, callback='NULL', string='A'),
    0x42: TVar(priority=0, callback='NULL', string='B'),
    0x43: TVar(priority=0, callback='NULL', string='C'),
    0x44: TVar(priority=0, callback='NULL', string='D'),
    0x45: TVar(priority=0, callback='NULL', string='E'),
    0x46: TVar(priority=0, callback='NULL', string='F'),
    0x47: TVar(priority=0, callback='NULL', string='G'),
    0x48: TVar(priority=0, callback='NULL', string='H'),
    0x49: TVar(priority=0, callback='NULL', string='I'),
    0x4A: TVar(priority=0, callback='NULL', string='J'),
    0x4B: TVar(priority=0, callback='NULL', string='K'),
    0x4C: TVar(priority=0, callback='NULL', string='L'),
    0x4D: TVar(priority=0, callback='NULL', string='M'),
    0x4E: TVar(priority=0, callback='NULL', string='N'),
    0x4F: TVar(priority=0, callback='NULL', string='O'),
    0x50: TVar(priority=0, callback='NULL', string='P'),
    0x51: TVar(priority=0, callback='NULL', string='Q'),
    0x52: TVar(priority=0, callback='NULL', string='R'),
    0x53: TVar(priority=0, callback='NULL', string='S'),
    0x54: TVar(priority=0, callback='NULL', string='T'),
    0x55: TVar(priority=0, callback='NULL', string='U'),
    0x56: TVar(priority=0, callback='NULL', string='V'),
    0x57: TVar(priority=0, callback='NULL', string='W'),
    0x58: TVar(priority=0, callback='NULL', string='X'),
    0x59: TVar(priority=0, callback='NULL', string='Y'),
    0x5A: TVar(priority=0, callback='NULL', string='Z'),
    0x5B: TVar(priority=0, callback='NULL', string='Omega'),

#0x5D: Token_INCOMPLETE(priority=0, callback='NULL', string='<incomplete>'),

#0x63: Token_INCOMPLETE(priority=0, callback='NULL', string='<incomplete>'),

    0x6A: TOp(priority=2, callback='ft_vm_functions_equal', string='='),
    0x6B: TOp(priority=2, callback='ft_vm_functions_lower', string='<'),
    0x6C: TOp(priority=2, callback='ft_vm_functions_greater', string='>'),

    0x6F: TOp(priority=2, callback='ft_vm_functions_not_equal', string='!='),
    0x70: TOp(priority=10, callback='ft_vm_functions_add', string='+'),
    0x71: TOp(priority=10, callback='ft_vm_functions_add', string='-'),

    0x82: TOp(priority=20, callback='ft_vm_functions_mul', string='*'),
    0x83: TOp(priority=20, callback='ft_vm_functions_div', string='/'),

    0x85: TFunc(priority=0, callback='ft_vm_functions_effdessin', string='EffDessin'),

    0x93: TFuncWithParam(priority=6, callback='ft_vm_functions_text', string='Texte('),

    0x9C: TFuncWithParam(priority=6, callback='ft_vm_functions_line', string='Ligne('),
    0x9E: TFuncWithParam(priority=6, callback='ft_vm_functions_ptaff', string='Pt-Aff('),
    0x9F: TFuncWithParam(priority=6, callback='ft_vm_functions_ptnaff', string='Pt-NAff'),

    0xB0: TFuncWithParam(priority=6, callback='ft_vm_functions_neg', string='(-)'),
    0xB1: TFuncWithParam(priority=6, callback='ft_vm_functions_partent', string='partEnt('),

    0xB5: TFuncWithParam(priority=6, callback='NULL', string='dim('),

    0xBA: TFuncWithParam(priority=6, callback='ft_vm_functions_partdec', string='partDec('),
#0xBB: Token_INCOMPLETE(priority=0, callback='NULL', string='<incomplete>'),
    0xBC: TFuncWithParam(priority=6, callback='ft_vm_function_sqrt', string='sqrt('),

    0xCE: TTest(priority=1, callback='ft_vm_functions_if', string='If'),
    0xCF: TTest(priority=1, callback='NULL', string='Then'),

    0xD0: TTest(priority=1, callback='NULL', string='Else'),
    0xD1: TTest(priority=1, callback='ft_vm_functions_while', string='While'),

    0xD3: TTest(priority=1, callback='ft_vm_functions_for', string='For('),
    0xD4: TTest(priority=1, callback='NULL', string='End'),

    0xD6: TOther(priority=0, callback='NULL', string='Lbl'),
    0xD7: TOther(priority=0, callback='NULL', string='Goto'),

    0xDC: TFuncWithParam(priority=6, callback='ft_vm_functions_input', string='Input('),

    0xDE: TFuncWithParam(priority=6, callback='ft_vm_functions_disp', string='Disp('),

    0xE1: TFunc(priority=0, callback='ft_vm_functions_effecr', string='EffEcr'),

    0xF0: TOp(priority=30, callback='ft_vm_function_pow', string='^'),

    (0x5d, 0x00): TVar(priority=0, callback='NULL', string='L1'),
    (0x5d, 0x01): TVar(priority=0, callback='NULL', string='L2'),

    (0x63, 0x02): TVar(priority=0, callback='NULL', string='Xgrad'),
    (0x63, 0x03): TVar(priority=0, callback='NULL', string='Ygrad'),
    (0x63, 0x0A): TVar(priority=0, callback='NULL', string='Xmin'),
    (0x63, 0x0B): TVar(priority=0, callback='NULL', string='Xmax'),
    (0x63, 0x0C): TVar(priority=0, callback='NULL', string='Ymin'),
    (0x63, 0x0D): TVar(priority=0, callback='NULL', string='Ymax'),

    (0xBB, 0x0A): TFuncWithParam(priority=6, callback='NULL', string='entAleat('),
}


class Tokenizer(object):
    def __init__(self, code):
        self.code = code

    def __iter__(self):
        generator = iter(self.code)
        for byte in generator:
            # try:
            yield tokens[byte]
            # except KeyError:
            #    yield tokens[(byte, generator.next())]
