#include "parser.hpp"
#include "utils.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

    std::string path;
    if (argc >= 2) {
        path = argv[1];
    } else {
        path = getHistoryFilePath();
        if (path.empty()) {
            std::cerr << "Failed to detect history file path.\n";
            return 1;
        }
    }

    HistoryParser parser(path);
    auto sorted = parser.wrapper();
    printWrapperStats(sorted);
    
    return 0;
}
