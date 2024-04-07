#include "expressao.hpp"

using namespace std;
Expressao::Expressao()
{
    expression = "";
    tipo = "";
}
Expressao::~Expressao()
{
    // delete pilha;
}

int Expressao::getPrecedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else
    {
        return 0; // operador inválido
    }
}

Pilha<string> *Expressao::infixToPostfixSemImprimir(Pilha<string> infix)
{
    FilaCircular<string> output(1001);
    Pilha<char> opStack(infix.tamanho);

    string currentNum = "";
    for (int i = 0; i < infix.tamanho; i++)
    {
        string elemento = infix.elementos[i];
        for (char c : elemento)
        {
            if ((c >= '0' && c <= '9') || (c == '.'))
            { // se for um número, adiciona à string numérica
                currentNum += c;
            }
            else
            {
                if (currentNum != "")
                { // se a string numérica não estiver vazia, adiciona à fila
                    output.enqueue(currentNum);
                    currentNum = "";
                }
                if (c == '+' || c == '-' || c == '*' || c == '/')
                { // se for um operador
                    while (!opStack.isEmpty() && getPrecedence(c) <= getPrecedence(opStack.peek()))
                    {
                        // enquanto houver operadores na pilha e o operador atual não tiver precedência maior que o topo da pilha
                        output.enqueue(string(1, opStack.pop())); // desempilha e adiciona na fila
                    }
                    opStack.push(c); // empilha o operador atual
                }
                else if (c == '(')
                { // se for um parêntese de abertura
                    opStack.push(c);
                }
                else if (c == ')')
                { // se for um parêntese de fechamento
                    while (opStack.peek() != '(')
                    { // desempilha todos os operadores até o parêntese de abertura
                        output.enqueue(string(1, opStack.pop()));
                    }
                    opStack.pop(); // remove o parêntese de abertura da pilha
                }
            }
        }
    }

    if (currentNum != "")
    { // adiciona a string numérica final à fila, se houver
        output.enqueue(currentNum);
    }
    while (!opStack.isEmpty())
    { // desempilha todos os operadores restantes e adiciona na fila
        output.enqueue(string(1, opStack.pop()));
    }

    Pilha<string> *postfix = new Pilha<string>();
    while (!output.isEmpty())
    {
        postfix->push(output.dequeue());
    }
    return postfix;
}
void Expressao::infixToPostfix(Pilha<string> infix)
{
    FilaCircular<string> output(1001);
    Pilha<char> opStack(infix.tamanho);

    string currentNum = "";
    for (int i = 0; i < infix.tamanho; i++)
    {
        string elemento = infix.elementos[i];
        for (char c : elemento)
        {
            if ((c >= '0' && c <= '9') || (c == '.'))
            { // se for um número, adiciona à string numérica
                currentNum += c;
            }
            else
            {
                if (currentNum != "")
                { // se a string numérica não estiver vazia, adiciona à fila
                    output.enqueue(currentNum);
                    currentNum = "";
                }
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
                { // se for um operador
                    while (!opStack.isEmpty() && getPrecedence(c) <= getPrecedence(opStack.peek()))
                    {
                        // enquanto houver operadores na pilha e o operador atual não tiver precedência maior que o topo da pilha
                        output.enqueue(string(1, opStack.pop())); // desempilha e adiciona na fila
                    }
                    opStack.push(c); // empilha o operador atual
                }
                else if (c == '(')
                { // se for um parêntese de abertura
                    opStack.push(c);
                }
                else if (c == ')')
                { // se for um parêntese de fechamento
                    while (opStack.peek() != '(')
                    { // desempilha todos os operadores até o parêntese de abertura
                        output.enqueue(string(1, opStack.pop()));
                    }
                    opStack.pop(); // remove o parêntese de abertura da pilha
                }
            }
        }
    }

    if (currentNum != "")
    { // adiciona a string numérica final à fila, se houver
        output.enqueue(currentNum);
    }
    while (!opStack.isEmpty())
    { // desempilha todos os operadores restantes e adiciona na fila
        output.enqueue(string(1, opStack.pop()));
    }

    Pilha<string> *postfix = new Pilha<string>();
    while (!output.isEmpty())
    {
        postfix->push(output.dequeue());
    }
    postfix->imprimir();
    delete postfix;
}

