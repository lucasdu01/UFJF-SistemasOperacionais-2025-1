#include "../include/TestRunner.h"
#include "../include/SimulatorUI.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Construtor
 */
TestRunner::TestRunner(std::unique_ptr<MemoryManager>& manager) 
    : memoryManager(manager) {}

/**
 * @brief Executa todos os testes automáticos
 */
void TestRunner::runAllTests() {
    SimulatorUI::clearScreen();
    std::cout << "=== TESTES AUTOMATICOS ===\n\n";
    
    runBasicTest();
    runTemporalLocalityTest();
    runWorstCaseTest();
    
    SimulatorUI::waitForUser();
}

/**
 * @brief Executa teste básico
 */
void TestRunner::runBasicTest() {
    std::vector<int> sequence = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    displayTestHeader("Teste 1: Sequencia Basica", sequence);
    
    memoryManager->reset();
    memoryManager->enableLogging(false);
    memoryManager->processSequence(sequence);
    
    const auto& stats = memoryManager->getStatistics();
    displayTestResults("Teste 1", stats);
    
    // Comparações com outros algoritmos
    memoryManager->compareWithFIFO(sequence);
    memoryManager->compareWithOptimal(sequence);
    memoryManager->compareClockWithSecondChance(sequence);
    
    std::cout << "\n";
}

/**
 * @brief Executa teste de localidade temporal
 */
void TestRunner::runTemporalLocalityTest() {
    std::vector<int> sequence = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    displayTestHeader("Teste 2: Localidade Temporal", sequence);
    
    memoryManager->reset();
    memoryManager->processSequence(sequence);
    
    const auto& stats = memoryManager->getStatistics();
    displayTestResults("Teste 2", stats, "Demonstra eficiencia com localidade temporal");
    
    std::cout << "\n";
}

/**
 * @brief Executa teste do pior caso
 */
void TestRunner::runWorstCaseTest() {
    std::vector<int> sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    displayTestHeader("Teste 3: Pior Caso (sem reutilizacao)", sequence);
    
    memoryManager->reset();
    memoryManager->processSequence(sequence);
    
    const auto& stats = memoryManager->getStatistics();
    displayTestResults("Teste 3", stats, "Demonstra comportamento no pior caso");
    
    memoryManager->enableLogging(true); // Reabilitar log
    std::cout << "\n";
}

/**
 * @brief Exibe cabeçalho do teste
 */
void TestRunner::displayTestHeader(const std::string& testName, const std::vector<int>& sequence) {
    std::cout << testName << "\n";
    std::cout << "Sequencia: ";
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i];
        if (i < sequence.size() - 1) std::cout << " ";
    }
    std::cout << "\n\n";
}

/**
 * @brief Exibe resultados do teste
 */
void TestRunner::displayTestResults(const std::string& testName, const AlgorithmStatistics& stats, 
                                   const std::string& description) {
    std::cout << "Resultado do " << testName << ":\n";
    std::cout << "- Total de referencias: " << stats.totalReferences << "\n";
    std::cout << "- Page Faults: " << stats.pageFaults << "\n";
    std::cout << "- Taxa de Hit: " << std::fixed << std::setprecision(2) 
              << stats.getHitRate() << "%\n";
    
    if (!description.empty()) {
        std::cout << "- " << description << "\n";
    }
    
    std::cout << "\n";
}
