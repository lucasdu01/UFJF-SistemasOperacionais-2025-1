#include "../include/MemoryManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>

/**
 * @brief Classe principal do simulador
 */
class ClockSimulator {
private:
    std::unique_ptr<MemoryManager> memoryManager;
    int physicalMemorySize;
    int virtualMemorySize;
    bool debugMode;
    AlgorithmType currentAlgorithm;

    // Metodos de interface
    void showMainMenu();
    void configureMemory();
    void selectAlgorithm();
    void runInteractiveSimulation();
    void runAutomaticTests();
    void showStatistics();
    void showHelp();
    
    // Metodos utilitarios
    int getIntInput(const std::string& prompt, int min = 1, int max = 100);
    std::vector<int> parseSequence(const std::string& input);
    void clearScreen();
    void waitForUser();

public:
    ClockSimulator();
    ~ClockSimulator() = default;
    
    void run();
};

/**
 * @brief Construtor do simulador
 */
ClockSimulator::ClockSimulator() 
    : physicalMemorySize(3), virtualMemorySize(20), debugMode(false), 
      currentAlgorithm(AlgorithmType::CLOCK) {
    
    memoryManager.reset(new MemoryManager(
        physicalMemorySize, virtualMemorySize, debugMode, true, currentAlgorithm));
}

/**
 * @brief Obtem entrada inteira do usuario com validacao
 */
int ClockSimulator::getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                break;
            } else {
                std::cout << "Valor deve estar entre " << min << " e " << max << "\n";
            }
        } else {
            std::cout << "Entrada invalida. Digite um numero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

/**
 * @brief Converte string em sequencia de numeros
 */
std::vector<int> ClockSimulator::parseSequence(const std::string& input) {
    std::vector<int> sequence;
    std::istringstream iss(input);
    int page;
    
    while (iss >> page) {
        sequence.push_back(page);
    }
    
    return sequence;
}

/**
 * @brief Limpa a tela (multiplataforma)
 */
void ClockSimulator::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Aguarda entrada do usuario
 */
void ClockSimulator::waitForUser() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.get();
}

/**
 * @brief Exibe menu principal
 */
void ClockSimulator::showMainMenu() {
    std::cout << "\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "|        SIMULADOR ALGORITMOS DE SUBSTITUICAO             |\n";
    std::cout << "|          Sistemas Operacionais - UFJF - 2025.1          |\n";
    std::cout << "|     Tema 28: Clock & Segunda Chance                     |\n";
    std::cout << "|---------------------------------------------------------|\n";
    std::cout << "|                                                         |\n";
    std::cout << "|  1. Configurar parametros de memoria                    |\n";
    std::cout << "|  2. Selecionar algoritmo                                |\n";
    std::cout << "|  3. Executar simulacao interativa                       |\n";
    std::cout << "|  4. Executar testes automaticos                         |\n";
    std::cout << "|  5. Visualizar estatisticas                             |\n";
    std::cout << "|  6. Ajuda                                               |\n";
    std::cout << "|  7. Sair                                                |\n";
    std::cout << "|                                                         |\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "\nConfiguracao atual:\n";
    std::cout << "- Memoria Fisica: " << physicalMemorySize << " frames\n";
    std::cout << "- Memoria Virtual: " << virtualMemorySize << " paginas\n";
    std::cout << "- Algoritmo: " << memoryManager->getCurrentAlgorithmName() << "\n";
    std::cout << "- Modo Debug: " << (debugMode ? "Ativado" : "Desativado") << "\n";
}

/**
 * @brief Configura parametros de memoria
 */
void ClockSimulator::configureMemory() {
    clearScreen();
    std::cout << "=== CONFIGURACAO DE PARAMETROS ===\n\n";
    
    physicalMemorySize = getIntInput(
        "Digite o numero de frames na memoria fisica (3-20): ", 3, 20);
    
    virtualMemorySize = getIntInput(
        "Digite o numero de paginas na memoria virtual (10-100): ", 10, 100);
    
    std::cout << "\nHabilitar modo debug? (1=Sim, 0=Nao): ";
    int debug = getIntInput("", 0, 1);
    debugMode = (debug == 1);
    
    // Recriar gerenciador com novas configuracoes
    memoryManager.reset(new MemoryManager(
        physicalMemorySize, virtualMemorySize, debugMode, true, currentAlgorithm));
    
    std::cout << "\nConfiguracao salva com sucesso!\n";
    waitForUser();
}

