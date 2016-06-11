
This is a TI83+ interpreter. It may or may not work with other versions of the TI language.

# How do I enjoy this piece of code ?

You can read the source code, but be warned that it was not very well designed, as it is my first interpreter (BTW, the C version is much worse than the Python one).

You can also see it in action :

* Compile with: `make` (For the C version)
* Test with (C):
    * `./a.out ../data/AATEST.8Xp`
    * `./a.out ../data/ABC.8Xp`
    * `./a.out ../data/BASE.8Xp`
    * `./a.out ../data/WTC.8Xp`
* Test with (Python):
    * `python3 main.py ../data/AATEST.8Xp`
    * `python3 main.py ../data/ABC.8Xp`
    * `python3 main.py ../data/BASE.8Xp`
    * `python3 main.py ../data/WTC.8Xp`

# Some theory about interpreters, compilation and ASTs

    (source code)
Lexer (also called Tokenizer)
    (tokens)
Parser
    (AST)
(Optionnal: Type Checker)
Code Generation / Interpretation

# Todo

* choose a license
* draw cursor
* draw axis

# License

todo
wtfpl ?
