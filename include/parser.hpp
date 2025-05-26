#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <map>

class HistoryParser {
public:
    explicit HistoryParser(const std::string& filePath);
    std::vector<std::string> parse();
    std::vector<std::pair<std::string, int>> wrapper();
    std::string normaliseCommand(const std::string& raw) const;
    std::string getPath() const;

private:
    std::string path = "DEFAULT_PATH";
};

#endif
