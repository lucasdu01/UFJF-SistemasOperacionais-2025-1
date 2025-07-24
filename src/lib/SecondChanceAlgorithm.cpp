#include "../include/SecondChanceAlgorithm.h"
#include "../include/ClockAlgorithm.h"  // Para usar a estrutura Statistics

/**
 * @brief Construtor do algoritmo Segunda Chance
 */
SecondChanceAlgorithm::SecondChanceAlgorithm(int size, bool debug)
    : memorySize(size), pageFaults(0), pageHits(0), totalReferences(0), debugMode(debug) {
    
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
 * @brief Exibe o estado atual da memoria
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
    
    std::cout << "| Faults: " << pageFaults 
              << ", Hits: " << pageHits 
              << ", Taxa: " << std::fixed << std::setprecision(2) 
              << getHitRate() << "%";
}

/**
 * @brief Referencia uma pagina (metodo principal do algoritmo)
 * @param pageNumber Numero da pagina a referenciar
 * @return true se houve page fault, false se foi hit
 */
bool SecondChanceAlgorithm::referencePage(int pageNumber) {
    totalReferences++;
    
    if (debugMode) {
        std::cout << "\n--- Referencia " << totalReferences 
                  << ": Pagina " << pageNumber << " ---\n";
    }
    
    // Procura a pagina na memoria
    int pageIndex = findPage(pageNumber);
    
    if (pageIndex != -1) {
        // PAGE HIT: pagina encontrada
        pageHits++;
        memory[pageIndex].referenceBit = true;  // Ativa bit de referencia
        
        if (debugMode) {
            std::cout << "HIT: Pagina " << pageNumber << " encontrada na posicao " 
                      << pageIndex << "\n";
            displayMemoryState();
            std::cout << "\n";
        }
        
        return false;
    }
    
    // PAGE FAULT: pagina nao encontrada
    pageFaults++;
    
    if (debugMode) {
        std::cout << "MISS: Pagina " << pageNumber << " nao encontrada\n";
    }
    
    // Se memoria nao esta cheia, simplesmente adiciona
    if (static_cast<int>(memory.size()) < memorySize) {
        memory.push_back(SecondChancePage(pageNumber));
        
        if (debugMode) {
            std::cout << "Adicionada na posicao " << (memory.size() - 1) << "\n";
            displayMemoryState();
            std::cout << "\n";
        }
        
        return true;
    }
    
    // Memoria cheia: aplicar algoritmo Segunda Chance
    while (true) {
        // Verifica a primeira pagina da lista
        if (!memory[0].referenceBit) {
            // Bit = 0: substitui esta pagina
            if (debugMode) {
                std::cout << "Substituindo pagina " << memory[0].pageNumber 
                          << " (bit=0) por " << pageNumber << "\n";
            }
            
            memory[0] = SecondChancePage(pageNumber);
            break;
        } else {
            // Bit = 1: da segunda chance
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
    pageFaults = 0;
    pageHits = 0;
    totalReferences = 0;
    
    if (debugMode) {
        std::cout << "Segunda Chance resetado\n\n";
    }
}

/**
 * @brief Calcula a taxa de hit
 * @return Taxa de hit em porcentagem
 */
double SecondChanceAlgorithm::getHitRate() const {
    if (totalReferences == 0) return 0.0;
    return (static_cast<double>(pageHits) / totalReferences) * 100.0;
}

/**
 * @brief Retorna estatisticas em formato compativel
 * @return Estrutura Statistics com os dados atuais
 */
Statistics SecondChanceAlgorithm::getStatistics() const {
    Statistics stats;
    stats.totalReferences = totalReferences;
    stats.pageFaults = pageFaults;
    stats.hits = pageHits;
    return stats;
}

/**
 * @brief Exibe estatisticas detalhadas
 */
void SecondChanceAlgorithm::displayStatistics() const {
    std::cout << "\n=== ESTATISTICAS SEGUNDA CHANCE ===\n";
    std::cout << "Total de referencias: " << totalReferences << "\n";
    std::cout << "Page Faults: " << pageFaults << "\n";
    std::cout << "Page Hits: " << pageHits << "\n";
    std::cout << "Taxa de Hit: " << std::fixed << std::setprecision(2) 
              << getHitRate() << "%\n";
    std::cout << "Taxa de Fault: " << std::fixed << std::setprecision(2) 
              << (100.0 - getHitRate()) << "%\n";
    
    std::cout << "\nEstado atual da memoria:\n";
    displayMemoryState();
    std::cout << "\n";
}

/**
 * @brief Retorna as paginas atualmente na memoria
 * @return Vetor com os numeros das paginas
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
 * @brief Verifica se a memoria esta cheia
 * @return true se cheia, false caso contrario
 */
bool SecondChanceAlgorithm::isMemoryFull() const {
    return static_cast<int>(memory.size()) >= memorySize;
}
