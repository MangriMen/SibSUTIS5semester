parent("����","���").
parent("����","���").
parent("����","���").
parent("���","���").
parent("���","����").
parent("���","���").
parent("����","���").

male("����").
male("���").
male("����").
male("���").
male("���").

female("����").
female("���").
female("���").

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