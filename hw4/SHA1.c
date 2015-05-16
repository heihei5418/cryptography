#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned const h0 = 0X67452301;
unsigned const h1 = 0XEFCDAB89;
unsigned const h2 = 0X98BADCFE;
unsigned const h3 = 0X10325476;
unsigned const h4 = 0XC3D2E1F0;

int SHA1(char* text, char* result) {
	int i, j, k; // loop vars
	unsigned l = strlen(text);
	unsigned long long l_in_bits = l * 8;
	char* p_text = calloc(l + 65, sizeof(char));
	int chunk[81];
	strcpy(p_text, text);
	for(i = 0; i < l;i ++)
		p_text[i] += 0x80;
	// printf("If 512 divide l is %u.\n", !((l + 64) % 512));
	l = (l + 8) / 64 * 64 + !!((l + 8) % 64) * 64;
	printf("p_l = %u\n", l);
	strncpy(text + l - 64, (char*)l_in_bits, 8);
	for(i = 0; i < l; i += 8) {
		strncpy((char*)chunk, p_text + i, 64);
		for(j = 16; j < 80; j ++)
			w[i] = (w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]) << 1;
		int a = h0;
		int b = h1;
		int c = h2;
		int d = h3;
		int e = h4;
/*
    Main loop:[42]
    for i from 0 to 79
        if 0 ¡Ü i ¡Ü 19 then
            f = (b and c) or ((not b) and d)
            k = 0x5A827999
        else if 20 ¡Ü i ¡Ü 39
            f = b xor c xor d
            k = 0x6ED9EBA1
        else if 40 ¡Ü i ¡Ü 59
            f = (b and c) or (b and d) or (c and d) 
            k = 0x8F1BBCDC
        else if 60 ¡Ü i ¡Ü 79
            f = b xor c xor d
            k = 0xCA62C1D6

        temp = (a leftrotate 5) + f + e + k + w[i]
        e = d
        d = c
        c = b leftrotate 30
        b = a
        a = temp

    Add this chunk's hash to result so far:
    h0 = h0 + a
    h1 = h1 + b 
    h2 = h2 + c
    h3 = h3 + d
    h4 = h4 + e

Produce the final hash value (big-endian) as a 160 bit number:
hh = (h0 leftshift 128) or (h1 leftshift 96) or (h2 leftshift 64) or (h3 leftshift 32) or h4*/
}

int main() {
	char input[10000], resultSHA1[21];
	FILE* fp = fopen("input4-1.txt", "r");
	while(fscanf(fp, "%s", input) != EOF) {
		SHA1(input, resultSHA1);
	}
	return 0;
}