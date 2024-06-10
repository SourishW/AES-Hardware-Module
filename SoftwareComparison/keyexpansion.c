#include "keyexpansion.h"

#include <stdbool.h>
#include <stdint.h>
#define ROTL8(x, shift) ((uint8_t)((x) << (shift)) | ((x) >> (8 - (shift))))

static sbox[256];
static invsbox[256];
static bool sbox_initialized = false;
static bool invsbox_initialized = false;

// Internal function to perform the Rijndael Rcon operation
// buffer rcon must be at least 4 bytes long
static void rcon_create(uint8_t round, uint8_t rcon[4]) {
    static const uint8_t rconTable[] = {0x01, 0x02, 0x04, 0x08, 0x10,
                                        0x20, 0x40, 0x80, 0x1b, 0x36};
    uint8_t MSB = rconTable[round - 1];
    rcon[0] = MSB;
    rcon[1] = 0x00;
    rcon[2] = 0x00;
    rcon[3] = 0x00;
}

// Internal function to perform the Rijndael RotWord operation
static void rotWord(uint8_t* word) {
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

// taken from wikipedia to initialize the sbox
void initialize_aes_sbox() {
    if (sbox_initialized) {
        return;
    }

    uint8_t p = 1, q = 1;

    /* loop invariant: p * q == 1 in the Galois field */
    do {
        /* multiply p by 3 */
        p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

        /* divide q by 3 (equals multiplication by 0xf6) */
        q ^= q << 1;
        q ^= q << 2;
        q ^= q << 4;
        q ^= q & 0x80 ? 0x09 : 0;

        /* compute the affine transformation */
        uint8_t xformed =
            q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

        sbox[p] = xformed ^ 0x63;
    } while (p != 1);

    /* 0 is a special case since it has no inverse */
    sbox[0] = 0x63;

    sbox_initialized = true;
}

// uses the sbox to initialize the invsbox
void initialize_aes_invsbox() {
    if (invsbox_initialized) {
        return;
    }

    if (!sbox_initialized) {
        initialize_aes_sbox();
    }

    for (int i = 0; i < 256; i++) {
        invsbox[sbox[i]] = i;
    }

    invsbox_initialized = true;
}

// Internal function to perform the Rijndael SubWord operation
static void subWord(uint8_t* word) {
    initialize_aes_sbox();
    for (int i = 0; i < 4; i++) {
        word[i] = sbox[word[i]];
    }
}

// Function to generate round keys for AES encryption
void generateRoundKeys(uint8_t* key, uint8_t* expandedkey, int keyBytes) {
    int N = keyBytes / 4; 
    int R = N + 7;
    for (int i = 0; i< 4*R; i++) {
        if (i < N) {
            for (int j = 0; j < 4; j++) {
                expandedkey[i*4 + j] = key[i*4 + j];
            }
        }
        else if (i >= N && i % N == 0) {
            uint8_t temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = expandedkey[(i-1)*4 + j];
            }
            rotWord(temp);
            subWord(temp);
            uint8_t rcon[4];
            rcon_create(i/N, rcon);
            for (int j = 0; j < 4; j++) {
                temp[j] = temp[j] ^ rcon[j];
            }
            for (int j = 0; j < 4; j++) {
                expandedkey[i*4 + j] = expandedkey[(i-N)*4 + j] ^ temp[j];
            }
        }
        else if (i >= N && N > 6 && i % N == 4) {
            uint8_t temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = expandedkey[(i-1)*4 + j];
            }
            subWord(temp);
            for (int j = 0; j < 4; j++) {
                expandedkey[i*4 + j] = expandedkey[(i-N)*4 + j] ^ temp[j];
            }
        }
        else {
            for (int j = 0; j < 4; j++) {
                expandedkey[i*4 + j] = expandedkey[(i-N)*4 + j] ^ expandedkey[(i-1)*4 + j];
            }
        }
        
    }


}