fibonacci(A,B,Counter):-
    NCounter is Counter-1,
    NNum is A+B, 
    (
        (Counter \== 0) -> fibonacci(B,NNum,NCounter); 
        writeln(A), !
    ).

print_fibonacci:-
    repeat,
    writeln("Enter the value: "),
    read(NUMBER),
    (NUMBER < 0 -> !; fibonacci(1,1,NUMBER), fail).
