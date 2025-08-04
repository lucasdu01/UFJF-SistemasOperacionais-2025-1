#include "../include/ConfigurationManager.h"
#include "../include/SimulatorUI.h"
#include <iostream>

/**
 * @brief Configura parametros de memoria
 */
void ConfigurationManager::configureMemory() {
    SimulatorUI::clearScreen();
    std::cout << "=== CONFIGURACAO DE PARAMETROS ===\n\n";
    
    config.physicalMemorySize = SimulatorUI::getIntInput(
        "Digite o numero de frames na memoria fisica (3-20): ", 3, 20);
    
    config.virtualMemorySize = SimulatorUI::getIntInput(
        "Digite o numero de paginas na memoria virtual (10-100): ", 10, 100);
    
    std::cout << "\nHabilitar modo debug? (1=Sim, 0=Nao): ";
    int debug = SimulatorUI::getIntInput("", 0, 1);
    config.debugMode = (debug == 1);
    
    std::cout << "\nConfiguracao salva com sucesso!\n";
    SimulatorUI::waitForUser();
}

/**
 * @brief Permite selecionar o algoritmo
 */
void ConfigurationManager::selectAlgorithm() {
    SimulatorUI::clearScreen();
    std::cout << "=== SELECAO DE ALGORITMO ===\n\n";
    std::cout << "1. Clock (Relogio) - Buffer circular com ponteiro\n";
    std::cout << "2. Segunda Chance - Lista linear com movimento de paginas\n\n";
    
    int choice = SimulatorUI::getIntInput("Escolha o algoritmo (1-2): ", 1, 2);
    
    AlgorithmType newAlgorithm;
    if (choice == 1) {
        newAlgorithm = AlgorithmType::CLOCK;
        std::cout << "\nAlgoritmo Clock selecionado!\n";
    } else {
        newAlgorithm = AlgorithmType::SECOND_CHANCE;
        std::cout << "\nAlgoritmo Segunda Chance selecionado!\n";
    }
    
    if (newAlgorithm != config.currentAlgorithm) {
        config.currentAlgorithm = newAlgorithm;
        std::cout << "Algoritmo alterado com sucesso!\n";
    } else {
        std::cout << "Algoritmo ja estava selecionado!\n";
    }
    
    SimulatorUI::waitForUser();
}

/**
 * @brief Cria uma instância do gerenciador de memória
 */
std::unique_ptr<MemoryManager> ConfigurationManager::createMemoryManager() const {
    return std::unique_ptr<MemoryManager>(new MemoryManager(
        config.physicalMemorySize, 
        config.virtualMemorySize, 
        config.debugMode, 
        true, 
        config.currentAlgorithm
    ));
}
