#include "arvore.hpp"

using namespace std;
Arvore::Arvore(vector4<TipoNo *> f)
{
    ide = 0;
    raiz = NULL;
    Heapsort(f);
    folhas = f;
    copia = folhas;
    Huff();
    if (folhas.size() != 1)
        codificacao();
}

void Arvore::Huff() // caso só haja um tipo de caractere o dicionário já é criado aqui mesmo, se não o processo normal é seguido, começando pela função descobreMaior
{
    if (copia.size() == 1)
    {
        Par x;
        x._caractere = folhas[0]->item;
        x._codificacao = "1";
        dicionario.push_back(x);
    }
    else
    {
        descobreMaior(raiz);
    }
}

void Arvore::Refaz(int Esq, int dir, vector4<TipoNo *> &arr)
{
    int i, j;
    TipoNo *x = new TipoNo();
    i = Esq;
    j = i * 2 + 1;
    x = arr[i];
    while (j <= dir)
    {
        if (j < dir)
        {
            if ((arr[j]->frequencia) < (arr[j + 1]->frequencia))
                j++;
        }
        if ((x->frequencia) >= (arr[j]->frequencia))
            break;
        arr[i] = arr[j];
        i = j;
        j = i * 2 + 1;
    }
    arr[i] = x;
}

void Arvore::Constroi(vector4<TipoNo *> &A, int n)
{
    int Esq;
    Esq = n / 2;
    while (Esq >= 0)
    {
        Refaz(Esq, n - 1, A);
        Esq--;
    }
}

void Arvore::Heapsort(vector4<TipoNo *> &A)
{
    int n = A.size();
    int Esq, Dir;
    TipoNo *x = new TipoNo();
    int tamanho = n;
    Constroi(A, tamanho); /* constroi o heap */
    Esq = 0;
    Dir = n - 1;
    while (Dir > 0)
    { /* ordena o vetor */
        x = A[0];
        A[0] = A[Dir];
        A[Dir] = x;
        Dir--;
        Refaz(Esq, Dir, A);
    }
}

int Arvore::gerarNumeroUnico()
{
    return ++ide; // ao adicionar 1 cada vez que chamada nesse tributo da árvore é possível adquirir sempre números diferentes
}
void Arvore::descobreMaior(TipoNo *&p)
{
    int contador = 0; // usado para separar o caso inicial quando não há nós combinados ainda
    while (contador != 2)
    {
        if (p == NULL)
        {
            p = new TipoNo();
            p->item = std::to_string(gerarNumeroUnico());
            p->frequencia = (copia[0])->frequencia + (copia[1])->frequencia; // soma-se os dois nós com menor frequência
            p->esq = folhas[0];
            p->esq->pai = p;
            p->dir = folhas[1];
            p->dir->pai = p;
            copia.erase(copia.begin());
            copia.erase(copia.begin());
            copia.insert(copia.begin(), p);
            nos.push_back(p);
            nosCopia.push_back(p);
            nosCopia.push_back(p->esq);
            nosCopia.push_back(p->dir);
            // cout << p->item << ", " << p->esq->item << ", " << p->dir->item << endl;
            Heapsort(copia); // chamado para reordenar o vetor de acordo com a frequência para que o algoritmo de Huffman continue funcionando
            maior = p;
            contador++;
        }

        if (contador != 0)
        {
            while (((copia.size()) != 1))
            {
                TipoNo *geral = new TipoNo();
                geral->frequencia = (copia[0])->frequencia + (copia[1])->frequencia;
                geral->item = std::to_string(gerarNumeroUnico());
                geral->esq = copia[0];
                geral->esq->pai = geral;
                geral->dir = copia[1];
                geral->dir->pai = geral;
                copia.erase(copia.begin());
                copia.erase(copia.begin());
                copia.insert(copia.begin(), geral);
                nosCopia.push_back(geral->esq);
                nosCopia.push_back(geral->dir);
                nosCopia.push_back(geral);
                nos.push_back(geral);
                maior = geral;
                Heapsort(copia);
            } // mais uma vez seguindo-se o algoritmo de Huffman soma-se a frequência dos dois primeiros nós, os quais tem a menor frequência
            contador++;
        }
    }
}

