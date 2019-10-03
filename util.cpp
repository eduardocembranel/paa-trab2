#include <sstream>

#include "util.hpp"

void eliminaAte(std::ifstream &arquivo, char c) {
   if (arquivo.is_open()) {
      char aux = EOF;
      do {
         arquivo >> aux;
      } while (aux != EOF && aux != c);
   }
}

bool isOnlySpaces(std::string str) {
   return (str.find_first_not_of(' ') == std::string::npos);
}

std::vector<std::string> split(std::string str, std::string delimiters) {
   std::vector<std::string> res;
   std::string::size_type pos = std::string::npos;
   while ((pos = str.find_first_of(delimiters)) != std::string::npos) {
      std::string str2 = str.substr(0, pos);
      if (!isOnlySpaces(str2))
         res.push_back(str2);
      str.erase(0, pos + 1);
   }
   if (!isOnlySpaces(str))
      res.push_back(str);
   return res;
}

int strToInt(std::string str) {
   std::stringstream ss(str);
   int x;
   ss >> x;
   return x;
}
