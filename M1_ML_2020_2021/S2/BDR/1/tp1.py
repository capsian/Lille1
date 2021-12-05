import random
from disque import *

def flux_carres(n):
    """Flux des carrés de 0 à n-1"""
    for i in range(n):
        yield i*i

def somme_carres(n):
    """Calcule la somme des carrés de 0 à n-1."""
    res = 0
    for i in flux_carres(n):
        res += i
    return res

#def carres(n):
#    res = []
#    for i in range(n):
#        print("foo")
#        res.append(i*i)
#    return res

#def flux_carres_bis(n):
#      for i in range(n):
#        print("bar")
#        yield i*i

#for c in carres(10):
#      print(c)

#for c in flux_carres_bis(10):
#      print(c)


def somme_carres_bis(n):
    return sum([i*i for i in range(n)])

def somme_carres_ter(n):
    res = 0
    for k in (i*i for i in range(n)):
        res+=k
    return k

def somme_carres_quad(n):
    return sum(i*i for i in range(n))

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

def exemple_table():
    """Exemple d'utilisation de la fonction table. Génère une table de 10 éléments
comportant les attributs 'a' et 'b' et les affiche en flux."""
    schema = {'a': (0,10), 'b': (100,100000)}
    for tuple_tbl in table(schema,nb=10):
        print(tuple_tbl)

def projection(table, champs):
    """
    Renvoie la table (sous forme de flux) obtenue à partir des tuples contenus
    dans ~table~ en n'y conservant que les attributs (les clés) qui sont
    contenus dans ~champs~.

    Renvoie une exception si un attribut de ~champs~ n'est pas un attribut des
    tuples de ~table~.
    """
    for tp in table:
        tp_res = {}
        for c in champs:
            tp_res[c] = tp[c]
        yield tp_res


def exemple_projection():
    """Exemple d'utilisation de la projection."""
    schema = {'a': (1, 10), 'b': (40, 100), 'c': (20,30)}
    for tuple_res in projection(table(schema ,nb=100),
                                ['a', 'c']):
        print(tuple_res)
#exemple_projection()
        
def transformation(table, f):
    """Renvoie un flux obtenu en appliquant ~f~ à chacun des tuples composant
~table~."""
    for tp in table:
        yield f(tp)

