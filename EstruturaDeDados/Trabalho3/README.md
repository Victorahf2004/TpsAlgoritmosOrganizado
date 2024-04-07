Neste trabalho, buscou-se trabalhar com algoritmos de compactação, para se reduzir o tamanho de arquivos de texto sem perda de informação. Nesse caso, foi-se orientado a utilizar o algoritmo de Huffman.

A entrada do programa será o nome de um arquivo ou que deseja-se compactar ou que deseja-se descompactar. Os arquivos a se descompactar testados foram arquivos.zip e os arquivos a se compactar foram arquivos txt.

Para se executar o programa deve-se utilizar o comando “make run ARGS=“argumentos”” para compilar e executar o código, o comando deve ser exatamente esse, com apenas nome, sendo substituído pelo conjunto de flags e nomes de arquivos desejados. Exemplos do que substituir o termo argumentos: “-c arquivo arquivoCompactado” (vai ler a mensagem de “arquivo” e colocar ela compactada no arquivo chamado “arquivoCompactado”), “-d arquivoCompactado arquivoDescompactado” (vai ler a mensagem de
“arquivoCompactado” e colocar ela descompactada no arquivo chamado “arquivoDescompactado”) ou, por fim, “-c arquivo.txt arquivoCompactado.zip -d arquivoCompactado.zip arquivoDescompactado” (vai ler  mensagem de “arquivo.txt” e colocar ela compactada no arquivo chamado “arquivoCompactado.zip” e vai ler a mensagem de “arquivoCompactado.zip” e colocar ela descompactada no arquivo
chamado “arquivoDescompactado”).

Atenção! As operações de compactação e descompactação podem ser realizadas quando e na ordem que for desejado, porém caso queira realizar qualquer operação que seja em um arquivo, seja compactá-lo ou
descompactar o arquivo com a mensagem compactada de outro arquivo, não delete o arquivo original, ele deve sempre estar no mesmo diretório que os demais para qualquer operação. Caso isso não seja obedecido, o programa retornará uma exceção.

Um arquivo de exemplo chamado "entrada.txt" está disponibilizado no diretório TP.