#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#include "filaCircular.hpp"
#include "pilha.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

class Expressao
{
public:
    // atributos
    string expression;
    string tipo;
    Pilha<string> pilha;
    // metodos
    Expressao();
    ~Expressao();
    int getPrecedence(char op);
    long double str_to_ld(string str);
    void infixToPostfix(Pilha<string> infix);
    Pilha<string> *infixToPostfixSemImprimir(Pilha<string> infix);
    void posfixaInfixa(Pilha<string> posfixa);
    string operacao2(string num1, string num2, string i);
    void resolver_posfixa2(Pilha<string> posfixa);
    void resolver_posfixa(Pilha<string> *posfixa);
    void resolver_infixa(Pilha<string> infixa);
    bool ler_infixa(string expression);
    bool ler_posfixa(string expression);
    Pilha<string> valida(string expression);
};

#endif
