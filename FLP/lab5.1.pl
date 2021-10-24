oddX(X):- X mod 2 =:= 1.

print_odd_help(MAX,MIN):-
    ((oddX(MAX)) -> write(MAX), write(" ")), fail;
    NMAX is MAX-1, ((MIN < MAX) -> print_odd_help(NMAX,MIN); !).

print_odd_dec(MIN, MAX):-
    ((MIN < MAX) -> print_odd_help(MAX, MIN); 
    print_odd_help(MIN, MAX)).

goal:-
    write('Enter A: '),read(A),
    write('Enter B: '),read(B),
    print_odd_dec(A,B).

