#include "cmac.h"
#include "aes.h"
#include "Utils.h"
// Calculate the CMAC
uint8* aes_cmac(uint8* in, unsigned int length, uint8* out, uint8* key)
{
    uint8* K1;
    uint8* K2;
    K1 = (uint8*)malloc(16);
    K2 = (uint8*)malloc(16);
    GenerateSubkey(key, K1, K2);

    int n = (length / const_Bsize);
    bool flag = false;
    if (length % const_Bsize != 0) {
        n++;
    }

    if (n == 0) {
        n = 1;
    } else if (length % const_Bsize == 0) {
        flag = true;
    }

    uint8 M[n][const_Bsize];
    memset(M[0], 0, n * const_Bsize);
    memcpy(M[0], in, length);
    if (!flag) {
        memset(M[0] + length, 0x80, 1);
    }
    if (flag) {
        block_xor(M[n - 1], M[n - 1], K1);
    } else {
        block_xor(M[n - 1], M[n - 1], K2);
    }

    uint8 X[] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    uint8 Y[const_Bsize];

    for (int i = 0; i < n - 1; i++) {
        block_xor(Y, M[i], X);
        aes_128_encrypt(Y, X, key);
    }
    block_xor(Y, M[n - 1], X);
    aes_128_encrypt(Y, out, key);
    free(K1);
    free(K2);
    return out;
}

// Verify the CMAC
bool verify_mac(uint8* in, unsigned int length, uint8* out, uint8* key)
{
    bool flag = true;
    uint8 result[16];
    aes_cmac(in, length, (uint8*)result, key);
    for (int i = 0; i < const_Bsize; i++) {
        if (!(result[i] ^ out[i])) {
            flag = false;
            break;
        }
    }
    return flag;
}

// Generate the Sub keys
void GenerateSubkey(uint8* key, uint8* K1, uint8* K2)
{
    uint8 const_Zero[] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    uint8 const_Rb[] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x87
    };

    uint8 L[16];
    aes_128_encrypt(const_Zero, L, key);
    block_leftshift(K1, L);
    if (L[0] & 0x80) {
        block_xor(K1, K1, const_Rb);
    }

    block_leftshift(K2, K1);
    if (K1[0] & 0x80) {
        block_xor(K2, K2, const_Rb);
    }
}
