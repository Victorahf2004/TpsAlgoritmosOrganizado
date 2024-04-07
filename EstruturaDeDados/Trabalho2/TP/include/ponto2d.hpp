#ifndef PONTO2D_HPP
#define PONTO2D_HPP

#include <iostream>
#include <cmath>

class Ponto2d
{
private: // atributos x e y de um ponto
    int _x;
    int _y;

public:
    Ponto2d();
    Ponto2d(int x, int y);
    int get_X() const;
    int get_Y() const;
    void imprimir();
    float calcularAnguloImprimir(Ponto2d referencia);
    float calcularDist(Ponto2d referencia); // calcula a distância de um ponto até outro ponto de referência
    float calcularAngulo(Ponto2d referencia);
    float calcularAnguloNegativo(Ponto2d referencia); // calcula ângulos considerando o eixo X negativo
};

#endif
