Neste trabalho, buscou-se estudar técnicas de aprendizado supervisionado e não-supervisionado, mais especificamente os algoritmos k-Nearest Neighbors (kNN) e k-Means. Além disso, buscou-se estudar e implementar matriz de confusão e medidas de desempenho como  acurácia, precisão, revocação (recall) e F1.

Neste trabalho estudou-se o conjunto de dados NBA Rookie Stats, ele possui diversos atributos entre eles se a carreira do jogador durou pelo menos 5 anos na liga.
Este trabalho foi dividido em duas partes:

Na primeira parte do trabalho implementou-se o algoritmo k-Nearest Neighbors para
classificar se a carreira de um jogador vai durar pelo menos 5 anos na liga ou não, utilizando os
atributos.

Na segunda parte implementou-se o algoritmo k-Means para agrupar os jogadores em
diferentes conjuntos (clusters) usando apenas os atributos das amostras (sem utilizar a coluna de
resposta TARGET_5Yrs), o KNN imprimirá a matriz de confusão e as medidas de desempenho faladas anteriormente e o KMeans os clusters (centroides).

Orientações:

Primeiramente, certifique-se que está no diretório dos arquivos do programa e que o diretório tem 
os arquivos das bases 'nba_treino.csv' e 'nba_teste.csv'.

Depois, esse código foi criado e executado usando o VsCOde e o Wsl(Windows Subsystem for Linux), então
certifique-se que sua máquina seja capaz de rodar códigos python 3.11.4 e compreendê-los.

Feito isso, para executar o código basta escrever no terminal 'python nome_arquivo', sendo nome do
arquivo o nome do arquivo que deseja executar (NÃO esquecer de incluir o nome dtodo, isso envolve a 
extensão, ou seja se o arquivo se chama 'x.py', o comando deve ser 'python x.py') e o resultado
aparecerá no terminal. Nesse trabalho, há 4 arquivos que devem ser executados 'knnFuncionando.py' 
a versão que eu implementei do KNN,'knnPontosExtrasFuncionando.py', a versão que usou bibliotecas 
prontas, seguindo a proposta dos pontos extras, 'kmeansFuncionando.py', a versão que eu implementei 
do KMeans e 'kmeansPontosExtras.py', a versão do KMeans que usou bibliotecas já prontas dele.