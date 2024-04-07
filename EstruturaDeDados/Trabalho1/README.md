Neste trabalho, buscou-se implementar um resolvedor de expressões numéricas, estas podendo estar na notação posfixa, ou na notação infixa, podendo escrever a expressão normalmente ou com parênteses, nesse caso. São aceitos números inteiros ou fracionários separados por "," e o programa é capaz de realizar operações de adição, subtração, multiplicação e divisão. Além disso, o programa é capaz de deduzir expressões inválidas.

Esse programa aceita 4 tipos principais de entradas:

1- LER TIPOEXP EXP
    Substituindo-se TIPOEXP por INFIXA ou POSFIXA dependendo da expressão, esse comando retorna se a expressão é ou não válida.

2- TIPOEXP
    Tendo-se executado previamente a expressão 1, esse comando tentará transformar a expressão lida anteriormente no tipo correspondente

3- RESOLVE
    Tendo-se executado previamente a expressão 1, esse comando tentará resolver a expressão lida anteriormente.

É importante destacar que atualmente o programa está executando comandos do arquivo "arquivo.txt" localizado na pasta "bin", caso deseje-se resolver alguma expressão após entrar nos diretórios corretos basta escrever os comandos no arquivo em questão e digitar "make run" no terminal.

Para apagar os arquivos ".o" da pasta obj basta digitar "make clean" no terminal seguindo a mesma regra do "make run".