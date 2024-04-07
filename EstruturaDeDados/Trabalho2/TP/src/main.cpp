#include "fechoconvexo.hpp"
#include <chrono>
#include <iomanip>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Uso: " << argv[0] << " entrada.txt" << std::endl; // caso não seja inserido o arquivo aparece isso na tela
        return 1;
    }

    std::string arquivoEntrada = argv[1];
    std::ifstream arquivo(arquivoEntrada);

    if (!arquivo.is_open()) // checa se, por qualquer razão, o arquivo não conseguiu ser aberto, exemplo:ele não existir
    {
        throw std::runtime_error("Erro ao abrir o arquivo de entrada");
    }

    vector<Ponto2d> pontos;
    int x, y;
    while (arquivo >> x >> y) // lê cada linha e o primeiro termo de cada linha e lido como x e o segundo como y
    {
        Ponto2d ponto(x, y);
        pontos.push_back(ponto);
    }

    arquivo.close();

    FechoConvexo f(pontos);

    auto start = std::chrono::high_resolution_clock::now();
    f.GrahamInsertion();
    auto end = std::chrono::high_resolution_clock::now();
    double duration1 = std::chrono::duration<double>(end - start).count();
    // a partir disso, usando-se o chrono calcula-se quanto tempo a função GrahamInsertion demorou para ser executada

    auto start1 = std::chrono::high_resolution_clock::now();
    f.GrahamMerge(f.copia);
    cout << endl;
    auto end1 = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end1 - start1).count();
    // a partir disso, usando-se o chrono calcula-se quanto tempo a função GrahamMerge demorou para ser executada

    std::cout << "GRAHAM+MERGESORT: " << std::fixed << std::setprecision(3) << duration << "s" << std::endl;
    std::cout << "GRAHAM+INSERTSORT: " << std::fixed << std::setprecision(3) << duration1 << "s" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    f.GrahamRadix(f.copia);
    auto end2 = std::chrono::high_resolution_clock::now();
    double duration2 = std::chrono::duration<double>(end2 - start2).count();
    // a partir disso, usando-se o chrono calcula-se quanto tempo a função GrahamRadix demorou para ser executada

    std::cout << "GRAHAM+RADIX: " << std::fixed << std::setprecision(3) << duration2 << "s" << std::endl;

    auto start3 = std::chrono::high_resolution_clock::now();
    f.Jarvis();
    auto end3 = std::chrono::high_resolution_clock::now();
    double duration3 = std::chrono::duration<double>(end3 - start3).count();
    // a partir disso, usando-se o chrono calcula-se quanto tempo a função Jarvis demorou para ser executada

    std::cout << "JARVIS: " << std::fixed << std::setprecision(3) << duration3 << "s" << std::endl;

    return 0;
}
