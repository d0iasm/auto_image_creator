#include <clocale>
#include <locale>
#include <iostream>
#include <mecab.h>
#include <string>
#include <sstream>
#include <vector>


#define CHECK(eval) if(! eval) {                                        \
    const char *e tagger ? tagger->what() : MeCab::getTaggerError();    \
    std::cerr << "Exception: " << e << std::endl;                       \
    delete tagger;                                                      \
    return -1; }


std::vector<std::string> split(const std::string &str, char delim) {
  std::vector<std::string> elems;
  std::string item;
  for (char ch: str) {
    if (ch == delim) {
      if (!item.empty()) {
        elems.push_back(item);
      }
      item.clear();
    } else {
      item += ch;
    }
  }
  if (!item.empty()) {
    elems.push_back(item);
  }
  return elems;
}


std::string filterNoun(const MeCab::Node *node, const int input_size) {
  std::string filtered;

  std::string feature;
  std::vector<std::string> noun;
  for (; node; node = node->next) {
    feature = node->feature;
    noun = split(feature, ',');
    if (noun[0] == "名詞") {
      // filtered = filtered + '\n' + (node->surface - *input);
      std::cout << node->surface <<std::endl;
      std::cout << (node->surface - input_size + node->length) <<std::endl;
      std::cout << (node->surface - input_size) <<std::endl;
      std::cout << "-----" <<std::endl;
    }
  }

  return filtered;
}


int main() {
  std::setlocale(LC_CTYPE, "ja_JP.UTF-8");

  std::string input;
  std::cin >> input;
  char c_input[1024];
  input.copy(c_input, input.size());

  MeCab::Tagger *tagger = MeCab::createTagger("");
  const MeCab::Node *node = tagger->parseToNode(c_input);
  std::string filtered = filterNoun(node, input.length());
  std::cout << filtered << std::endl;
  delete tagger;

  MeCab::Tagger *wakati = MeCab::createTagger("-Owakati");
  const char *res = wakati->parse(c_input);
  std::cout << res << std::endl;
  delete wakati;

  return 0;
} 
