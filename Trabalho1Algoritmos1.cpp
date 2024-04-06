#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <numeric>
#include <unordered_set>

using namespace std;

class Node {
    public:
        double x, y;
        int id;
        double angulo;
        bool passou = false;
        int posicaoEmVizinhos; 
        vector<Node> neighbors;

        void SetCoordinates(const double& _x, const double& _y) {
            this->x = _x;
            this->y = _y;
        }
};
class Aresta {
public:
    int inicio, fim;
    bool passou2 = false;
    Aresta(const int& _inicio, const int& _fim) : inicio(_inicio), fim(_fim) {};
    void SetInicioFim(int& _inicio, int& _fim) {
        inicio = _inicio;
        fim = _fim;
    }
};

double relativeInclination(Node p, Node q) {
    double angulo = atan2(q.y - p.y, q.x - p.x);
    if (angulo < 0)
        angulo+= 2 * M_PI;
    return angulo;
}

bool CompararAngulos(Node a, Node b) {
    return a.angulo < b.angulo;
}

void organize(vector<Node>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].neighbors.size(); j++) {
            int id = graph[i].neighbors[j].id - 1;
            graph[i].neighbors[j].SetCoordinates(graph[id].x, graph[id].y);
            graph[i].neighbors[j].angulo = relativeInclination(graph[i].neighbors[j], graph[i]);
        }
        sort(graph[i].neighbors.begin(), graph[i].neighbors.end(), CompararAngulos);
    }
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].neighbors.size(); j++) {
            graph[i].neighbors[j].posicaoEmVizinhos = j;
            graph[i].neighbors[j].passou = false;            
        }
    }
}

Node retornar(int idAnterior, vector<Node>& graph, int idDepois){
    int tamanho = graph[idDepois - 1].neighbors.size();
    int indice = 0;
    for (indice; indice < tamanho; indice++){
        if (graph[idDepois - 1].neighbors[indice].id == idAnterior){
            indice = indice + 1;
            break;
        }
    }
    if (indice == tamanho) indice = 0;    
    return graph[idDepois - 1].neighbors[indice];
}
bool noVetor(Aresta& a1, vector<Aresta>& vec){
    int tamanho = vec.size();
    for (int i = 0; i < tamanho; i++){
        if ((vec[i].inicio == a1.inicio) && (vec[i].fim == a1.fim)){
            return true;
        }
    }
    return false;
}
bool noVetor2(Aresta& a1, vector<Aresta>& vec){
    int tamanho = vec.size();
    for (int i = 0; i < tamanho; i++) {
        if (((vec[i].inicio == a1.inicio) && (vec[i].fim == a1.fim)) || ((vec[i].inicio == a1.fim) && (vec[i].fim == a1.inicio))){
            return true;
        }
    }
    return false;
}

std::vector<std::vector<int>> removeDuplicates(std::vector<std::vector<int>> facesVert) {
    // Cria um unordered_set para armazenar as strings
    std::unordered_set<std::string> setOfFaces;

    // Cria o vetor de saída com a ordem original mantida
    std::vector<std::vector<int>> facesVertOficial;

    for (auto &face : facesVert) {
        std::vector<int> tempFace = face;
        std::sort(tempFace.begin(), tempFace.end());

        std::stringstream ss;
        for (int num : tempFace) {
            ss << num << ' ';
        }

        if (setOfFaces.insert(ss.str()).second) {
            facesVertOficial.push_back(face);
        }
    }

    return facesVertOficial;
}

void montarFaces(vector<Node>& graph, vector<Aresta>& todas_arestas_percorridas, Aresta aresta_inicial, vector<vector<int>>& geral, int posInicial){
    int auxiliar, atual, proximo;
    atual = aresta_inicial.inicio;
    proximo = aresta_inicial.fim;
    std::vector<int> faces;
    Aresta nova_aresta(-1, -1);
    faces.push_back(atual);
    nova_aresta.SetInicioFim(atual, proximo);
    graph[atual - 1].neighbors[posInicial].passou = true;
    do
    {
        todas_arestas_percorridas.push_back(nova_aresta);
        nova_aresta.passou2 = true;
        auxiliar = atual;
        if ((atual != aresta_inicial.inicio) && (proximo != aresta_inicial.fim)){
            graph[atual - 1].neighbors[posInicial].passou = true;
        }
        atual = proximo;
        faces.push_back(atual);
        Node proxNode = retornar(auxiliar, graph, atual);
        proximo = proxNode.id;
        posInicial = proxNode.posicaoEmVizinhos;
        nova_aresta.SetInicioFim(atual, proximo);
    } while (!(graph[atual - 1].neighbors[posInicial].passou));
    if (faces.size() > 2) geral.push_back(faces);
}

void montarFacesAuxiliar(vector<Node>& graph) {
    vector<Aresta> todas_arestas_percorridas;
    vector<vector<int>> geral;
    for (int i = 0; i < graph.size(); i++)  {
        for (int j = 0; j < graph[i].neighbors.size(); j++) {
            Aresta inicio(i + 1, graph[i].neighbors[j].id);
            if (!(graph[inicio.inicio - 1].neighbors[j].passou)) {
                montarFaces(graph, todas_arestas_percorridas, inicio, geral, j);
            }
        }
    }
    int tamanho = geral.size();
    cout << geral.size() << endl;
    for (int i = 0; i < geral.size(); i++){
        if (geral[i].size() > 2) 
        cout << geral[i].size() << " ";
        for(int k = 0; k < geral[i].size(); k++){
            cout << geral[i][k] << " ";
        }
        cout << endl;
    }
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int N, M;

    ss >> N >> M; // N é o número de vertices e M é o número de arestas

    vector<Node> G;
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        stringstream ss(line);
        double x, y;
        int skip;
        if (ss >> x >> y >> skip) {
            Node node;
            node.x = x;
            node.y = y;
            node.id = i+1;
            while (ss >> skip) {
                Node vizinho;
                vizinho.id = skip;
                node.neighbors.push_back(vizinho);
            }
            G.push_back(node);
        }
    }
    organize(G);
    montarFacesAuxiliar(G);
    return 0;
}