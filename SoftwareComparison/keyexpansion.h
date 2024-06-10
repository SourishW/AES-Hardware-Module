#ifndef KEYEXPANSION_H
#define KEYEXPANSION_H

#include <stdint.h>
#include <stdbool.h>

// Function to generate round keys for AES encryption
// expanded key must be 15 * 4 * 4 bytes long or 240 bytes long
// returns the number of bytes written to expandedkey
int generateRoundKeys(uint8_t* key, uint8_t* expandedkey, int keyBytes);

#endif // KEYEXPANSION_H