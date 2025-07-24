#ifndef CLOCK_ALGORITHM_H
#define CLOCK_ALGORITHM_H

#include <vector>
#include <iostream>
#include <iomanip>

/**
 * @brief Representa um frame na memoria fisica
 */
class Frame {
public:
    int pageNumber;     // Numero da pagina (-1 se vazio)
    bool referenceBit;  // Bit de referencia (true = referenciado recentemente)
    bool valid;         // Frame esta ocupado?

    // Construtor
    Frame() : pageNumber(-1), referenceBit(false), valid(false) {}
    
    // Construtor com parametros
    Frame(int page, bool refBit = true) 
        : pageNumber(page), referenceBit(refBit), valid(true) {}

    // Verifica se o frame esta vazio
    bool isEmpty() const { return !valid; }
    
    // Limpa o frame
    void clear() {
        pageNumber = -1;
        referenceBit = false;
        valid = false;
    }
};

/**
 * @brief Estrutura para estatisticas do algoritmo
 */
struct Statistics {
    int totalReferences;
    int pageFaults;
    int hits;
    
    Statistics() : totalReferences(0), pageFaults(0), hits(0) {}
    
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
 * @brief Implementacao do Algoritmo Clock (Segunda Chance)
 */
class ClockAlgorithm {
private:
    std::vector<Frame> frames;    // Frames de memoria fisica
    int clockHand;                // Ponteiro do relogio (posicao atual)
    int memorySize;               // Numero total de frames
    Statistics stats;             // Estatisticas do algoritmo
    bool debugMode;               // Modo debug para visualizacao

    // Métodos privados
    int findPage(int pageNumber) const;
    int findEmptyFrame() const;
    int getNextClockPosition() const;
    void advanceClock();

public:
    // Construtor
    explicit ClockAlgorithm(int size, bool debug = false);
    
    // Destrutor
    ~ClockAlgorithm() = default;

    // Metodos principais
    bool referencePage(int pageNumber);
    void displayMemory() const;
    void displayStatistics() const;
    
    // Getters
    const Statistics& getStatistics() const { return stats; }
    int getMemorySize() const { return memorySize; }
    int getClockPosition() const { return clockHand; }
    
    // Utilitarios
    void reset();
    void setDebugMode(bool debug) { debugMode = debug; }
    
    // Operadores para facilitar uso
    friend std::ostream& operator<<(std::ostream& os, const ClockAlgorithm& clock);
};

#endif // CLOCK_ALGORITHM_H
