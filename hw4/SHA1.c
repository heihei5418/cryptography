#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA1.h"
#include "operation.h"

int SHA1(unsigned char* text, unsigned* result) {
	unsigned h0 = 0X67452301;
    unsigned h1 = 0XEFCDAB89;
    unsigned h2 = 0X98BADCFE;
    unsigned h3 = 0X10325476;
    unsigned h4 = 0XC3D2E1F0;
    int i, j;
	unsigned l = strlen(text);
	unsigned long long l_in_bits = l * 8;
	unsigned char* p_text = calloc(l + 65, sizeof(unsigned char));
	unsigned chunk[80];
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
        unsigned k;
        for(j = 0; j < 16; j ++)
            chunk[j] = char_to_unsigned(p_text + i + j * 4);
		for(j = 16; j < 80; j ++)
			chunk[j] = leftrotate(chunk[j - 3] ^ chunk[j - 8] ^ chunk[j - 14] ^ chunk[j - 16], 1);
        for(j = 0; j < 80; j ++) {
            unsigned f, temp;
            if(0 <= j && j <= 19) {
                f = (b & c) | (~b & d);
                k = 0X5A827999;
            } else if(20 <= j && j <= 39) {
                f = b ^ c ^ d;
                k = 0X6ED9EBA1;
            } else if(40 <= j && j <= 59) {
                f = (b & c) | (b & d) | (c & d); 
                k = 0X8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0XCA62C1D6;
            }
            temp = leftrotate(a, 5) + f + e + k + chunk[j];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }
    free(p_text);
    result[0] = h0;
    result[1] = h1;
    result[2] = h2;
    result[3] = h3;
    result[4] = h4;
    return 1;
}