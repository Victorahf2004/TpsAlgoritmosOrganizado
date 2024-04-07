#include "ponto2d.hpp"

Ponto2d::Ponto2d() // construtor padrão para incializar o Ponto
{
    _x = 0;
    _y = 0;
}

Ponto2d::Ponto2d(int x, int y)
{
    _x = x;
    _y = y;
}

int Ponto2d::get_X() const // como o atributo é private, retorna o elemento
{
    return _x;
}

int Ponto2d::get_Y() const // como o atributo é private, retorna o elemento
{
    return _y;
}

void Ponto2d::imprimir() // imprime os atributos de um ponto
{
    std::cout << _x << " " << _y << std::endl;
}

float Ponto2d::calcularAnguloImprimir(Ponto2d referencia) // usado para calcular o valor de um ângulo e imprimi-lo
{
    int x = get_X();
    int y = get_Y();
    int deltaY = y - referencia._y;
    int deltaX = x - referencia._x;
    float anguloEmRadianos = atan2(deltaY, deltaX);
    float anguloEmGraus = anguloEmRadianos * (180 / M_PI);
    if (anguloEmGraus < 0)
    {
        anguloEmGraus = 360 + anguloEmGraus;
    }
    std::cout << "Ângulo: " << anguloEmGraus << std::endl;
    return anguloEmGraus;
}

float Ponto2d::calcularDist(Ponto2d referencia) // usado para calcular a distância entre dois pontos
{
    int x = get_X();
    int y = get_Y();
    float deltaX = x - referencia._x;
    float deltaY = y - referencia._y;
    float distancia = sqrt((deltaY * deltaY) + (deltaX * deltaX));
    return distancia;
}

float Ponto2d::calcularAngulo(Ponto2d referencia) // usado para calcular o ângulo entre dois pontos, usa da função atan2, a qual retorna o ângulo entre o eixo X positivo e um ponto, sem utilizar de vetores, usa da matemática padrão
{
    int x = get_X();
    int y = get_Y();
    int deltaY = y - referencia._y;
    int deltaX = x - referencia._x;
    float anguloEmRadianos = atan2(deltaY, deltaX);
    float anguloEmGraus = anguloEmRadianos * (180 / M_PI);

    if (anguloEmGraus < 0)
    {
        anguloEmGraus += 360;
    }

    return anguloEmGraus;
}

float Ponto2d::calcularAnguloNegativo(Ponto2d referencia) // igual ao anterior só que retirando-se 180 graus para que seja em relação ao eixo X negativo
{
    int x = get_X();
    int y = get_Y();
    int deltaY = y - referencia._y;
    int deltaX = x - referencia._x;
    float anguloEmRadianos = atan2(deltaY, deltaX);
    float anguloEmGraus = anguloEmRadianos * (180 / M_PI);

    anguloEmGraus -= 180;
    if (anguloEmGraus < 0)
    {
        anguloEmGraus += 360;
    }

    return anguloEmGraus;
}
