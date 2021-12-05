%Q1
longueur([],0).
longueur([_ | XS], A) :- longueur(XS,Z), A is Z + 1.

%Q2
somme([],0).
somme([X|XS],A) :- somme(XS,Z), A is Z + X.

%Q3
membre(X,[X|_]).
membre(X,[_|XS]) :- membre(X,XS).

%Q4
ajoute_en_tete(X,[],L) :- L is X.
ajoute_en_tete(X,[T|TT],L) :- append([X],[T|TT],L).

ajoute_en_tete_liste([],L1,[L1]).
ajoute_en_tete_liste(L1,[],[L1]).
ajoute_en_tete_liste([],[],[]).
ajoute_en_tete_liste(L1,L2,[L1|L2]).

%Q5
ajoute_en_queue(E,[],[L]) :- L is E.
ajoute_en_queue(E,[A|L],[A|LL]) :- ajoute_en_queue(E,L,LL).

%Q6
extraire_tete([X|L],A,B) :- ajoute_en_tete_liste(L,[],B), A is X.
extraire_tete_simple([X|XS],X,XS).

%Q7 !!
concatene([],[],[]).
concatene(L1,[],[L1]).
concatene([],[L1],[L1]).
concatene(L,LL,K) :- ajoute_en_tete_liste(LL,K,M), concatene(L,M,K).

%Q8
retourne([],[],[]).
retourne([],L,L).
retourne(L,[],L).
retourne([X|XS],A,R) :- ajoute_en_tete(X,A,Z), retourne(XS,Z,R).

%Q9
insert_trie(K,[],[K]).
insert_trie(K,[X|XS],L) :- K =< X, !, ajoute_en_tete_liste(K,[X|XS],L).
insert_trie(K,[X|XS],[X|YS]) :- K > X, !, insert_trie(K,XS,YS).

%Q10
tri_insert([],[]).
tri_insert([X|XS], L) :- tri_insert(XS,R), insert_trie(X, R, L).


%Q11
divise([], [], []).
divise([X], [X], []).
divise([X1,X2|XS], [X1|Y], [X2|Z]) :- divise(XS, Y, Z).

%Q12
fusion([],[],[]).
fusion([X],[],[X]).
fusion([],[X],[X]).
fusion([X|XS],[Y|YS],T) :- X > Y, !,  tri_insert(Y,T), fusion([X|XS],YS,T).
fusion([X|XS],[Y|YS],T) :- X < Y, !,  tri_insert(X,T), fusion(XS,[Y|YS],T).