void Expressao::posfixaInfixa(Pilha<string> posfixa)
{
    Pilha<string> *resolvido = new Pilha<string>();
    for (int u = 0; u < posfixa.tamanho; u++)
    {
        string elemento = posfixa.elementos[u];
        int tamanho = posfixa.elementos[u].length();
        for (int k = 0; k < tamanho; k++)
        {
            char caracter = posfixa.elementos[u][k];
            if (posfixa.elementos[u][k] >= '0' && posfixa.elementos[u][k] <= '9')
            { // pra cada char de cada elemento, se for um número adiciona o elemento todo
                resolvido->push(posfixa.elementos[u]);
                break;
            }
            else if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^')
            { // se não for desempilha-se os últimos dois elementos, cria-se um elemento que é ( + elemento1retirado + operador + elemento2retirado + ) e o empilha
                string b = resolvido->pop();
                string a = resolvido->pop();
                string resultado = "(" + a + " " + elemento + " " + b + ")";
                resolvido->push(resultado);
            }
        }
    }
    resolvido->imprimir(); // Dessa forma, no fim haverá apenas 1 elemento que é a expressão posfixa transformada em infixa
    delete resolvido;
}

long double Expressao::str_to_ld(string str)
{
    stringstream ss(str);
    long double num;
    ss >> num;
    ss.clear();
    ss.str("");
    ss << fixed << setprecision(10) << num;
    ss >> num;
    return num;
}

string Expressao::operacao2(string num1, string num2, string i)
{
    long double num1_float = str_to_ld(num1);
    long double num2_float = str_to_ld(num2);
    long double resultado = 0;
    char op = i[0];
    if (op == '+')
    {
        resultado = (num1_float + num2_float);
    }
    else if (op == '-')
    {
        resultado = (num1_float - num2_float);
    }
    else if (op == '*')
    {
        resultado = (num1_float * num2_float);
    }
    else if (op == '/')
    {
        resultado = (num1_float / num2_float);
    }

    stringstream ss;
    ss << fixed << setprecision(10) << resultado;
    return ss.str();
}

void Expressao::resolver_posfixa2(Pilha<string> posfixa)
{
    Pilha<string> *resolvido = new Pilha<string>();
    for (int u = 0; u < posfixa.tamanho; u++)
    {
        int tamanho = posfixa.elementos[u].length();
        for (int k = 0; k < tamanho; k++)
        {
            if (posfixa.elementos[u][k] >= '0' && posfixa.elementos[u][k] <= '9')
            { // pra cada char de cada elemento, se for um número adiciona o elemento todo
                resolvido->push(posfixa.elementos[u]);
                break;
            }
            else
            { // se não for, desempilha-se os dois últimos elementos, realiza-se a operação indicada pelo operador, entre os elementos, e empilha-se o resultado, isso ocorre até todos os elementos da expressão numérica serem lidos
                string num2 = resolvido->pop();
                string num1 = resolvido->pop();
                string operador = posfixa.elementos[u];
                resolvido->push((operacao2(num1, num2, operador)));
            }
        }
    }
    resolvido->imprimir();
    delete resolvido;
}
void Expressao::resolver_posfixa(Pilha<string> *posfixa)
{
    Pilha<string> *resolvido = new Pilha<string>();
    for (int u = 0; u < posfixa->tamanho; u++)
    {
        int tamanho = posfixa->elementos[u].length();
        for (int k = 0; k < tamanho; k++)
        {
            if (posfixa->elementos[u][k] >= '0' && posfixa->elementos[u][k] <= '9')
            { // pra cada char de cada elemento, se for um número adiciona o elemento todo
                resolvido->push(posfixa->elementos[u]);
                break;
            }
            else
            { // se não for, desempilha-se os dois últimos elementos, realiza-se a operação indicada pelo operador, entre os elementos, e empilha-se o resultado, isso ocorre até todos os elementos da expressão numérica serem lidos
                string num2 = resolvido->pop();
                string num1 = resolvido->pop();
                string operador = posfixa->elementos[u];
                resolvido->push((operacao2(num1, num2, operador)));
            }
        }
    }
    resolvido->imprimir();
    delete resolvido;
}
// a partir de uma combinação de funções transforma em posfixa, depois resolve a posfixa
void Expressao::resolver_infixa(Pilha<string> infixa)
{
    Pilha<string> *a = infixToPostfixSemImprimir(infixa);
    resolver_posfixa(a);
    delete a;
}

