#ifndef UTILS_H
#define UTILS_H

#include "common.h"

void print_bytes(uint8* buf, const size_t len);
void block_xor(uint8* dst, uint8* a, uint8* b);
void block_leftshift(uint8* dst, uint8* src);


#endif // UTILS_H
