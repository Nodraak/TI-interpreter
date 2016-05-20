#!/usr/bin/env python
# -*- coding: utf-8 -*-

import struct
import sys

def eigthxp_read_code(filename):
    FILE_TYPE = [
        'Real number',
        'List',
        'Matrix',
        'Y-var or equ',
        'String',
        'Program',
        'Assembler',
        'Picture',
        'Gdb',
    ]

    with open(filename, 'rb') as f:
        # read header
        calculator = f.read(8)
        _ = f.read(3)  # unknown
        date = f.read(40)
        _ = f.read(8)  # unknown
        file_type = struct.unpack('B', f.read(1))[0]
        name = f.read(7)
        _ = f.read(7)  # unknown

        code = f.read()
        code = code[:-1]  # remove null byte
        code, control_sum = code[:-2], struct.unpack('>H', code[-2:])[0]
        code = [struct.unpack('B', byte)[0] for byte in code]

        print('Calculator   %s' % calculator)
        print('Date         %s' % date)
        print('File_type    %s (%d)' % (FILE_TYPE[file_type], file_type))
        print('Name         %s' % name)
        print('Control_sum  %x' % control_sum)
        print('Program length %d' % len(code))

        return code

"""
priority:
    0 default
    1 if while (special too)
    2 != > (special)

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
    0x5B: TVar(priority=0, callback='NULL', string='0mega'),

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
            try:
                yield tokens[byte]
            except KeyError:
                yield tokens[(byte, generator.next())]



def parse_instruction(tokens):
    if len(tokens) == 0:
        raise ValueError('token list to parse is empty')

    if len(tokens) == 1:
        return -1

    ret_index = -1
    ret_priority = 100
    in_parenthesis = 0
    in_text = False
    for i, t in enumerate(tokens):
        if not isinstance(t, TAssign):
            if isinstance(t, TParenthesisOpen) or isinstance(t, TFuncWithParam):
                in_parenthesis += 1
                continue
            if isinstance(t, TDoubleQuotes):
                in_text = not in_text
                continue
            if isinstance(t, TParenthesisClose):
                in_parenthesis -= 1
                continue

            if in_text or in_parenthesis:
                continue

        if (t.priority != 0) and (t.priority < ret_priority):
            ret_priority = t.priority
            ret_index = i

    if in_text:
        raise ValueError('Missing double quotes')

    if (in_parenthesis > 0) and (not isinstance(tokens[ret_index], TAssign)):
        print 'Warning: missing closing parenthesis, forgiving'
        return 0

    return ret_index


def parse_int(tokens):
    ret = 0
    for t in tokens:
        if not isinstance(t, TNumber):
            raise ValueError('Unexpected non TNumber token')

        ret = ret*10 + int(t.string)

    return ret


def split_by_class(tokens, delim):
    ret = []
    tmp = []
    for t in tokens:
        if isinstance(t, delim):
            if tmp:
                ret.append(tmp)
                tmp = []
        else:
            tmp.append(t)
    if tmp:
        ret.append(tmp)
    return ret


class Instruction(object):
    def __init__(self, tokens):
        # print 'Instruction():', tokens

        if len(tokens) == 1:
            self.token = tokens[0]
            self.children = []
        else:
            i = parse_instruction(tokens)
            if i == -1:
                if all([isinstance(t, TNumber) for t in tokens]):
                    self.token = TNumber(priority=-1, callback=None, string=parse_int(tokens))
                    self.children = []
                elif isinstance(tokens[0], TDoubleQuotes) and isinstance(tokens[-1], TDoubleQuotes):
                    text = ''.join([t.string for t in tokens[1:-1]])
                    self.token = TString(priority=-1, callback=None, string=text)
                    self.children = []
                elif isinstance(tokens[0], TFuncWithParam):
                    missing_closin_parenthesis = sum([isinstance(t, TParenthesisClose) for t in tokens]) \
                        - sum([isinstance(t, TParenthesisOpen) for t in tokens]) \
                        - sum([isinstance(t, TFuncWithParam) for t in tokens])

                    tokens.extend([TParenthesisClose(priority=0, callback='NULL', string=')')]*missing_closin_parenthesis)

                    self.token = tokens[0]
                    self.children = [Instruction(sub_tokens) for sub_tokens in split_by_class(tokens[1:-1], TComma)]
                else:
                    print tokens
                    raise ValueError('parse_instruction returned -1, but I dont how to parse these bytes')
            elif i == 0:
                self.token = tokens[0]
                self.children = [
                    Instruction(tokens[1:]),
                ]
            else:
                self.token = tokens[i]
                self.children = [
                    Instruction(tokens[:i]),
                    Instruction(tokens[i+1:]),
                ]

    def dump(self, i):
        if i == 0:
            print 'dump:'
        print '\t'*i + str(self.token)
        for c in self.children:
            c.dump(i+1)


def main():
    if len(sys.argv) != 2:
        print('Usage: %s FILE' % sys.argv[0])
        exit(0)

    code = eigthxp_read_code(sys.argv[1])

    token_list = Tokenizer(code)  # actually, ByteReader

    print '---'
    for tokens in split_by_class(token_list, TEndOfInstruction):  # actually Lexer / Tokenizer
        print ''.join([t.string for t in tokens])
        Instruction(tokens).dump(0)
        print '---'

if __name__ == '__main__':
    main()
