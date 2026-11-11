% P2 - Problem 6

% a. Determine the product of a number represented as digits in a list to a given digit.
% Eg.: [1 9 3 5 9 9] * 2 => [3 8 7 1 9 8]


% mulAux(L1..Ln, D) = ([],0), if n = 0
%                   = (dig+TR, carry), where
%                      (TR, c) = mulAux(L2..Ln, d)
%                      v = L1*d + c
%                      dig = v mod 10, carry = v div 10, if n > 0
%
% mulAux(L - list of digits, D - digit, R - result digits, C - carry)
% flow model (i, i, o, o)
mulAux([], _, [], 0).
mulAux([H|T], D, [Dig|TR], OutC):-
  mulAux(T, D, TR, InC),
  V is H * D + InC,
  Dig is V mod 10,
  OutC is V div 10.

% mul(L1..Ln, D) = TR, if carry = 0
%                  carry + TR,if carry > 0 where (TR, carry) = mulAux(L1..Ln, d)
%
% mul(L - list of digits, D - digit, R - result list of digits)
% flow model (i, i, o)
mul(L, D, R):-
  mulAux(L, D, TR, C),
  C =:= 0,
  R = TR.
mul(L, D, R):-
  mulAux(L, D, TR, C),
  C > 0,
  R = [C|TR].



% b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to replace
% every sublist with the position of the maximum element from that sublist.
% [1, [2, 3], [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
% [1, [2], [1, 3], 3, 6, [2], 5, [1, 2, 3], 7]

% maxL(L1..Ln) = L1, if n = 1
%                L1, if n > 1 and L1 > maxL(L2..ln)
%                maxL(L2..Ln), if n > 1 and L1 =< maxL(L2..ln)
%
% maxL(L - list of numbers, M - integer)
% flow model (i,o)
maxL([H], H).
maxL([H|T], M):-
  maxL(T, TM),
  H > TM,
  M = H.
maxL([H|T], M):-
  maxL(T, TM),
  H =< TM,
  M = TM.

% posAux(L1..Ln, m, i) = [], if n = 0
%                        i + posAux(L2..Ln, m, i+1), if L1 = m
%                        posAux(L2..Ln, m, i+1), if L1 != m
%
% posAux(L - list, M - the maximum, I - current position, R - list of positions)
% flow model (i,i,i,o)
posAux([], _, _, []).
posAux([H|T], M, I, [I|TR]):-
  H =:= M,
  I1 is I + 1,
  posAux(T, M, I1, TR).
posAux([H|T], M, I, TR):-
  H =\= M,
  I1 is I + 1,
  posAux(T, M, I1, TR).

% maxPos(L) = posAux(L, maxL(L), 1)
%
% maxPos(L - list of numbers, R - list of position of the maximum)
% flow model (i, o)
maxPos(L, R):-
  maxL(L, M),
  posAux(L, M, 1, R).

% replaceMaxPos(L1..Ln) = [], if n = 0
%                         L1 + replaceMaxPos(L2..Ln), if L1 is a number 
%                         maxPos(L1) + replaceMaxPos(L2..Ln), if L1 is a list
%
% replaceMaxPos(L - heterogeneous list, R - result list)
% flow model(i, o)
replaceMaxPos([], []).
replaceMaxPos([H|T], [H|R]):-
  number(H),
  !,
  replaceMaxPos(T, R).
replaceMaxPos([H|T], [P|R]):-
  is_list(H),
  maxPos(H, P),
  replaceMaxPos(T, R).


% Tests:
%
% a.
% ?- mul([1,9,3,5,9,9], 2, R).      R = [3,8,7,1,9,8].
% ?- mul([5,5], 2, R).              R = [1,1,0].
% ?- mul([9,9,9], 9, R).            R = [8,9,9,1].
% ?- mul([4], 3, R).                R = [1,2].
% ?- mul([1,2,3], 0, R).            R = [0,0,0].
% ?- mul([], 5, R).                 R = [].
%
% b.
% ?- maxPos([10,14,12,13,14], P).   P = [2,5].
% ?- replaceMaxPos([1,[2,3],[4,1,4],3,6,[7,10,1,3,9],5,[1,1,1],7], R).
%                                   R = [1,[2],[1,3],3,6,[2],5,[1,2,3],7].
% ?- replaceMaxPos([[8]], R).       R = [[1]].
% ?- replaceMaxPos([[3,3]], R).     R = [[1,2]].
% ?- replaceMaxPos([5], R).         R = [5].
% ?- replaceMaxPos([], R).          R = [].
