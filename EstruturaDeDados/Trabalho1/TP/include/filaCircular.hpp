#include <stdexcept>
#include <iostream>
template <typename T>
class FilaCircular
{
public:
    // atributos
    int capacidade, inicio, fim;
    T *elementos;
    // métodos
    FilaCircular(int capacidade) : capacidade(capacidade), inicio(0), fim(0)
    {
        elementos = new T[capacidade];
    }

    ~FilaCircular()
    {
        delete[] elementos;
    }

    bool isEmpty() const
    {
        return inicio == fim;
    }

    bool isFull() const
    {
        return (fim + 1) % capacidade == inicio;
    }

    void enqueue(const T &elemento)
    {
        if (isFull())
        {
            throw std::out_of_range("Fila cheia");
        }

        elementos[fim] = elemento;
        fim = (fim + 1) % capacidade;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Fila vazia");
        }

        T elemento = elementos[inicio];
        inicio = (inicio + 1) % capacidade;
        return elemento;
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Fila vazia");
        }

        return elementos[inicio];
    }
};