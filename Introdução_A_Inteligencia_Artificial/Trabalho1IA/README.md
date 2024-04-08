Neste trabalho, buscou-se implementar e comparar diferentes métodos de busca aprendidos ao longo do curso, aplicado ao problema do quebra-cabeça das 8 peças (8-Puzzle, composto por uma moldura 3x3, conjunto de peças numeradas de 1 a 8 e um espaço vazio). O objetivo é tentar chegar na configuração:

1 2 3
4 5 6
7 8  

Deslizando as peças adjacentes ao espaço vazio em direção a ele, 1 movimento por vez, pela moldura, podendo movimentar peças horizontalmente e verticalmente. Esse problema é denominado N-Puzzle, é NP-Difícil.

Foram implementados os algoritmos de busca sem informação: Breadth-first search (BFS), Iterative deepening search (IDS), Uniform-cost search (UCS);

Os seguintes algoritmos de busca com informação: A* search e Greedy best-first search

E o seguinte algoritmo de busca local: Hill Climbing

Para executar o programa primeiro deve-se entrar no diretório "Trabalho1IA", O formato de entrada é "python TP1.py ordemDeNumeros", com "ordemDeNumeros" devendo ser substituído por "letra configInicial", com letra devendo ser substituído por ("A": A*; "B": BFS; "G": Greedy; "H": HillClimbing; "I": IDS; "U": UCS), ":" indica qual algoritmo será executado para resolver o problema, e configInicial por um arranjo dos números 1, 2, 3, 4, 5, 6, 7, 8 e o termo " ", ex: "1 2 3 4 5 6  8 7". Caso desejar pode-se acrescentar PRINT no final para se imprimir os passos até se chegar na solução final, mais a quantidade de passos até se chegar na solução. Caso não se coloque isso, será impresso o número de passos até se chegar na solução.