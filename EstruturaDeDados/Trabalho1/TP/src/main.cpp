#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "expressao.hpp"

using namespace std;
Expressao c;
int main()
{
    ifstream arquivo("bin/arquivo.txt"); // abre o arquivo
    string linha;

    while (getline(arquivo, linha))
    {                             // lê cada linha do arquivo
        istringstream iss(linha); // cria um objeto istringstream a partir da linha lida

        string comando, tipo, expressao;
        iss >> comando >> tipo; // lê o primeiro "token" da linha, que representa o tipo de operação
        if (comando == "LER")
        { // se o comando for "LER", lê o tipo de expressão e a expressão em si
            getline(iss, expressao);
            c.expression = expressao;
            c.tipo = tipo;
            if (c.tipo == "INFIXA")
            {
                if (c.ler_infixa(c.expression))
                {
                    c.pilha = c.valida(expressao);
                } // basicamente aqui se a expressão infixa for válida, armazena-se a expressão como uma pilha de seus termos
                else if (!(c.ler_infixa(c.expression)))
                {
                    cout << "ERRO:"
                         << " "
                         << "EXP"
                         << " "
                         << "NAO VALIDA" << endl;
                    c.expression = "";
                    c.tipo = "";
                } // se nao for válida, a expressão não é armazenada, e seus tipo e atributo expression são armazenados como strings vazias
            }
            else if (c.tipo == "POSFIXA")
            {
                if (c.ler_infixa(c.expression))
                {
                    c.pilha = c.valida(expressao);
                }
                else if (!(c.ler_infixa(c.expression)))
                {
                    cout << "ERRO:"
                         << " "
                         << "EXP"
                         << " "
                         << "NAO VALIDA" << endl;
                    c.expression = "";
                    c.tipo = "";
                } // é realizado a mesma verificação de cima, só que para expressões posfixas
            }
        }
        else if (comando == "POSFIXA")
        { // para que esse comando possa ser realizado, a expressão deve ser infixa, logo se ela é validada pela expressão ler_infixa, sua transformação em posfixa pode ocorrer
            if (c.ler_infixa(c.expression))
            {
                cout << "POSFIXA: ";
                c.infixToPostfix(c.pilha);
                cout << endl;
            }
            else
            { // caso não seja, para que a execução do programa não encerre nesse caso, podendo ler outras linhas do arquivo, apenas imprime-se que a expressão é inválida
                cout << "ERRO:"
                     << " "
                     << "EXP"
                     << " "
                     << "NAO EXISTE" << endl;
            }
        }
        else if (comando == "INFIXA")
        {
            if (c.ler_posfixa(c.expression))
            {
                cout << "INFIXA: ";
                c.posfixaInfixa(c.pilha);
                cout << endl;
            }
            else
            { // mesmas situações do que o comando POSFIXA, só que agora para expressões POSFIXAS
                cout << "ERRO:"
                     << " "
                     << "EXP"
                     << " "
                     << "NAO EXISTE" << endl;
            }
        }
        else if (comando == "RESOLVE")
        {
            if (c.tipo == "INFIXA")
            { // segue-se a mesma ideia dos outros comandos, só que realiza-se uma verificação de tiipo primeiro, para dependendo do tipo, resolver a expressão como infixa ou posfixa
                if (c.ler_infixa(c.expression))
                {
                    cout << "VAL: ";
                    c.resolver_infixa(c.pilha);
                    cout << endl;
                }
                else
                {
                    cout << "ERRO:"
                         << " "
                         << "EXP"
                         << " "
                         << "NAO EXISTE" << endl;
                }
            }
            else if (c.tipo == "POSFIXA")
            {
                if (c.ler_posfixa(c.expression))
                {
                    cout << "VAL: ";
                    c.resolver_posfixa2(c.pilha);
                    cout << endl;
                }
                else
                {
                    cout << "ERRO:"
                         << " "
                         << "EXP"
                         << " "
                         << "NAO EXISTE" << endl;
                }
            }
            else
            {
                cout << "ERRO:"
                     << " "
                     << "EXP"
                     << " "
                     << "NAO EXISTE" << endl;
            }
        }
    }
    arquivo.close(); // fecha o arquivo
    return 0;
}