/**
 * @brief Permite selecionar o algoritmo
 */
void ClockSimulator::selectAlgorithm() {
    clearScreen();
    std::cout << "=== SELECAO DE ALGORITMO ===\n\n";
    std::cout << "1. Clock (Relogio) - Buffer circular com ponteiro\n";
    std::cout << "2. Segunda Chance - Lista linear com movimento de paginas\n\n";
    
    int choice = getIntInput("Escolha o algoritmo (1-2): ", 1, 2);
    
    AlgorithmType newAlgorithm;
    if (choice == 1) {
        newAlgorithm = AlgorithmType::CLOCK;
        std::cout << "\nAlgoritmo Clock selecionado!\n";
    } else {
        newAlgorithm = AlgorithmType::SECOND_CHANCE;
        std::cout << "\nAlgoritmo Segunda Chance selecionado!\n";
    }
    
    if (newAlgorithm != currentAlgorithm) {
        currentAlgorithm = newAlgorithm;
        memoryManager->setAlgorithm(currentAlgorithm);
        std::cout << "Algoritmo alterado com sucesso!\n";
    } else {
        std::cout << "Algoritmo ja estava selecionado!\n";
    }
    
    waitForUser();
}

/**
 * @brief Executa simulacao interativa
 */
void ClockSimulator::runInteractiveSimulation() {
    clearScreen();
    std::cout << "=== SIMULACAO INTERATIVA ===\n\n";
    std::cout << "Memoria configurada: " << physicalMemorySize << " frames\n";
    std::cout << "Digite as paginas a serem referenciadas (separadas por espaco)\n";
    std::cout << "Digite 'q' para sair da simulacao\n\n";
    
    memoryManager->reset();
    
    std::string input;
    while (true) {
        std::cout << "Paginas: ";
        std::getline(std::cin, input);
        
        if (input == "q" || input == "Q") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        auto sequence = parseSequence(input);
        if (!sequence.empty()) {
            memoryManager->processSequence(sequence);
        } else {
            std::cout << "Sequencia invalida. Tente novamente.\n";
        }
        
        std::cout << "\n";
    }
    
    std::cout << "\n=== RESUMO DA SIMULACAO ===\n";
    memoryManager->displayDetailedStatistics();
    waitForUser();
}

/**
 * @brief Executa testes automaticos
 */
void ClockSimulator::runAutomaticTests() {
    clearScreen();
    std::cout << "=== TESTES AUTOMATICOS ===\n\n";
    
    // Teste 1: Sequencia basica
    std::cout << "Teste 1: Sequencia Basica\n";
    std::cout << "Memoria: " << physicalMemorySize << " frames | ";
    std::vector<int> sequence1 = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    std::cout << "Sequencia: ";
    for (size_t i = 0; i < sequence1.size(); ++i) {
        std::cout << sequence1[i];
        if (i < sequence1.size() - 1) std::cout << " ";
    }
    std::cout << "\n\n";
    
    memoryManager->reset();
    memoryManager->enableLogging(false); // Desabilitar log detalhado
    memoryManager->processSequence(sequence1);
    
    std::cout << "Resultado do Teste 1:\n";
    const auto& stats1 = memoryManager->getStatistics();
    std::cout << "- Total de referencias: " << stats1.totalReferences << "\n";
    std::cout << "- Page Faults: " << stats1.pageFaults << "\n";
    std::cout << "- Taxa de Hit: " << std::fixed << std::setprecision(2) 
              << stats1.getHitRate() << "%\n\n";
    
    // Comparacao com outros algoritmos
    memoryManager->compareWithFIFO(sequence1);
    memoryManager->compareWithOptimal(sequence1);
    memoryManager->compareClockWithSecondChance(sequence1);
    
    std::cout << "\n";
    
    // Teste 2: Localidade temporal
    std::cout << "Teste 2: Localidade Temporal\n";
    std::vector<int> sequence2 = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    std::cout << "Sequencia: ";
    for (size_t i = 0; i < sequence2.size(); ++i) {
        std::cout << sequence2[i];
        if (i < sequence2.size() - 1) std::cout << " ";
    }
    std::cout << "\n\n";
    
    memoryManager->reset();
    memoryManager->processSequence(sequence2);
    
    const auto& stats2 = memoryManager->getStatistics();
    std::cout << "Resultado do Teste 2:\n";
    std::cout << "- Page Faults: " << stats2.pageFaults << "\n";
    std::cout << "- Taxa de Hit: " << std::fixed << std::setprecision(2) 
              << stats2.getHitRate() << "%\n";
    std::cout << "- Demonstra eficiencia com localidade temporal\n\n";
    
    // Teste 3: Pior caso
    std::cout << "Teste 3: Pior Caso (sem reutilizacao)\n";
    std::vector<int> sequence3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Sequencia: ";
    for (size_t i = 0; i < sequence3.size(); ++i) {
        std::cout << sequence3[i];
        if (i < sequence3.size() - 1) std::cout << " ";
    }
    std::cout << "\n\n";
    
    memoryManager->reset();
    memoryManager->processSequence(sequence3);
    
    const auto& stats3 = memoryManager->getStatistics();
    std::cout << "Resultado do Teste 3:\n";
    std::cout << "- Page Faults: " << stats3.pageFaults << "\n";
    std::cout << "- Taxa de Hit: " << std::fixed << std::setprecision(2) 
              << stats3.getHitRate() << "%\n";
    std::cout << "- Demonstra comportamento no pior caso\n\n";
    
    memoryManager->enableLogging(true); // Reabilitar log
    waitForUser();
}

