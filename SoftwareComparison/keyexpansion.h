#ifndef KEYEXPANSION_H
#define KEYEXPANSION_H

#include <stdint.h>
#include <stdbool.h>

void generateRoundKeys(uint8_t* key, uint8_t* expandedkey, int keyBytes);

#endif // KEYEXPANSION_H