mynot(A) :- A, !, fail.
mynot(_).
add(A,B,C) :- C is A + B.