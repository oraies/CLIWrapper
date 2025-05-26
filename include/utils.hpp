#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>      
#include <utility> 
std::string detectShell();        
std::string getHistoryFilePath(); 
void printWrapperStats(const std::vector<std::pair<std::string, int>>& sortedCommands);


#endif
