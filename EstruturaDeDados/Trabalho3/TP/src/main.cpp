#include <iostream>
#include "arvore.hpp"
#include <string>
#include <cctype>
#include <fstream>
#include <bitset>

using namespace std;

void countCharacterFrequency(const std::string &filename, vector4<TipoNo *> &pares) // função que cria nós para cada caractere determinado no arquivo e caso eles apreçam mais de uma vez altera-se apenas o atributo frequência de cada um, mas outro nó não é adicionado nesse caso
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::invalid_argument("Erro ao abrir o arquivo.");
    }
    std::string line;
    int contador = 0;
    bool primeiraLinha = true;
    bool adicionouLqq = false;

    while (std::getline(file, line))
    {
        for (char c : line)
        {
            string aux2(1, c);
            bool found = false;
            for (int i = 0; i < pares.size(); i++)
            {
                if (pares[i]->item == aux2)
                {
                    pares[i]->frequencia++;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                contador++;
                TipoNo *novoPar = new TipoNo();
                novoPar->item = aux2;
                novoPar->frequencia = 1;
                pares.push_back(novoPar);
            }
        }

        if (!file.eof())
        {
            // Adiciona o par com o caractere "\n" ao final de cada linha, exceto a última
            if (!adicionouLqq)
            {
                TipoNo *novoPar = new TipoNo();
                novoPar->item = "lqq";
                novoPar->frequencia = 1;
                pares.push_back(novoPar);
                adicionouLqq = true;
            }
            if (adicionouLqq)
            {
                for (int i = 0; i < pares.size(); i++)
                {
                    if (pares[i]->item == "lqq")
                    {
                        pares[i]->frequencia++;
                        break;
                    }
                }
            }
        }

        primeiraLinha = false;
    }

    for (int i = 0; i < pares.size(); i++)
    {
        if (pares[i]->item == "lqq")
        {
            pares[i]->frequencia--;
            break;
        }
    }
    file.close();
}

void imprime(Arvore arv)
{
    for (int y = 0; y < arv.dicionario.size(); y++)
    {
        cout << "A codificação do caractere " << arv.dicionario[y]._caractere << " é: " << arv.dicionario[y]._codificacao << endl;
    }
}

void ajustarNumeros(vector4<TipoNo *> &pares) // caso haja nós cujos itens são números é adicionado o caractere c antes de cada item deles para diferenciá-los de nós resultantes da união das frequências de dois outros nós
{
    for (int i = 0; i < pares.size(); i++)
    {
        if (isdigit((pares[i]->item[0])))
        {
            string aux2 = "c";
            string aux = aux2 + pares[i]->item;
            pares[i]->item = aux;
        }
    }
}

string achaarqEscondido(const string &_arquivoCompactado)
{
    string arqOriginal;
    std::ifstream arquivoCompactado(_arquivoCompactado, std::ios::binary);
    if (!arquivoCompactado.is_open())
    {
        throw std::invalid_argument("Erro ao abrir o arquivo compactado.");
    }
    int tamanho2 = 0;
    arquivoCompactado.read(reinterpret_cast<char *>(&tamanho2), 1);
    char *nomeArquivoOriginal = new char[tamanho2];
    arquivoCompactado.read((nomeArquivoOriginal), tamanho2);
    string aux(nomeArquivoOriginal, tamanho2);
    arquivoCompactado.close();
    return aux;
}

int main(int argc, char **argv)
{
    string flag = argv[1];
    string flag2 = "0";
    if (argc >= 5)
        flag2 = argv[4];
    if (flag == "-c" && flag2 == "-d")
    {
        if (argc >= 7)
        {
            std::string filename = argv[2];
            string filenameCompactado = argv[3];
            string filenameCompactado2 = argv[5];
            string fileNameDescompactado = argv[6];
            vector4<TipoNo *> pares;
            if (filenameCompactado == filenameCompactado2)
            {
                countCharacterFrequency(filename, pares);
                ajustarNumeros(pares);
                Arvore arv(pares);
                arv.compactarArquivo(filename, filenameCompactado);
                arv.descompactarArquivo(filenameCompactado2, fileNameDescompactado);
            }
            else
            {
                vector4<TipoNo *> pares2;
                countCharacterFrequency(filename, pares2);
                ajustarNumeros(pares2);
                Arvore arv1(pares2);
                arv1.compactarArquivo(filename, filenameCompactado);

                string filename2 = achaarqEscondido(filenameCompactado2);
                countCharacterFrequency(filename2, pares);
                ajustarNumeros(pares);
                Arvore arv(pares);
                arv.compactarArquivo(filename2, filenameCompactado2);
                arv.descompactarArquivo(filenameCompactado2, fileNameDescompactado);
            }
        }
    }
    else if (flag == "-c")
    {
        std::string filename = argv[2];
        string filenameCompactado = argv[3];
        vector4<TipoNo *> pares;
        countCharacterFrequency(filename, pares);
        ajustarNumeros(pares);
        Arvore arv(pares);
        arv.compactarArquivo(filename, filenameCompactado);
    }
    else if (flag == "-d")
    {
        std::string filenameCompactado = argv[2];
        string filenameDescompactado = argv[3];
        string filename = achaarqEscondido(filenameCompactado);
        vector4<TipoNo *> pares;
        countCharacterFrequency(filename, pares);
        ajustarNumeros(pares);
        Arvore arv(pares);
        arv.descompactarArquivo(filenameCompactado, filenameDescompactado);
    }
    return 0;
}