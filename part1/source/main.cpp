#include "hashtable.hpp"
#include <iostream>
#include <fstream>

std::ifstream open_file(const std::string& name) {
  std::ifstream file;
  file.open(name);
  if (!file.is_open()) {
    std::cout << "Can't open supplied file name" << std::endl;
    exit(1);
  }
  return file;
}

int main(int argumentCount, char* arguments[]) {
  if(argumentCount <= 1) {
    std::cout << "Supply a text file as an argument. " << std::endl;
    return 1;
  }

  std::string fileName{arguments[1]};
  auto file {open_file(fileName)};

  std::string word;
  HashTable table;
  while (file >> word)
  {
    if(!table.get(word).has_value()) {
      table.insert(word, 1);
    } else{
      const auto count {table.get(word).value()};
      table.insert(word, count + 1);
    }
  }

  table.print_contents();

  return 0;
}
