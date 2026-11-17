% P3 - Problem 6

% Generate the list of all arrangements of K elements of a given list.
% Eg: [2, 3, 4] K=2 => [[2,3], [3,2], [2,4], [4,2], [3,4], [4,3]] (not necessary in this order)

% allArr(L1..Ln, K) = arrangement(L1..Ln, k)

% allArr(L - list, K - integer, R - list of all arrangements)
% flow model (i,i,o)
allArr(L, K, R):-
  findall(X, arrangement(L, K, X), R).


% arrangement(L1...Ln, K) = c , where C = candidate(L1...Ln, K) and isSet(c) holds

% arrangement(L - list, K - integer, R - one arrangement of K elements)
% flow model (i,i, o)
arrangement(L, K, R):-
  candidate(L, K, R),
  isSet(R).


% candidate(L1..Ln, K) = [], if k = 0
%                        e + candidate(L1..Ln, K-1), if k > 0, where e is any element of L1..Ln

% candidate(L - list, K - integer, R - a list of K elements of L, repeats allowed)
% flow model (i,i,o) 
candidate(_, 0, []).
candidate(L, K, [E|R]):-
  K > 0,
  member1(E, L),
  K1 is K-1,
  candidate(L, K1, R).


% member1(E - element, L - list)
% flow model (i, i) (o, i)
member1(E, [E|_]).
member1(E, [_|L]):-
  member1(E, L).

% isSet(L - list)
% flow model (i)
isSet([]).
isSet([H|T]):-
  \+ member1(H, T),
  isSet(T).



% Tests:
% ?- allArr([2,3,4], 2, R).    R = [[2,3],[2,4],[3,2],[3,4],[4,2],[4,3]].
% ?- allArr([2,3,4], 1, R).    R = [[2],[3],[4]].
% ?- allArr([2,3,4], 0, R).    R = [[]].
% ?- allArr([2,3], 5, R).      R = [].
% ?- allArr([], 0, R).         R = [[]].
% ?- allArr([], 1, R).         R = [].
% ?- allArr([1], 1, R).        R = [[1]].
