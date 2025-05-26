#include "parser.hpp"    
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <unordered_map>


HistoryParser::HistoryParser(const std::string& filePath): path(filePath) {}


std::string HistoryParser::getPath() const {
    return path;
}
std::string HistoryParser::normaliseCommand(const std::string& raw) const {
    namespace fs = std::filesystem;
    std::string name = fs::path(raw).filename().string();
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (name.rfind("python", 0) == 0)
        return "python";
    if (name.rfind("pip", 0) == 0)
        return "pip";

    return name;
}


std::vector<std::string> HistoryParser::parse() {
    std::vector<std::string> commands;
    std::ifstream file(path);
    std::string line;

    if (!file) {
        std::cerr << "Failed to open history file: " << path << std::endl;
        return commands;
    }

    while (std::getline(file, line)) {
        if (!line.empty()) {
            line.erase(0, line.find_first_not_of(" \t"));

            std::istringstream iss(line);
            std::string firstWord;
            iss >> firstWord;

            if (!firstWord.empty()) {
                commands.push_back(normaliseCommand(firstWord));
            }
        }
    }
    return commands;
}


std::vector<std::pair<std::string, int>> HistoryParser::wrapper() {
    std::unordered_map<std::string, int> commandCount;
    std::vector<std::string> commands = parse();

    for (const auto& cmd : commands) {
        commandCount[cmd]++;
    }

    std::vector<std::pair<std::string, int>> sortedCommands(commandCount.begin(), commandCount.end());

    std::sort(sortedCommands.begin(), sortedCommands.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    return sortedCommands;
}


