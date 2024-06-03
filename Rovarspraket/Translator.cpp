//
// Created by Brian Cassriel on 8/31/23.
//

#include "Translator.h"
#include "Model.h"

Translator::Translator() {}
Translator::~Translator() {}

/**
 * Translates an English word into a Rövarspråket word. Should contain no non-alpha characters.
 * @param word - A string that is the English word to be converted.
 * @return - A string that is the converted Rövarspråket word.
 */
std::string Translator::translateEnglishWord(std::string word) {
    std::string newWord = std::string();
    Model* m = new Model();
    for (char letter : word) {
        if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
            newWord += m->translateSingleVowel(letter);
        else
            newWord += m->translateSingleConsonant(letter);
    }
    return newWord;
}

/**
 * Translates an English sentence into a Rövarspråket sentence.
 * @param sentence - A string that is the English sentence to be converted.
 * @return - A string that is the converted Rövarspråket sentence.
 */
std::string Translator::translateEnglishSentence(std::string sentence) {
    std::string newSentence = std::string();
    Model* m = new Model();
    for (char letter : sentence) {
        if (!isalpha(letter))
            newSentence += letter;
        else if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
            newSentence += m->translateSingleVowel(letter);
        else
            newSentence += m->translateSingleConsonant(letter);
    }
    return newSentence;
}


