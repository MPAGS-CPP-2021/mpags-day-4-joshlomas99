#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <utility>
#include <cmath>

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
    using coords = std::pair< int, int >;
    using Letter2Coords = std::map< char, coords >;
    using Coords2Letter = std::map< coords, char >;

    // Create an instance of each map
    Letter2Coords coordinates;
    Coords2Letter letter;

    // Loop over each letter, calculate the row and column numbers and then
    // store both the letter and a std::pair of the coordinates in each map.
    int count = 0;
    for (auto iter{std::begin(key_)}; iter != std::end(key_); ++iter){
        coords c{floor(count/5), count%5};
        std::pair<char, coords> p_l2c{*iter, c};
        std::pair<coords, char> p_c2l{c, *iter};
        coordinates.insert(p_l2c);
        letter.insert(p_c2l);
        count++;
    }

    // Checking everything is working
    std::cout << "Original key: " << key << std::endl;
    std::cout << "New key: " << key_ << std::endl;

    std::cout << "Letter2Coords coordinates:" << std::endl;
    for ( auto p : coordinates )
    {
        std::cout << p.first << " : [" << p.second.first << ", " << p.second.second << "]" << std::endl;
    }

    std::cout << "Coords2Letter letter:" << std::endl;
    for ( auto p : letter )
    {
        std::cout << "[" << p.first.first << ", " << p.first.second << "] : " << p.second << std::endl;
    }

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
