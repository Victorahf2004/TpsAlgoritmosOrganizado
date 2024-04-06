#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <numeric>
#include <unordered_set>
#include <queue>
#include <map>
#include <unordered_map>
const long long int INFINITO = 9223372036854775807LL; 
using namespace std;

//long long pra todos os ints
class Vizinho {
    public:
        long long int id;
        long long int pesoCusto;
        long long int pesoTempo;
        long long int ano;
        long long int idInicio;
};
class Node {
    public:
        long long int id;
        long long int tempo;
        long long int custo;
        long long int rank;
        long long int anoDijsktra;
        bool usado = false;
        Node* pai;
        vector<Vizinho*> neighbors;
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.tempo > b.tempo;
    }
};

struct CompareCusto {
    bool operator()(Vizinho* a, Vizinho* b) {
        return a->pesoCusto > b->pesoCusto;
    }
};

void relax(Node& u, Node& v, long long int& peso, long long int& ano){
    Node* pai = &u;
    if (v.tempo > (u.tempo + peso)){
        v.anoDijsktra = ano;
        v.tempo = u.tempo + peso;
        v.pai = pai;
    } 

    else if (v.tempo == ((u.tempo) + peso)){
        if (v.anoDijsktra > ano){
            v.anoDijsktra = ano;
            v.pai = pai;
        }
    }   
}
void Dijsktra(unordered_map<long long int, Node>& grafo, Node& verticeInicial){
    // initializeSingleSource(grafo, verticeInicial);
    verticeInicial.tempo = 0;
    priority_queue<Node, vector<Node>, Compare> Q;
    // priority_queue<Vizinho, vector<Vizinho>, Compare2> anos;
    verticeInicial.anoDijsktra = 0;
    Q.push(verticeInicial);
    long long int anoX = 0;
    while (!(Q.empty())){
        // cout << "oi" << endl;
        Node u = Q.top();
        Q.pop();
        // cout << "O índice normal é: " << u.id << ", e O índice reduzido é: " << u.id -1 << endl;
        if (grafo[u.id].usado == true) continue;
        for (int i = 0; i < u.neighbors.size(); i++){
            relax(u, grafo[u.neighbors[i]->id], u.neighbors[i]->pesoTempo, u.neighbors[i]->ano);
            Q.push(grafo[u.neighbors[i]->id]);
            // anos.push(v);
        }
        grafo[u.id].usado = true;
    }

    for (int key = 1; key < (grafo.size() + 1); key++) {
        cout << grafo[key].tempo << endl;
        if (grafo[key].anoDijsktra > anoX){
            anoX = grafo[key].anoDijsktra;
        }
    }
    cout << anoX << endl;
}
Node* FindSet(Node* x){
    if (x != x->pai){
        x->pai = FindSet(x->pai);
    }
    return x->pai;
}

void makeset(Node& x){
    x.pai = &x;
    x.rank = 0;
}

void Link(Node* x, Node* y){
    if (x->rank > y->rank){
        y->pai = x;
    }
    else {
        x->pai = y;
        if (x->rank == y->rank){
            y->rank = y->rank + 1;
        }
    }
}

void Union(Node& x, Node& y){
    Link(FindSet(&x), FindSet(&y));
}

void Kruskal(unordered_map<long long int, Node>& grafo, priority_queue<Vizinho, vector<Vizinho*>, CompareCusto>& ordenadoVizinhosX){
    long long int custo = 0;

    for (auto& v : grafo){
        makeset(v.second);
    }

    while (!ordenadoVizinhosX.empty()){
        Vizinho* ultimo = ordenadoVizinhosX.top();
        ordenadoVizinhosX.pop();
        if (FindSet(&(grafo[ultimo->idInicio])) != FindSet(&(grafo[ultimo->id]))){
            Union(grafo[ultimo->idInicio], grafo[ultimo->id]);
            custo += ultimo->pesoCusto;
        }
    }
    cout << custo << endl;
}

struct Compare2 {
    bool operator()(Vizinho* a, Vizinho* b) {
        return a->ano > b->ano;
    }
};

struct Compare3 {
    bool operator()(Vizinho* a, Vizinho* b) {
        return a->ano < b->ano;
    }
};

void Kruskal2(unordered_map<long long int, Node>& grafo, priority_queue<Vizinho, vector<Vizinho*>, Compare2>& ordenadoVizinhos2){
    for (auto& v : grafo){
        makeset(v.second);
    }

    Vizinho* ultimoAno;
    bool found = false;
    
    while (!ordenadoVizinhos2.empty()){
        Vizinho* ultimo = ordenadoVizinhos2.top();
        ordenadoVizinhos2.pop();
        if (FindSet(&(grafo[ultimo->idInicio])) != FindSet(&(grafo[ultimo->id]))){
            Union(grafo[ultimo->idInicio], grafo[ultimo->id]);
            ultimoAno = ultimo;
            found = true;
        }
    }
    
    if (found) {
        cout << ultimoAno->ano << endl;
    } else {
        cout << "Nenhum ano encontrado" << endl;
    }
}

int main()
{
    long long int N, M;
    scanf("%lld %lld", &M, &N); // N é o número de vertices e M é o número de arestas

    std::unordered_map<long long int, Node> G;
    // std::vector<long long int> keys;
    priority_queue<Vizinho, vector<Vizinho*>, CompareCusto> ordenadoVizinhosX;
    priority_queue<Vizinho, vector<Vizinho*>, Compare2> ordenadoVizinhos2;
    // keys.reserve(N);
    vector<Vizinho*> vizinhos;
    for (long long int i = 0; i < N; i++) { // Altere para M se estiver lendo arestas
        long long int ano;
        long long int peso;
        long long int custo;
        long long int inicio;
        long long int fim;
        scanf("%lld %lld %lld %lld %lld", &inicio, &fim, &ano, &peso, &custo);
        
        Node& nodeInicio = G[inicio];
        Node& nodeFim = G[fim];
        
        if (nodeInicio.id == 0){
            nodeInicio.id = inicio;
            nodeInicio.tempo = INFINITO;
            nodeInicio.pai = NULL;
        }
        if (nodeFim.id == 0){
            nodeFim.id = fim;
            nodeFim.tempo = INFINITO;
            nodeFim.pai = NULL;
        }
        
        Vizinho* nodeV = new Vizinho();
        nodeV->id = fim;
        nodeV->pesoTempo = peso;
        nodeV->pesoCusto = custo;
        nodeV->ano = ano;
        nodeV->idInicio = inicio;
        nodeInicio.neighbors.push_back(nodeV);
        ordenadoVizinhosX.push(nodeV);
        ordenadoVizinhos2.push(nodeV);
        vizinhos.push_back(nodeV);

        Vizinho* nodeFinal = new Vizinho();
        nodeFinal->id = inicio;
        nodeFinal->pesoTempo = peso;
        nodeFinal->pesoCusto = custo;
        nodeFinal->ano = ano;
        nodeFinal->idInicio = fim;
        nodeFim.neighbors.push_back(nodeFinal);
        ordenadoVizinhosX.push(nodeFinal);
        ordenadoVizinhos2.push(nodeFinal);
        vizinhos.push_back(nodeFinal);
    }
    Dijsktra(G, G[1]);
    Kruskal2(G, ordenadoVizinhos2);
    Kruskal(G, ordenadoVizinhosX);
    for (long long int i = 0; i < vizinhos.size(); i++){
        delete(vizinhos[i]);
    }
    return 0;
}