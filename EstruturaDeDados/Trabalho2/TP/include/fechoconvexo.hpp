#ifndef FECHOCONVEXO_H
#define FECHOCONVEXO_H
#include "ponto2d.hpp"
#include <string>
#include "vector4.hpp"

using namespace std;

class FechoConvexo
{
public:
    // atributos
    Ponto2d p0;
    vector<Ponto2d> _pontos;
    vector<Ponto2d> copia;

    vector<Ponto2d> S;
    // métodos
    FechoConvexo(vector<Ponto2d> pontos) : _pontos(pontos)
    {
        temElemRepetido();
        copia = _pontos;
        p0 = YMenor(_pontos);
        RemoverP0();
    };
    void InsertionSort();
    void temElemRepetido();
    void temAngIgual();
    void temAngIgual2(vector<Ponto2d> &pontos3, Ponto2d p0);
    Ponto2d XMenor(const vector<Ponto2d> &pontos, int yMenor);
    Ponto2d YMenor(const vector<Ponto2d> &_pontos);
    void RemoverP0();
    bool curvaEsquerda(Ponto2d, Ponto2d, Ponto2d);
    void MergeSort2(vector<Ponto2d> &arr, int start, int end);
    vector<Ponto2d> MergeSort(vector<Ponto2d> &arr);
    vector<Ponto2d> merge(vector<Ponto2d> &esquerda, vector<Ponto2d> &direita);
    int getBinaryDigit(float digit, int n);
    void radixSort(vector<Ponto2d> &arr, Ponto2d p);
    float numeroDig(vector<float> arr);
    vector<Ponto2d> GrahamRadix(vector<Ponto2d> x);
    void quicksortB(vector<Ponto2d>::iterator start, vector<Ponto2d>::iterator end, int w, Ponto2d p0);
    vector<Ponto2d> GrahamInsertion();
    vector<Ponto2d> GrahamMerge(vector<Ponto2d> pontos);
    vector<Ponto2d> JarvisRight(vector<Ponto2d> _pontos);
    vector<Ponto2d> JarvisLeft(vector<Ponto2d> _pontos);
    vector<Ponto2d> Jarvis();
    Ponto2d YMaior(const vector<Ponto2d> &pontos);
    Ponto2d XMaior();
};
#endif