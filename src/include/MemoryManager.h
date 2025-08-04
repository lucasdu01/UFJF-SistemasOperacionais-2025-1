#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "PageReplacementAlgorithm.h"
#include "ClockAlgorithm.h"
#include "SecondChanceAlgorithm.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @brief Tipo de algoritmo de substituicao de pagina
 */
enum class AlgorithmType {
    CLOCK,          // Algoritmo Clock (buffer circular)
    SECOND_CHANCE   // Algoritmo Segunda Chance (lista linear)
};

/**
 * @brief Tipo de resultado de uma operacao de referencia
 */
enum class ReferenceResult {
    HIT,        // Pagina encontrada na memoria
    MISS,       // Page fault - pagina nao encontrada
    INVALID     // Referencia invalida
};

/**
 * @brief Informacoes sobre uma referencia de pagina
 */
struct ReferenceInfo {
    int pageNumber;
    ReferenceResult result;
    std::string description;
    
    ReferenceInfo(int page, ReferenceResult res, const std::string& desc = "")
        : pageNumber(page), result(res), description(desc) {}
};

/**
 * @brief Gerenciador de memoria que utiliza algoritmos de substituicao
 */
class MemoryManager {
private:
    std::unique_ptr<ClockAlgorithm> clockAlgorithm;
    std::unique_ptr<SecondChanceAlgorithm> secondChanceAlgorithm;
    std::vector<ReferenceInfo> referenceHistory;
    int virtualMemorySize;    // Numero maximo de paginas validas
    bool loggingEnabled;      // Log de operacoes habilitado
    AlgorithmType currentAlgorithm;  // Algoritmo atualmente em uso

    // Metodos de validacao
    bool isValidPageNumber(int pageNumber) const;
    std::string getResultString(ReferenceResult result) const;

public:
    // Construtor
    MemoryManager(int physicalMemorySize, int virtualMemorySize = 100, 
                  bool debug = false, bool logging = true, 
                  AlgorithmType algorithm = AlgorithmType::CLOCK);
    
    // Destrutor
    ~MemoryManager() = default;

    // Metodos principais de gerenciamento
    ReferenceResult processPageReference(int pageNumber);
    void processSequence(const std::vector<int>& pageSequence);
    
    // Metodos de configuracao
    void setVirtualMemorySize(int size);
    void enableLogging(bool enable) { loggingEnabled = enable; }
    void enableDebug(bool enable);
    void setAlgorithm(AlgorithmType algorithm);
    
    // Metodos de consulta
    const AlgorithmStatistics& getStatistics() const;
    const std::vector<ReferenceInfo>& getHistory() const { return referenceHistory; }
    int getPhysicalMemorySize() const;
    int getVirtualMemorySize() const { return virtualMemorySize; }
    AlgorithmType getCurrentAlgorithm() const { return currentAlgorithm; }
    std::string getCurrentAlgorithmName() const;
    
    // Metodos de exibicao
    void displayCurrentState() const;
    void displayDetailedStatistics() const;
    void displayHistory(int lastN = -1) const;
    
    // Metodos de comparacao
    void compareWithFIFO(const std::vector<int>& sequence) const;
    void compareWithOptimal(const std::vector<int>& sequence) const;
    void compareClockWithSecondChance(const std::vector<int>& sequence) const;
    
    // Utilitarios
    void reset();
    void clearHistory() { referenceHistory.clear(); }
    
    // Operadores
    friend std::ostream& operator<<(std::ostream& os, const MemoryManager& manager);
};

/**
 * @brief Simulador simples de algoritmo FIFO para comparacao
 */
class FIFOSimulator {
private:
    std::vector<int> frames;
    int nextFrame;
    int memorySize;

public:
    explicit FIFOSimulator(int size);
    int simulate(const std::vector<int>& sequence);
};

/**
 * @brief Simulador de algoritmo otimo (Belady) para comparacao
 */
class OptimalSimulator {
private:
    int memorySize;
    
    int findOptimalVictim(const std::vector<int>& frames, 
                         const std::vector<int>& sequence, 
                         int currentIndex) const;

public:
    explicit OptimalSimulator(int size) : memorySize(size) {}
    int simulate(const std::vector<int>& sequence);
};

#endif // MEMORY_MANAGER_H
