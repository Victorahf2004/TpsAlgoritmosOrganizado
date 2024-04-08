import sys
import heapq
from collections import deque
class Node:
    def __init__(self):
        self.parent = None
        self.profundidade = 0
        self.state = None 
        self.cost = None
    def __hash__(self):
        return hash((self.state, self.profundidade))
    def __lt__(self, other):
        return self.cost < other.cost
    def __eq__(self, other):
        if isinstance(other, Node):
            return self.state == other.state
        return False
class Problem:
    def __init__(self, initial_state, goal_state):
        self.initial_state = initial_state
        self.endGoal = goal_state
def solution(no, fronteiras, imprimir):
    caminho2 = deque([no])
    contador = 0
    if not fronteiras:
        contador = 0
        print('0')
        print('')
        for number in no.state.split(' '):
            if (number == '0'): 
                print(' ', end=' ')
            else: 
                print(number, end=' ')
            contador += 1
            if (contador == 3):
                contador = 0
                print('')
    else:
        if (no.state) in fronteiras:
            ultimo = fronteiras[len(fronteiras) - 1]
            counter = 0
            while (no.state in fronteiras):
                if (counter < 1):
                    pai = no.parent
                    caminho2.appendleft(pai)
                    no = pai
                    if (fronteiras.index(pai.state) == 0): 
                        counter = 1
                        break
            caminho2 = list(caminho2)
            caminho3 = []
            for elem in caminho2:
                caminho3.append(elem.state)
            print(f'{(len(caminho3)) - 1}')
            print('')
            # print(f'O caminho é:{caminho3}')
            contador = 0
            if (imprimir):
                for elem in caminho3:
                    numbers = elem.split(' ')
                    for number in numbers:
                        if (number == '0'): print(' ', end=' ')
                        else: print(number, end=' ')
                        contador += 1
                        if (contador == 3):
                            contador = 0
                            print('')
                    print('')
def retornarEstado(matriz):
    state = ''
    for submatriz in matriz:
        for elemento in submatriz:
            state += elemento
            state += ' '
    state = state[:-1]
    return state
def action(estado, mov):
    matriz = [] #original
    submatriz = []
    contador = 0
    indicesMatrizes = 0
    matrizVazio = 0
    for numero in estado:
        if (contador < 3):
            if (numero != ' '):
                submatriz.append(numero)
                contador += 1
                if (numero == '0'): 
                    matrizVazio = indicesMatrizes 
        else:
            if (submatriz): matriz.append(submatriz)
            submatriz = []
            indicesMatrizes += 1
            contador = 0
    if (submatriz): matriz.append(submatriz)
    matrizOriginal = matriz
    # print(f'A matriz é:{matrizOriginal}')
    subIndex = matriz[matrizVazio].index('0')
    naoAdequado = 'Nao'
    if mov == 'left':
        if (subIndex > 0):
            auxiliar = None
            auxiliar = matriz[matrizVazio][subIndex]
            matriz[matrizVazio][subIndex] = matriz[matrizVazio][subIndex - 1]
            matriz[matrizVazio][subIndex - 1] = auxiliar
            resultado = retornarEstado(matriz)
            # print(f'O elemento é: {matriz[matrizVazio][1]}')
            # print(f'A matriz é: {matriz}')
            # print(f'A nova matriz é:{matriz}')
            # print(f'O resultado é: {resultado}')
            return resultado
        return naoAdequado
    if mov == 'right':
        if (subIndex < 2):
            auxiliar = None
            auxiliar = matriz[matrizVazio][subIndex]
            matriz[matrizVazio][subIndex] = matriz[matrizVazio][subIndex + 1]
            matriz[matrizVazio][subIndex + 1] = auxiliar
            resultado = retornarEstado(matriz)
            # print(f'A nova matriz é:{matriz}')
            # print(f'O resultado é: {resultado}')
            return resultado
        return naoAdequado
    if mov == 'up':
        if (matrizVazio > 0):
            auxiliar = None
            auxiliar = matriz[matrizVazio-1][subIndex]
            matriz[matrizVazio-1][subIndex] = matriz[matrizVazio][subIndex]
            matriz[matrizVazio][subIndex] = auxiliar
            resultado = retornarEstado(matriz)
            # print(f'A nova matriz é:{matriz}')
            # print(f'O resultado é: {resultado}')
            return resultado
        return naoAdequado
    if mov == 'down':
        if (matrizVazio < 2):
            auxiliar = None
            auxiliar = matriz[matrizVazio+1][subIndex]
            matriz[matrizVazio+1][subIndex] = matriz[matrizVazio][subIndex]
            matriz[matrizVazio][subIndex] = auxiliar
            resultado = retornarEstado(matriz)
            # print(f'A nova matriz é:{matriz}')
            # print(f'O resultado é: {resultado}')
            return resultado
        return naoAdequado
def ids(problema, imprimir):
    profundidade = 0
    caminho = []
    node = Node()
    node.state = problema.initial_state
    if (node.state == problema.endGoal):
        return solution(node, caminho, imprimir)
    while True:
        resultado = dls(problema, profundidade, caminho)
        if (type(resultado) != str):
            if (resultado.state == problema.endGoal):
                return solution(resultado, caminho, imprimir)
        profundidade += 1

def dls(problema, fundura, caminho):
    node = Node()
    node.state = problema.initial_state
    node.profundidade = 0
    frontier = []
    frontier.append(node)
    frontier_set = set()
    frontier_set.add(node)
    objetivo = problema.endGoal
    movimentos = ['left', 'up', 'right', 'down']
    explored = set()
    while frontier_set:
        node = frontier.pop()
        frontier_set.remove(node)
        if (node.state == objetivo):
            return node
        if (node.profundidade > fundura):
            continue
        explored.add(node)
        caminho.append(node.state)
        for mov in movimentos:
            child = Node()
            child.state = action(node.state, mov)
            if (child.state == 'Nao'): continue
            if (child not in explored and child not in frontier_set):
                child.profundidade = node.profundidade + 1
                child.parent = node
                frontier.append(child)
                frontier_set.add(child)
                caminho.append(child.state)
    return 'falha'
# printVar = False
# if len(sys.argv) == 1:
#     print('Nenhum argumento da linha de comando fornecido.')
#     sys.exit()
# if len(sys.argv) > 1:
#     argumentos = sys.argv[1:]
#     tamanho = len(argumentos) - 1
#     if ((argumentos[len(argumentos) - 1]) == 'PRINT'): 
#         printVar = True
#         argumentos = argumentos[:tamanho]
#     # tamanho = len(argumentos) - 1
#     # argumentosSemPrint = argumentos[:tamanho]
#     string = ' '.join(argumentos)
#     estadoInicial = string
# # else:
# #     print('Nenhum argumento da linha de comando fornecido.')
# goal = '1 2 3 4 5 6 7 8 0'
# problema1 = Problem(estadoInicial, goal)
# ids(problema1, printVar)