//
// Created by Brian Cassriel on 8/31/23.
//

#include "Model.h"

Model::Model() {}
Model::~Model() {}

/**
 * Changes an English consonant into a Rövarspråket consonant.
 *  1. Consonants are duplicated.
 *  2. An 'o' is placed between them.
 * @param consonant - A char that is the consonant to be translated.
 * @return - A string that is the translated consonant.
 */
std::string Model::translateSingleConsonant(char& consonant) {
    std::string result = consonant + std::string("o") + char(std::tolower(consonant));;
    return result;
}

/**
 * Changes an English vowel into a Rövarspråket vowel.
 *  1. Vowels stay the same.
 * @param vowel - A char that is the vowel to be translated.
 * @return - A string that is the translated vowel.
 */
std::string Model::translateSingleVowel(char vowel) {
    std::string result{vowel};
    return result;
}
