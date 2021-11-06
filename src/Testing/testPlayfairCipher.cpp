//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../MPAGSCipher/PlayfairCipher.hpp"

TEST_CASE("Playfair Cipher with odd length Input string", "[playfair]") {
        PlayfairCipher pc{"Monarchy"};
    SECTION("Encryption") {
        std::string testInput = "INSTRUMENTS";
        REQUIRE(pc.applyCipher(testInput, CipherMode::Encrypt) == "GATLMZCLRQTX");
    }
    SECTION("Decryption") {
        std::string testInput = "GATLMZCLRQTX";
        REQUIRE(pc.applyCipher(testInput, CipherMode::Decrypt) == "INSTRUMENTSZ");
    }
}

TEST_CASE("Playfair Cipher with even length Input string", "[playfair]") {
        PlayfairCipher pc{"Monarchy"};
    SECTION("Encryption") {
        std::string testInput = "INSTRUMENT";
        REQUIRE(pc.applyCipher(testInput, CipherMode::Encrypt) == "GATLMZCLRQ");
    }
    SECTION("Decryption") {
        std::string testInput = "GATLMZCLRQ";
        REQUIRE(pc.applyCipher(testInput, CipherMode::Decrypt) == "INSTRUMENT");
    }
}

TEST_CASE("Playfair Cipher with repeated letters in Input string", "[playfair]") {
        PlayfairCipher pc{"playfair example"};
    SECTION("Encryption") {
        std::string testInput = "HIDETHEGOLDINTHETREESTUMP";
        REQUIRE(pc.applyCipher(testInput, CipherMode::Encrypt) == "BMODZBXDNABEKUDMUIXMMOUVIF");
    }
    SECTION("Decryption") {
        std::string testInput = "BMODZBXDNABEKUDMUIXMMOUVIF";
        REQUIRE(pc.applyCipher(testInput, CipherMode::Decrypt) == "HIDETHEGOLDINTHETREXESTUMP");
    }
}
