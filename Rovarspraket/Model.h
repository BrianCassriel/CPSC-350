//
// Created by Brian Cassriel on 8/31/23.
//

#ifndef ROVARSPRAKET_MODEL_H
#define ROVARSPRAKET_MODEL_H
#include <string>

class Model {
public:
    Model();
    virtual ~Model();
    std::string translateSingleConsonant(char& consonant);
    std::string translateSingleVowel(char vowel);
};


#endif //ROVARSPRAKET_MODEL_H
