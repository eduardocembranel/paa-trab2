#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>
#include <vector>
#include <string>

void eliminaAte(std::ifstream &, char);
std::vector<std::string> split(std::string, std::string);
bool isOnlySpaces(std::string);
int strToInt(std::string);

#endif // !UTIL_HPP
