#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "MemoryManager.h"
#include <memory>
#include <vector>

/**
 * @brief Classe responsável por executar testes automáticos
 */
class TestRunner {
private:
    std::unique_ptr<MemoryManager>& memoryManager;

public:
    explicit TestRunner(std::unique_ptr<MemoryManager>& manager);
    
    void runAllTests();
    
private:
    void runBasicTest();
    void runTemporalLocalityTest();
    void runWorstCaseTest();
    void runComparisonTests();
    void runOptimalComparisonTests();
    
    // Métodos de display visual
    void displayMainHeader();
    void displaySectionHeader(const std::string& sectionName);
    void displayTestHeader(const std::string& testName, const std::vector<int>& sequence);
    void displayTestResults(const std::string& testName, const AlgorithmStatistics& stats, 
                           const std::string& description = "");
    void displayFinalSummary();
    void displayComparisonTable(const std::vector<std::string>& testNames,
                               const std::vector<std::vector<int>>& testSequences,
                               const std::vector<int>& clockResults,
                               const std::vector<int>& secondChanceResults,
                               const std::vector<int>& optimalResults);
};

#endif // TEST_RUNNER_H
