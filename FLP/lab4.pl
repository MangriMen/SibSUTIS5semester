parent("Мэри","Боб").
parent("Мэри","Энн").
parent("Джон","Боб").
parent("Боб","Лиз").
parent("Боб","Паул").
parent("Боб","Сэм").
parent("Паул","Пат").

male("Джон").
male("Боб").
male("Паул").
male("Сэм").
male("Пат").

female("Мэри").
female("Энн").
female("Лиз").

father(X,Y):-
    parent(X,Y),male(X).

mother(X,Y):-
    parent(X,Y),female(X).

brother(X,Y):-
    parent(Z,X),parent(Z,Y),male(X),X\==Y.

sister(X,Y):-
    parent(Z,X),parent(Z,Y),female(X),X\==Y.

grandson(X,Y):-
    parent(X,Z),parent(Z,Y),male(Y).

granddaughter(X,Y):-
    parent(X,Z),parent(Z,Y),female(Y).

aunt(X,Y):-
    parent(Z,Y),sister(X,Z).

two_children(X):-
    (male(X); female(X)),
    findall(Y, parent(X, Y), YList),length(YList, N),N =:= 2.

successor(X):-
    father(X,Y),male(Y).