import sys
import heapq
from collections import deque
class Node:
    def __init__(self):
        self.parent = None
        self.action = None
        self.state = None 
        self.costH = None
        self.costG = None
        self.costF = None
    def __hash__(self):
        return hash((self.state, self.costG, self.costH, self.costF))
    def __lt__(self, other):
        return self.costF < other.costF
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
def CustoNo(estado):
    estadoLista = estado.split()
    heuristicaTotal = 0
    if (estadoLista[0] != '1'):
        posDeveria = estadoLista.index('1')
        heuristicaParcial = posDeveria - 0
        heuristicaTotal += heuristicaParcial
    if (estadoLista[1] != '2'):
        posDeveria = estadoLista.index('2')
        heuristicaParcial = posDeveria - 1
        heuristicaTotal += heuristicaParcial
    if (estadoLista[2] != '3'):
        posDeveria = estadoLista.index('3')
        heuristicaParcial = posDeveria - 2
        heuristicaTotal += heuristicaParcial
    if (estadoLista[3] != '4'):
        posDeveria = estadoLista.index('4')
        heuristicaParcial = posDeveria - 3
        heuristicaTotal += heuristicaParcial
    if (estadoLista[4] != '5'):
        posDeveria = estadoLista.index('5')
        heuristicaParcial = posDeveria - 4
        heuristicaTotal += heuristicaParcial
    if (estadoLista[5] != '6'):
        posDeveria = estadoLista.index('6')
        heuristicaParcial = posDeveria - 5
        heuristicaTotal += heuristicaParcial
    if (estadoLista[6] != '7'):
        posDeveria = estadoLista.index('7')
        heuristicaParcial = posDeveria - 6
        heuristicaTotal += heuristicaParcial
    if (estadoLista[7] != '8'):
        posDeveria = estadoLista.index('8')
        heuristicaParcial = posDeveria - 7
        heuristicaTotal += heuristicaParcial
    if (estadoLista[8] != '0'):
        posDeveria = estadoLista.index('0')
        heuristicaParcial = posDeveria - 8
        heuristicaTotal += heuristicaParcial
    return heuristicaTotal
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
def A(problema, impresso):
    caminho = []
    objetivo = problema.endGoal
    node = Node()
    node.state = problema.initial_state
    node.costG = 0
    node.costH = CustoNo(node.state)
    node.costF = node.costG + node.costH
    node.parent = None
    open = []
    open_set = set()
    heapq.heappush(open, node)
    open_set.add(node)
    closed = set()
    explored = set()
    while open:
        node = heapq.heappop(open)
        if (node.state == objetivo):
            return solution(node, caminho, impresso)
        open_set.remove(node)
        heapq.heapify(open)  # Reorganize a lista em um heap
        closed.add(node.state)  # Adicione apenas o estado do nó ao conjunto closed
        explored.add(node.state)
        movimentos = ['left', 'up', 'right', 'down']
        caminho.append(node.state)
        for mov in movimentos:
            child = Node()
            estadoAtual = node.state
            child.state = action(estadoAtual, mov)
            # print(f'O estado é:{child.state}')
            if (child.state == 'Nao'): continue
            if (child.state in explored): continue
            caminho.append(child.state)
            explored.add(child.state)
            if (child.state not in closed):  # Verifique se child.state está em closed, não child
                if (child not in open_set):
                    child.costG = node.costG + 1
                    child.costH = CustoNo(child.state)
                    child.costF = child.costG + child.costH
                    child.parent = node
                    open_set.add(child)  # Use add() para adicionar um único elemento a um conjunto
                    heapq.heappush(open, child)  # Adicione child à lista open, não node
                elif ((node.costG + 1) < (child.costG)):
                    child.costG = node.costG + 1
                    child.costF = child.costG + child.costH
                    child.parent = node
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
# # estadoInicial = '8 6 7 2 5 4 3 0 1'
# goal = '1 2 3 4 5 6 7 8 0'
# problema1 = Problem(estadoInicial, goal)
# A(problema1, printVar)