#ifndef CMAC_H
#define CMAC_H
#include "common.h"
#include "Std_Types.h"
#define const_Bsize 16

uint8* aes_cmac(uint8* in, uint32 length, uint8 * out, uint8 * key);
bool verify_mac(uint8 * in, uint32 length, uint8* out, uint8 * key);

void GenerateSubkey(uint8* key, uint8* K1, uint8 * K2);

#endif // !CMAC_H
