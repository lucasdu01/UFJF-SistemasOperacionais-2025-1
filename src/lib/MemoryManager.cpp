#include "../include/MemoryManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

/**
 * @brief Construtor do MemoryManager
 */
MemoryManager::MemoryManager(int physicalMemorySize, int virtualMemorySize, 
                           bool debug, bool logging, AlgorithmType algorithm)
    : virtualMemorySize(virtualMemorySize), loggingEnabled(logging), 
      currentAlgorithm(algorithm) {
    
    if (physicalMemorySize <= 0 || virtualMemorySize <= 0) {
        throw std::invalid_argument("Tamanhos de memoria devem ser positivos");
    }
    
    // Inicializa ambos os algoritmos
    clockAlgorithm.reset(new ClockAlgorithm(physicalMemorySize, debug));
    secondChanceAlgorithm.reset(new SecondChanceAlgorithm(physicalMemorySize, debug));
    
    if (loggingEnabled) {
        std::cout << "MemoryManager inicializado:\n";
        std::cout << "- Memoria Fisica: " << physicalMemorySize << " frames\n";
        std::cout << "- Memoria Virtual: " << virtualMemorySize << " paginas\n";
        std::cout << "- Algoritmo: " << getCurrentAlgorithmName() << "\n";
    }
}

/**
 * @brief Valida se o numero da pagina e valido
 */
bool MemoryManager::isValidPageNumber(int pageNumber) const {
    return pageNumber >= 0 && pageNumber < virtualMemorySize;
}

/**
 * @brief Converte resultado em string
 */
