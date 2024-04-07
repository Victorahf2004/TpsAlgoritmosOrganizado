#include "fechoconvexo.hpp"

using namespace std;

Ponto2d FechoConvexo::XMenor(const vector<Ponto2d> &pontos, int yMenor) // função que em caso de dois pontos no vector com a menor coordenada Y, retorna o ponto entre esses com a menor coordenada X também
{
    int tamanho = pontos.size();
    int xMenor = pontos[0].get_X();
    int numero = 0;

    for (int i = 1; i < tamanho; i++)
    {
        int y = pontos[i].get_Y();
        int x = pontos[i].get_X();

        if (y == yMenor)
        {
            if (x < xMenor)
            {
                xMenor = x;
                numero = i;
            }
        }
    }

    return pontos[numero];
}

Ponto2d FechoConvexo::YMenor(const vector<Ponto2d> &_pontos) // função que retorna o ponto dentro do vector com a menor coordenada Y
{
    int tamanho = _pontos.size();
    int yMenor = _pontos[0].get_Y();
    int numero = 0;

    for (int i = 1; i < tamanho; i++)
    {
        int y = _pontos[i].get_Y();

        if (y < yMenor)
        {
            yMenor = y;
            numero = i;
        }
    }

    Ponto2d pontoYMenor = _pontos[numero];
    Ponto2d pontoXMenor = XMenor(_pontos, yMenor);

    if (pontoYMenor.get_Y() == pontoXMenor.get_Y())
    {
        return pontoXMenor;
    }

    return pontoYMenor;
}

void FechoConvexo::temElemRepetido() // retira elementos repetidos do vector, deixando apenas um deles
{
    vector<Ponto2d> aux;
    for (int i = 0; i < _pontos.size(); i++)
    {
        bool repetido = false;
        for (int j = 0; j < aux.size(); j++)
        {
            if (((_pontos[i].get_X()) == aux[j].get_X()) && (_pontos[i].get_Y() == aux[j].get_Y()))
            {
                repetido = true;
                break;
            }
        }
        if (!repetido)
        {
            aux.push_back(_pontos[i]);
        }
    }
    _pontos = aux;
}

void FechoConvexo::temAngIgual() // retira elementos do vector que tenham um mesmo ângulo deixando apenas o mais distante em relação à p0
{
    vector<Ponto2d> aux;
    bool repete = false;
    for (int i = 0; i < _pontos.size(); i++)
    {
        repete = false;
        for (int j = 0; j < aux.size(); j++)
        {
            if (_pontos[i].calcularAngulo(p0) == aux[j].calcularAngulo(p0))
            {
                repete = true;
                float dist1 = _pontos[i].calcularDist(p0);
                float dist2 = aux[j].calcularDist(p0);
                if (dist1 > dist2)
                {
                    aux[j] = _pontos[i];
                }
            }
        }
        if (!repete)
        {
            aux.push_back(_pontos[i]);
        }
    }
    _pontos = aux;
}

void FechoConvexo::InsertionSort() // método Insertion Sort
{
    temAngIgual();
    int tamanho = _pontos.size();
    for (int i = 1; i < tamanho; i++)
    {
        Ponto2d aux = _pontos[i];
        int j = i - 1;
        while ((j >= 0) && (aux.calcularAngulo(p0) < _pontos[j].calcularAngulo(p0)))
        {
            _pontos[j + 1] = _pontos[j];
            j--;
        }
        _pontos[j + 1] = aux;
    }
}

void FechoConvexo::RemoverP0() // remove o p0 do vector
{
    int id = 0;
    for (int i = 0; i < _pontos.size(); i++)
    {
        if ((_pontos[i].get_X() == p0.get_X()) && (_pontos[i].get_Y() == p0.get_Y()))
        {
            id = i;
            break;
        }
    }
    vector<Ponto2d>::iterator it = _pontos.begin() + id;
    _pontos.erase(it);
}
bool FechoConvexo::curvaEsquerda(Ponto2d p1, Ponto2d p2, Ponto2d p3) // checa se a curva formada por esses pontos está orientada para a esquerda ou não
{
    float vetor1X = p2.get_X() - p1.get_X();
    float vetor1Y = p2.get_Y() - p1.get_Y();
    float vetor2X = p3.get_X() - p2.get_X();
    float vetor2Y = p3.get_Y() - p2.get_Y();

    float produtoVetorial = vetor1X * vetor2Y - vetor1Y * vetor2X;

    if (produtoVetorial > 0)
        return true;
    else if (produtoVetorial < 0)
        return false;
    else
        return false;
}

