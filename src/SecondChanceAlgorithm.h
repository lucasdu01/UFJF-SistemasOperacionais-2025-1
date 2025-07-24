#ifndef SECOND_CHANCE_ALGORITHM_H
#define SECOND_CHANCE_ALGORITHM_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>

// Forward declaration
struct Statistics;

/**
 * @brief Estrutura que representa uma pagina na memoria
 */
struct SecondChancePage {
    int pageNumber;      // Numero da pagina
    bool referenceBit;   // Bit de referencia
    
    SecondChancePage() : pageNumber(-1), referenceBit(false) {}
    SecondChancePage(int page) : pageNumber(page), referenceBit(true) {}
};

/**
 * @brief Implementacao do algoritmo Segunda Chance (Second Chance)
 * 
 * O algoritmo Segunda Chance e uma variacao do FIFO que usa uma lista linear
 * e move fisicamente as paginas quando dao uma "segunda chance".
 * Diferente do Clock que usa buffer circular com ponteiro fixo.
 */
class SecondChanceAlgorithm {
private:
    std::vector<SecondChancePage> memory;  // Memoria fisica como lista
    int memorySize;                        // Tamanho da memoria fisica
    int pageFaults;                        // Contador de page faults
    int pageHits;                          // Contador de page hits
    int totalReferences;                   // Total de referencias
    bool debugMode;                        // Modo debug ativo
    
    // Metodos auxiliares
    int findPage(int pageNumber) const;
    void moveToEnd(int index);
    void displayMemoryState() const;
    
public:
    SecondChanceAlgorithm(int size, bool debug = false);
    ~SecondChanceAlgorithm() = default;
    
    // Metodos principais
    bool referencePage(int pageNumber);
    void reset();
    
    // Metodos de consulta
    int getPageFaults() const { return pageFaults; }
    int getPageHits() const { return pageHits; }
    int getTotalReferences() const { return totalReferences; }
    double getHitRate() const;
    Statistics getStatistics() const;
    
    // Metodos de exibicao
    void displayStatistics() const;
    void setDebugMode(bool enabled) { debugMode = enabled; }
    
    // Metodos para comparacao
    std::vector<int> getCurrentPages() const;
    bool isMemoryFull() const;
};

#endif // SECOND_CHANCE_ALGORITHM_H
