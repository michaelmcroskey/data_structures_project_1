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
    
The complexity of the interpreter is O(N), where N is the total number of nodes, that is, the total number of numbers and operands combined.  The asymptotic behavoir is linear because for each node there is an O(1) evaluation, and that evaluation happens N times.  Each node is traversed and a number is added to and from the stack during the evaluation at every node (if the node has a number, the number is added, if it has an operant, the sum/difference/product/divedend of the children nodes are added).

2. Compare the resource usage of your two versions of the Scheme interpreter (i.e. uscheme and uschemeSmart) by determining:

    - Which executable is larger? 

uscheme is 80Kb, uschemesmart is 89Kb. uschemeSmart is larger.
    
    - Which executable uses more memory?

uscheme uses 2,751,861 bytes when run with input as the input, uscheme smart uses 4,062,541 bytes when run with input as the input.   uschemeSmart uses more memory.
        
    Which implementation do you prefer: the one with manual memory management, or the one with smart pointers? Explain the trade-offs and your reasoning.

I perfer the implementation with manual memory management.  I like this better because I like to know exactly what I am doing and where I am deleting the memory.  Valgrind also reports that without smart pointers over a million less bytes had to be allocated. The use of smart pointers is more hands off and it also requires code that is a tad more complicated.  However, it does garauntee that the memory will be handled properly.


3. Real world Scheme interpreters such as Racket and Guile support arbitrary length expressions. For instance, instead of binary operations such as (+ 1 2), these implementations support (+ 1 2 3 4 5). What changes to your interpreter would you need to make support such syntax? Explain how the structures, parser, and interpreter would need to be modified.
    
I would implement it almost the same way but I would use a tree that would have to have the ability to hold more than just two nodes.  I think the best way to do this would be to have a vector of pointer to nodes in the Node struct, as opposed to a left pointer and right pointer.  When the data is read in, instead of left and right being assigned, new nodes would be pushed onto that vector.  Then the interprer would use the operator on all of the node's children, looping across the vector of nodes, rather than just operating on left and right. The parser would have to continue reading numbers and adding them to the vector until it reaches a close parentheses.  
    

Group Contributions
-------------------

**Troy Prince (tprince): Did most of uscheme and helped on the README.**

**David Mellitt (dmellitt): Helped on uscheme, did the smart pointers and the README.**

**Michael McRoskey (mmcrosk1): Helped on uscheme, did the smart pointers and the README**