int FechoConvexo::getBinaryDigit(float number, int digit) // retorna o dígito digit de determinado número na base decimal convertido para a base binária
{
    // Converte o número de ponto flutuante em um inteiro sem sinal
    uint32_t n = *reinterpret_cast<uint32_t *>(&number);

    // Retorna o dígito binário especificado
    return (n >> digit) & 1;
}
void FechoConvexo::quicksortB(vector<Ponto2d>::iterator start, vector<Ponto2d>::iterator end, int w, Ponto2d p0) // algoritmo de ordenação que utiliza dos números equivalentes na base binária e é semelhante ao quicksort
{
    if (w < 0 || start == end)
    {
        return;
    }

    auto id1 = start;
    auto id2 = end - 1;

    while (id1 <= id2)
    {
        while (id1 <= id2 && getBinaryDigit(((*id1).calcularAngulo(p0)), w) == 0)
        {
            id1++;
        }

        while (id1 <= id2 && getBinaryDigit(((*id2).calcularAngulo(p0)), w) == 1)
        {
            id2--;
        }

        if (id1 <= id2)
        {
            swap(*id1, *id2);
            id1++;
            id2--;
        }
    }

    quicksortB(start, id1, w - 1, p0);
    quicksortB(id1, end, w - 1, p0);
}

void FechoConvexo::radixSort(vector<Ponto2d> &arr, Ponto2d p0) // em conjunto com a função quicksortB e as demais auxiliares utilizadas nela forma uma implementação do Radix Exchange Sort
{
    // Define o número de bits para a representação binária de números de ponto flutuante
    int num_bits = 32;

    quicksortB(arr.begin(), arr.end(), num_bits - 1, p0);
}

void FechoConvexo::temAngIgual2(vector<Ponto2d> &pontos, Ponto2d p0) // semelhante à temAngIgual, mas escolhe-se qual vetor será passado como parâmetro, assim como o ponto de referência
{
    vector<Ponto2d> aux;
    bool repete = false;
    for (int i = 0; i < pontos.size(); i++)
    {
        repete = false;
        for (int j = 0; j < aux.size(); j++)
        {
            if (pontos[i].calcularAngulo(p0) == aux[j].calcularAngulo(p0))
            {
                repete = true;
                float dist1 = pontos[i].calcularDist(p0);
                float dist2 = aux[j].calcularDist(p0);
                if (dist1 > dist2)
                {
                    aux[j] = pontos[i];
                }
            }
        }
        if (!repete)
        {
            aux.push_back(pontos[i]);
        }
    }
    pontos = aux;
}
vector<Ponto2d> FechoConvexo::GrahamRadix(vector<Ponto2d> copia) // realiza o método Graham para descobrir o fecho convexo, mas em conjunto com o algoritmo Radix
{
    temAngIgual2(copia, p0);
    radixSort(copia, p0);
    int m = copia.size();
    vector<Ponto2d> S;
    Ponto2d p1 = copia[0];
    S.push_back(p1);
    Ponto2d p2 = copia[1];
    if (copia.size() >= 2)
        S.push_back(p2);
    for (int i = 2; i < m; i++)
    {
        int tamanho = S.size();
        while (tamanho >= 2 && !curvaEsquerda(S[tamanho - 2], S[tamanho - 1], copia[i]))
        {
            S.pop_back();
            tamanho = S.size();
        }
        S.push_back(copia[i]);
    }
    return S;
}
vector<Ponto2d> FechoConvexo::GrahamInsertion() // realiza o método Graham para descobrir o fecho convexo, mas em conjunto com o algoritmo de ordenação Insertion
{
    InsertionSort();
    int m = _pontos.size();
    vector<Ponto2d> S;
    S.push_back(p0);
    Ponto2d p1 = _pontos[0];
    S.push_back(p1);
    Ponto2d p2 = _pontos[1];
    if (_pontos.size() >= 2)
        S.push_back(p2);
    for (int i = 2; i < m; i++)
    {
        int tamanho = S.size();
        while (tamanho >= 2 && !curvaEsquerda(S[tamanho - 2], S[tamanho - 1], _pontos[i]))
        {
            S.pop_back();
            tamanho = S.size();
        }
        S.push_back(_pontos[i]);
    }
    cout << "FECHO CONVEXO: " << endl;
    for (int i = 0; i < S.size(); i++)
    {
        S[i].imprimir();
    }
    return S;
}
vector<Ponto2d> FechoConvexo::merge(vector<Ponto2d> &esquerda, vector<Ponto2d> &direita) // junta dois vetores recebidos em um só
{
    vector<Ponto2d> junto;
    int id1 = 0;
    int id2 = 0;
    // normal
    while ((id1 < esquerda.size()) && (id2 < direita.size()))
    {
        if ((esquerda[id1].calcularAngulo(p0)) < (direita[id2].calcularAngulo(p0)))
        {
            junto.push_back(esquerda[id1]);
            id1++;
        }
        else
        {
            junto.push_back(direita[id2]);
            id2++;
        }
    }
    // se sobrarem elementos
    while (id1 < esquerda.size())
    {
        junto.push_back(esquerda[id1]);
        id1++;
    }
    while (id2 < direita.size())
    {
        junto.push_back(direita[id2]);
        id2++;
    }
    return junto;
}
void FechoConvexo::MergeSort2(vector<Ponto2d> &arr, int start, int end) // função que junto com merge realiza o algoritmo de ordenação MergeSort
{
    if (start >= end)
    {
        return;
    }

    int meio = (start + end) / 2;
    MergeSort2(arr, start, meio);
    MergeSort2(arr, meio + 1, end);

    vector<Ponto2d> subEsquerdo(arr.begin() + start, arr.begin() + meio + 1);
    vector<Ponto2d> subDireito(arr.begin() + meio + 1, arr.begin() + end + 1);
    vector<Ponto2d> subvetorEsquerdoOrdenado = merge(subEsquerdo, subDireito);

    int i = start;
    for (Ponto2d element : subvetorEsquerdoOrdenado)
    {
        arr[i++] = element;
    }
}

