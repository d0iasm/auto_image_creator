#include <clocale>
#include <locale>
#include <iostream>
#include <mecab.h>
#include <string>
#include <sstream>
#include <vector>


#define CHECK(eval) if (! eval) {                                       \
    const char *e = tagger ? tagger->what() : MeCab::getTaggerError();  \
    std::cerr << "Exception:" << e << std::endl;                        \
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


std::string filterNoun(const MeCab::Node *node) {
  std::string filtered;
  std::vector<std::string> feature;
  for (; node; node = node->next) {
    feature = split(node->feature, ',');
    if (feature[0] == "名詞") {
      std::cout << feature[6] << std::endl;
      filtered.append(feature[6] + " ");
    }
  }
  return filtered;
}


int main(int argc, char **argv) {
  std::setlocale(LC_CTYPE, "ja_JP.UTF-8");

  MeCab::Tagger *tagger = MeCab::createTagger("");
  CHECK(tagger);
  
  const MeCab::Node *node = tagger->parseToNode(argv[1]);
  CHECK(node);
  
  std::string filtered = filterNoun(node);
  std::cout << filtered << std::endl;
  delete tagger;

  return 0;
} 
