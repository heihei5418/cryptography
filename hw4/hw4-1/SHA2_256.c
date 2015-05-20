#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA2_256.h"
#include "operation.h"

int SHA2_256(unsigned char* text, unsigned* result) {
    unsigned h0 = 0x6a09e667;
    unsigned h1 = 0xbb67ae85;
    unsigned h2 = 0x3c6ef372;
    unsigned h3 = 0xa54ff53a;
    unsigned h4 = 0x510e527f;
    unsigned h5 = 0x9b05688c;
    unsigned h6 = 0x1f83d9ab;
    unsigned h7 = 0x5be0cd19;
    unsigned k[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    int i, j;
	unsigned l = strlen(text);
	unsigned long long l_in_bits = l * 8;
	unsigned char* p_text = calloc(l + 65, sizeof(unsigned char));
	unsigned chunk[64];
	strcpy(p_text, text);
	p_text[l] = 0x80;
	l = (l + 9) / 64 * 64 + !!((l + 9) % 64) * 64;
    longlong_to_char(p_text + l - 8, l_in_bits);
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
        for(j = 16; j < 64; j ++) {
            unsigned s0 = rightrotate(chunk[j - 15], 7) ^ rightrotate(chunk[j - 15], 18) ^ (chunk[j - 15] >> 3);
            unsigned s1 = rightrotate(chunk[j - 2], 17) ^ rightrotate(chunk[j - 2], 19) ^ (chunk[j - 2] >> 10);
            chunk[j] = chunk[j - 16] + s0 + chunk[j - 7] + s1;
        }
        for(j = 0; j < 64; j ++) {
            unsigned s1 =  rightrotate(e, 6) ^ rightrotate(e, 11) ^ rightrotate(e, 25);
            unsigned ch = (e & f) ^ (~e & g);
            unsigned temp1 = h + s1 + ch + k[j] + chunk[j];
            unsigned s0 = rightrotate(a, 2) ^ rightrotate(a, 13) ^ rightrotate(a, 22);
            unsigned maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned temp2 = s0 + maj;
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
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