% (i,o) (i,i)
fact1(0,1).
fact1(N,F) :- 
  N>0,
  N1 is N-1,
  fact1(N1,F1),
  F is N*F1.

% (o,i)
fact2(N,F) :- 
  fact_aux(N,F,1).
fact_aux(F,F,F) :- !.
fact_aux(N,F,M) :-
  F1 is F div M,
  F mod M =:= 0,
  M1 is M+1,
  fact_aux(N,F1,M1).
  
% (o,o)
fact3(0,1).
fact3(N,F) :-
  fact3(N1,F1),
  N is N1+1,
  F is F1*N.

fact(N,F) :-
  not(var(N)),
  fact1(N,F).
fact(N,F) :-
  var(N),
  not(var(F)),
  fact2(N,F).
fact(N,F) :-
  var(N),
  var(F),
  fact3(N,F).
