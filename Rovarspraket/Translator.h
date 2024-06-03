//
// Created by Brian Cassriel on 8/31/23.
//

#ifndef ROVARSPRAKET_TRANSLATOR_H
#define ROVARSPRAKET_TRANSLATOR_H
#include <string>

class Translator {
public:
    Translator();
    virtual ~Translator();
    std::string translateEnglishWord(std::string word);
    std::string translateEnglishSentence(std::string sentence);
};


#endif //ROVARSPRAKET_TRANSLATOR_H
