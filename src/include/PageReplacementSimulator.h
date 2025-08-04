#ifndef PAGE_REPLACEMENT_SIMULATOR_H
#define PAGE_REPLACEMENT_SIMULATOR_H

#include "MemoryManager.h"
#include "ConfigurationManager.h"
#include "TestRunner.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief Classe principal do simulador de algoritmos de substituição de página
 * Suporta Clock, Second Chance e outros algoritmos de forma genérica
 */
class PageReplacementSimulator {
private:
    std::unique_ptr<MemoryManager> memoryManager;
    ConfigurationManager configManager;
    std::unique_ptr<TestRunner> testRunner;

    // Métodos principais
    void runInteractiveSimulation();
    void showStatistics();
    
    // Métodos utilitários
    std::vector<int> parseSequence(const std::string& input);
    void updateMemoryManager();

public:
    PageReplacementSimulator();
    ~PageReplacementSimulator() = default;
    
    void run();
};

#endif // PAGE_REPLACEMENT_SIMULATOR_H
