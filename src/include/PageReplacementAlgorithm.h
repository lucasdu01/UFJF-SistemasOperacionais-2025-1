#ifndef PAGE_REPLACEMENT_ALGORITHM_H
#define PAGE_REPLACEMENT_ALGORITHM_H

#include <vector>
#include <iostream>
#include <iomanip>

/**
 * @brief Estrutura para estatisticas dos algoritmos
 */
struct AlgorithmStatistics {
    int totalReferences;
    int pageFaults;
    int hits;
    
    AlgorithmStatistics() : totalReferences(0), pageFaults(0), hits(0) {}
    
    double getHitRate() const {
        return totalReferences > 0 ? (double)hits / totalReferences * 100.0 : 0.0;
    }
    
    double getFaultRate() const {
        return totalReferences > 0 ? (double)pageFaults / totalReferences * 100.0 : 0.0;
    }
    
    void reset() {
        totalReferences = 0;
        pageFaults = 0;
        hits = 0;
    }
};

/**
 * @brief Interface base para algoritmos de substituicao de pagina
 */
class PageReplacementAlgorithm {
protected:
    int memorySize;
    AlgorithmStatistics stats;
    bool debugMode;

public:
    explicit PageReplacementAlgorithm(int size, bool debug = false)
        : memorySize(size), debugMode(debug) {}
    
    virtual ~PageReplacementAlgorithm() = default;
    
    // Metodos virtuais puros
    virtual bool referencePage(int pageNumber) = 0;
    virtual void displayMemory() const = 0;
    virtual void reset() = 0;
    virtual std::string getAlgorithmName() const = 0;
    
    // Metodos comuns
    const AlgorithmStatistics& getStatistics() const { return stats; }
    int getMemorySize() const { return memorySize; }
    void setDebugMode(bool debug) { debugMode = debug; }
    
    virtual void displayStatistics() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << " | Faults: " << stats.pageFaults
                  << ", Hits: " << stats.hits
                  << ", Taxa Hit: " << stats.getHitRate() << "%";
    }
};

#endif // PAGE_REPLACEMENT_ALGORITHM_H
