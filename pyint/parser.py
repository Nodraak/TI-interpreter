#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tokenizer import (
    TAssign,
    TComma,
    TDoubleQuotes,
    TEndOfInstruction,
    TFuncWithParam,
    TNumber,
    TParenthesisClose,
    TParenthesisOpen,
    TString,
)


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

    if (in_parenthesis > 0) and (ret_index != -1):
        print('Warning: missing closing parenthesis, forgiving:')
        print('\t%s' % tokens)
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
        if len(tokens) == 1:
            self.data = tokens[0]
        else:
            i = parse_instruction(tokens)
            if i == -1:
                if all([isinstance(t, TNumber) for t in tokens]):
                    self.data = TNumber(priority=-1, callback=None, string=parse_int(tokens))
                elif isinstance(tokens[0], TDoubleQuotes) and isinstance(tokens[-1], TDoubleQuotes):
                    text = ''.join([t.string for t in tokens[1:-1]])
                    self.data = TString(priority=-1, callback=None, string=text)
                elif isinstance(tokens[0], TFuncWithParam):
                    missing_closing_parenthesis = \
                        + sum([isinstance(t, TParenthesisOpen) for t in tokens]) \
                        + sum([isinstance(t, TFuncWithParam) for t in tokens]) \
                        - sum([isinstance(t, TParenthesisClose) for t in tokens])

                    tokens.extend([TParenthesisClose(priority=0, callback='NULL', string=')')]*missing_closing_parenthesis)

                    self.data = tokens[0]
                    self.data.add_children(
                        [Instruction(sub_tokens) for sub_tokens in split_by_class(tokens[1:-1], TComma)]
                    )
                else:
                    print(tokens)
                    raise ValueError('parse_instruction returned -1, but I dont how to parse these bytes')
            elif i == 0:
                self.data = tokens[0]
                self.data.add_children([
                    Instruction(tokens[1:]),
                ])
            else:
                self.data = tokens[i]
                self.data.add_children([
                    Instruction(tokens[:i]),
                    Instruction(tokens[i+1:]),
                ])

    def as_token(self):
        return self.data

    def __repr__(self):
        return '<%s "%s">' % (self.__class__.__name__, self.as_token())

    def dump(self, i):
        if i == 0:
            print('dump:')
        print('%s%s' % ('\t'*i, self.as_token()))
        for c in self.as_token().children:
            c.dump(i+1)


class Parser(object):
    def __init__(self, tokens):
        self.tokens = tokens

    def __iter__(self):
        instructions = []
        tmp = []
        for token in self.tokens:
            if isinstance(token, TEndOfInstruction):
                if tmp:
                    instructions.append(Instruction(tmp))
                    tmp = []
            else:
                tmp.append(token)

        for i in instructions:
            yield i
