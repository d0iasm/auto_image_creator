#include <clocale>
#include <iostream>
#include <mecab.h>
#include <string>

int main() {
  std::setlocale(LC_ALL, "Japanese");

  char input[1024] = "²æÇÚ¤ÏÇ­¤Ç¤¢¤ë¡£";

  std::cout << input << std::endl;

  MeCab::Tagger *tagger = MeCab::createTagger("");
  const char *result = tagger->parse(input);

  std::cout << result << std::endl;

  delete tagger;
  return 0;
} 