std::string MemoryManager::getResultString(ReferenceResult result) const {
    switch (result) {
        case ReferenceResult::HIT: return "HIT";
        case ReferenceResult::MISS: return "MISS";
        case ReferenceResult::INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Processa uma referencia de pagina
 */
ReferenceResult MemoryManager::processPageReference(int pageNumber) {
    // Validar numero da pagina
    if (!isValidPageNumber(pageNumber)) {
        if (loggingEnabled) {
            std::cout << "ERRO: Pagina " << pageNumber << " e invalida "
                      << "(deve estar entre 0 e " << virtualMemorySize-1 << ")\n";
        }
        
        referenceHistory.emplace_back(pageNumber, ReferenceResult::INVALID, 
                                    "Numero de pagina invalido");
        return ReferenceResult::INVALID;
    }
    
    // Processar referencia com algoritmo ativo
    bool pageFault;
    if (currentAlgorithm == AlgorithmType::CLOCK) {
        pageFault = clockAlgorithm->referencePage(pageNumber);
    } else {
        pageFault = secondChanceAlgorithm->referencePage(pageNumber);
    }
    ReferenceResult result = pageFault ? ReferenceResult::MISS : ReferenceResult::HIT;
    
    // Registrar no historico
    std::stringstream desc;
    desc << "Pagina " << pageNumber << " - " << getResultString(result);
    if (pageFault) {
        desc << " (Page Fault)";
    }
    
    referenceHistory.emplace_back(pageNumber, result, desc.str());
    
    // Log da operacao
    if (loggingEnabled) {
        std::cout << "Referencia: " << pageNumber 
                  << " | Status: " << getResultString(result);
        if (pageFault) {
            std::cout << " (Page Fault)";
        }
        std::cout << "\n";
        displayCurrentState();
        std::cout << "\n";
    }
    
    return result;
}

/**
 * @brief Processa uma sequencia de referencias
 */
void MemoryManager::processSequence(const std::vector<int>& pageSequence) {
    if (loggingEnabled) {
        std::cout << "\n=== PROCESSANDO SEQUENCIA DE PAGINAS ===\n";
        std::cout << "Sequencia: ";
        for (size_t i = 0; i < pageSequence.size(); ++i) {
            std::cout << pageSequence[i];
            if (i < pageSequence.size() - 1) std::cout << " ";
        }
        std::cout << "\n\n";
    }
    
    for (size_t i = 0; i < pageSequence.size(); ++i) {
        if (loggingEnabled) {
            std::cout << "Step " << (i + 1) << ": ";
        }
        
        processPageReference(pageSequence[i]);
    }
    
    if (loggingEnabled) {
        std::cout << "\n=== SEQUENCIA PROCESSADA ===\n";
        displayDetailedStatistics();
    }
}

/**
 * @brief Define o tamanho da memoria virtual
 */
void MemoryManager::setVirtualMemorySize(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Tamanho da memoria virtual deve ser positivo");
    }
    virtualMemorySize = size;
}

/**
 * @brief Habilita/desabilita modo debug
 */
void MemoryManager::enableDebug(bool enable) {
    clockAlgorithm->setDebugMode(enable);
    secondChanceAlgorithm->setDebugMode(enable);
}

/**
 * @brief Define o algoritmo a ser usado
 */
void MemoryManager::setAlgorithm(AlgorithmType algorithm) {
    currentAlgorithm = algorithm;
    
    if (loggingEnabled) {
        std::cout << "Algoritmo alterado para: " << getCurrentAlgorithmName() << "\n";
    }
}

/**
 * @brief Retorna o nome do algoritmo atual
 */
std::string MemoryManager::getCurrentAlgorithmName() const {
    switch (currentAlgorithm) {
        case AlgorithmType::CLOCK:
            return "Clock (Relogio)";
        case AlgorithmType::SECOND_CHANCE:
            return "Segunda Chance";
        default:
            return "Desconhecido";
    }
}

/**
 * @brief Obtem estatisticas do algoritmo ativo
 */
const Statistics& MemoryManager::getStatistics() const {
    if (currentAlgorithm == AlgorithmType::CLOCK) {
        return clockAlgorithm->getStatistics();
    } else {
        static Statistics stats = secondChanceAlgorithm->getStatistics();
        return stats;
    }
}

/**
 * @brief Obtem tamanho da memoria fisica
 */
int MemoryManager::getPhysicalMemorySize() const {
    if (currentAlgorithm == AlgorithmType::CLOCK) {
        return clockAlgorithm->getMemorySize();
    } else {
        // SecondChance não tem getMemorySize, vamos usar os dados do Clock
        return clockAlgorithm->getMemorySize();
    }
}

/**
 * @brief Exibe estado atual da memoria
 */
void MemoryManager::displayCurrentState() const {
    std::cout << *clockAlgorithm;
}

/**
 * @brief Exibe estatisticas detalhadas
 */
void MemoryManager::displayDetailedStatistics() const {
    const auto& stats = getStatistics();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== ESTATISTICAS DETALHADAS ===\n";
    std::cout << "Total de referencias: " << stats.totalReferences << "\n";
    std::cout << "Page Faults: " << stats.pageFaults << "\n";
    std::cout << "Hits: " << stats.hits << "\n";
    std::cout << "Taxa de Page Fault: " << stats.getFaultRate() << "%\n";
    std::cout << "Taxa de Hit: " << stats.getHitRate() << "%\n";
    std::cout << "Memoria Fisica: " << getPhysicalMemorySize() << " frames\n";
    std::cout << "Memoria Virtual: " << virtualMemorySize << " paginas\n";
}

/**
 * @brief Exibe historico de referencias
 */
void MemoryManager::displayHistory(int lastN) const {
    std::cout << "=== HISTORICO DE REFERENCIAS ===\n";
    
    int start = 0;
    if (lastN > 0 && lastN < static_cast<int>(referenceHistory.size())) {
        start = referenceHistory.size() - lastN;
    }
    
    for (size_t i = start; i < referenceHistory.size(); ++i) {
        const auto& ref = referenceHistory[i];
        std::cout << std::setw(3) << (i + 1) << ": " 
                  << ref.description << "\n";
    }
}

/**
 * @brief Compara com algoritmo FIFO
 */
void MemoryManager::compareWithFIFO(const std::vector<int>& sequence) const {
    FIFOSimulator fifo(getPhysicalMemorySize());
    int fifoFaults = fifo.simulate(sequence);
    
    const auto& clockStats = getStatistics();
    
    std::cout << "\n=== COMPARACAO COM FIFO ===\n";
    std::cout << "Algoritmo Clock: " << clockStats.pageFaults << " page faults\n";
    std::cout << "Algoritmo FIFO:  " << fifoFaults << " page faults\n";
    
    if (clockStats.pageFaults < fifoFaults) {
        std::cout << "Clock teve melhor desempenho!\n";
    } else if (clockStats.pageFaults > fifoFaults) {
        std::cout << "FIFO teve melhor desempenho!\n";
    } else {
        std::cout << "Ambos tiveram o mesmo desempenho!\n";
    }
}

/**
 * @brief Compara com algoritmo ótimo
 */
void MemoryManager::compareWithOptimal(const std::vector<int>& sequence) const {
    OptimalSimulator optimal(getPhysicalMemorySize());
    int optimalFaults = optimal.simulate(sequence);
    
    const auto& clockStats = getStatistics();
    
    std::cout << "\n=== COMPARACAO COM ALGORITMO OTIMO ===\n";
    std::cout << "Algoritmo Clock:  " << clockStats.pageFaults << " page faults\n";
    std::cout << "Algoritmo Otimo:  " << optimalFaults << " page faults\n";
    
    if (clockStats.pageFaults == optimalFaults) {
        std::cout << "Clock alcancou desempenho otimo!\n";
    } else {
        double efficiency = (double)optimalFaults / clockStats.pageFaults * 100.0;
        std::cout << "Eficiencia do Clock: " << std::setprecision(1) 
                  << efficiency << "% do otimo\n";
    }
}

/**
 * @brief Reseta o gerenciador de memoria
 */
void MemoryManager::reset() {
    clockAlgorithm->reset();
    secondChanceAlgorithm->reset();
    referenceHistory.clear();
    
    if (loggingEnabled) {
        std::cout << "MemoryManager resetado\n";
    }
}

/**
 * @brief Operador de saída para MemoryManager
 */
std::ostream& operator<<(std::ostream& os, const MemoryManager& manager) {
    manager.displayCurrentState();
    return os;
}

// ============================================================================
// Implementação dos simuladores de comparação
// ============================================================================

/**
 * @brief Construtor do FIFOSimulator
 */
FIFOSimulator::FIFOSimulator(int size) : nextFrame(0), memorySize(size) {
    frames.resize(size, -1);
}

/**
 * @brief Simula algoritmo FIFO
 */
int FIFOSimulator::simulate(const std::vector<int>& sequence) {
    int pageFaults = 0;
    frames.assign(memorySize, -1);
    nextFrame = 0;
    
    for (int page : sequence) {
        // Verificar se página já está na memória
        bool found = std::find(frames.begin(), frames.end(), page) != frames.end();
        
        if (!found) {
            // Page fault - inserir página
            frames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % memorySize;
            pageFaults++;
        }
    }
    
    return pageFaults;
}

/**
 * @brief Encontra vitima otima para substituicao
 */
int OptimalSimulator::findOptimalVictim(const std::vector<int>& frames, 
                                       const std::vector<int>& sequence, 
                                       int currentIndex) const {
    int farthest = currentIndex;
    int victimIndex = 0;
    
    for (size_t i = 0; i < frames.size(); ++i) {
        int nextUse = sequence.size(); // Assume que nunca será usada novamente
        
        // Procurar proximo uso desta pagina
        for (size_t j = currentIndex + 1; j < sequence.size(); ++j) {
            if (sequence[j] == frames[i]) {
                nextUse = j;
                break;
            }
        }
        
        if (nextUse > farthest) {
            farthest = nextUse;
            victimIndex = i;
        }
    }
    
    return victimIndex;
}

/**
 * @brief Simula algoritmo otimo (Belady)
 */
int OptimalSimulator::simulate(const std::vector<int>& sequence) {
    int pageFaults = 0;
    std::vector<int> frames;
    
    for (size_t i = 0; i < sequence.size(); ++i) {
        int page = sequence[i];
        
        // Verificar se pagina ja esta na memoria
        bool found = std::find(frames.begin(), frames.end(), page) != frames.end();
        
        if (!found) {
            pageFaults++;
            
            if (static_cast<int>(frames.size()) < memorySize) {
                // Ainda ha espaco livre
                frames.push_back(page);
            } else {
                // Precisa substituir - usar algoritmo otimo
                int victimIndex = findOptimalVictim(frames, sequence, i);
                frames[victimIndex] = page;
            }
        }
    }
    
    return pageFaults;
}

/**
 * @brief Compara algoritmo Clock com Segunda Chance
 */
void MemoryManager::compareClockWithSecondChance(const std::vector<int>& sequence) const {
    std::cout << "\n=== COMPARACAO CLOCK vs SEGUNDA CHANCE ===\n";
    
    // Testa Clock
    ClockAlgorithm tempClock(getPhysicalMemorySize(), false);
    for (int page : sequence) {
        tempClock.referencePage(page);
    }
    auto clockStats = tempClock.getStatistics();
    
    // Testa Segunda Chance
    SecondChanceAlgorithm tempSecondChance(getPhysicalMemorySize(), false);
    for (int page : sequence) {
        tempSecondChance.referencePage(page);
    }
    auto secondChanceStats = tempSecondChance.getStatistics();
    
    // Exibe resultados
    std::cout << "Algoritmo Clock:        " << clockStats.pageFaults << " page faults\n";
    std::cout << "Algoritmo Segunda Chance: " << secondChanceStats.pageFaults << " page faults\n";
    
    if (clockStats.pageFaults < secondChanceStats.pageFaults) {
        std::cout << "Clock teve melhor desempenho!\n";
    } else if (secondChanceStats.pageFaults < clockStats.pageFaults) {
        std::cout << "Segunda Chance teve melhor desempenho!\n";
    } else {
        std::cout << "Ambos tiveram o mesmo desempenho!\n";
    }
    
    std::cout << "Diferenca: " << abs(clockStats.pageFaults - secondChanceStats.pageFaults) 
              << " page faults\n";
}
