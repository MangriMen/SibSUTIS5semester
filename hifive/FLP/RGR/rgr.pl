% 1.13. Удалите из списка все вхождения элемента X.
% Например, [1,2,1,3,1,1,2,5,6], X=1-> [2,3,2,5,6].

removeAllEntries(_, [], []).
removeAllEntries(Item, [Item | Tail], TailSecond):- removeAllEntries(Item, Tail, TailSecond).
removeAllEntries(Item, [Head | Tail], [Head | TailSecond]):- removeAllEntries(Item, Tail, TailSecond).

testRemoveEntries:- (
    write("Enter X:"),
    read(X),

    write("Enter your list:"),
    read(NewList),

    write("Your list is: "),
    removeAllEntries(X, NewList, OutList),
    write(OutList)
).

% 2.13. Переставьте строки текстового файла в обратном порядке. Сформируйте новый файл.

reverse([], Out, Out).
reverse([Head | Tail], Out, Acc):- reverse(Tail, Out, [Head | Acc]).

read_file(Stream, []) :- at_end_of_stream(Stream).
read_file(Stream, [Head | Tail]) :- (
    \+ at_end_of_stream(Stream),
    read_line_to_string(Stream, Head),
    read_file(Stream, Tail)
).

write_file(_, []).
write_file(Stream, [Head | Tail]) :- (
    writeln(Stream, Head),
    write_file(Stream, Tail)
).

createReversedFile(Filename):- (
    working_directory(CWD, CWD),

    atom_concat(CWD, Filename, Path),
    open(Path, read, InStream),
    read_file(InStream, Lines),
    close(InStream),

    reverse(Lines, Out, []),

    atom_concat(CWD, 'reversed.txt', OutPath),
    open(OutPath, write, OutStream),
    write_file(OutStream, Out),
    close(OutStream)
).

testCreateFile:- (
    write("Enter the filename:"),
    read(Filename),
    createReversedFile(Filename)
).