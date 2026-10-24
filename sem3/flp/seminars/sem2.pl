% suma(L1L2...Ln) = 0, if n =0
%					   L1 + suma(L2..Ln), if n > 0

% suma(L-list, S - integer)
% flow model(i, o)
suma([],0).
suma([H|T], S):-
    suma(T, TS),
    S is H+TS.

% Collector variable method
% sumc(L1L2..Ln, Col) = Col, if  n = 0
%						sumc(L2..Ln, Col+L1), n > 0
% sumaMain(L1L2...Ln)=sumc(L1L2..Ln,0)

% sumc(L - list, Col - integer, R - integer)
% flow model (i, i, o)
sumc([], Col, Col).
sumc([H|T], Col, R):-
    NCol is H+Col,
    sumc(T, NCol, R).

% sumMain(L - list i, R - ingteger o)
sumMain(L, R):- sumc(L, 0, R).


% Compute the number of occurences of an element in a list
% nrOcc(L1L2..Ln, X) = 0, if n = 0
%						 nrOcc(L2..Ln, X) + 1, if L1 = X
% 						 nrOcc(L2..Ln, X), if L1 \= X

% nrOcc(L - list, X - element, R - integer)
% flow model (i, i, o)

nrOcc([], _, 0).
nrOcc([H|T], X, R):-
    H=X, %!, % ! - mean cut, it cuts the backtracking
    nrOcc(T, X, TR),
    R is TR+1.
nrOcc([H|T], X, R):-
    H\=X,% if we have cut, we don t need this one anymore
    nrOcc(T, X, R).


% nrOccC(L - list, X - elem, Col - integer, R - integer)
% flow model (i, i, i, o)
nrOccC([], _, Col, Col).
% nrOccC([H|T], X, Col, R):- or we can use:
nrOccC([X|T], X, Col, R):-
    NCol is Col+1,
    nrOccC(T, X, NCol, R).
nrOccC([H|T], X, Col, R):-
    H\=X,
    nrOccC(T, X, Col, R).

% nrOccMain(L1L2..Ln, x) = nrOccC(L1L2..Ln, X, 0)
% nrOccMain(L - list, X - elem, R - integer)
nrOccMain(L, X, R):- nrOccC(L, X, 0 , R).

% Write a predicate to remove froma list all the elements
% that appear only once.
% [1,2,1,4,1,3,4] => [1,1,4,1,4]

% rem(L1L2..Ln, CL) = [], if n = 0
%				  	  L1 U rem(L2...Ln, CL), if nrOcc(CL, L1) > 1
%					  rem(L2..Ln, CL), if nrOcc(CL, L1) = 1

% remMain(L) = rem(L, L)
% rem(L - list, CL - copy list, R - list)
% flow model (i, i, o)
rem([], _, []).
%rem([H|T], CL, R):-
rem([H|T], CL, [H|TR]):-
    nrOcc(CL, H, N), % (   i, i, o)
    N > 1,
    rem(T, CL, TR).
    %R=[H|TR].
rem([H|T], CL, R):-
    nrOcc(CL, H, 1), % (   i, i, i)
    rem(T, CL, R).

% remMain(L - list, R - list) (i, o)
remMain(L, R):- rem(L, L, R).


% remC(L1L2..Ln, CL, Col) = Col, if n = 0
%							remc(L2...Ln, CL, Col U {L1}), if nrOccMain(CL, L1) > 1
%							remc(L2..Ln, CL, Col), if nrOccMain(CL, L1) = 1

%remCMain(L1L2..Ln) = remC(L1L2..Ln, L1L2..Ln, [])

% remC(L - list, CL - copy list, Col - list, R - list)
% flow model (i, i, i, o)
remC([], _, Col, Col).
remC([H|T], CL, Col, R):-
     nrOccMain(CL, H, N), % (   i ,i ,o)
     N>1,
     NCol=[H|Col],
     %addEnd(Col, H, NCol), % (   i, i, o)
	 remC(T, CL, NCol, R).
remC([H|T], CL, Col, R):-
     nrOccMain(CL, H, 1), %(   i, i, o)
     remC(T, CL, Col, R).
     
% remCMain(L - list i, R - list o)
remCMain(L, R):-remC(L, L, [], R).


% Compute the gcd of all elements of a numeric linear list.
% [10, 20, 15]

% gcd2
% gcd_list1(L1L2..Ln) = L1, if n = 1
% 					   gcd2(L1, gcd_list(L2..Ln)), if n > 1

% gcd_list2(L1L2..Ln, col) = col, if n = 0
%							gcd_list(L2L3..Ln, gcd(col, L1)), if  n > 0
% gcd_list_main(L1L2..Ln) = gcd_list(L1L2..Ln, L1) 

% gcd_list3(L1L2..Ln) = L1, if n = 1
% 						gcd_list3(gcd2(L1,L2) U L3..Ln),