bool Expressao::ler_infixa(string expression)
{
    int contadorNumeros = 0;
    int contadorOperadores = 0;
    int contadorAberto = 0;
    int contadorFechado = 0;
    int contadorNaoVazio = 0;
    int contadorPonto = 0;
    // se a expressão estiver vazia gera essa exceção
    if (expression.empty())
    {
        return false;
    }
    for (char f : expression)
    {
        if (f != ' ')
        {
            contadorNaoVazio++;
        }
    }
    // se a expressão for vários caracteres de espaço gera essa exceção
    if (contadorNaoVazio == 0)
    {
        return false;
    }
    Pilha<string> termos(expression.length());
    string termo_atual = "";
    int tamanho = expression.length();
    for (int y = 0; y < tamanho; y++)
    {
        if (expression[y] == ' ')
        {
            termos.push(termo_atual);
            termo_atual = "";
        }
        else
        {
            termo_atual += expression[y];
        }
    }

    termos.push(termo_atual);

    for (int o = 0; o < termos.tamanho; o++)
    {
        string termo = termos.elementos[o];
        contadorPonto = 0;
        int tamanho = termo.length();
        if (termo[0] >= '0' && termo[0] <= '9')
        {
            for (int a = 0; a < tamanho; a++)
            {
                if (termo[a] == '.')
                {
                    contadorPonto++;
                    // checa se caso haja um ponto se há um caractere de numero antes e depois dele
                    if ((!isdigit(termo[a - 1])) || (!isdigit(termo[a + 1])))
                    {
                        return false;
                    }
                }
                // se a expressão tiver caracteres como numero e parenteses sem espaço ou numeros e operadores sem espaço gera essa exceção
                else if ((!isdigit(termo[a])) && termo[a] != '.')
                {
                    return false;
                }
            }
            contadorNumeros++;
        }
        else
        {
            int tamanho = termo.length();
            for (int a = 0; a < tamanho; a++)
            {
                char t = termo[a];
                // se a expressão tiver letras gera essa exceção
                if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z'))
                {
                    return false;
                }
                else if (t >= '0' && t <= '9')
                {
                    continue;
                }
                else if (t == '+' || t == '-' || t == '/' || t == '*')
                {
                    contadorOperadores++;
                }
                else if (t == '(' || t == ')')
                {
                    if (t == '(')
                    {
                        contadorAberto++;
                    }
                    else if (t == ')')
                    {
                        contadorFechado++;
                    }
                }
                // se a expressão tiver algo diferente de parêntesis, operadores, numeros e letras gera essa exceção
                else
                {
                    return false;
                }
            }
        }
    }

    for (int u = 0; u < termos.tamanho; u++)
    {
        string termo2 = termos.elementos[u];
        if (termo2[0] == '(' || termo2[0] == ')')
        {
            int contador = 0;
            int tamanho = termo2.length();
            contador = tamanho;
            // checa se junto de um parêntesis foi escrito um numero ou um operador sem dar espaço
            if (contador != 1)
            {
                return false;
            }
        }
    }

    for (int u = 0; u < termos.tamanho; u++)
    {
        string termo2 = termos.elementos[u];
        if (termo2[0] == '+' || termo2[0] == '*' || termo2[0] == '-' || termo2[0] == '/')
        {
            int contador = 0;
            int tamanho2 = termo2.length();
            contador = tamanho2;
            // checa se junto de um operador foi escrito um numero ou um parentesis sem dar espaço
            if (contador != 1)
            {
                return false;
            }
        }
    }
    // checa se para cada parêntesis aberto escrito há um parentesis fechado e vice-versa
    if (contadorAberto != contadorFechado)
    {
        return false;
    }
    // checa se na expressão inserida há tanto números como operadores
    else if ((contadorNumeros == 0) || (contadorOperadores == 0))
    {
        return false;
    }
    // checa se pra cada dois numeros há um operador
    else if (contadorNumeros != contadorOperadores + 1)
    {
        return false;
    }
    return true;
}

