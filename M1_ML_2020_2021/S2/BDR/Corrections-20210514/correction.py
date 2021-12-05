import random
from disque import *

def table(descr, nb=10000):
    """Cette fonction génère une séquence de tuples décrits par le dictionnaire
    descr. Le dictionnaire associe à une clé une paire (k,l). La fonction
    génère nb dictionnaires de la manière suivante :
    - chaque clé de descr est une clé de ces dictionnaires
    - à chacune de ces clés x, ces dictionnaires associent un nombre tiré au hasard
      entre k et l lorsque la paire (k,l) est associée à x dans descr.
    NB : cette fonction requiert d'importer le module random.
    """
    for _ in range(nb):
        tuple_res = {}
        for a, (k,l) in descr.items():
            tuple_res[a] = random.randint(min(k, l), max(k, l))
        yield tuple_res

def projection(table, champs):
    """Renvoie la table (sous forme de flux) obtenue à partir des tuples contenus
      dans ~table~ en n'y conservant que les attributs (les clés) qui sont contenus
      dans ~champs~.

      Renvoie une exception si un attribut de ~champs~ n'est pas un attribut des tuples de ~table~."""
    for tuple_tbl in table:
        tuple_res = {}
        for ch in champs:
            tuple_res[ch] = tuple_tbl[ch]
        yield tuple_res

def transformation(table, f):
    """Renvoie un flux obtenu en appliquant ~f~ à chacun des tuples composant
~table~."""
    return (f(tp) for tp in table)

def projection2(table, champs):
    """Renvoie la table (sous forme de flux) obtenue à partir des tuples contenus
dans ~table~ en n'y conservant que les attributs (les clés) qui sont contenus
dans ~champs~.

    Renvoie une erreur si un attribut de ~champs~ n'est pas un attribut des tuples de ~table~."""
    def f(tp):
        tuple_res = {}
        for ch in champs:
            tuple_res[ch] = tp[ch]
        return tuple_res
    return transformation(table,f)

def union(tbl1, tbl2):
    """construit un flux qui énumère les éléments de ~t1~ puis ceux de ~t2~."""
    for tp in tbl1:
        yield tp
    for tp in tbl2:
        yield tp

def union(tbl1, tbl2):
    """construit un flux qui énumère les éléments de ~t1~ puis ceux de ~t2~."""
    yield from tbl1
    yield from tbl2

def selection(table, pred):
    """Construit le flux des éléments de ~table~ qui satisfont le prédicat
       ~pred~ (fonction des tuples dans les booléens)."""
    return (tp for tp in table if pred(tp))

def selection_index(fichier, idx, valeurs):
    """
    On suppose que ~fichier~ contient des tuples dont l'une des colonnes est
    indexée par ~idx~. La fonction renvoie le flux des tuples qui associe a la
    colonne indexée une valeur dans la séquence ~valeurs~.

    Attention : si un élément de ~valeurs~ n'est pas référencé dans ~idx~, on
    souhaite qu'il n'y ait pas d'erreur.
    """
    for v in valeurs:
        if v in idx:
            for tp in trouve_sur_disque(fichier,idx[v]):
                yield tp

def appariement(t1, t2):
    """Renvoie un tuple ayant pour clé les clés de ~t1~ et de ~t2~.

    Lorsqu'une clé n'apparaît que dans un tuple la valeur qui lui associe ce
    tuple est celle associée à la clé dans le résultat.

    À une clé qui apparaît dans les deux tuples, le résultat associe la valeur
    que lui associe ~t2~.
    """
    tuple_res = {}
    for v in t1:
        tuple_res[v] = t1[v]
    for v in t2:
        tuple_res[v] = t2[v]
    return tuple_res

def produit_cartesien(table1, table2):
    """Construit le flux de tuples obtenus en appariant tous les tuples de
    ~table1~ et de ~table2~.

    Ce flux correspond au produit cartésien des deux tables produit par l'algorithme double boucle :
    - ~table1~ est la table utilisée dans le boucle extérieure,
    - ~table2~ est la table utilisée dans la boucle intérieure.
    """
    for tp1 in table1:
        for tp2 in table2:
            yield appariement(tp1,tp2)

def produit_cartesien_fichier(fichier1, fichier2):
    """Construit le flux de tuples obtenus en appariant tous les tuples contenus
    dans les fichiers ~fichier1~ et ~fichier2~.

    Ce flux correspond au produit cartésien des deux tables contenues dans les
    fichiers produit par l'algorithme double boucle :
    - la table contenue dans ~fichier1~ est utilisée dans le boucle extérieure,
    - la table contenue dans ~fichier2~ est la table utilisée dans la boucle intérieure.

    """
    for tp1 in lire_sur_disque(fichier1):
        for tp2 in lire_sur_disque(fichier2):
            yield appariement(tp1,tp2)

