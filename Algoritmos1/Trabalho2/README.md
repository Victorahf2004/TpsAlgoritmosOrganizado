Neste trabalho, buscou-se continuar o estudo de grafos, trabalhando-se com grafos temporais.
O foco principal consistiu na implementação de algoritmos como Dijsktra e Kruskal, para a resolução de situações fictícias em que deseja-se a distância mínima de um ponto do grafo até cada outro,
e situações que requerem a construção da árvore geradora mínima do grafo. Nesse trabalho foram informados dados como Número de vilas (N) e conexões de um reino (M) (podem ser interpretados como número de vértices e arestas do grafo) e informações adicionais como vila (u), vizinho (v) custo pra construir cada conexão (c), o tempo para atravessá-las (l) e o ano de construção dela (a).

As entradas seguem o formato:

N M
...
(a seguir devem vir M linhas no formato: )
u v a l c

A saída segue o formato: N linhas, com cada uma representada por um inteiro que
representa o tempo mínimo necessário para sair do palácio real e chegar à vila i, seguido por uma linha com um inteiro que represente o primeiro ano no qual as distâncias listadas
nas linha anteriores são mutuamente realizáveis, seguido por outra linha com um inteiro que representa o primeiro ano a partir do qual é possível chegar em qualquer vila do reino a partir do
palácio real e, por fim, uma linha com um inteiro que representa o menor custo necessário
para conectador todo o reino.