#include "ClockAlgorithm.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Construtor do ClockAlgorithm
 * @param size Numero de frames na memoria fisica
 * @param debug Habilita modo debug
 */
ClockAlgorithm::ClockAlgorithm(int size, bool debug) 
    : frames(size), clockHand(0), memorySize(size), debugMode(debug) {
    
    if (size <= 0) {
        throw std::invalid_argument("Tamanho da memoria deve ser positivo");
    }
    
    // Inicializar todos os frames como vazios
    for (auto& frame : frames) {
        frame.clear();
    }
    
    if (debugMode) {
        std::cout << "ClockAlgorithm inicializado com " << size << " frames\n";
    }
}

/**
 * @brief Procura uma pagina especifica na memoria
 * @param pageNumber Numero da pagina a procurar
 * @return Indice do frame se encontrado, -1 caso contrario
 */
int ClockAlgorithm::findPage(int pageNumber) const {
    for (int i = 0; i < memorySize; ++i) {
        if (frames[i].valid && frames[i].pageNumber == pageNumber) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Procura um frame vazio na memoria
 * @return Indice do frame vazio se encontrado, -1 caso contrario
 */
int ClockAlgorithm::findEmptyFrame() const {
    for (int i = 0; i < memorySize; ++i) {
        if (frames[i].isEmpty()) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Calcula a proxima posicao do ponteiro do relogio
 * @return Proxima posicao (circular)
 */
int ClockAlgorithm::getNextClockPosition() const {
    return (clockHand + 1) % memorySize;
}

/**
 * @brief Avanca o ponteiro do relogio
 */
void ClockAlgorithm::advanceClock() {
    clockHand = getNextClockPosition();
}

/**
 * @brief Processa uma referencia de pagina usando o algoritmo Clock
 * @param pageNumber Numero da pagina referenciada
 * @return true se houve page fault, false se hit
 */
bool ClockAlgorithm::referencePage(int pageNumber) {
    stats.totalReferences++;
    
    if (debugMode) {
        std::cout << "\n--- Referencia a pagina " << pageNumber << " ---\n";
    }
    
    // Verificar se a pagina ja esta na memoria
    int frameIndex = findPage(pageNumber);
    
    if (frameIndex != -1) {
        // HIT: Pagina encontrada na memoria
        frames[frameIndex].referenceBit = true;
        stats.hits++;
        
        if (debugMode) {
            std::cout << "HIT: Pagina " << pageNumber 
                      << " encontrada no frame " << frameIndex << "\n";
        }
        
        return false; // Nao houve page fault
    }
    
    // MISS: Pagina nao esta na memoria - page fault
    stats.pageFaults++;
    
    if (debugMode) {
        std::cout << "MISS: Pagina " << pageNumber << " nao encontrada\n";
    }
    
    // Procurar frame vazio primeiro
    int emptyFrame = findEmptyFrame();
    if (emptyFrame != -1) {
        // Usar frame vazio
        frames[emptyFrame] = Frame(pageNumber, true);
        
        if (debugMode) {
            std::cout << "Frame vazio " << emptyFrame 
                      << " utilizado para pagina " << pageNumber << "\n";
        }
        
        return true; // Houve page fault
    }
    
    // Nao ha frames vazios - usar algoritmo Clock para substituicao
    if (debugMode) {
        std::cout << "Aplicando algoritmo Clock para substituicao...\n";
    }
    
    int iterations = 0;
    
    while (true) {
        Frame& currentFrame = frames[clockHand];
        
        if (debugMode) {
            std::cout << "Verificando frame " << clockHand 
                      << ": pagina " << currentFrame.pageNumber
                      << ", bit=" << (currentFrame.referenceBit ? 1 : 0);
        }
        
        if (!currentFrame.referenceBit) {
            // Bit de referencia = 0, substituir esta pagina
            if (debugMode) {
                std::cout << " -> Substituindo pagina " << currentFrame.pageNumber
                          << " por pagina " << pageNumber << "\n";
            }
            
            currentFrame = Frame(pageNumber, true);
            advanceClock();
            break;
        } else {
            // Bit de referencia = 1, dar segunda chance
            currentFrame.referenceBit = false;
            
            if (debugMode) {
                std::cout << " -> Segunda chance, limpando bit\n";
            }
            
            advanceClock();
        }
        
        // Protecao contra loop infinito (nao deveria acontecer)
        iterations++;
        if (iterations > memorySize * 2) {
            std::cerr << "ERRO: Loop infinito detectado no algoritmo Clock!\n";
            break;
        }
    }
    
    return true; // Houve page fault
}

/**
 * @brief Exibe o estado atual da memoria
 */
void ClockAlgorithm::displayMemory() const {
    std::cout << "Memoria: ";
    
    for (int i = 0; i < memorySize; ++i) {
        std::cout << "[";
        
        if (frames[i].isEmpty()) {
            std::cout << " ";
        } else {
            std::cout << frames[i].pageNumber;
            if (frames[i].referenceBit) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        
        std::cout << "]";
        
        if (i < memorySize - 1) {
            std::cout << " ";
        }
    }
    
    std::cout << " | Clock: " << clockHand;
}

/**
 * @brief Exibe as estatisticas do algoritmo
 */
void ClockAlgorithm::displayStatistics() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << " | Faults: " << stats.pageFaults
              << ", Hits: " << stats.hits
              << ", Taxa Hit: " << stats.getHitRate() << "%";
}

/**
 * @brief Reseta o estado do algoritmo
 */
void ClockAlgorithm::reset() {
    for (auto& frame : frames) {
        frame.clear();
    }
    clockHand = 0;
    stats.reset();
    
    if (debugMode) {
        std::cout << "ClockAlgorithm resetado\n";
    }
}

/**
 * @brief Operador de saida para ClockAlgorithm
 */
std::ostream& operator<<(std::ostream& os, const ClockAlgorithm& clock) {
    clock.displayMemory();
    clock.displayStatistics();
    return os;
}
