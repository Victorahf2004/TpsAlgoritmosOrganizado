#include <iostream>
#include <stdexcept>
#include <limits>

template <typename T>
class vector
{
public: // atributos
    static const int INITIAL_CAPACITY = 3000;
    T elements[INITIAL_CAPACITY]; // a alocação estática foi escolhida, devido à maior facilidade no gerenciamento de memória
    int capacity;
    int top_; // índice do último elemento

public:
    class iterator // iterador que retorna um ponteiro para um elemento de uma posição do vetor
    {
    public: // atributos
        T *ptr;
        iterator(T *pointer) : ptr(pointer) {}
        // métodos
        T &operator*() const
        {
            return *ptr;
        }

        iterator &operator++() // se somar um ao ponteiro ele passa a apontar para a próxima posição do vetor
        {
            ++ptr;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        iterator &operator--() // se subtrair um ao ponteiro ele passa a apontar para a posição anterior do vetor
        {
            --ptr;
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --ptr;
            return temp;
        }

        bool operator==(const iterator &other) const // permite realizar comparações entre ponteiros
        {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator &other) const // semelhante ao caso anterior, mas uma comparação de diferença
        {
            return ptr != other.ptr;
        }

        bool operator<=(const iterator &other) const // semelhante ao caso anterior, mas uma comparação de menor ou igual
        {
            return ptr <= other.ptr;
        }

        bool operator>=(const iterator &other) const // semelhante ao caso anterior, mas uma comparação de maior ou igual
        {
            return ptr >= other.ptr;
        }

        iterator operator+(int n) const // semelhante aos primeiros casos, mas somando-se um valor inteiro ao invés de simplesmente ++
        {
            return iterator(ptr + n);
        }

        iterator operator-(int n) const // semelhante aos primeiros casos, mas subtraindo-se um valor inteiro ao invés de simplesmente --
        {
            return iterator(ptr - n);
        }

        ptrdiff_t operator-(const iterator &other) const // semelhante aos anteriores, mas retorna a diferença entre dois ponteiros
        {
            return ptr - other.ptr;
        }

        iterator &operator+=(int n)
        {
            ptr += n;
            return *this;
        }

        iterator &operator-=(int n)
        {
            ptr -= n;
            return *this;
        }
    };
    // métodos
    vector() : capacity(INITIAL_CAPACITY), top_(-1) {} // construtor padrão de vector incializando a capacidade inicial e o índice

    vector(const iterator &start, const iterator &end) : capacity(INITIAL_CAPACITY), top_(-1) // construtor para inicializar um vector com iteradores
    {
        int size = end - start;
        for (iterator it = start; it != end; ++it)
        {
            push_back(*it);
        }
    }

    void push_back(const T &value) // função para adicionar um elemento ao vector, const faz com que elementos de qualquer const tipo também possam ser adicionados
    {
        if (top_ >= capacity - 1)
        {
            throw std::overflow_error("Vector está cheio");
        }
        elements[++top_] = value;
    }

    void pop_back() // função para remover um elemento ao vector
    {
        if (top_ < 0)
        {
            throw std::underflow_error("Vector está vazio");
        }
        --top_;
    }

    T &operator[](int index) // função que permite acessar qualquer elemento do vector usando [], assim como em um vector normal
    {
        if (index < 0 || index > top_)
        {
            throw std::out_of_range("Posição inexistente nesse vector");
        }
        return elements[index];
    }

    const T &operator[](int index) const // função que permite acessar qualquer elemento do vector usando [], assim como em um vector normal mas também para valores const
    {
        if (index < 0 || index > top_)
        {
            throw std::out_of_range("Posição inexistente nesse vector");
        }
        return elements[index];
    }

    int size() const // retorna o tamanho do vector, assim como em um vector normal
    {
        return top_ + 1;
    }

    iterator begin() const // retorna um ponteiro para o elemento da primeira posição, assim como em um vector normal
    {
        return iterator(const_cast<T *>(elements));
    }

    iterator end() const // retorna um ponteiro para depois da última posição
    {
        return iterator(const_cast<T *>(elements) + top_ + 1);
    }

    iterator erase(iterator pos) // permite apagar iteradores
    {
        if (pos == end())
        {
            throw std::out_of_range("Iterador inválido");
        }

        iterator next = pos;
        ++next;

        for (; next != end(); ++pos, ++next)
        {
            *pos = *next;
        }

        --top_;

        return pos;
    }
};
