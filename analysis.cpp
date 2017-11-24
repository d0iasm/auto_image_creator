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


std::string filterNoun(const MeCab::Node *node, char *input) {
  std::string filtered;

  std::string feature;
  std::vector<std::string> noun;
  for (; node; node = node->next) {
    feature = node->feature;
    noun = split(feature, ',');
    if (noun[0] == "名詞") {
      // filtered = filtered + '\n' + (node->surface - *input);
      std::cout << node->surface <<std::endl;
      std::cout << (int)(node->surface - input + node->length) <<std::endl;
      std::cout << (int)(node->surface - input) <<std::endl;
      std::cout << node->rcAttr <<std::endl;
      std::cout << node->lcAttr <<std::endl;
      std::cout << node->alpha <<std::endl;
      std::cout << node->posid <<std::endl;
      std::cout << node->beta <<std::endl;
      std::cout << node->prob <<std::endl;
      std::cout << node->cost <<std::endl;
      std::cout << "-----" <<std::endl;
    }
  }

  return filtered;
}


int main(int argc, char **argv) {
  std::setlocale(LC_CTYPE, "ja_JP.UTF-8");

  // char input[1024];
  // std::cin >> input;

  // MeCab::Tagger *tagger = MeCab::createTagger("");
  // const MeCab::Node *node = tagger->parseToNode(input);
  // std::string filtered = filterNoun(node, input);
  // std::cout << filtered << std::endl;
  // delete tagger;

  // std::cout << argv[1] << std::endl;
  // char input[1024] = "吾輩は猫である。";
  MeCab::Tagger *wakati = MeCab::createTagger("-Owakati");
  // const char *res = wakati->parse(argv[1]);
  const char *res = wakati->parse(argv[1]);
  std::cout << res << std::endl;
  delete wakati;

  return 0;
} 