vector<Ponto2d> FechoConvexo::MergeSort(vector<Ponto2d> &arr) // recebe apenas o vector como parâmetro e a partir disso chama o MergeSort2 que realiza o algoritmo de ordenação MergeSort
{
    MergeSort2(arr, 0, arr.size() - 1);
    return arr;
}
vector<Ponto2d> FechoConvexo::GrahamMerge(vector<Ponto2d> pontos) // calcula o fecho convexo Graham mas em conjunto com o algoritmo de ordenação MergeSort
{
    vector<Ponto2d> _pontos = MergeSort(pontos);
    int m = _pontos.size();
    vector<Ponto2d> S;
    Ponto2d p1 = _pontos[0];
    S.push_back(p1);
    Ponto2d p2 = _pontos[1];
    if (_pontos.size() >= 2)
        S.push_back(p2);
    for (int i = 2; i < m; i++)
    {
        int tamanho = S.size();
        while (tamanho >= 2 && !curvaEsquerda(S[tamanho - 2], S[tamanho - 1], _pontos[i]))
        {
            S.pop_back();
            tamanho = S.size();
        }
        S.push_back(_pontos[i]);
    }
    return S;
}

Ponto2d FechoConvexo::XMaior() // retorna o ponto com a maior coordenada X e maior coordenada Y
{
    int tamanho = _pontos.size();
    int xMaior = _pontos[0].get_X();
    int numero = 0;

    for (int i = 1; i < tamanho; i++)
    {
        int x = _pontos[i].get_X();

        if (x > xMaior)
        {
            xMaior = x;
            numero = i;
        }
        else if (x == xMaior)
        {
            int y = _pontos[i].get_Y();

            if (y > _pontos[numero].get_Y())
            {
                numero = i;
            }
        }
    }

    return _pontos[numero];
}