void Arvore::isFilho(Par &x, string item)
{
    // todas as letras são diferentes então funciona
    int contador = 0;
    TipoNo *aux2 = new TipoNo();
    // compara-se o valor de cada nó para ver se é igual ao filho esquerdo do pai ou ao direito do pai para ver se ele é um filho esquerdo, ou filho direito e, a partir disso, constrói a codificação de cada caractere a partir do algoritmo de Huffman, se for filho esquerdo adiciona um 0 se for direito adiciona 1, isso é feito até chegar ao nó maior
    while (contador != 2)
    {
        if (contador == 0)
        {
            int retorno = 0;
            for (int i = 0; i < (nos.size()); i++)
            {
                if (nos[i]->esq->item == item)
                {
                    aux2 = nos[i]->esq;
                }
                else if (nos[i]->dir->item == item)
                {
                    aux2 = nos[i]->dir;
                }
            }
            if (aux2->item == (((aux2->pai)->dir)->item))
            {
                retorno = 1;
                x._codificacao += "1";
                contador++;
            }
            else if (aux2->item == (((aux2->pai)->esq)->item))
            {
                retorno = 2;
                x._codificacao += "0";
                contador++;
            }
            else
            {
                contador++;
            }
        }
        else
        {
            aux2 = aux2->pai;
            while (aux2->pai != NULL)
            {
                if (aux2->item == (((aux2->pai)->dir)->item))
                {
                    x._codificacao += "1";
                }
                else if (aux2->item == (((aux2->pai)->esq)->item))
                {
                    x._codificacao += "0";
                }
                aux2 = aux2->pai;
                if (aux2->pai == NULL)
                {
                    break;
                }
            }
            contador++;
        }
    }
}

string Arvore::achaDescompactado(string caractere)
{
    string aux;
    string y;
    for (int y = 0; y < dicionario.size(); y++)
    {
        if (dicionario[y]._codificacao == caractere)
        {
            aux = dicionario[y]._caractere;
        }
    }
    return aux;
}

