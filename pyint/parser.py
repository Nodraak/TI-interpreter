#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tokenizer import (
    TAssign,
    TComma,
    TDoubleQuotes,
    TEndOfInstruction,
    TFact,
    TFuncWithParam,
    TNumber,
    TVar,
    TParenthesisClose,
    TParenthesisOpen,
    TString,
    TIf,
    TThen,
    TElse,
    TEnd,
    TWhile,
    TFor,
    TOp,
)


def parse_instruction(tokens):
    assert len(tokens) not in (0, 1)

    ret_index = -1
    ret_priority = 100
    in_parenthesis = 0
    in_text = False
    for i, t in enumerate(tokens):
        if not isinstance(t, TAssign):
            # explicit parenthesis open or implicit with TFuncWithParam (but not with conditionnal statement TOp) or For
            if isinstance(t, TParenthesisOpen) \
                or (isinstance(t, TFuncWithParam) and not isinstance(t, TOp)) \
                or isinstance(t, TFor):
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
        raise ValueError('SyntaxError: missing double quotes.')

    if (in_parenthesis > 0) and (ret_index != -1):
        print('Warning: missing closing parenthesis, forgiving:')
        print('\t%s' % tokens)

    return ret_index


def parse_int(tokens):
    exponent = 0
    ret = 0

    for t in tokens[::-1]:
        if not isinstance(t, TNumber):
            raise ValueError('SyntaxError: unexpected non TNumber token.')

        if t.payload is None:  # got a point, ie the number is a float
            ret *= 10 ** -exponent
        else:
            ret += t.payload * 10**exponent

        exponent += 1

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
        assert len(tokens) != 0

        if len(tokens) == 1:
            self.data = tokens[0]
        else:
            i = parse_instruction(tokens)
            if i == -1:
                if all([isinstance(t, TNumber) for t in tokens]):
                    val = parse_int(tokens)
                    self.data = TNumber(priority=-1, string=str(val), payload=val)
                elif all([isinstance(t, TNumber) for t in tokens[:-1]]) and isinstance(tokens[-1], TVar):
                    before, after = tokens[:-1], [tokens[-1]]
                    self.data = TOp(priority=20, string='*', payload='ft_vm_functions_mul').clone()  # fixme: this is fragile
                    self.data.add_children([
                        Instruction(before),
                        Instruction(after),
                    ])
                elif isinstance(tokens[0], TDoubleQuotes) and isinstance(tokens[-1], TDoubleQuotes):
                    text = ''.join([t.string for t in tokens[1:-1]])
                    self.data = TString(priority=-1, string=text)
                elif isinstance(tokens[0], TFuncWithParam) or isinstance(tokens[0], TFor):
                    missing_closing_parenthesis = \
                        + sum([isinstance(t, TParenthesisOpen) for t in tokens]) \
                        + sum([isinstance(t, TFuncWithParam) and not isinstance(t, TOp) for t in tokens]) \
                        - sum([isinstance(t, TParenthesisClose) for t in tokens])

                    tokens.extend([TParenthesisClose(priority=0, string=')')]*missing_closing_parenthesis)

                    self.data = tokens[0]
                    self.data.add_children(
                        [Instruction(sub_tokens) for sub_tokens in split_by_class(tokens[1:-1], TComma)]
                    )

                    if isinstance(tokens[0], TFor):
                        if len(self.data.children) == 3:
                            self.data.add_children([
                                Instruction([TNumber(priority=0, string='1', payload=1)]),
                            ])  # fixme: this is fragile
                else:
                    print(tokens)
                    raise ValueError('parse_instruction returned -1, but I dont how to parse these bytes')
            elif i == 0:
                self.data = tokens[0]
                self.data.add_children([
                    Instruction(tokens[1:]),
                ])
            else:
                before, current, after = tokens[:i], tokens[i], tokens[i+1:]

                self.data = current
                self.data.add_children([
                    Instruction(before),
                ])

                if not (isinstance(current, TFact) and (len(after) == 0)):
                    self.data.add_children([
                        Instruction(after),
                    ])

    def as_token(self):
        return self.data

    def __repr__(self):
        return '<%s "%s">' % (self.__class__.__name__, self.as_token())

    def dump(self, depth=0):
        t = self.as_token()

        if depth == 0:
            print('dump:')

        print('%s%s' % ('\t'*depth, t))

        if t.children:
            print('%schildren:' % ('\t'*depth))
            for c in t.children:
                c.dump(depth+1)

        if hasattr(t, 'if_true'):
            print('%sif_true:' % ('\t'*depth))
            for c in t.if_true:
                c.dump(depth+1)


def parse_logic(instruction_generator):
    ret = []

    for cur_ins in instruction_generator:
        cur_token = cur_ins.as_token()

        if isinstance(cur_token, TFor) or isinstance(cur_token, TWhile):
            cur_token.add_if_true(parse_logic(instruction_generator))
            ret.append(cur_ins)
        elif isinstance(cur_token, TIf):
            next_ins = next(instruction_generator)
            next_token = next_ins.as_token()
            if isinstance(next_token, TThen):
                cur_token.add_if_true(parse_logic(instruction_generator))
            else:
                cur_token.add_if_true([next_token])
            ret.append(cur_ins)
        elif isinstance(cur_token, TEnd):
            return ret
        elif isinstance(cur_token, TElse):
            raise ValueError('ParserError: unhandled instructions Else.')
        else:
            ret.append(cur_ins)

    return ret


class Parser(object):
    def __init__(self, tokens):
        self.tokens = tokens

    def __iter__(self):

        # parse instructions

        instructions = []
        tmp = []
        for token in self.tokens:
            if isinstance(token, TEndOfInstruction):
                if tmp:
                    instructions.append(Instruction(tmp))
                    tmp = []
            else:
                tmp.append(token)
        if tmp:
            instructions.append(Instruction(tmp))

        # parse logic (if, while, ...)

        instructions = parse_logic(iter(instructions))

        # return

        for i in instructions:
            i.dump()
            yield i
