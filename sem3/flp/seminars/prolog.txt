
% Multiply the elements ofa list with a constant value
% [1,2,3], k=3 => [3,6,9]

% mulk(L- List, K- integer, R- List )
% flow model( i, i, o) (i,i,i)

mulK([],_,[]).
mulK([H|T],K,R):-
    NewH is H*K,
    mulK(T, K, TR),
    R=[NewH| TR].

%Add an element at the end of a List.
% addE(L -list, E - element, R - result list)
% flow model (i,i,o) (i,i,i)
addE([], E, [E]).
addE([H|T], E, R):-
    addE(T,E,TR),
    R=[H|TR].

% Compute the sum of elements in a List
% suma(L-list, S-integer)
% flow model (i,o) (i,i)
suma([],0).
suma([H|T], S):-
    suma(T, TS),
    S is H+TS.

% Compute the product of even numvers in a numerical list.
% evenProd(L1L2..Ln)=1, if n = 0
%					L1*evenProd(L2..Ln), if n>0 and L1%2=0
%					evenProd(L2..Ln), otherwise

% evenProd(L-list, P-integer)
% flow model (i,o) (i,i)
evenProd([],1).
evenProd([H|T], P):-
    H mod 2 =:= 0,
    evenProd(T,TP),
    P is H*TP.
evenProd([H|T], P):-
    H mod 2 =\= 0,
    evenProd(T, TP),
    P=TP.








