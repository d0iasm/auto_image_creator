#include <clocale>
#include <locale>
#include <iostream>
#include <mecab.h>
#include <string>

#define CHECK(eval) if(! eval) {                                        \
    const char *e tagger ? tagger->what() : MeCab::getTaggerError();    \
    std::cerr << "Exception: " << e << std::endl;                       \
    delete tagger;                                                      \
    return -1; }

int main() {
  std::setlocale(LC_CTYPE, "ja_JP.UTF-8");

  char input[1024] = "我輩は猫である。";

  MeCab::Tagger *tagger = MeCab::createTagger("");
  const char *result = tagger->parse(input);
  std::cout << result << std::endl;
  delete tagger;

  MeCab::Tagger *wakati = MeCab::createTagger("-Owakati");
  const char *res = wakati->parse(input);
  std::cout << res << std::endl;
  delete wakati;

  return 0;
} 
