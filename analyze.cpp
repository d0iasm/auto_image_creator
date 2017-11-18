#include <clocale>
#include <locale>
#include <iostream>
#include <mecab.h>
#include <string>

int main() {
  std::setlocale( LC_CTYPE, "ja_JP.UTF-8");

  char input[1024] = "我輩は猫である。";

  std::cout << input << std::endl;

  MeCab::Tagger *tagger = MeCab::createTagger("");
  const char *result = tagger->parse(input);

  std::cout << result << std::endl;

  delete tagger;
  return 0;
} 
