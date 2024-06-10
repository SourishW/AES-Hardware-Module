#ifndef KEYEXPANSION_H
#define KEYEXPANSION_H

#include <cstdint>

void generateRoundKeys128(const uint8_t* key, uint8_t* roundKeys);
void generateRoundKeys192(const uint8_t* key, uint8_t* roundKeys);
void generateRoundKeys256(const uint8_t* key, uint8_t* roundKeys);

#endif // KEYEXPANSION_H