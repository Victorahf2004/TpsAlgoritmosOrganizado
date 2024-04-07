#ifndef ARVORE_H
#define ARVORE_H
#include "par.hpp"
#include "TipoNo.hpp"
#include <string>
#include "vector4.hpp"
#include <cctype>
#include <algorithm>
#include <bitset>
#include <cctype>
#include <fstream>

class Arvore
{
public:
    // atributos
    int ide; // usado para atribuir números únicos aos nós, junto da função gerarNumeroUnico
    string nomeArquivoOriginalCompactado;
    TipoNo *raiz;  // nó usado incialmente para construir a árvore, mas não é a raiz da árvore, de fato
    TipoNo *maior; // nó que posteriormente passa a exercer a função de raiz, já que a árvore é construída de baixo para cima
    vector4<TipoNo *> folhas;
    vector4<TipoNo *> copia;    // copia do vetor folhas, permitindo realizar alterações nele, mas ainda preservando o original
    vector4<string> letras;     // todos os caracteres adquiridos do arquivo
    vector4<TipoNo *> nos;      // vetor auxiliar
    vector4<TipoNo *> nosCopia; // vetor auxiliar
    vector4<Par> dicionario;    // vetor que vai armazenar estruturas de dados que tenham um atributo caractere e um atributo codificação, possibilitando fazer uma correspondência entre ambos pra cada caractere ou codificação
    vector4<int> tamanhos;      // vetor auxiliar que armazena os tamanhos da codificação de cada caractere na ordem de leitura do arquivo para saber quais bits devem ser lidos na descompactação
    // métodos
    Arvore(vector4<TipoNo *> f);
    void compactarArquivo(const string &nomeArquivoOriginal, string nome);
    string acha(string caractere); // acha a correspondência entre um caractere e uma codificação, usado na função de compactar arquivos
    void descompactarArquivo(const string &nomeArquivoCompactado, string nome);
    string achaDescompactado(string caractere); // acha a correspondência entre uma codificação e um caractere usado na função de descompactar arquivo
    int gerarNumeroUnico();
    void Huff();                       // chama a função descobre maior
    void isFilho(Par &x, string item); // determina se um nó é o filho direito ou o filho esquerdo de seu nó pai e a partir disso constrói a codificação
    void codificacao();                // por loop que chama a função isFilho constrói a codificação de cada caractere e a partir disso o dicionário
    void Limpa();
    void descobreMaior(TipoNo *&p); // constroi a árvore interligando os nós de folhas e ao mesmo tempo criando novos, seguindo o algoritmo de Huffman, até culminar no nó maior
    void Constroi(vector4<TipoNo *> &A, int n);
    void Refaz(int Esq, int dir, vector4<TipoNo *> &arr);
    void Heapsort(vector4<TipoNo *> &A); // função que ordena os nós com base no seu atributo frequência, em conjunto com as funções Refaz e Constroi
    void ApagaRecursivo(TipoNo *p);
};
#endif
