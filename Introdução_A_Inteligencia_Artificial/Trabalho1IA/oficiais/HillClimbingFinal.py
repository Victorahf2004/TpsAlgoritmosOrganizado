import heapq
import random
import sys
from collections import deque
import time
class Node:
    def __init__(self):
        self.parent = None
        self.action = None
        self.state = None 
        self.valor = None
    def __hash__(self):
        return hash((self.state, self.valor))
    def __lt__(self, other):
        return self.valor < other.valor
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
    if not fronteiras or (len(fronteiras) == 1):
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
def CustoNo(estado):
    valor = 9
    # print(f'A função é: {estado}')
    estadoLista = estado.split()
    # print(f'O estado lista é: {estadoLista}')
    if (estadoLista[0] != '1'): valor -= 1
    if (estadoLista[1] != '2'): valor -= 1
    if (estadoLista[2] != '3'): valor -= 1
    if (estadoLista[3] != '4'): valor -= 1
    if (estadoLista[4] != '5'): valor -= 1
    if (estadoLista[5] != '6'): valor -= 1
    if (estadoLista[6] != '7'): valor -= 1
    if (estadoLista[7] != '8'): valor -= 1
    if (estadoLista[8] != '0'): valor -= 1
    # print(f'O valor é: {valor}')
    return valor
def HillClimbing(problema, impresso):
    node = Node()
    node.state = problema.initial_state
    objetivo = problema.endGoal
    k = 1000
    contador = 0
    caminho = []
    # print(f'O objetivo é: {objetivo}')
    movimentos = ['left', 'up', 'right', 'down']
    if (objetivo == node.state): 
            # print('Achou') 
            # print(f'A resposta é: {node.state}') 
            # print(f'O impresso é: {impresso}')
            return solution(node, caminho, impresso)
    while True:
        sucessores = []
        heapq.heappush(sucessores, node)
        node = heapq.heappop(sucessores)
        # print(f'O estado é: {node.state}')
        node.valor = CustoNo(node.state)
        caminho.append(node.state)
        for mov in movimentos: #calcula todos os sucessores, como a fila é de prioridades estão ordenados, aí lá em baixo é só pegar o sucessor
            child = Node()
            estadoAtual = node.state
            child.state = action(estadoAtual, mov)
            if (child.state == 'Nao'): continue
            child.parent = node
            # print(f'O estado é: {node.state}')
            child.valor = CustoNo(child.state)
            heapq.heappush(sucessores, child)
        contador += 1
        melhorouIgual = []
        for i in sucessores:
            if (i.valor >= node.valor):
                melhorouIgual.append(i)
        if (not melhorouIgual): 
            return solution(node, caminho, impresso)
        aleatorio = random.choice(melhorouIgual)
        child = aleatorio
        caminho.append(child.state)
        # print(f'O estado CHILD é: {child.state}')
        if (objetivo == child.state):
            return solution(child, caminho, impresso)
        if ((child.valor == node.valor) and (contador < k)):
            node = child 
            continue
        if (contador > k):
            # print(child.state)
            # print('Achou contador')
            return solution(child, caminho, impresso)
        node = child    
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