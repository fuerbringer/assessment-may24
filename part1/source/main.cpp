#include "hashtable.hpp"
#include <iostream>
#include <fstream>

std::ifstream open_file(const std::string &name)
{
  std::ifstream file;
  file.open(name);
  if (!file.is_open()) {
    std::cout << "Can't open supplied file name" << std::endl;
    exit(1);
  }
  return file;
}

std::string remove_punctuation(const std::string word)
{
  std::string result{};
  std::remove_copy_if(word.begin(), word.end(),
                      std::back_inserter(result),
                      std::ptr_fun<int, int>(&std::ispunct));
  return result;
}

/*
(Comment)
Could do further filtering for multichars like “ or ’ (remove_punctuation not enough for that)
*/

std::string to_lower_case(std::string word)
{
  std::transform(word.begin(), word.end(), word.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); });
  return word;
}

int main(const int argumentCount, const char *arguments[])
{
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
    word = remove_punctuation(word);
    word = to_lower_case(word);
    if(!table.get(word).has_value()) {
      table.insert(word, 1);
    } else {
      const auto count {table.get(word).value()};
      table.insert(word, count + 1);
    }
  }

  table.print_contents();

  return 0;
}