Ponto2d FechoConvexo::YMaior(const vector<Ponto2d> &pontos) // retorna o ponto com a maior coordenada Y
{
    int tamanho = pontos.size();
    int yMaior = pontos[0].get_Y();
    int xMaior = pontos[0].get_X();
    int numero = 0;

    for (int i = 1; i < tamanho; i++)
    {
        int y = pontos[i].get_Y();

        if (y > yMaior)
        {
            yMaior = y;
            xMaior = pontos[i].get_X();
            numero = i;
        }
        else if (y == yMaior)
        {
            if (pontos[i].get_X() > xMaior)
            {
                xMaior = pontos[i].get_X();
                numero = i;
            }
        }
    }
    return pontos[numero];
}
vector<Ponto2d> FechoConvexo::JarvisRight(vector<Ponto2d> _pontos) // calcula a cadeia direita do fecho convexo calculado a partir do algoritmo de ordenação Jarvis
{
    vector<Ponto2d> rightChain;
    Ponto2d bottomPoint = YMenor(_pontos);
    Ponto2d maior = YMaior(_pontos);
    Ponto2d referencePoint = bottomPoint;
    Ponto2d aux = bottomPoint;
    rightChain.push_back(bottomPoint);

    while ((referencePoint.get_Y() != maior.get_Y()) || (referencePoint.get_X() != maior.get_X()))
    {
        Ponto2d aux;
        Ponto2d minAnglePoint;
        float minDistance = std::numeric_limits<float>::max();
        for (int i = 0; i < _pontos.size(); i++)
        {
            aux = _pontos[i];
            if (((aux.get_X()) != (referencePoint.get_X())) || ((aux.get_Y()) != (referencePoint.get_Y())))
            {
                float angle = aux.calcularAngulo(referencePoint);
                float minAngle = minAnglePoint.calcularAngulo(referencePoint);
                if (angle < minAngle)
                {
                    minAnglePoint = _pontos[i];
                    minDistance = aux.calcularDist(referencePoint);
                }
                else if (angle == minAngle)
                {
                    float distance = aux.calcularDist(referencePoint);
                    if (distance > minDistance)
                    {
                        minAnglePoint = _pontos[i];
                        minDistance = distance;
                    }
                }
            }
        }
        referencePoint = minAnglePoint;
        rightChain.push_back(referencePoint);
    }
    return rightChain;
}

vector<Ponto2d> FechoConvexo::JarvisLeft(vector<Ponto2d> _pontos) // retorna a cadeia esquerda do fecho convexo calculado a partir do algoritmo de Jarvis
{
    vector<Ponto2d> leftChain;
    Ponto2d bottomPoint = YMenor(_pontos);
    Ponto2d maior = YMaior(_pontos);
    Ponto2d referencePoint = maior;

    while ((referencePoint.get_Y() != bottomPoint.get_Y()) || (referencePoint.get_X() != bottomPoint.get_X()))
    {
        Ponto2d aux;
        Ponto2d minAnglePoint = _pontos[0];
        float minDistance = std::numeric_limits<float>::max();
        for (int i = 0; i < _pontos.size(); i++)
        {
            aux = _pontos[i];
            if (((aux.get_X()) != (referencePoint.get_X())) || ((aux.get_Y()) != (referencePoint.get_Y())))
            {
                float angle = aux.calcularAnguloNegativo(referencePoint);
                float minAngle = minAnglePoint.calcularAnguloNegativo(referencePoint);
                if (angle < minAngle)
                {
                    minAnglePoint = _pontos[i];
                    minDistance = aux.calcularDist(referencePoint);
                }
                else if (angle == minAngle)
                {
                    float distance = aux.calcularDist(referencePoint);
                    if (distance > minDistance)
                    {
                        minAnglePoint = _pontos[i];
                        minDistance = distance;
                    }
                }
            }
        }
        referencePoint = minAnglePoint;
        leftChain.push_back(referencePoint);
    }
    leftChain.pop_back();
    return leftChain;
}

vector<Ponto2d> FechoConvexo::Jarvis() // retorna o fecho convexo de Jarvis completo
{
    vector<Ponto2d> direita = JarvisRight(copia);
    vector<Ponto2d> esquerda = JarvisLeft(copia);
    vector<Ponto2d> resultado;
    for (int i = 0; i < direita.size(); i++)
    {
        resultado.push_back(direita[i]);
    }

    for (int i = 0; i < esquerda.size(); i++)
    {
        resultado.push_back(esquerda[i]);
    }
    return resultado;
}
