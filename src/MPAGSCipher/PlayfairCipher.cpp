#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"\

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

PlayfairCipher::PlayfairCipher(const std::string& key) : key_{""}
{
    setKey(key);
}

void PlayfairCipher::setKey(const std::string& key)
{
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += alphabet_;

    // Remove non-alpha characters
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),
                              [](char c) {return !std::isalpha(c); }),
               std::end(key_));

    // Make sure the key is upper case
    std::transform(std::begin(key_), std::end(key_), std::begin(key_), ::toupper);

    // Change J -> I
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                   [](char c) {if (c == 'J'){return 'I';} else {return c;}});
    
    // Remove duplicated letters
    std::string encounteredLetters{""};
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),
                              [&encounteredLetters](char c){bool encountered{encounteredLetters.find(c) != encounteredLetters.npos};
                                                            if (!encountered) {
                                                                encounteredLetters += c;
                                                            }
                                                            return encountered;}),
               std::end(key_));
    std::cout << "Key = " << key_ << std::endl;
    // Store the coords of each letter

    // Store the playfair cihper key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{
    // Change J → I

    // If repeated chars in a digraph add an X or Q if XX

    // if the size of input is odd, add a trailing Z

    // Loop over the input in Digraphs

    // - Find the coords in the grid for each digraph
    // - Apply the rules to these coords to get 'new' coords
    // - Find the letter associated with the new coords
    // return the text
    std::cout
        << "PlayfairCipher.applyCipher("
        << inputText
        << ", "
        << (cipherMode == CipherMode::Encrypt)
        << ")"
        << std::endl;
    return inputText;
}
