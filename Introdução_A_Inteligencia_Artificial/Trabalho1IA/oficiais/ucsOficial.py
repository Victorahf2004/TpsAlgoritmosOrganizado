import sys
import heapq
from collections import deque
class Node:
    def __init__(self):
        self.parent = None
        self.action = None
        self.state = None 
        self.cost = None
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
# caminhoS = []
def solution(no, fronteiras, imprimir):
    caminho2 = deque([no])
    contador = 0
    # caminhoS.append(len(fronteiras))
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
            contador = 0
            # print(f'O caminho é: {caminho3}')
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
            return resultado
        return naoAdequado
    if mov == 'down':
        if (matrizVazio < 2):
            auxiliar = None
            auxiliar = matriz[matrizVazio+1][subIndex]
            matriz[matrizVazio+1][subIndex] = matriz[matrizVazio][subIndex]
            matriz[matrizVazio][subIndex] = auxiliar
            resultado = retornarEstado(matriz)
            return resultado
        return naoAdequado
def ucs(problema, imprimir2):
    node = Node()
    node.state = problema.initial_state
    objetivo = problema.endGoal
    node.cost = 0
    caminho = []
    frontier = []
    frontier_set = set()
    frontier_set.add(node.state)
    heapq.heappush(frontier, node)
    explored = set()
    movimentos = ['left', 'up', 'right', 'down']
    while frontier:
        # node = frontier.pop()
        node = heapq.heappop(frontier)
        if (objetivo == node.state):
            print('oi')
            return solution(node, caminho, imprimir2)
        explored.add(node.state)
        caminho.append(node.state)
        for mov in movimentos:
            child = Node()
            estadoAtual = node.state
            child.state = action(estadoAtual, mov)
            child.parent = node
            child.cost = node.cost + 1
            estado = child.state
            if (estado == 'Nao'): continue
            if (estado in explored): continue
            caminho.append(child.state)
            if estado not in explored or estado not in frontier_set:
                heapq.heappush(frontier, child)
                frontier_set.add(child.state)
            elif estado in frontier_set:
                for i in range(len(frontier)):
                    if ((frontier[i].state) == estado and frontier[i].cost > child.cost):
                        frontier[i] = child
                        heapq.heapify(frontier)  # Reordenar o heap após a atualização
                        break
    print('Failure')
    return 0
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
# ucs(problema1, printVar)

# printVar = False
# tempos = []
# estadosIniciais = ['1 2 3 4 5 6 7 8 0', '1 2 3 4 5 6 7 0 8', '1 2 3 4 0 5 7 8 6', '1 0 3 4 2 5 7 8 6', '1 5 2 4 0 3 7 8 6', '1 5 2 0 4 3 7 8 6', '1 5 2 4 8 3 7 6 0', '1 5 2 4 8 0 7 6 3', '0 5 2 1 8 3 4 7 6', '1 0 2 8 5 3 4 7 6', '5 8 2 1 0 3 4 7 6']
# goal = '1 2 3 4 5 6 7 8 0'
# for inicio in estadosIniciais:
#     problema1 = Problem(inicio, goal)
#     comeco = time.time()
#     ucs(problema1, printVar)
#     fim = time.time()
#     tempo = comeco - fim
#     tempos.append(tempo)
# print(f'Os tempos são: {tempos}')
# print(f'Os tamanhos são: {caminhoS}')