#include <stdexcept>
#include <iostream>

template <typename T>
class Pilha
{
public:
    // atributos
    int capacidade, topo;
    int tamanho = 0;
    T elementos[2000];

    // métodos
    Pilha(int capacidade = 2000) : capacidade(capacidade), topo(-1)
    {
    }

    bool isEmpty() const
    {
        return topo == -1;
    }

    bool isFull() const
    {
        return topo == capacidade - 1;
    }

    void push(const T &elemento)
    {
        tamanho++;
        topo++;
        elementos[topo] = elemento;
    }

    void imprimir()
    {
        if (isEmpty())
        {
            std::cout << "Pilha vazia" << std::endl;
            return;
        }

        for (int i = 0; i < (topo + 1); i++)
        {
            std::cout << elementos[i] << " ";
        }

        std::cout << std::endl;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Pilha vazia");
        }

        T elemento = elementos[topo];
        tamanho--;
        topo--;

        // if (tamanho < capacidade / 4) {
        //     realocar(capacidade / 2);
        // }

        return elemento;
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Pilha vazia");
        }

        return elementos[topo];
    }
    ~Pilha(){};
};
