#include "../include/SimulatorUI.h"
#include <iostream>
#include <limits>

/**
 * @brief Limpa a tela (multiplataforma)
 */
void SimulatorUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Aguarda entrada do usuario
 */
void SimulatorUI::waitForUser() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.get();
}

/**
 * @brief Obtem entrada inteira do usuario com validacao
 */
int SimulatorUI::getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                break;
            } else {
                std::cout << "Valor deve estar entre " << min << " e " << max << "\n";
            }
        } else {
            std::cout << "Entrada invalida. Digite um numero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

/**
 * @brief Exibe menu principal
 */
void SimulatorUI::showMainMenu(int physicalMemorySize, int virtualMemorySize, 
                              const std::string& algorithmName, bool debugMode) {
    std::cout << "\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "|        SIMULADOR ALGORITMOS DE SUBSTITUIÇÃO             |\n";
    std::cout << "|          Sistemas Operacionais - UFJF - 2025.1          |\n";
    std::cout << "|     Tema 28: Clock & Segunda Chance                     |\n";
    std::cout << "|---------------------------------------------------------|\n";
    std::cout << "|                                                         |\n";
    std::cout << "|  1. Configurar parametros de memoria                    |\n";
    std::cout << "|  2. Selecionar algoritmo                                |\n";
    std::cout << "|  3. Executar simulacao interativa                       |\n";
    std::cout << "|  4. Executar testes automaticos                         |\n";
    std::cout << "|  5. Visualizar estatisticas                             |\n";
    std::cout << "|  6. Ajuda                                               |\n";
    std::cout << "|  7. Sair                                                |\n";
    std::cout << "|                                                         |\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "\nConfiguracao atual:\n";
    std::cout << "- Memoria Fisica: " << physicalMemorySize << " frames\n";
    std::cout << "- Memoria Virtual: " << virtualMemorySize << " paginas\n";
    std::cout << "- Algoritmo: " << algorithmName << "\n";
    std::cout << "- Modo Debug: " << (debugMode ? "Ativado" : "Desativado") << "\n";
}

/**
 * @brief Mostra ajuda
 */
void SimulatorUI::showHelp() {
    clearScreen();
    std::cout << "=== AJUDA - SIMULADOR ALGORITMO CLOCK ===\n\n";
    
    std::cout << "SOBRE O ALGORITMO:\n";
    std::cout << "O algoritmo Clock (Segunda Chance) e uma melhoria do FIFO que usa\n";
    std::cout << "um bit de referencia para dar uma 'segunda chance' a paginas\n";
    std::cout << "frequentemente acessadas.\n\n";
    
    std::cout << "COMO FUNCIONA:\n";
    std::cout << "1. Mantem um ponteiro circular (relogio) nos frames\n";
    std::cout << "2. Quando precisa substituir:\n";
    std::cout << "   - Se bit = 1: limpa bit e avanca (segunda chance)\n";
    std::cout << "   - Se bit = 0: substitui a pagina\n\n";
    
    std::cout << "USANDO O SIMULADOR:\n";
    std::cout << "Configure a memoria (recomendado: 3-5 frames)\n";
    std::cout << "Na simulacao interativa, digite sequencias como: 1 2 3 4\n";
    std::cout << "Use testes automaticos para comparar algoritmos\n";
    std::cout << "O simbolo * indica bit de referencia ativado\n\n";
    
    std::cout << "EXEMPLO DE SAIDA:\n";
    std::cout << "Memoria: [1*] [2 ] [3*] | Clock: 1 | Faults: 3, Hits: 2\n";
    std::cout << "\n";
    std::cout << "       pagina bit  bit\n";
    std::cout << "          1   ativo inativo\n\n";
    
    waitForUser();
}
