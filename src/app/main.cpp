#include "../include/PageReplacementSimulator.h"
#include <iostream>

/**
 * @brief Função principal do programa
 * @return 0 se sucesso, 1 se erro
 */
int main() {
    try {
        PageReplacementSimulator simulator;
        simulator.run();
    } catch (const std::exception& e) {
        std::cerr << "ERRO: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
