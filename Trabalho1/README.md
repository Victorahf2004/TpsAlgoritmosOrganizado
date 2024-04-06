Esse foi um trabalho feito na disciplina de algoritmos 1, nele buscava-se entender melhor e colocar em prática, conceitos de grafos. Assim, foi determinado que se construísse um programa que dado um grafo planar G e as coordenadas de seus vértices em um desenho válido de
G, fossem listadas todas as faces de G

São inseridas informações como número de vértices (N) e arestas (M) do grafo de entrada, seguida por N linhas, cada uma dessas i linhas, com as seguintes informações: coordenadas x e y (xi e yi), um inteiro que representa o grau do vértice i (di), seguido por di inteiros, cada um correspondendo a um vizinho do vértice i.

Formato:
N M
(seguidos por N linhas)
xi yi di vizinho1 vizinho2 ...vizinhoi


Na saída são apresentadas informações como o número de faces (F) do grafo, seguido pelas próximas i linhas, cada uma contendo um inteiro si que repsenta o tamanho da face i, seguido por si inteiros, representando o circuito que corresponde à borda da face.

Formato:
F
(seguidos por F linhas)
si inteiro1 inteiro 2 ...inteirosi