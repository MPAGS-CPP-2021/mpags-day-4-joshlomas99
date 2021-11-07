#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <utility>

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
                //    [](char c){if (c == 'J'){return 'I';} else {return c; }});
                   [](char c){return (c=='J' ? 'I' : c); });
    
    // Remove duplicated letters
    std::string encounteredLetters{""};
    auto detectDuplicates = [&](char c) {
        if (encounteredLetters.find(c) == std::string::npos) {
            encounteredLetters += c;
            return false;
        } else {
            return true;
        }
    };
    key_.erase(std::remove_if(std::begin(key_), std::end(key_), detectDuplicates),
               std::end(key_));


    // Store the coords of each letter and store the playfair cipher key map
    // Create a new label for each type – could also use 'typedef'
    // using PlayfairCoords = std::pair< size_t, size_t >;

    // Loop over each letter, calculate the row and column numbers and then
    // store both the letter and a std::pair of the coordinates in each map.
    int count = 0;
    for (auto iter{std::begin(key_)}; iter != std::end(key_); ++iter){
        PlayfairCoords c{count/5, count%5};
        std::pair<char, PlayfairCoords> p_l2c{*iter, c};
        std::pair<PlayfairCoords, char> p_c2l{c, *iter};
        lookUpCoordinates_.insert(p_l2c);
        lookUpLetter_.insert(p_c2l);
        count++;
    }

}

std::string PlayfairCipher::applyCipher(std::string& inputText, const CipherMode cipherMode) const
{
    std::string processedInputText{""};
    // Process inputText for encrytion
    if (cipherMode == CipherMode::Encrypt) {
        // Change J → I
        std::transform(std::begin(inputText), std::end(inputText), std::begin(inputText),
                        [](char c){return (c=='J' ? 'I' : c); });

        // If repeated chars in a digraph add an X or Q if XX
        for (size_t i{0}; i < inputText.length()-1; ++i) {
            processedInputText += inputText[i];
            if (inputText[i] == inputText[i+1]) {
                if (inputText[i] == 'X') {
                    processedInputText += 'Q';
                } else {
                    processedInputText += 'X';
                }
            }
        }
        processedInputText += *(std::end(inputText)-1);

        // if the size of input is odd, add a trailing Z
        if (processedInputText.length() % 2 != 0) {
            processedInputText += 'Z';
        }
    }
    // For decryption just use raw inputText
    else {
        processedInputText += inputText;
    }

    // Loop over the input in Digraphs, applying Playfair cipher
    std::string outputText{""};
        
    for (auto iterLetterIn{std::begin(processedInputText)}; iterLetterIn != std::end(processedInputText); iterLetterIn+=2){
        //// - Find the coords in the grid for each digraph
        auto iterPairIn_i = lookUpCoordinates_.find(*iterLetterIn);
        auto iterPairIn_iplus1 = lookUpCoordinates_.find(*(iterLetterIn+1));
        PlayfairCoords coordsIn_i{(*iterPairIn_i).second};
        PlayfairCoords coordsIn_iplus1{(*iterPairIn_iplus1).second};

        //// - Apply the rules to these coords to get 'new' coords
        PlayfairCoords coordsOut_i{(*iterPairIn_i).second};
        PlayfairCoords coordsOut_iplus1{(*iterPairIn_iplus1).second};
        // 1. If letters are on the same row: Encrypt: replace with letter to the right, wrap to left if needed
        //                                    Decrypt: replace with letter to the left, wrap to right if needed
        if (coordsIn_i.first == coordsIn_iplus1.first) {
            if (cipherMode == CipherMode::Encrypt) {
                coordsOut_i.second = (coordsIn_i.second + 1) % 5;
                coordsOut_iplus1.second = (coordsIn_iplus1.second + 1) % 5;
            }
            else {
                coordsOut_i.second = (coordsIn_i.second - 1 + 5) % 5;
                coordsOut_iplus1.second = (coordsIn_iplus1.second - 1 + 5) % 5;
            }
        }

        // 2. If in same column: Encrypt: replace with letters directly below, wrap to top if needed
        //                       Decrypt: replace with letters directly above, wrap to bottom if needed
        else if (coordsIn_i.second == coordsIn_iplus1.second) {
            if (cipherMode == CipherMode::Encrypt) {
                coordsOut_i.first = (coordsIn_i.first + 1) % 5;
                coordsOut_iplus1.first = (coordsIn_iplus1.first + 1) % 5;
            }
            else {
                coordsOut_i.first = (coordsIn_i.first - 1 + 5) % 5;
                coordsOut_iplus1.first = (coordsIn_iplus1.first - 1 + 5) % 5;
            }
        }

        // 3. If they form a rectangle, replace with ones from corner on the same row (same for Encrypt/Decrypt)
        else {
            coordsOut_i.second = (coordsIn_iplus1.second);
            coordsOut_iplus1.second = (coordsIn_i.second);
        }

        //// - Find the letter associated with the new coords
        auto iterPairOut_i = lookUpLetter_.find(coordsOut_i);
        auto iterPairOut_iplus1 = lookUpLetter_.find(coordsOut_iplus1);
        outputText += (*iterPairOut_i).second;
        outputText += (*iterPairOut_iplus1).second;

    }

    // return the text
    return outputText;
}
