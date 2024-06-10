#include "keyexpansion.h"

// Internal function to perform the Rijndael key schedule
static void keySchedule(uint8_t* key, uint8_t* roundKey, int numWords) {
    // TODO: Implement the key schedule algorithm
    // ...
}

// Internal function to perform the Rijndael Rcon operation
static uint8_t rcon(uint8_t round) {
    static const uint8_t rconTable[] = {
        0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
    };
    return rconTable[round];
}

// Internal function to perform the Rijndael RotWord operation
static void rotWord(uint8_t* word) {
    // TODO: Implement the RotWord operation
    // ...
}

// Internal function to perform the Rijndael SubWord operation
static void subWord(uint8_t* word) {
    // TODO: Implement the SubWord operation
    // ...
}

// Function to generate round keys for AES encryption
void generateRoundKeys(uint8_t* key, uint8_t* roundKeys, int numRounds) {
    // TODO: Implement the key expansion algorithm
    // ...
}