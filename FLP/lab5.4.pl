is_empty(List):- not(member(_,List)).

car([Element|_], Result):- (is_empty([Element]) -> Result=[]; Result=Element).
cdr([_|List], Result):- (is_empty(List) -> Result=[]; Result=List).
  
readList(ResultList, Size, Pos, List):-
  (0 < Size -> NewSize is Size - 1, NewPos is Pos + 1, 
  write("element["), write(Pos), write("]:"), 
  read(Element), append(ResultList, [Element], L), readList(L, NewSize, NewPos, List);
  List=ResultList). 
  
uniqueElements(List,TempList,ResultList):-
  (not(is_empty(List)) -> car(List, CarResult), cdr(List,CdrResult),
    (member(CarResult,TempList) -> uniqueElements(CdrResult, TempList, ResultList);
                                   append(TempList,[CarResult],NewTempList),uniqueElements(CdrResult, NewTempList, ResultList)
    );
    ResultList=TempList
  ).
  
maxCountElementList(List,UniqueList,Count, TempList, ResultList):-
  (not(is_empty(UniqueList)) -> car(UniqueList, CarResult), cdr(UniqueList,CdrResult),
    findall(CarResult,member(CarResult,List),GroopList),
    length(GroopList,Size),
    (Count < Size -> maxCountElementList(List,CdrResult,Size, [CarResult], ResultList);
      (Count == Size -> append(TempList,[CarResult],NewTempList), maxCountElementList(List,CdrResult,Count, NewTempList, ResultList);
                        maxCountElementList(List,CdrResult,Count, TempList, ResultList))
    );
    ResultList=TempList
  ).

maxFreq:-
    write("Enter list size: "), 
    read(Size), readList([],Size, 1, List),
    uniqueElements(List,[],UniqueList), 
    maxCountElementList(List,UniqueList,0, [] ,ResultList),
    writeln(ResultList).