bool Expressao::ler_posfixa(string expression)
{
    int contadorNumeros = 0;
    int contadorOperadores = 0;
    int contadorNaoVazio = 0;
    int contadorPonto = 0;
    // se a expressão estiver vazia gera essa exceção
    if (expression.empty())
    {
        return false;
    }
    for (char f : expression)
    {
        if (f != ' ')
        {
            contadorNaoVazio++;
        }
    }
    // se a expressão for vários caracteres de espaço gera essa exceção
    if (contadorNaoVazio == 0)
    {
        return false;
    }
    Pilha<string> termos(expression.length());
    string termo_atual = "";
    int tamanho = expression.length();
    for (int y = 0; y < tamanho; y++)
    {
        if (expression[y] == ' ')
        {
            termos.push(termo_atual);
            termo_atual = "";
        }
        else
        {
            termo_atual += expression[y];
        }
    }

    termos.push(termo_atual);

    for (int o = 0; o < termos.tamanho; o++)
    {
        string termo = termos.elementos[o];
        contadorPonto = 0;
        int tamanho = termo.length();
        if (termo[0] >= '0' && termo[0] <= '9')
        {
            for (int a = 0; a < tamanho; a++)
            {
                if (termo[a] == '.')
                {
                    contadorPonto++;
                    // checa se caso haja um ponto se há um caractere de numero antes e depois dele
                    if ((!isdigit(termo[a - 1])) || (!isdigit(termo[a + 1])))
                    {
                        return false;
                    }
                }
                // se a expressão tiver caracteres como numero e operadores sem espaço gera essa exceção
                else if ((!isdigit(termo[a])) && termo[a] != '.')
                {
                    return false;
                }
            }
            contadorNumeros++;
        }
        else
        {
            int tamanho = termo.length();
            for (int a = 0; a < tamanho; a++)
            {
                char t = termo[a];
                // se a expressão tiver letras gera essa exceção
                if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z'))
                {
                    return false;
                }
                else if (t >= '0' && t <= '9')
                {
                    continue;
                }
                else if (t == '+' || t == '-' || t == '/' || t == '*')
                {
                    contadorOperadores++;
                }
                // se a expressão tiver algo diferente de operadores, numeros e letras gera essa exceção
                else
                {
                    return false;
                }
            }
        }
    }

    for (int u = 0; u < termos.tamanho; u++)
    {
        string termo2 = termos.elementos[u];
        if (termo2[0] == '+' || termo2[0] == '*' || termo2[0] == '-' || termo2[0] == '/')
        {
            int contador = 0;
            int tamanho = termo2.length();
            contador = tamanho;
            // checa se junto de um operador foi escrito um numero sem dar espaço
            if (contador != 1)
            {
                return false;
            }
        }
    }
    // checa se na expressão inserida há tanto números como operadores
    if ((contadorNumeros == 0) || (contadorOperadores == 0))
    {
        return false;
    }
    // checa se pra cada dois numeros há um operador
    else if (contadorNumeros != contadorOperadores + 1)
    {
        return false;
    }
    return true;
}

Pilha<string> Expressao::valida(string expression)
{
    Pilha<string> termos(expression.length());
    string termo_atual = "";
    int tamanho = expression.length();
    for (int y = 0; y < tamanho; y++)
    {
        if (expression[y] == ' ')
        {
            termos.push(termo_atual);
            termo_atual = "";
        }
        else
        {
            termo_atual += expression[y];
        }
    }

    termos.push(termo_atual);
    Pilha<string> pilha_valida;
    for (int t = 0; t < termos.tamanho; t++)
    {
        pilha_valida.push(termos.elementos[t]);
    }
    cout << "EXPRESSAO OK:" << expression << endl;
    return pilha_valida;
}
