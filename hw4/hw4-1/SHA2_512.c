#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA2_512.h"
#include "operation.h"

int SHA2_512(unsigned char* text, unsigned long long* result) {
    unsigned long long h0 = 0x6a09e667f3bcc908;
    unsigned long long h1 = 0xbb67ae8584caa73b;
    unsigned long long h2 = 0x3c6ef372fe94f82b;
    unsigned long long h3 = 0xa54ff53a5f1d36f1;
    unsigned long long h4 = 0x510e527fade682d1;
    unsigned long long h5 = 0x9b05688c2b3e6c1f;
    unsigned long long h6 = 0x1f83d9abfb41bd6b;
    unsigned long long h7 = 0x5be0cd19137e2179;
    unsigned long long k[] = {0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
                              0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
                              0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
                              0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
                              0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
                              0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
                              0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
                              0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
                              0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
                              0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
                              0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
                              0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
                              0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
                              0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
                              0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
                              0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};
    int i, j;
	unsigned long long l = strlen(text);
	unsigned long long l_in_bits = l * 8;
	unsigned char* p_text = calloc(l + 65, sizeof(unsigned char));
	unsigned chunk[64];
	strcpy(p_text, text);
	p_text[l] = 0x80;
	l = (l + 9) / 64 * 64 + !!((l + 9) % 64) * 64;
    longlong_to_char(p_text + l - 8, l_in_bits);
	for(i = 0; i < l; i += 64) {
		unsigned long long a = h0;
		unsigned long long b = h1;
		unsigned long long c = h2;
		unsigned long long d = h3;
		unsigned long long e = h4;
		unsigned long long f = h5;
		unsigned long long g = h6;
		unsigned long long h = h7;
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