void Arvore::descompactarArquivo(const string &nomeArquivoCompactado, string nome)
{
    // Abre o arquivo compactado para leitura
    std::ifstream arquivoCompactado(nomeArquivoCompactado, std::ios::binary);
    if (!arquivoCompactado.is_open())
    {
        throw std::invalid_argument("Erro ao abrir o arquivo compactado.");
    }
    int tamanho2 = 0;
    arquivoCompactado.read(reinterpret_cast<char *>(&tamanho2), 1);
    char *nomeArquivoOriginal = new char[tamanho2];
    arquivoCompactado.read((nomeArquivoOriginal), tamanho2);
    string aux(nomeArquivoOriginal, tamanho2);
    compactarArquivo(aux, nomeArquivoCompactado);
    // Cria o nome do arquivo descompactado
    // string nomeArquivoDescompactado = nomeArquivoCompactado + "Descompactado";
    string nomeArquivoDescompactado = nome;
    // Vetor para armazenar as linhas descompactadas
    vector4<string> linhasDescompactadas;

    // Variáveis para armazenar a sequência de caracteres e o caractere atual
    string sequencia;
    char caractere;

    // Lê cada linha do arquivo compactado
    string linha;
    char byte;
    int contador = 0;
    while (arquivoCompactado.get(byte))
    {
        string linhaDescompactada;
        std::bitset<8> bits(byte);
        for (int i = 7; i >= 0; i--)
        {
            if (contador < tamanhos.size())
            {
                if (i < tamanhos[contador])
                {
                    // pra cada byte analisa-se somando bit a bit se a sequência tem correspondência, quando tiver passa-se para a condição de baixo
                    sequencia += to_string(bits[i]);
                    string descompactacao = achaDescompactado(sequencia);
                    if (!descompactacao.empty())
                    {
                        if (descompactacao.size() == 2) // se o tamanho da descompactação for 2, isso indica que é um número, como a correspondência no dicionário vai ser uma string de c + o número, o que deve ser impresso na descompactação vai ser só o número, logo o segundo caractere da string
                        {
                            string aux(1, descompactacao[1]);
                            descompactacao = aux;
                            linhaDescompactada += descompactacao;
                        }
                        // A descompactação foi encontrada, adiciona ao conteúdo da linha descompactada
                        else
                            linhaDescompactada += descompactacao;

                        // Limpa a sequência
                        sequencia.clear();
                    }
                }
            }
        }
        contador++;
        linhasDescompactadas.push_back(linhaDescompactada);
    }

    // Fecha o arquivo compactado
    arquivoCompactado.close();

    // Abre o arquivo descompactado para escrita
    ofstream arquivoDescompactado(nomeArquivoDescompactado);
    if (!arquivoDescompactado.is_open())
    {
        cout << "Erro ao criar o arquivo descompactado." << endl;
        return;
    }

    // Grava as linhas descompactadas no arquivo descompactado
    for (const string &linhaDescompactada : linhasDescompactadas)
    {
        if (linhaDescompactada == "lqq")
            arquivoDescompactado << endl; // a string lqq é usada como símbolo para quebra de linha
        else
            arquivoDescompactado << linhaDescompactada;
    }

    // Fecha o arquivo descompactado
    arquivoDescompactado.close();
}
string Arvore::acha(string caractere)
{
    string aux;
    for (int y = 0; y < dicionario.size(); y++)
    {
        if (dicionario[y]._caractere == caractere)
        {
            aux = dicionario[y]._codificacao;
        }
    }
    return aux;
}
void Arvore::compactarArquivo(const string &nomeArquivoOriginal, string nome)
{
    // Abre o arquivo original para leitura
    ifstream arquivoOriginal(nomeArquivoOriginal);
    if (!arquivoOriginal.is_open())
    {
        throw std::invalid_argument("Erro ao abrir o arquivo original.");
    }

    // Cria o nome do arquivo compactado
    // string nomeArquivoCompactado = nomeArquivoOriginal + "Compactado";
    string nomeArquivoCompactado = nome;
    // nomeArquivoOriginalCompactado = nomeArquivoCompactado;
    //  Abre o arquivo compactado para escrita
    ofstream arquivoCompactado(nomeArquivoCompactado, std::ios::binary);
    if (!arquivoCompactado.is_open())
    {
        cout << "Erro ao criar o arquivo compactado." << endl;
        return;
    }

    // Variável para armazenar a linha de texto do arquivo original
    string linha;
    int tamanho = nomeArquivoOriginal.size();
    arquivoCompactado.write(reinterpret_cast<const char *>(&tamanho), 1);
    arquivoCompactado.write(reinterpret_cast<const char *>(nomeArquivoOriginal.c_str()), tamanho);
    // Lê cada linha do arquivo original
    while (getline(arquivoOriginal, linha))
    {
        // Para cada caractere da linha
        for (char c : linha)
        {
            if (isdigit(c))
            {
                string add = "c"; // com o intuito de diferenciar nós resultantes da soma de frequências de nós com caracteres que são números é adicionado um c no início do caractere deles
                string aux2(1, c);
                string aux3 = add + aux2;
                // Obtém a codificação do caractere na árvore de Huffman
                string codificacao = acha(aux3);
                tamanhos.push_back(codificacao.size());
                bitset<8> bits(codificacao);
                // escreve no arquivo em bytes
                unsigned char byte = static_cast<unsigned char>(bits.to_ulong());
                arquivoCompactado.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
            }
            else
            {
                string aux2(1, c);
                // Obtém a codificação do caractere na árvore de Huffman
                string codificacao = acha(aux2);
                tamanhos.push_back(codificacao.size());
                bitset<8> bits(codificacao);
                // escreve no arquivo em bytes
                unsigned char byte = static_cast<unsigned char>(bits.to_ulong());
                arquivoCompactado.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
            }
        }
        // Adiciona um byte que ao ser descompactado é traduzido como quebra de linha
        string quebraLinha = acha("lqq");
        tamanhos.push_back(quebraLinha.size());
        bitset<8> bits(quebraLinha);
        unsigned char byte = static_cast<unsigned char>(bits.to_ulong());
        arquivoCompactado.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
    }

    // Fecha os arquivos
    arquivoOriginal.close();
    arquivoCompactado.close();
}
void Arvore::codificacao()
{
    vector4<string> codifica;

    for (int i = 0; i < folhas.size(); i++)
    {
        letras.push_back(folhas[i]->item);
    }

    for (int r = 0; r < letras.size(); r++)
    {
        Par aux;
        aux._caractere = letras[r];
        isFilho(aux, aux._caractere);
        reverse(aux._codificacao.begin(), aux._codificacao.end());
        dicionario.push_back(aux);
    }
}
void Arvore::Limpa()
{
    ApagaRecursivo(raiz);
    raiz = NULL;
}

void Arvore::ApagaRecursivo(TipoNo *p)
{
    if (p != NULL)
    {
        ApagaRecursivo(p->esq);
        ApagaRecursivo(p->dir);
        delete p;
    }
}