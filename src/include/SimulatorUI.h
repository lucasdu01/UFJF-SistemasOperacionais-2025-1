#ifndef SIMULATOR_UI_H
#define SIMULATOR_UI_H

#include <string>

/**
 * @brief Classe responsável pela interface do usuário
 */
class SimulatorUI {
public:
    static void clearScreen();
    static void waitForUser();
    static int getIntInput(const std::string& prompt, int min = 1, int max = 100);
    static void showMainMenu(int physicalMemorySize, int virtualMemorySize, 
                           const std::string& algorithmName, bool debugMode);
    static void showHelp();
};

#endif // SIMULATOR_UI_H