def exemple_transformation():
    schema = {'a': (1, 10), 'b': (40, 100), 'c': (20,30)}
    f = lambda tp: {'a': tp['a'], 'm': (tp['b']+tp['c'])//2}
    for tuple_res in transformation(table(schema,nb=100), f):
        print(tuple_res)
print("exemple_transformation")
exemple_transformation()

def projection2(table, champs):
    """
    Renvoie la table (sous forme de flux) obtenue à partir des tuples contenus
    dans ~table~ en n'y conservant que les attributs (les clés) qui sont
    contenus dans ~champs~.

    Renvoie une erreur si un attribut de ~champs~ n'est pas un attribut des
    tuples de ~table~.
    """
    f = lambda tp: {champ: tp[champ] for champ in champs}
    for dic in transformation(table, f):
        yield dic
    
def exemple_projection2():
    """Exemple d'utilisation de la projection."""
    schema = {'a': (1, 10), 'b': (40, 100), 'c': (20,30)}
    for tuple_res in projection(table(schema ,nb=100),
                                ['a', 'c']):
        print(tuple_res)
print("exemple_projection2")
exemple_projection2()

def union(t1, t2):
    """Construit un flux qui énumère les éléments de ~t1~ puis ceux de ~t2~."""
    for t in t1:
        yield t
    for tt in t2:
        yield tt

def exemple_union():
    """Exemple d'utilisation de la fonction union."""
    schema1 = {'a':(30, 100), 'b': (10, 50)}
    schema2 = {'a': (40, 50), 'n': (100, 200), 'm': (0,10)}
    f = lambda tp: {'a': tp['a']//2, 'b': (tp['m']*tp['m'])//4}
    for tp in union(table(schema1, nb = 10),
                    transformation(table(schema2,nb=10),f)):
        print(tp)
print("exemple_union")
exemple_union()

def selection(table, pred):
    """Construit le flux des éléments de ~table~ qui satisfont le prédicat
       ~pred~ (fonction des tuples dans les booléens)."""
    for tp in table:
        if pred(tp):
            yield tp

def exemple_selection():
    for un_tuple in selection(table({'a': (30, 100), 'b': (10, 50)}, nb=10),
               lambda tp: tp['a'] > 50 and tp['b'] < 45):
        print(un_tuple)
print("exemple_selection")
exemple_selection()

def selection_index(fichier, idx, valeurs) :
    """
    On suppose que ~fichier~ contient des tuples dont l'une des colonnes est
    indexée par ~idx~. La fonction renvoie le flux des tuples qui associe a la
    colonne indexée une valeur dans la séquence ~valeurs~.

    Attention : si un élément de ~valeurs~ n'est pas référencé dans ~idx~, on
    souhaite qu'il n'y ait pas d'erreur.
    """
    for v in valeurs:
        for v in idx:
            for tp in trouve_sur_disque(fichier,idx[v]):
                yield tp
    
def exemple_selection_index():
    schema = {'a' : (0,10), 'b' : (1,10000000)}
    tbl = table(schema, nb=1000000)
    fichier = "/tmp/tbl.table"
    mem_sur_disque(tbl, fichier)
    idx = index_fichier(fichier, 'a')
    for tp in selection_index(fichier, idx, range(2,5)):
        print(tp)
print("selection_index")
exemple_selection()

def appariement(t1, t2):
    """Renvoie un tuple ayant pour clé les clés de ~t1~ et de ~t2~.

    Lorsqu'une clé n'apparaît que dans un tuple la valeur que lui associe ce
    tuple est celle associée à la clé dans le résultat.

    À une clé qui apparaît dans les deux tuples, le résultat associe la valeur
    que lui associe ~t2~.
    """
    tp_res = {}
    
    for k in t1.keys():
        tp_res[k] = t1[k]
    for k in t2.keys():
        tp_res[k] = t2[k]
    
    return tp_res

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
            
def exemple_prod_cart():
    tb1 = table({'a': (1,1)}, nb=2)
    tb2 = table({'b': (2,2)}, nb=2)
    for tp in produit_cartesien(tb1,tb2):
        print(tp)
print("exemple_prod_cart")
exemple_prod_cart()

def produit_cartesien_fichier(fichier1, fichier2):
    """Construit le flux de tuples obtenus en appariant tous les tuples contenus
    dans les fichiers ~fichier1~ et ~fichier2~.

    Ce flux correspond au produit cartésien des deux tables contenues dans les
    fichiers produit par l'algorithme double boucle :
    - la table contenue dans ~fichier1~ est utilisée dans la boucle extérieure,
    - la table contenue dans ~fichier2~ est la table utilisée dans la boucle intérieure.

    """
    for tp1 in selection_index(fichier1, idx, valeurs):
        for tp2 in table2:
            yield appariement(tp1,tp2)
    
    yield {}

    
def exemple_produit_cartesien_fichier():
    tb = [table({'a': (1,1)}, nb=2), table({'b': (2,2)}, nb=2)]
    fichiers = ["/tmp/tb1.table", "/tmp/tb2.table"]
    for i in range(2): mem_sur_disque(tb[i], fichiers[i])
    for tp in produit_cartesien_fichier(fichiers[0],fichiers[1]): print(tp)
print("exemple_produit_cartesien_fichier")
exemple_produit_cartesien_fichier()

def jointure_theta(fichier1, fichier2, pred):
    """Renvoie le flux des appariements de tuples contenus dans les tables des
    fichiers ~fichier1~ et ~fichier2~" qui satisfont la propriété du prédicat
    ~pred~ (fonction des tuples dans les booléens)."""
    yield {}

def jointure_naturelle(fichier1, fichier2):
    """Renvoie le flux des tuples de la jointure naturelle des tables contenues
    dans ~fichier1~ et ~fichier2~.

    Il s'agit des appariements des tuples provenant des tables contenues dans
    ~fichier1~et ~fichier2~ qui associent les mêmes valeurs à leurs attributs
    communs.
    """
    for t1 in lire_sur_disque(fichier1):
        for t2 in lire_sur_disque(fichier2):
            if all((t1[k] == t2[k] for k in t1 if k in t2)):
                yield apparriement(t1, t2)

def jointure_naturelle_mem(fichier1, fichier2):
    """Renvoie le flux des tuples de la jointure naturelle des tables contenues
    dans ~fichier1~ et ~fichier2~.

    L'un des deux fichiers est chargé en mémoire afin qu'il ne soit lu qu'une
    seule fois.

    Il s'agit des appariements des tuples provenant des tables contenues dans
    ~fichier1~et ~fichier2~ qui associent les mêmes valeurs à leurs attributs
    communs.

    """
    tb2 = list(lire_sur_disque(fichier2))
    for t1 in lire_sur_disque(fichier1):
        for t2 in lire_sur_disque(fichier2):
            if all((t1[k] == t2[k] for k in t1 if k in t2)):
                yield apparriement(t1, t2)
    

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
    for k in index1:
        if k in index2:
            for tp1 in trouve_sur_disque(fichier1, index1[k]):
                for tp2 in trouve_sur_disque(fichier2, index2[k])
                    yield appariement(tp1, tp2)

def jointure_triee(table1, col1, table2, col2):
    """Implémente la jointure de ~table1~ et ~table2~ sous la condition que les
    valeurs de l'attribut ~col1~ de ~table1~ soient égales aux valeurs de
    l'attribut ~col2~ de ~table2~.

    On suppose que ~table1~ est triée suivant les valeurs croissantes de ~col1
    et que ~table2~ est triée suivant les valeurs croissantes de ~col2~.
    """
    yield {}
