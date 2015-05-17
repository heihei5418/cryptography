#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SM3.h"
#include "operation.h"

unsigned P0(unsigned x) {
    return x ^ leftrotate(x, 9) ^ leftrotate(x, 17);
}

unsigned P1(unsigned x) {
    return x ^ leftrotate(x, 15) ^ leftrotate(x, 23);
}

int SM3(unsigned char* text, unsigned* result) {
    unsigned h0 = 0x7380166f;
    unsigned h1 = 0x4914b2b9;
    unsigned h2 = 0x172442d7;
    unsigned h3 = 0xda8a0600;
    unsigned h4 = 0xa96f30bc;
    unsigned h5 = 0x163138aa;
    unsigned h6 = 0xe38dee4d;
    unsigned h7 = 0xb0fb0e4e;
    unsigned t[] = {0x79cc4519, 0x7a879d8a};
    int i, j;
	unsigned l = strlen(text);
	unsigned long long l_in_bits = l * 8;
	unsigned char* p_text = calloc(l + 65, sizeof(unsigned char));
	unsigned chunk[132];
	strcpy(p_text, text);
	p_text[l] = 0x80;
	l = (l + 9) / 64 * 64 + !!((l + 9) % 64) * 64;
    longlong_to_char(p_text + l - 8, l_in_bits);
    /*for(i = 0; i < l / 4; i ++) {
        for(j = 0; j < 4; j ++)
            printf("%02x", p_text[i * 4 + j]);
        printf(" ");
    }
    printf("\n");*/
	for(i = 0; i < l; i += 64) {
		unsigned a = h0;
		unsigned b = h1;
		unsigned c = h2;
		unsigned d = h3;
		unsigned e = h4;
		unsigned f = h5;
		unsigned g = h6;
		unsigned h = h7;
        for(j = 0; j < 16; j ++)
            chunk[j] = char_to_unsigned(p_text + i + j * 4);
        for(j = 16; j < 68; j ++)
            chunk[j] = P1(chunk[j - 16] ^ chunk[j - 9] ^ leftrotate(chunk[j - 3], 15)) ^ leftrotate(chunk[j - 13], 7) ^ chunk[j - 6];
        for(j = 0; j < 64; j ++)
            chunk[j + 68] = chunk[j] ^ chunk[j + 4];
        /*for(j = 0; j < 132; j ++)
            printf("%08x ", chunk[j]);
        printf("\n");*/
        // printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", a, b, c, d, e, f, g, h);
        for(j = 0; j < 64; j ++) {
            unsigned ss1 = leftrotate(leftrotate(a, 12) + e + leftrotate(t[j >= 16], j), 7);
            unsigned ss2 = ss1 ^ leftrotate(a, 12);
            unsigned tt1 = ((j < 16) ? (a ^ b ^ c) : ((a & b) | (a & c) | (b & c))) + d + ss2 + chunk[j + 68];
            unsigned tt2 = ((j < 16) ? (e ^ f ^ g) : ((e & f) | (~e & g))) + h + ss1 + chunk[j];
            h = g;
            g = leftrotate(f, 19);
            f = e;
            e = P0(tt2);
            d = c;
            c = leftrotate(b, 9);
            b = a;
            a = tt1;
            // printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", a, b, c, d, e, f, g, h);
        }
        h0 ^= a;
        h1 ^= b;
        h2 ^= c;
        h3 ^= d;
        h4 ^= e;
        h5 ^= f;
        h6 ^= g;
        h7 ^= h;
    }
    free(p_text);
    result[0] = h0;
    result[1] = h1;
    result[2] = h2;
    result[3] = h3;
    result[4] = h4;
    result[5] = h5;
    result[6] = h6;
    result[7] = h7;
    return 1;
}