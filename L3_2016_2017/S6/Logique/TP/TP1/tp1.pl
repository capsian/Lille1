% Lakhdar Selim
% TP1 Logique

% Salle 1
% Q1
contenu(tigre).
contenu(princesse).

% Q2
pancarte1_1(tigre, _).
pancarte1_1(_, princesse).
pancarte1_2(princesse, _).

% Q3
% les deux pancartes sont vrai
salle1(X,Y) :- contenu(X), contenu(Y), pancarte1_1(X, Y), pancarte1_2(X, Y).
% les deux pancartes sont fausses
salle1(X,Y) :- contenu(X), contenu(Y), not(pancarte1_1(X, Y)), not(pancarte1_2(X, Y)).

% Q4
	% [tp1].
	% salle1(X,Y).
		% X = Y, Y = princesse . 

% Q5

% Salle 2
% Q6
pancarte2_1(princesse,tigre).
pancarte2_2(princesse,tigre).
pancarte2_2(tigre,princesse).

% pancarte1 Vrai
salle2(X,Y) :- contenu(X), contenu(Y), pancarte2_1(X,Y), not(pancarte2_2(X,Y)).
% pancarte2 Faux
salle2(X,Y) :- contenu(X), contenu(Y), not(pancarte2_1(X,Y)), pancarte2_2(X,Y).

% Q7
%?- salle2(X,Y).
% X = tigre,
% Y = princesse .

% Q8
%?- trace(pancarte2_1), trace(pancarte2_2), trace(salle2).
%         pancarte2_1/2: [call,redo,exit,fail]
%         pancarte2_2/2: [call,redo,exit,fail]
%         salle2/2: [call,redo,exit,fail]
%true.
/*
	[debug]  ?- salle2(X,Y).
 T Call: (7) salle2(_G2311, _G2312)
 T Call: (8) contenu(_G2311)
 T Exit: (8) contenu(tigre)
 T Call: (8) contenu(_G2312)
 T Exit: (8) contenu(tigre)
 T Call: (8) pancarte2_1(tigre, tigre)
 T Fail: (8) pancarte2_1(tigre, tigre)
 T Redo: (8) contenu(_G2312)
 T Exit: (8) contenu(princesse)
 T Call: (8) pancarte2_1(tigre, princesse)
 T Fail: (8) pancarte2_1(tigre, princesse)
 T Redo: (8) contenu(_G2311)
 T Exit: (8) contenu(princesse)
 T Call: (8) contenu(_G2312)
 T Exit: (8) contenu(tigre)
 T Call: (8) pancarte2_1(princesse, tigre)
 T Exit: (8) pancarte2_1(princesse, tigre)
 T Call: (9) pancarte2_2(princesse, tigre)
 T Exit: (9) pancarte2_2(princesse, tigre)
 T Redo: (8) contenu(_G2312)
 T Exit: (8) contenu(princesse)
 T Call: (8) pancarte2_1(princesse, princesse)
 T Fail: (8) pancarte2_1(princesse, princesse)
 T Redo: (7) salle2(_G2311, _G2312)
 T Call: (8) contenu(_G2311)
 T Exit: (8) contenu(tigre)
 T Call: (8) contenu(_G2312)
 T Exit: (8) contenu(tigre)
 T Call: (9) pancarte2_1(tigre, tigre)
 T Fail: (9) pancarte2_1(tigre, tigre)
 T Call: (8) pancarte2_2(tigre, tigre)
 T Fail: (8) pancarte2_2(tigre, tigre)
 T Redo: (8) contenu(_G2312)
 T Exit: (8) contenu(princesse)
 T Call: (9) pancarte2_1(tigre, princesse)
 T Fail: (9) pancarte2_1(tigre, princesse)
 T Call: (8) pancarte2_2(tigre, princesse)
 T Exit: (8) pancarte2_2(tigre, princesse)
 T Exit: (7) salle2(tigre, princesse)
X = tigre,
Y = princesse .

*/


% Q9
% La pancarte : pancarte2_2

% Q10
resultat(X,Y) :- salle2(X,Y), write('porte 1 : '), write(X), write(' | porte 2 : '), write(Y).




% Salle 3
ncontenu(tigre).
ncontenu(princesse).
ncontenu(v).

% Q11
pancarte3_1(princesse,tigre,v).
pancarte3_1(tigre,princesse,v).

pancarte3_2(tigre,princesse,vide).
pancarte3_2(tigre,vide,princesse).

pancarte3_3(tigre,princesse,v).
pancarte3_3(princesse,tigre,v).

porte1(X,Y,Z) :- pancarte3_1(X,Y,Z), pancarte3_2(X,Y,Z), not(pancarte3_3(X,Y,Z)).
porte2(X,Y,Z) :- not(pancarte3_1(X,Y,Z)), pancarte3_2(X,Y,Z), not(pancarte3_3(X,Y,Z)).
porte3(X,Y,Z) :- pancarte3_1(X,Y,Z), pancarte3_2(X,Y,Z), not(pancarte3_3(X,Y,Z)).


% Q12
tmp(X,Y,Z) :- ncontenu(X), ncontenu(Y), ncontenu(Z).
salle3(X,Y,Z) :- tmp(X,Y,Z), porte1(X,Y,Z), not(porte2(X,Y,Z)), not(porte3(X,Y,Z)).
salle3(X,Y,Z) :- tmp(X,Y,Z), not(porte1(X,Y,Z)), porte2(X,Y,Z), porte3(X,Y,Z). 

