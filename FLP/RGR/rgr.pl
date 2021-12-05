% 1.11. Список целых чисел разделите на два списка: из чётных элементов и нечётных
% элементов.
% Например, [1,-2,3,5,-4]-> [1,3,5], [-2,-4]

splitListByEvenOdd([], EvenList, OddList):- (
    write("Even list: "),
    writeln(EvenList),

    write("Odd list: "),
    writeln(OddList)
).
splitListByEvenOdd([Head | Tail], EvenList, OddList):- (
    (
        Head mod 2 =:= 0 -> append(EvenList, [Head], NewEvenList), splitListByEvenOdd(Tail, NewEvenList, OddList);
                            append(OddList, [Head], NewOddList), splitListByEvenOdd(Tail, EvenList, NewOddList)
    )
).

testSplit:- (
    write("Enter the list: "),
    read(X),

    splitListByEvenOdd(X, _, _)
).

% 2.11. Найдите в файле все слова максимальной длины. Сформируйте новый файл из
% найденных слов.

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

splitInputToWords([], Out, Out).
splitInputToWords([Head | Tail], Out, Acc):- (
    split_string(Head, " ", " .,:;?!+-=...", L),
    append(L, Acc, Temp),
    splitInputToWords(Tail, Out, Temp)
).

findOnlyMaxLength([], MaxLenghtWords, _, MaxLenghtWords).
findOnlyMaxLength([Head | Tail], MaxLenghtWords, Lenght, Acc):- (
    string_length(Head, StringLenght),
    (Lenght == StringLenght -> append(Acc, [Head], NewMaxLenghtWords), findOnlyMaxLength(Tail, MaxLenghtWords, Lenght, NewMaxLenghtWords);
        (
            Lenght < StringLenght -> findOnlyMaxLength(Tail, MaxLenghtWords, StringLenght, [Head]);
                                     findOnlyMaxLength(Tail, MaxLenghtWords, Lenght, Acc)
        )
    )
).

createMaxLenghtWordsFile(Filename):- (
    working_directory(CWD, CWD),

    atom_concat(CWD, Filename, Path),
    open(Path, read, InStream),
    read_file(InStream, Lines),

    splitInputToWords(Lines, Out, []),
    findOnlyMaxLength(Out, MaxLenghtWords, 0, []),
    close(InStream),

    atom_concat(CWD, 'maxLength.txt', OutPath),
    open(OutPath, write, OutStream),
    write_file(OutStream, MaxLenghtWords),
    close(OutStream)
).

testMaxLenghtWords:- (
    write("Enter the filename:"),
    read(Filename),
    createMaxLenghtWordsFile(Filename)
).