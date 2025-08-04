#ifndef CLOCK_ALGORITHM_H
#define CLOCK_ALGORITHM_H

#include "PageReplacementAlgorithm.h"
#include <vector>

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
 * @brief Implementacao do Algoritmo Clock (Buffer Circular)
 * 
 * O algoritmo Clock mantem um ponteiro que circula pelos frames
 * dando "segunda chance" a paginas com bit de referencia ativo.
 */
class ClockAlgorithm : public PageReplacementAlgorithm {
private:
    std::vector<Frame> frames;    // Frames de memoria fisica
    int clockHand;                // Ponteiro do relogio (posicao atual)

    // Metodos privados
    int findPage(int pageNumber) const;
    int findEmptyFrame() const;
    int getNextClockPosition() const;
    void advanceClock();

public:
    // Construtor
    explicit ClockAlgorithm(int size, bool debug = false);
    
    // Destrutor
    ~ClockAlgorithm() override = default;

    // Implementacao dos metodos virtuais
    bool referencePage(int pageNumber) override;
    void displayMemory() const override;
    void reset() override;
    std::string getAlgorithmName() const override { return "Clock (Buffer Circular)"; }
    
    // Metodos especificos do Clock
    int getClockPosition() const { return clockHand; }
    
    // Operadores para facilitar uso
    friend std::ostream& operator<<(std::ostream& os, const ClockAlgorithm& clock);
};

#endif // CLOCK_ALGORITHM_H
