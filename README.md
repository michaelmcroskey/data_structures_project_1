Project 01: uScheme
===================

This is a simple implementation of a [Scheme] interpreter that supports the
following syntax:

    <digit>         = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    <number>        = {<digit>}
    <op>            = - | + | * | /
    <expression>    = (<op> <expression> <expression>) | <number>

Examples
--------

    :::scheme
    1
    (+ 1 2)
    (+ 1 (- 2 3))
    (+ (* 1 2) (- 3 4))

[Scheme]:   https://en.wikipedia.org/wiki/Scheme_(programming_language)


Questions
---------

1. What is the complexity of your interpreter in terms of Big-O notation? Explain exactly what N is in this case and the asymptotic behavior of your interpreter for when N grows. Moreover, be sure to consider the impact of using a stack during evaluation.
    

2. Compare the resource usage of your two versions of the Scheme interpreter (i.e. uscheme and uschemeSmart) by determining:

    - Which executable is larger?
    
    - Which executable uses more memory?
        

    Which implementation do you prefer: the one with manual memory management, or the one with smart pointers? Explain the trade-offs and your reasoning.

    

3. Real world Scheme interpreters such as Racket and Guile support arbitrary length expressions. For instance, instead of binary operations such as (+ 1 2), these implementations support (+ 1 2 3 4 5). What changes to your interpreter would you need to make support such syntax? Explain how the structures, parser, and interpreter would need to be modified.
    
    

Group Contributions
-------------------

**Troy: **

**David: **

**Michael: **


