% P1 - Problem 6

% a. Write a predicate to test if a list is a set.

% member1(E, L1...Ln) = false, if n = 0
%                     = true, if L1 = E
%                     member1(E, L2..Ln), otherwise
                     
% member1(E - element, L - list)
% flow model (i,i)
member1(E, [E|_]).
member1(E, [_|L]):-
  member1(E,L).

% isSet(L1...Ln) = true, if n = 0
%                = false, if L1 is in L2..Ln
%                isSet(L2..Ln), otherwise
%
% isSet(L - list)
% flow model (i)
isSet([]).
isSet([H|T]):-
  \+ member1(H,T),
  isSet(T).


% b. Write a predicate to remove the first three occurrences of an element in a list. 
% If the element occurs less than three times, all occurrences will be removed.

% removeN(L1...Ln, E, K) = [], if n = 0
%                        = L1...Ln, if K = 0
%                        = removeN(L2...Ln, E, K-1), if L1 = e and K > 0
%                        = L1 + removeN(L2..Ln, E, K) if L1 != E and K > 0

% removeN(L - list, E - element, N - integer, R - result list)
% removes the first N occurrences of E from L
% flow model (i,i,i,o) (i,i,i,i)
removeN([], _, _,[]).
removeN([H|T], _, 0, [H|T]).
removeN([H|T], E, N, R):-
  H == E,
  N > 0,
  N1 is N-1,
  removeN(T, E, N1, R).
removeN([H|T], E, N, R):-
  H \==E,
  N > 0,
  removeN(T, E, N, TR),
  R = [H|TR].


% remove3(L - list, E - element , R - result list)
% flow model (i,i,o) (i,i,i)
remove3(L, E, R):-
  removeN(L, E, 3, R).


% Tests:
% ?- isSet([1,2,3]).                   true
% ?- isSet([1,2,1]).                   false
% ?- remove3([1,2,1,3,1,1], 1, R).     R = [2,3,1]
