#include <omp.h>
#include <iostream>
#include <random>
#include <vector>

void imprimeArreglo(const std::vector<int>& arreglo, int mostrar);

int main() {
    std::cout << "Sumando arreglos en paralelo\n";

    int length; 
    const int mostrar = 10; 
    std::cout << "Tamaño de los arreglos: ";
    std::cin >> length;
    std::vector<int> a1(length);
    std::vector<int> a2(length);
    std::vector<int> a3(length);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < length; i++) {
        a1[i] = dist(gen);
        a2[i] = dist(gen);
    }

    int chunk = length / omp_get_max_threads(); 
    #pragma omp parallel for shared(a1, a2, a3, chunk) schedule(static, chunk)
    for (int i = 0; i < length; i++) {
        a3[i] = a1[i] + a2[i];
    }

    std::cout << "Valores del arreglo 1:\n";
    imprimeArreglo(a1, mostrar);
    std::cout << "Valores del arreglo 2:\n";
    imprimeArreglo(a2, mostrar);
    std::cout << "Valores del arreglo 3 (suma):\n";
    imprimeArreglo(a3, mostrar);

    return 0;
}

void imprimeArreglo(const std::vector<int>& arreglo, int mostrar) {
    for (int i = 0; i < mostrar && i < arreglo.size(); i++) {
        std::cout << arreglo[i] << " - ";
    }
    std::cout << std::endl;
}