def jointure_theta(fichier1, fichier2, pred):
    """Renvoie le flux des appariements de tuples contenus dans les tables des
    fichiers ~fichier1~ et ~fichier2~" qui satisfont la propriété du prédicat
    ~pred~ (fonction des tuples dans les booléens)."""
    return selection(produit_cartesien_fichier(fichier1, fichier2), pred)

def jointure_naturelle_mem(fichier1, fichier2):
    """Renvoie le flux des tuples de la jointure naturelle des tables contenues
    dans ~fichier1~ et ~fichier2~.

    Le fichier ~fichier2~ est chargé en mémoire afin qu'il ne soit lu qu'une
    seule fois. Les deux fichiers ne sont lus depuis le disque qu'une seule
    fois.

    Il s'agit des appariements des tuples provenant des tables contenues dans
    ~fichier1~et ~fichier2~ qui associent les mêmes valeurs à leurs attributs
    communs.

    """
    table2 = list(lire_sur_disque(fichier2))
    for tp1 in lire_sur_disque(fichier1):
        for tp2 in table2:
            if all([tp1[k]==tp2[k] for k in tp1 if k in tp2]):
                yield appariement(tp1,tp2)

def jointure_index(table1, col1, fichier2, index):
    """Renvoie le flux des tuples de la jointure de la ~table1~ et de la table
    contenue dans ~fichier2~ sous la condition que les valeurs de l'attribut
    ~col1~ de ~table1~ soient identiques aux valeurs de l'attribut ~col2~ la
    table de ~fichier2~.

    ~index~ est un index de l'attribut ~col2~ dans ~fichier2~.
    """
    for tp1 in table1:
        if tp1[col1] in index:
            for tp2 in trouve_sur_disque(fichier2, index[tp1[col1]]):
                yield appariement(tp1,tp2)

def jointure_double_index(fichier1, index1, fichier2, index2):
    """Renvoie le flux de tuples obtenue par la jointure des tables contenues dans
     ~fichier1~ et ~fichier2~ avec la condition que les valeurs indexées par
     ~index1~ pour ~table1~ soient égaux aux valeurs indexées par ~index2~ pour
     ~table2~."""
    for k, adr1 in index1.items():
        if k in index2:
            adr2 = index2[k]
            for tp1 in trouve_sur_disque(fichier1, adr1):
                for tp2 in trouve_sur_disque(fichier2, adr2):
                    yield appariement(tp1,tp2)

def jointure_triee(table1, col1, table2, col2):
    """Implémente la jointure de ~table1~ et ~table2~ sous la condition que les
    valeurs de l'attribut ~col1~ de ~table1~ soient égales aux valeurs de
    l'attribut ~col2~ de ~table2~.

    On suppose que ~table1~ est triée suivant les valeurs croissantes de ~col1
    et que ~table2~ est triée suivant les valeurs croissantes de ~col2~.
    """
    def liste_invariant(tp,table,col):
        v=tp[col]
        res=[]
        while tp != None and tp[col]==v:
            res.append(tp)
            tp = next(table,None)
        return (res, tp)
    tp1 = next(table1, None)
    tp2 = next(table2, None)
    while tp1 != None and tp2 != None:
        v1 = tp1[col1]
        v2 = tp2[col2]
        if v1 < v2:
            (_, tp1) = liste_invariant(tp1, table1, col1)
        elif v1 > v2:
            (_, tp2) = liste_invariant(tp2, table2, col2)
        else:
            (r1,tp1) = liste_invariant(tp1, table1, col1)
            (r2,tp2) = liste_invariant(tp2, table2, col2)
            yield from produit_cartesien(r1, r2)

def minimum_table(table, col):
    """Renvoie la plus petite des valeurs associées à l'attribut ~col~ dans ~table~.
    Si ~table~ est vide, renvoie None.
    """
    m = None
    for tp in table:
        if m == None or m > tp[col]:
            m = tp[col]
    return m

def moyenne_table(table, col):
    """Renvoie la moyenne des valeurs que les tuples de ~table~ associent à
    l'attribut ~col~.
    Si ~table~ est vide, renvoie None.
    """
    somme = 0
    nb = 0
    for tp in table:
        somme += tp[col]
        nb += 1
    return None if nb == 0 else somme / nb

def ecart_type_table(table, col):
    """Renvoie l'écart type des valeurs que les tuples de ~table~ associent à
    l'attribut ~col~.
    Si ~table~ est vide, renvoie None.
    """
    somme_carres = 0
    somme = 0
    nb = 0
    for tp in table:
        somme_carres += tp[col]*tp[col]
        somme += tp[col]
        nb += 1
    if nb == 0:
        return None
    else:
        moy = somme/nb
        moy_dist2 = somme_carres/nb - moy * moy
        return  math.sqrt(moy_dist2)
