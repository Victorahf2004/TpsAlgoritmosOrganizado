import sys
from oficiais import AOficial
from oficiais import bfsOficial3
from oficiais import buscaGulosaOficial
from oficiais import HillClimbingFinal
from oficiais import idsFinal
from oficiais import ucsOficial

printVar = False
if len(sys.argv) == 1:
    print('Nenhum argumento da linha de comando fornecido.')
    sys.exit()
if len(sys.argv) > 1:
    argumentos = sys.argv[1:]
    tamanho = len(argumentos) - 1
    if ((argumentos[len(argumentos) - 1]) == 'PRINT'): 
        printVar = True
        argumentos = argumentos[:tamanho]
    algoritmo = argumentos[0]
    argumentos = argumentos[1:]
    string = ' '.join(argumentos)
    estadoInicial = string
    objetivo = '1 2 3 4 5 6 7 8 0'
    problema1 = AOficial.Problem(estadoInicial, objetivo)
    if (algoritmo == 'A'): AOficial.A(problema1, printVar)
    if (algoritmo == 'B'): bfsOficial3.bfs(problema1, printVar)
    if (algoritmo == 'G'): buscaGulosaOficial.greedy(problema1, printVar)
    if (algoritmo == 'H'): HillClimbingFinal.HillClimbing(problema1, printVar)
    if (algoritmo == 'I'): idsFinal.ids(problema1, printVar)
    if (algoritmo == 'U'): ucsOficial.ucs(problema1, printVar)