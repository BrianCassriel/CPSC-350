//
// Created by Brian Cassriel on 8/31/23.
//

#include <fstream>
#include "FileProcessor.h"
#include "Translator.h"

FileProcessor::FileProcessor() {}
FileProcessor::~FileProcessor() {}

/**
 * Creates a formatted HTML file out of an input .txt file.
 * @param inputFile - The path to a .txt file.
 * @param outputFile - The path where a .html file will be created.
 */
void FileProcessor::processFile(std::string inputFile, std::string outputFile) {
    std::string fileContents = FileProcessor::readTXTFile(inputFile);
    std::string translatedContents = FileProcessor::translateTXTFile(inputFile);
    std::string htmlContents = FileProcessor::createHTMLContents(outputFile, fileContents, translatedContents);

    FileProcessor::writeFile(htmlContents, outputFile);
}

/**
 * Reads in the .txt file. Adds HTML line breaks instead of \n breaks for later formatting.
 * @param filePath - The path to a .txt file.
 * @return - A string containing all of the .txt file's contents, broken up with <br/> instead of newlines.
 */
std::string FileProcessor::readTXTFile(std::string filePath) {
    std::ifstream file;
    file.open(filePath, std::ios::in);
    std::string contents = std::string();

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            contents += line + "<br/>";
        }
    }
    file.close();
    return contents;
}

/**
 * Reads in and translates an english .txt file into a string of Rövarspråket, broken up with <br/> instead of newlines.
 * @param filePath - The path to a .txt file.
 * @return - A string containing all of the .txt file's contents in Rövarspråket, broken up with <br/>.
 */
std::string FileProcessor::translateTXTFile(std::string filePath) {
    Translator translator;
    std::ifstream file;
    file.open(filePath, std::ios::in);
    std::string contents = std::string();

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            contents += translator.translateEnglishSentence(line) + "<br/>";
        }
    }
    file.close();
    return contents;
}

/**
 * Formats the HTML file to prepare it for writing & viewing.
 * @param filePath - The path to the location where the .html file will be created.
 * @param englishContents - A string containing all of the .txt file's contents in English, broken up with <br/>.
 * @param translatedContents - A string containing all of the .txt file's contents in Rövarspråket, broken up with <br/>.
 * @return - A string containing the complete HTML file, ready for writing.
 */
std::string FileProcessor::createHTMLContents(std::string filePath, std::string englishContents, std::string translatedContents) {
    std::string htmlContents = std::string();
    htmlContents += "<!DOCTYPE html>\n"
                    "<html>\n"
                    "<p>\n";
    htmlContents += "<b>" + englishContents + "</b><br/>"; // Bold english contents
    htmlContents += "<i>" + translatedContents + "</i>"; // Italic translated contents
    htmlContents += "</body>\n"
                    "</html>\n"
                    "</p>";
    return htmlContents;
}

/**
 * Writes a string to a file.
 * @param contents - The string to be written.
 * @param filePath - The path to the location where the file will be created.
 */
void FileProcessor::writeFile(std::string contents, std::string filePath) {
    std::ofstream file;
    file.open(filePath, std::ios::out);
    file << contents;
    file.close();
}
