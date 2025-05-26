#include "utils.hpp"
#include <cstdlib>    
#include <string>
#include <iostream>
#include <iomanip> 
#include <algorithm>
#include <vector>

std::string detectShell() {
    const char* shellEnv = std::getenv("SHELL");
    if (!shellEnv) return "unknown";

    std::string shellPath(shellEnv); 
    size_t lastSlash = shellPath.find_last_of('/');
    if (lastSlash != std::string::npos) {
        return shellPath.substr(lastSlash + 1);
    }
    return shellPath;
}

std::string getHistoryFilePath() {
    const char* home = std::getenv("HOME");
    if (!home) return "";

    std::string shell = detectShell();
    if (shell == "bash") {
        return std::string(home) + "/.bash_history";
    } else if (shell == "zsh") {
        return std::string(home) + "/.zsh_history";
    } else if (shell == "fish") {
        return std::string(home) + "/.local/share/fish/fish_history";
    } else {
        std::cerr << "Unsupported shell: " << shell << std::endl;
        return "";
    }
}

void printWrapperStats(const std::vector<std::pair<std::string, int>>& sortedCommands) {
    if (sortedCommands.empty()) {
        std::cout << "No commands to display.\n";
        return;
    }

    size_t maxCmdLen = 0;
    int total = 0;
    for (const auto& [cmd, count] : sortedCommands) {
        maxCmdLen = std::max(maxCmdLen, cmd.length());
        total += count;
    }

    std::cout << "\n Most Used CLI Wrappers\n";
    std::cout << std::string(maxCmdLen + 40, '=') << "\n";

    for (const auto& [cmd, count] : sortedCommands) {
        double percent = (100.0 * count) / total;
        int barWidth = static_cast<int>(percent / 2); 

        std::cout
            << std::left << std::setw(maxCmdLen + 2) << cmd  
            << std::right << std::setw(4) << count << "x   " 
            << std::setw(6) << std::fixed << std::setprecision(1) << percent << "%   " 
            << std::string(barWidth, '#') << "\n";  
    }

    std::cout << std::string(maxCmdLen + 40, '=') << "\n";
}
