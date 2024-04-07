Neste trabalho, buscou-se trabalhar com conceitos de geometria computacional em combinação com algoritmos de ordenação (neste trabalho, em particular, usou-se do MergeSort, do InsertionSort e do RadixSort).  

O principal objetivo deste programa é calcular o fecho convexo de um conjunto de pontos do plano cartesiano. Esses pontos deverão ser escritos em um arquivo "txt" no formato:

coordenadaX coordenadaY
(para cada ponto desejado insere-se uma linha nesse formato)

A saída do programa seguirá esse mesmo formato, porém imprimirá os pontos que fazem parte do fecho convexo e o tempo necessário para ter se chegado nesse resultado usando o algoritmo Graham Scan e o algoritmo da marcha de Jarvis. Porém, em uma das etapas do algoritmo de Graham Scan é necessário fazer uma ordenação, logo serão realizados 4 processos para o cálculo do mesmo fecho convexo com o intuito de analisar qual foi mais rápido para cada caso:

1- Graham Scan + MergeSort
2- Graham Scan + Insertion Sort
3- Graham Scan + Radix Sort
4- Marcha de Jarvis

É importante destacar que para realizar a execução do programa, deve-se ou criar um novo arquivo, ou substituir o conteúdo de um dos já existentes no diretório ("entrada.txt", "entrada2.txt" e "entrada3.txt") e digitar no terminal após entrar nos diretórios corretos o comando:"make run file=ARQUIVO", com arquivo devendo ser substituído pelo nome do arquivo junto com seu tipo (exemplo: "arquivo.txt").