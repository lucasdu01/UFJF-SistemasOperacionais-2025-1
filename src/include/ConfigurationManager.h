#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include "MemoryManager.h"
#include <memory>

/**
 * @brief Estrutura para armazenar configurações do simulador
 */
struct SimulatorConfig {
    int physicalMemorySize;
    int virtualMemorySize;
    bool debugMode;
    AlgorithmType currentAlgorithm;
    
    SimulatorConfig() 
        : physicalMemorySize(3), virtualMemorySize(20), 
          debugMode(false), currentAlgorithm(AlgorithmType::CLOCK) {}
};

/**
 * @brief Classe responsável por gerenciar configurações
 */
class ConfigurationManager {
private:
    SimulatorConfig config;

public:
    ConfigurationManager() = default;
    
    const SimulatorConfig& getConfig() const { return config; }
    
    void configureMemory();
    void selectAlgorithm();
    
    std::unique_ptr<MemoryManager> createMemoryManager() const;
};

#endif // CONFIGURATION_MANAGER_H
