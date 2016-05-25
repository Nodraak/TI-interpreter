#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import struct
import sys

from tokenizer import Tokenizer
from parser import Parser
from interpreter import VM


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
        # code = [struct.unpack('B', byte)[0] for byte in code]  # for python 2

        print('Calculator   %s' % calculator)
        print('Date         %s' % date)
        print('File_type    %s (%d)' % (FILE_TYPE[file_type], file_type))
        print('Name         %s' % name)
        print('Control_sum  %x' % control_sum)
        print('Program length %d' % len(code))

        return code


def main():
    if len(sys.argv) != 2:
        print('Usage: %s FILE' % sys.argv[0])
        exit(0)

    code = eigthxp_read_code(sys.argv[1])
    print('%s%s%s' % ('='*30, 'Tokenizer', '='*30))
    tokens = list(Tokenizer(code))
    print('%s%s%s' % ('='*30, 'Parser', '='*30))
    instructions = list(Parser(tokens))
    print('%s%s%s' % ('='*30, 'VM', '='*30))
    VM(instructions).run()


if __name__ == '__main__':
    main()
