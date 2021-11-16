#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <map>

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
  public:
    /**
     * \brief Create a new PlayfairCipher, with the given string as the key
     *
     * \param key the string to be used as the key in the cipher
     */
    explicit PlayfairCipher(const std::string& key);

    /**
     * \brief Set the cipher key to a specified string
     *
     * \param key the string to be used as the new key in the cipher
     */
    void setKey(const std::string& key);

    /**
     * \brief Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(std::string& inputText,
                            const CipherMode cipherMode) const;

  private:
    
    const std::string alphabet_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        ///< The alphabet - used to determine create the usable cipher key from the input string

    // Define labels for the types used in the letter <-> coord maps
    using PlayfairCoords = std::pair< size_t, size_t >; ///< Used for storing pairs of coordinates (row, column)
    using Letter2Coords = std::map< char, PlayfairCoords >; ///< Used for mapping letters onto corresponding coordinates
    using Coords2Letter = std::map< PlayfairCoords, char >; ///< Used for mapping coordinates onto corresponding letters

    // Create an instance of each map
    
    Letter2Coords lookUpCoordinates_; ///< Map the look up coordinates of a given letter

    Coords2Letter lookUpLetter_; ///< Map the look up letter at given coordinates

    std::string key_{""}; ///< The cipher key
};

#endif