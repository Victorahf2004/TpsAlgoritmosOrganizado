#ifndef TIPONO_H
#define TIPONO_H
#include <iostream>
#include <string>

class TipoNo
{
public:
    // atributos
    std::string item;
    int frequencia; // usado para armazenar a frequência de cada caractere
    TipoNo *esq;    // filho esquerdo
    TipoNo *dir;    // filho direito
    TipoNo *pai;    // nó pai
    // métodos
    TipoNo()
    {
        item = "";
        esq = NULL;
        dir = NULL;
        pai = NULL;
        frequencia = 0;
    }
    TipoNo(TipoNo *_esq, TipoNo *_dir, TipoNo *_pai)
    {
        item = "";
        esq = _esq;
        dir = _dir;
        pai = _pai;
        frequencia = 0;
    }
    ~TipoNo()
    {
        // Desaloca a memória dos nós filhos
        delete esq;
        delete dir;
        delete pai;
    }
    friend class Arvore;
};
#endif