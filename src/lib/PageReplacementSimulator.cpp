#include "../include/PageReplacementSimulator.h"
#include "../include/SimulatorUI.h"
#include <iostream>
#include <sstream>

/**
 * @brief Construtor do simulador
 */
PageReplacementSimulator::PageReplacementSimulator() {
    updateMemoryManager();
}

/**
 * @brief Atualiza o gerenciador de memória com as configurações atuais
 */
void PageReplacementSimulator::updateMemoryManager() {
    memoryManager = configManager.createMemoryManager();
    testRunner = std::unique_ptr<TestRunner>(new TestRunner(memoryManager));
}

/**
 * @brief Converte string em sequência de números
 */
std::vector<int> PageReplacementSimulator::parseSequence(const std::string& input) {
    std::vector<int> sequence;
    std::istringstream iss(input);
    int page;
    
    while (iss >> page) {
        sequence.push_back(page);
    }
    
    return sequence;
}

/**
 * @brief Executa simulação interativa
 */
void PageReplacementSimulator::runInteractiveSimulation() {
    const auto& config = configManager.getConfig();
    
    SimulatorUI::clearScreen();
    std::cout << "=== SIMULACAO INTERATIVA ===\n\n";
    std::cout << "Memoria configurada: " << config.physicalMemorySize << " frames\n";
    std::cout << "Digite as paginas a serem referenciadas (separadas por espaco)\n";
    std::cout << "Digite 'q' para sair da simulacao\n\n";
    
    memoryManager->reset();
    
    std::string input;
    while (true) {
        std::cout << "Paginas: ";
        std::getline(std::cin, input);
        
        if (input == "q" || input == "Q") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        auto sequence = parseSequence(input);
        if (!sequence.empty()) {
            memoryManager->processSequence(sequence);
        } else {
            std::cout << "Sequencia invalida. Tente novamente.\n";
        }
        
        std::cout << "\n";
    }
    
    std::cout << "\n=== RESUMO DA SIMULACAO ===\n";
    memoryManager->displayDetailedStatistics();
    SimulatorUI::waitForUser();
}

/**
 * @brief Mostra estatísticas
 */
void PageReplacementSimulator::showStatistics() {
    SimulatorUI::clearScreen();
    std::cout << "=== ESTATÍSTICAS ATUAIS ===\n\n";
    
    memoryManager->displayDetailedStatistics();
    std::cout << "\n";
    memoryManager->displayHistory(10); // Últimas 10 referências
    
    SimulatorUI::waitForUser();
}

/**
 * @brief Loop principal do simulador
 */
void PageReplacementSimulator::run() {
    int choice;
    
    while (true) {
        const auto& config = configManager.getConfig();
        
        SimulatorUI::clearScreen();
        SimulatorUI::showMainMenu(
            config.physicalMemorySize, 
            config.virtualMemorySize,
            memoryManager->getCurrentAlgorithmName(), 
            config.debugMode
        );
        
        choice = SimulatorUI::getIntInput("\nEscolha uma opcao (1-7): ", 1, 7);
        
        switch (choice) {
            case 1:
                configManager.configureMemory();
                updateMemoryManager();
                break;
            case 2:
                configManager.selectAlgorithm();
                updateMemoryManager();
                break;
            case 3:
                runInteractiveSimulation();
                break;
            case 4:
                testRunner->runAllTests();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                SimulatorUI::showHelp();
                break;
            case 7:
                std::cout << "\nObrigado por usar o simulador!\n";
                std::cout << "Simulador de Algoritmos de Substituicao de Pagina\n";
                std::cout << "Desenvolvido para Sistemas Operacionais - UFJF\n";
                return;
        }
    }
}
