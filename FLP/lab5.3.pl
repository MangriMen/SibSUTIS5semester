is_empty(List):- not(member(_,List)).

car([Element|_], Result):- (is_empty([Element]) -> Result=[]; Result=Element).
cdr([_|List], Result):- (is_empty(List) -> Result=[]; Result=List).

readList(Resultlist, SizeCounter, Pos, List):-
  (0 < SizeCounter -> NewSizeCounter is SizeCounter - 1, NewPos is Pos + 1, 
  write("element["), write(Pos), write("]:"),
  read(Element),
  append(Resultlist, [Element], L),
  readList(L, NewSizeCounter, NewPos, List);
  List=Resultlist). 
  
min_max(A,B, MIN, MAX):-
  (A < B -> MIN=A, MAX=B; 
                   MIN=B, MAX=A).  
  
split(List, MIN, MAX, L1,L2,L3):-
  (is_empty(List) -> write(L1),write(","),write(L2),write(","),write(L3), !;
  car(List, CarResult),
  cdr(List, CdrResult),
  (CarResult < MIN -> append(L1, [CarResult], NewL1),split(CdrResult,MIN,MAX,NewL1,L2,L3);
  (CarResult > MAX -> append(L3, [CarResult], NewL3),split(CdrResult,MIN,MAX,L1,L2,NewL3);
                       append(L2, [CarResult], NewL2),split(CdrResult,MIN,MAX,L1,NewL2,L3)))).

splitList:-
  write("Enter list size: "),
  read(SizeCounter),
  readList([], SizeCounter, 1, List),
  write("From="), read(FROM),
  write("To="), read(TO),
  min_max(FROM,TO,MIN,MAX), 
  split(List,MIN,MAX,[],[],[]).