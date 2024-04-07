#ifndef PAR_H
#define PAR_H
#include <iostream>
#include <string>
using namespace std;

class Par
{
public:
    string _caractere;   // armazena o caractere
    int _frequencia;     // armazena a frequência
    string _codificacao; // armazena a codificação correspondente
    int id;

    Par()
    {
        _caractere = "";
        _frequencia = 0;
        _codificacao = "";
        id = 0;
    }
    Par(char caractere, int frequencia)
    {
        _caractere = caractere;
        _frequencia = frequencia;
        id = 0;
    }
    void imprimir()
    {
        cout << _caractere << ": " << _frequencia << endl;
    }
};
#endif