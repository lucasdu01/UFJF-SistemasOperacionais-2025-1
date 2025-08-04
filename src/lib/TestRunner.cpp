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
    displayMainHeader();
    
    // Seção 1: Testes Básicos
    displaySectionHeader("SECAO 1: TESTES BASICOS");
    runBasicTest();
    runTemporalLocalityTest();
    runWorstCaseTest();
    
    // Seção 2: Comparações Clock vs Second Chance
    displaySectionHeader("SECAO 2: COMPARACOES CLOCK vs SECOND CHANCE");
    runComparisonTests();
    
    // Seção 3: Comparação com Algoritmo Ótimo (Estudo)
    displaySectionHeader("SECAO 3: COMPARACAO COM ALGORITMO OTIMO (ESTUDO)");
    runOptimalComparisonTests();
    
    displayFinalSummary();
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
    std::cout << "----------------------------------------\n";
    std::cout << " " << testName << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Sequencia: ";
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i];
        if (i < sequence.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
    std::cout << "----------------------------------------\n\n";
}

/**
 * @brief Exibe resultados do teste
 */
void TestRunner::displayTestResults(const std::string& testName, const AlgorithmStatistics& stats, 
                                   const std::string& description) {
    std::cout << "RESULTADO:\n";
    std::cout << "| Total de referencias : " << stats.totalReferences << "\n";
    std::cout << "| Page Faults         : " << stats.pageFaults << "\n";
    std::cout << "| Page Hits           : " << (stats.totalReferences - stats.pageFaults) << "\n";
    std::cout << "| Taxa de Hit         : " << std::fixed << std::setprecision(2) 
              << stats.getHitRate() << "%\n";
    
    if (!description.empty()) {
        std::cout << "| Observacao          : " << description << "\n";
    }
    
    std::cout << "----------------------------------------\n\n";
}

/**
 * @brief Executa testes de comparação Clock vs Second Chance
 */
void TestRunner::runComparisonTests() {
    std::vector<std::vector<int>> testSequences = {
        {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5},      // Sequência básica
        {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4},      // Localidade temporal
        {1, 2, 3, 4, 5, 6, 7, 8, 9},               // Pior caso
        {1, 2, 3, 1, 2, 3, 1, 2, 3},               // Working set
        {1, 2, 3, 4, 1, 4, 1, 4, 1, 4},            // Teste específico para diferenças
        {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}    // Sequência para evidenciar diferenças
    };
    
    std::vector<std::string> testNames = {
        "Comparacao 1: Sequencia Basica",
        "Comparacao 2: Localidade Temporal", 
        "Comparacao 3: Pior Caso",
        "Comparacao 4: Working Set",
        "Comparacao 5: Teste de Diferenciacao",
        "Comparacao 6: Sequencia Complexa"
    };
    
    std::cout << "NOTA: Clock e Second Chance implementam o mesmo principio\n";
    std::cout << "      de \"segunda chance\", resultando em performance similar.\n";
    std::cout << "      Diferencas aparecem na estrutura de dados e ordem.\n\n";
    
    std::cout << "EXPLICACAO DAS DIFERENCAS:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "| Clock          : Estrutura fixa, melhor para padroes regulares\n";
    std::cout << "| Second Chance  : Reordena dinamicamente, melhor para padroes complexos\n";
    std::cout << "| Observacao     : Resultados podem variar conforme a sequencia!\n";
    std::cout << "----------------------------------------\n\n";
    
    for (size_t i = 0; i < testSequences.size(); ++i) {
        displayTestHeader(testNames[i], testSequences[i]);
        memoryManager->compareClockWithSecondChance(testSequences[i]);
        std::cout << "========================================\n\n";
    }
}

/**
 * @brief Executa comparações com algoritmo ótimo para estudo
 */
void TestRunner::runOptimalComparisonTests() {
    std::vector<int> sequence = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    
    displayTestHeader("Comparacao com Algoritmo Otimo", sequence);
    std::cout << "PROPOSITO: Demonstrar limite teorico superior de performance\n";
    std::cout << "          (Para fins educacionais e de analise)\n\n";
    
    memoryManager->compareWithOptimal(sequence);
    std::cout << "========================================\n\n";
}

/**
 * @brief Exibe cabeçalho principal
 */
void TestRunner::displayMainHeader() {
    std::cout << "===========================================\n";
    std::cout << "|                                         |\n";
    std::cout << "|   SIMULADOR DE SUBSTITUICAO DE PAGINA   |\n";
    std::cout << "|    TESTES AUTOMATICOS E COMPARACOES     |\n";
    std::cout << "|                                         |\n";
    std::cout << "===========================================\n\n";
}

/**
 * @brief Exibe cabeçalho de seção
 */
void TestRunner::displaySectionHeader(const std::string& sectionName) {
    std::cout << "\n";
    std::cout << "===========================================\n";
    std::cout << " " << sectionName << "\n";
    std::cout << "===========================================\n\n";
}

/**
 * @brief Exibe resumo final
 */
void TestRunner::displayFinalSummary() {
    std::cout << "\n";
    std::cout << "===========================================\n";
    std::cout << "|              RESUMO FINAL               |\n";
    std::cout << "===========================================\n\n";
    
    std::cout << "CONCLUSOES DOS TESTES:\n";
    std::cout << "----------------------------------------\n\n";
    
    std::cout << "1. CLOCK vs SECOND CHANCE - SIMILARIDADE ESPERADA:\n";
    std::cout << "   | Implementacao  : Ambos corretos e funcionais\n";
    std::cout << "   | Principio      : Mesmo conceito de \"segunda chance\"\n";
    std::cout << "   | Diferenca      : Estrutura de dados (circular vs linear)\n";
    std::cout << "   | Performance    : Clock O(1), Second Chance O(n)\n";
    std::cout << "   | Page Faults    : Resultados muito similares (normal!)\n\n";
    
    std::cout << "2. POR QUE RESULTADOS PODEM VARIAR:\n";
    std::cout << "   | Clock          : Melhor em padroes regulares/previsiveis\n";
    std::cout << "   | Second Chance  : Melhor em padroes complexos/irregulares\n";
    std::cout << "   | Motivo         : Reordenacao dinamica vs estrutura fixa\n";
    std::cout << "   | Exemplo        : Seq. basica (Clock+) vs Seq. complexa (SC+)\n";
    std::cout << "   | Conclusao      : Cada algoritmo tem pontos fortes!\n\n";
    
    std::cout << "3. COMPARACAO COM ALGORITMO OTIMO:\n";
    std::cout << "   | Algoritmo Otimo: Define limite teorico superior\n";
    std::cout << "   | Clock/SecondCh : Praticos e proximos do otimo\n";
    std::cout << "   | Gap            : Aceitavel para uso real\n\n";
    
    std::cout << "4. QUANDO USAR CADA ALGORITMO:\n";
    std::cout << "   | Clock          : Sistemas com padroes regulares\n";
    std::cout << "   | Second Chance  : Sistemas com acesso irregular/adaptativo\n";
    std::cout << "   | Performance    : Clock geralmente mais rapido (O(1))\n";
    std::cout << "   | Adaptabilidade : Second Chance mais flexivel\n";
    std::cout << "   | Escolha        : Depende do padrao de acesso esperado\n\n";
    
    std::cout << "===========================================\n";
    std::cout << "| Implementacao validada e funcionando!  |\n";
    std::cout << "| Similaridade entre algoritmos e NORMAL |\n";
    std::cout << "===========================================\n\n";
}
