#include "../include/SecondChanceAlgorithm.h"

/**
 * @brief Construtor do algoritmo Segunda Chance
 */
SecondChanceAlgorithm::SecondChanceAlgorithm(int size, bool debug)
    : PageReplacementAlgorithm(size, debug) {
    
    if (size <= 0) {
        throw std::invalid_argument("Tamanho da memoria deve ser positivo");
    }
    
    memory.reserve(size);
}

/**
 * @brief Encontra uma pagina na memoria
 * @param pageNumber Numero da pagina a procurar
 * @return Indice da pagina ou -1 se nao encontrada
 */
int SecondChanceAlgorithm::findPage(int pageNumber) const {
    for (size_t i = 0; i < memory.size(); ++i) {
        if (memory[i].pageNumber == pageNumber) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

/**
 * @brief Move uma pagina para o final da lista (segunda chance)
 * @param index Indice da pagina a mover
 */
void SecondChanceAlgorithm::moveToEnd(int index) {
    if (index < 0 || index >= static_cast<int>(memory.size())) {
        return;
    }
    
    // Salva a pagina
    SecondChancePage page = memory[index];
    
    // Remove da posicao atual
    memory.erase(memory.begin() + index);
    
    // Adiciona no final
    memory.push_back(page);
}

/**
 * @brief Exibe o estado atual da memória
 */
void SecondChanceAlgorithm::displayMemoryState() const {
    std::cout << "Memoria: ";
    
    for (size_t i = 0; i < static_cast<size_t>(memorySize); ++i) {
        std::cout << "[";
        if (i < memory.size() && memory[i].pageNumber != -1) {
            std::cout << std::setw(2) << memory[i].pageNumber;
            if (memory[i].referenceBit) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        } else {
            std::cout << "   ";
        }
        std::cout << "] ";
    }
    
    displayStatistics();
}

/**
 * @brief Implementação do displayMemory para interface
 */
void SecondChanceAlgorithm::displayMemory() const {
    displayMemoryState();
}

/**
 * @brief Referencia uma página (método principal do algoritmo)
 * @param pageNumber Número da página a referenciar
 * @return true se houve page fault, false se foi hit
 */
bool SecondChanceAlgorithm::referencePage(int pageNumber) {
    stats.totalReferences++;
    
    if (debugMode) {
        std::cout << "\n--- Referencia " << stats.totalReferences 
                  << ": Pagina " << pageNumber << " ---\n";
    }
    
    // Procura a página na memória
    int pageIndex = findPage(pageNumber);
    
    if (pageIndex != -1) {
        // PAGE HIT: página encontrada
        stats.hits++;
        memory[pageIndex].referenceBit = true;  // Ativa bit de referência
        
        if (debugMode) {
            std::cout << "HIT: Pagina " << pageNumber << " encontrada na posicao " 
                      << pageIndex << "\n";
            displayMemoryState();
            std::cout << "\n";
        }
        
        return false;
    }
    
    // PAGE FAULT: página não encontrada
    stats.pageFaults++;
    
    if (debugMode) {
        std::cout << "MISS: Pagina " << pageNumber << " não encontrada\n";
    }
    
    // Se memória não está cheia, simplesmente adiciona
    if (static_cast<int>(memory.size()) < memorySize) {
        memory.push_back(SecondChancePage(pageNumber));
        
        if (debugMode) {
            std::cout << "Adicionada na posição " << (memory.size() - 1) << "\n";
            displayMemoryState();
            std::cout << "\n";
        }
        
        return true;
    }
    
    // Memória cheia: aplicar algoritmo Segunda Chance
    while (true) {
        // Verifica a primeira página da lista
        if (!memory[0].referenceBit) {
            // Bit = 0: substitui esta página
            if (debugMode) {
                std::cout << "Substituindo pagina " << memory[0].pageNumber 
                          << " (bit=0) por " << pageNumber << "\n";
            }
            
            memory[0] = SecondChancePage(pageNumber);
            break;
        } else {
            // Bit = 1: dá segunda chance
            if (debugMode) {
                std::cout << "Segunda chance para pagina " << memory[0].pageNumber 
                          << " (bit=1->0, movendo para o final)\n";
            }
            
            memory[0].referenceBit = false;  // Limpa bit
            moveToEnd(0);                    // Move para o final
        }
    }
    
    if (debugMode) {
        displayMemoryState();
        std::cout << "\n";
    }
    
    return true;
}

/**
 * @brief Reseta o algoritmo
 */
void SecondChanceAlgorithm::reset() {
    memory.clear();
    stats.reset();
    
    if (debugMode) {
        std::cout << "Segunda Chance resetado\n\n";
    }
}

/**
 * @brief Retorna as páginas atualmente na memória
 * @return Vetor com os números das páginas
 */
std::vector<int> SecondChanceAlgorithm::getCurrentPages() const {
    std::vector<int> pages;
    for (const auto& page : memory) {
        if (page.pageNumber != -1) {
            pages.push_back(page.pageNumber);
        }
    }
    return pages;
}

/**
 * @brief Verifica se a memória está cheia
 * @return true se cheia, false caso contrário
 */
bool SecondChanceAlgorithm::isMemoryFull() const {
    return static_cast<int>(memory.size()) >= memorySize;
}
