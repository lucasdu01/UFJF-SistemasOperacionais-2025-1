#ifndef SECOND_CHANCE_ALGORITHM_H
#define SECOND_CHANCE_ALGORITHM_H

#include "PageReplacementAlgorithm.h"
#include <vector>
#include <queue>

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
 * @brief Implementacao do algoritmo Segunda Chance (Lista Linear)
 * 
 * O algoritmo Segunda Chance usa uma lista linear e move fisicamente 
 * as paginas quando dao uma "segunda chance", diferente do Clock que 
 * usa buffer circular com ponteiro fixo.
 */
class SecondChanceAlgorithm : public PageReplacementAlgorithm {
private:
    std::vector<SecondChancePage> memory;  // Memoria fisica como lista
    
    // Metodos auxiliares
    int findPage(int pageNumber) const;
    void moveToEnd(int index);
    void displayMemoryState() const;
    
public:
    SecondChanceAlgorithm(int size, bool debug = false);
    ~SecondChanceAlgorithm() override = default;
    
    // Implementacao dos metodos virtuais
    bool referencePage(int pageNumber) override;
    void displayMemory() const override;
    void reset() override;
    std::string getAlgorithmName() const override { return "Segunda Chance (Lista Linear)"; }
    
    // Metodos especificos do Segunda Chance
    std::vector<int> getCurrentPages() const;
    bool isMemoryFull() const;
};

#endif // SECOND_CHANCE_ALGORITHM_H
