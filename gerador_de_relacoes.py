#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
    Gerador de relações
    Vinícius R. Miguel, Gustavo B. de Oliveira, Davi J. Alves, Ivan dos S. Muniz, Melissa F. Mendes, Eduardo M. Pereira
"""

from itertools import combinations
from random import choice as choose
from sys import exit

# -- Códigos ANSI para colorir texto -- #

AVISO = '\033[93m'
FIM = '\033[0m'

# ------------------------------------- #


# -- Flags de controle -- #

is_null          = None
is_reflexive     = None
is_symmetric     = None
is_transitive    = None
is_antisymmetric = None

# ----------------------- #


# -- Funções auxiliares -- #

''' Adiciona relações quase-reflexivas no conjunto de relações. 
	Por exemplo, se A = {1, 2, 3}, adiciona coisas como {(1,1), (3,3)}'''
def add_non_reflexive():       # Tudo certo aqui
    ref_set = [[x, x] for x in A]   # Relação reflexiva em A
    for i in range(n):  # Pra cada i em {1 .. n-1} ...
        for quasireflexive in combinations(ref_set, i):  # .. adicionaremos elementos tais que ..
            rel_set.append(list(quasireflexive))  # .. a relação seja quase reflexiva

def add_symmetric():
    for rel in rel_set:
        for pair in combinations(A, 2):
            pair = list(pair)
            if pair[0] != pair[1]:
                if choose([True, False]):     # Escolher aleatóriamente se o par será posto na
                    rel.append(pair)
                    # Adiciona pares até aqui -- reutilizar em add_non_symmetric
                    rel.append(pair[::-1])

def add_non_symmetric():
    for rel in rel_set:
        for pair in combinations(A, 2):
            pair = list(pair)
            if pair[0] != pair[1]:
                if choose([True, False]):     # Escolher aleatóriamente se o par será posto na
                    rel.append(pair)
                    if choose([True, False]): rel.append(pair[::-1])   # Escolhe aleatóriamente quais pares inversos serão adicionados
        for pair in rel:
            symmetric_pairs = 0
            if rel[::-1] in pair:
                symmetric_pairs += 1
        if symmetric_pairs == len(rel): # Se todos os pares tiverem seus inversos, a função é simétrica. Devemos mudar isso.
            for pair in rel:
                if pair[0] != pair[1]:
                    if pair[::-1] in rel:
                        rel.remove(pair[::-1])

def add_transitive():
    for relation in rel_set:
        for pair in relation:
            if not isinstance(pair, list):
                pair = list(pair)

    for relation in rel_set:
        for [x,y] in relation:
            for [z, w] in relation:
                if [x,y] == [z,w]: continue 
                if y == z:  # Para cada (x,y) e (z,w), com y=z, verificaremos se (x,w) está em R, de forma com que R seja transitiva.
                    if [x, w] not in relation: relation.append([x,w])

def add_non_transitive():
    if is_antisymmetric:
        return  # Se é antissimétrica, então é melhor nada fazer
    for relation in rel_set:
        for pair in relation:
            if not isinstance(pair, list):
                pair = list(pair)
    for relation in rel_set:
        for [x,y] in relation:
            for [z, w] in relation:
                if [x,y] == [z, w]: continue
                if y == z:
                    if choose([True, False]):
                        if [x, w] not in relation: relation.append([x, w])
        for [x,y] in relation:
            for [z, w] in relation:
                if [x, y] == [z, w]: continue
                if y == z:
                    if [x, w] in relation:  # Verifica se existe pelo menos um caso não-transitivo.
                        relation.remove([x,w])
                        break                

def add_antisymmetric():
    for relation in rel_set:
        for pair in relation:
            if not isinstance(pair, list): pair = list(pair)
            if pair[0] == pair[1]: continue # Não quebrar reflexividade
            if pair[::-1] in relation:
                relation.remove(pair[::-1])

def add_reflexive():
    for i in range(1, 8):
        rel_set.append([[x, x] for x in A])  # Adicionando a única relação reflexiva em A.

def remove_repetition(list_a):
    for ind_i, val_i in enumerate(list_a):
        for ind_j, val_j in enumerate(list_a):
            if ind_i == ind_j:
                continue
            if val_i == val_j:
                list_a.remove(val_i)

# Função pretty-print para exibir o conjunto de relações com notação correta.
def pprint(rel_set):
    
    if [] in rel_set:
        if not is_null:
            rel_set = list(filter(lambda x: x != [], rel_set))
    else:
        if is_null:
            rel_set.insert(0, [])
    for relation in rel_set:
        remove_repetition(relation)
    remove_repetition(rel_set)
    for rel_str in rel_set:
        rel_str = list(str(rel_str))
        rel_str[0] = '{';
        rel_str[-1] = '}'
        print("".join(rel_str).replace('[', '(').replace(']', ')') + '\n')

# ------------------------ #

# -- Obtenção de flags -- #

# Passo 1: Obter n tal que A = {1, ..., n}

try:
    n = int(input("Digite n: "))    
except ValueError:
    raise ValueError("Um número inteiro positivo deve ser digitado.")
    
if n <= 0:
    raise ValueError("n deve ser um número inteiro positivo.")
    

A = list(range(1, n + 1))  # Conjunto na qual todas as relações serão definidas
print('As relações serão definidas em: ')
pprint([A])
print('Como xRy ⫅ A² e |A| = n, então o número de relações em A é dado por 2^(n*n) = ' + str(2**(n*n)) + '.')

rel_set = []  # Conjunto que contém todas as relações

# Passo 2: Verificar se a relação é não-vazia.

print("\nResponda às seguintes perguntas com 's' (sim), 'n' (não) ou 'i' (indiferente)\n")

prompt = input("A relação é não-vazia?      (S\\n\i) ")

if prompt.lower() == 's':
    is_null = False

elif prompt.lower() == 'n':
    is_null = True

elif prompt.lower() == 'i':
    print("Assumindo que sim.\n")
    is_null = False
    
else:
    raise Exception("Entrada inválida.")

# Passo 3: Verificar se R é reflexiva.

prompt = input("A relação é reflexiva?      (S\\n\i) ")

if prompt.lower() == 's':
    if is_null:
        print(AVISO + "Relações vazias não podem ser reflexivas" + FIM)
        is_null = False
    is_reflexive = True
    
elif prompt.lower() == 'n':
    is_reflexive = False  # Adicionar relações quase-reflexivas em rel_set.
    
elif prompt.lower() == 'i':
    print("Assumindo que a relação é reflexiva.")
    if is_null:
        print(AVISO + "\nAviso: Relações vazias não podem ser reflexivas!" + FIM)
        is_null = False
    is_reflexive = True
else:
    raise Exception("Entrada inválida.")    

# Passo 4: Verificar se R é simétrica.

prompt = input("A relação é simétrica?      (S\\n\i) ")
if prompt.lower() == 's':
    is_symmetric = True  # Adicionar (x,y) e (y,x) com x, y, x not y, em A em R.

elif prompt.lower() == 'n':
    is_symmetric = False  # Adicionar para todo x,y em A, adicionar alguns (x,y) e alguns (y,x) em R, de forma que R não seja simétrica.

elif prompt.lower() == 'i':
    is_symmetric = True
    print("Assumindo que a relação é simétrica.\n")  # TODO: Construir e adicionar relações como no caso 's'

else:
    raise Exception("Entrada inválida.")

# Passo 5: Verificar se R é antissimétrica.

prompt = input("A relação é antissimétrica? (S\\n\i) ")
if prompt.lower() == 's':
    is_antisymmetric = True  # Se (x,y), x != y, está em R, então (y,x) não poderá estar em R

elif prompt.lower() == 'n':
    is_antisymmetric = False

elif prompt.lower() == 'i':
    print("Assumimos que a relação não é antissimétrica.")
    is_antisymmetric = False

else:
    raise Exception("Entrada inválida.")

# Passo 6: Verificar se R é transitiva.

prompt = input("A relação é transitiva?     (S\\n\i) ")

if prompt.lower() == 's':
    is_transitive = True
elif prompt.lower() == 'n':
    is_transitive = False
    if is_antisymmetric and is_symmetric:
        raise Exception("Não há relação simétrica, antissimétrica e não transitiva")
elif prompt.lower() == 'i':
    print('Assumimos que a relação é transitiva.')
    is_transitive = True
else:
    raise Exception("Entrada inválida.")
# ----------------------- #

# -- Obtendo relações -- #

if is_reflexive: 
    add_reflexive()
else: 
    add_non_reflexive()
    
if is_symmetric and is_antisymmetric:   # Se for simétrica e antissimétrica, então é transitiva (e de igualdade)
    #rel_set = [rel for rel in rel_set if x==y]
    #print('Adicionando simétrico & antissimétrico')
    for relation in rel_set:
        for [x,y] in relation:
            if x != y:  # Não quebrar reflexividade
                relation.remove([x,y])
    pprint(rel_set)
    exit(1)
    
if is_symmetric: 
    add_symmetric()
else: 
    add_non_symmetric()

if is_transitive: 
    add_transitive()
#else: 
    #add_non_transitive()

if is_antisymmetric: 
    add_antisymmetric()

if not is_reflexive:    # Função auxiliar para verificar se a reflexividade não foi acidentalmente adicionada por outras funções
    for relation in rel_set:
        for pair in relation:
            if not isinstance(pair, list): pair = list(pair)

    reflexivity = True
    for relation in rel_set:
        for elem in A:
            if [elem, elem] not in relation:
                reflexivity = False
                break
        if reflexivity:
            elem = choose(A)
            relation.remove([elem, elem])
        reflexivity = True

print('\n ----------------------------------- \n')
print("Algumas das relações encontradas que seguem as propriedades requeridas são: ")
pprint(rel_set)