/**
 * @brief Mostra estatisticas
 */
void ClockSimulator::showStatistics() {
    clearScreen();
    std::cout << "=== ESTATiSTICAS ATUAIS ===\n\n";
    
    memoryManager->displayDetailedStatistics();
    std::cout << "\n";
    memoryManager->displayHistory(10); // Ultimas 10 referencias
    
    waitForUser();
}

/**
 * @brief Mostra ajuda
 */
void ClockSimulator::showHelp() {
    clearScreen();
    std::cout << "=== AJUDA - SIMULADOR ALGORITMO CLOCK ===\n\n";
    
    std::cout << "SOBRE O ALGORITMO:\n";
    std::cout << "O algoritmo Clock (Segunda Chance) e uma melhoria do FIFO que usa\n";
    std::cout << "um bit de referencia para dar uma 'segunda chance' a paginas\n";
    std::cout << "frequentemente acessadas.\n\n";
    
    std::cout << "COMO FUNCIONA:\n";
    std::cout << "1. Mantem um ponteiro circular (relogio) nos frames\n";
    std::cout << "2. Quando precisa substituir:\n";
    std::cout << "   - Se bit = 1: limpa bit e avanca (segunda chance)\n";
    std::cout << "   - Se bit = 0: substitui a pagina\n\n";
    
    std::cout << "USANDO O SIMULADOR:\n";
    std::cout << "Configure a memoria (recomendado: 3-5 frames)\n";
    std::cout << "Na simulacao interativa, digite sequencias como: 1 2 3 4\n";
    std::cout << "Use testes automaticos para comparar algoritmos\n";
    std::cout << "O simbolo * indica bit de referencia ativado\n\n";
    
    std::cout << "EXEMPLO DE SAIDA:\n";
    std::cout << "Memoria: [1*] [2 ] [3*] | Clock: 1 | Faults: 3, Hits: 2\n";
    std::cout << "\n";
    std::cout << "       pagina bit  bit\n";
    std::cout << "          1   ativo inativo\n\n";
    
    waitForUser();
}

/**
 * @brief Loop principal do simulador
 */
void ClockSimulator::run() {
    int choice;
    
    while (true) {
        clearScreen();
        showMainMenu();
        
        choice = getIntInput("\nEscolha uma opcao (1-7): ", 1, 7);
        
        switch (choice) {
            case 1:
                configureMemory();
                break;
            case 2:
                selectAlgorithm();
                break;
            case 3:
                runInteractiveSimulation();
                break;
            case 4:
                runAutomaticTests();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                showHelp();
                break;
            case 7:
                std::cout << "\nObrigado por usar o simulador!\n";
                std::cout << "Desenvolvido para Sistemas Operacionais - UFJF\n";
                return;
        }
    }
}

/**
 * @brief Funcao principal
 */
int main() {
    try {
        ClockSimulator simulator;
        simulator.run();
    } catch (const std::exception& e) {
        std::cerr << "ERRO: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
