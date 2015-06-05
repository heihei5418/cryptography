#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AES.h"
#include "operation.h"
#include "GCM.h"

int test_bit(unsigned char* v, int pos) {
    int a = pos / 8;
    int b = pos % 8;
    return (v[a] & (1 << (7 - b))) != 0;
}

unsigned char* galois_mult(unsigned char* X, unsigned char* Y) {
    unsigned char Z[129][16];
    unsigned char V[129][16];
    unsigned char R[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87};
    int i, j, hi_bit;
    memset(Z[0], 0, 16);
    memcpy(V[0], Y, 16);
    for(i = 0; i < 128; i ++) {
        if(test_bit(X, 127 - i)) {
            for(j = 0; j < 16; j++)
                Z[i + 1][j] = Z[i][j] ^ V[i][j];
        } else
            memcpy(Z[i + 1], Z[i], 16);
        hi_bit = 0;
        for(j = 15; j >= 0; j --) {
            if(hi_bit != 0)
                V[i + 1][j] = (V[i][j] << 1) | 0x01;
            else
                V[i + 1][j] = V[i][j] << 1;
            hi_bit = (V[i][j] & 0x80) != 0;
        }
        if(hi_bit)
            for(j = 0; j < 16; j ++)
                V[i + 1][j] ^= R[j];
    }
    memcpy(X, Z[128], 16);
    return X;
}

unsigned char* GHASH(unsigned char* hash, unsigned char* H, unsigned char* A, unsigned char* C, unsigned long long lenA, unsigned long long lenC) {
    int i, j;
    unsigned char l[16];
    longlong_to_char(l, lenA);
    longlong_to_char(l + 8, lenC);
    for(j = 0; j < 16; j ++)
        hash[j] = 0;
    for(i = 1; i <= lenA / 128; i ++) {
        for(j = 0; j < 16; j ++)
            hash[i * 16 + j] = hash[(i - 1) * 16 + j] ^ A[(i - 1) * 16 + j];
        galois_mult(hash + i * 16, H);
    }
    for(i = lenA / 128 + 1; i <= (lenA + lenC) / 128; i ++) {
        for(j = 0; j < 16; j ++)
            hash[i * 16 + j] = hash[(i - 1) * 16 + j] ^ C[(i - lenA - 1) * 16 + j];
        galois_mult(hash + i * 16, H);
    }/*
    memcpy(hash + (lenA + lenC + 1) * 16, l, 16);
    galois_mult(hash + (lenA + lenC + 1) * 16, H);*/
    return hash;
}

int GCM(unsigned char* text, unsigned char* key, unsigned char* result, unsigned char* t, ENCRYPT_FUNC encrypt_func, KEY_FUNC key_func, int block_size) {
    int i, j, l = strlen(text), n;
    unsigned char* p_text = calloc(l + 16, sizeof(unsigned char)), *hash = calloc(l + 16 + 16 + 32, sizeof(unsigned char)), *tmp = calloc(block_size, sizeof(unsigned char)), *zero = calloc(block_size, sizeof(unsigned char));
    unsigned char subkey[768], H[16];
    strcpy(p_text, text);
    n = l / block_size + !!(l % block_size);
    key_func(subkey, key);
    for(i = 0; i < n; i ++) {
        unsigned char* block = p_text + i * block_size;
        int cnt = i + 1;
        for(j = block_size - 1; j >= 0; j --) {
            tmp[j] = cnt % 256;
            cnt /= 256;
        }
        encrypt_func(tmp, subkey, tmp);
        for(j = 0; j < block_size; j ++)
            block[j] ^= tmp[j];
    }
    memcpy(result, p_text, n * block_size);
    encrypt_func(zero, subkey, H);
    GHASH(hash, H, zero, result, 128, n * block_size * 8);
    for(i = 0; i < block_size; i ++)
        t[i] = hash[i] ^ (result + block_size)[i];
    free(p_text);
    free(tmp);
    free(zero);
    free(hash);
    return 1;
}