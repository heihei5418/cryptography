#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AES.h"
#include "DES.h"
#include "SM4.h"
#include "operation.h"
#include "mode.h"

int CBC(unsigned char* text, unsigned char* key, unsigned char* result, ENCRYPT_FUNC encrypt_func, KEY_FUNC key_func, int block_size) {
    int i, j, l = strlen(text), n;
    unsigned char* p_text = calloc(l + 16, sizeof(unsigned char)), *tmp = calloc(block_size, sizeof(unsigned char));
    unsigned char subkey[768];
    strcpy(p_text, text);
    n = l / block_size + !!(l % block_size);
    key_func(subkey, key);
    for(i = 0; i < n; i ++) {
        unsigned char* block = p_text + i * block_size;
        for(j = 0; j < block_size; j ++)
            block[j] ^= tmp[j];
        encrypt_func(block, subkey, tmp);
        memcpy(result + i * block_size, tmp, block_size);
    }
    free(p_text);
    free(tmp);
    return 1;
}

int OFB(unsigned char* text, unsigned char* key, unsigned char* result, ENCRYPT_FUNC encrypt_func, KEY_FUNC key_func, int block_size) {
    int i, j, l = strlen(text), n;
    unsigned char* p_text = calloc(l + 16, sizeof(unsigned char)), *tmp = calloc(block_size, sizeof(unsigned char));
    unsigned char subkey[768];
    strcpy(p_text, text);
    n = l / block_size + !!(l % block_size);
    key_func(subkey, key);
    for(i = 0; i < n; i ++) {
        unsigned char* block = p_text + i * block_size;
        encrypt_func(tmp, subkey, tmp);
        for(j = 0; j < block_size; j ++)
            block[j] ^= tmp[j];
    }
    memcpy(result, p_text, n * block_size);
    free(p_text);
    free(tmp);
    return 1;
}

int CTR(unsigned char* text, unsigned char* key, unsigned char* result, ENCRYPT_FUNC encrypt_func, KEY_FUNC key_func, int block_size) {
    int i, j, l = strlen(text), n;
    unsigned char* p_text = calloc(l + 16, sizeof(unsigned char)), *tmp = calloc(block_size, sizeof(unsigned char));
    unsigned char subkey[768];
    strcpy(p_text, text);
    n = l / block_size + !!(l % block_size);
    key_func(subkey, key);
    for(i = 0; i < n; i ++) {
        unsigned char* block = p_text + i * block_size;
        int cnt = i;
        for(j = block_size - 1; j >= 0; j --) {
            tmp[j] = cnt % 256;
            cnt /= 256;
        }
        encrypt_func(tmp, subkey, tmp);
        for(j = 0; j < block_size; j ++)
            block[j] ^= tmp[j];
    }
    memcpy(result, p_text, n * block_size);
    free(p_text);
    free(tmp);
    return 1;
}