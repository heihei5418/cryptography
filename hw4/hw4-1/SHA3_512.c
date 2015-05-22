#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA3_512.h"
#include "operation.h"

int SHA3_512(unsigned char* text, unsigned long long* result) {
	unsigned long long offset[5][5] = { { 0, 36,  3, 41, 18},
                                        { 1, 44, 10, 45,  2},
                                        {62,  6, 43, 15, 61},
                                        {28, 55, 25, 21, 56},
                                        {27, 20, 39,  8, 14}};
    unsigned long long RC[24] = { 0x0000000000000001, 0x0000000000008082,
                                  0x800000000000808A, 0x8000000080008000,
                                  0x000000000000808B, 0x0000000080000001,
                                  0x8000000080008081, 0x8000000000008009,
                                  0x000000000000008A, 0x0000000000000088,
                                  0x0000000080008009, 0x000000008000000A,
                                  0x000000008000808B, 0x800000000000008B,
                                  0x8000000000008089, 0x8000000000008003,
                                  0x8000000000008002, 0x8000000000000080,
                                  0x000000000000800A, 0x800000008000000A,
                                  0x8000000080008081, 0x8000000000008080,
                                  0x0000000080000001, 0x8000000080008008};
    unsigned long long state[5][5];
    int i, l = strlen(text), x, y, k;
    unsigned char* p_text = calloc(l + 72, sizeof(unsigned char));
    strcpy(p_text, text);
	if(!(l % 72)) {
		p_text[l] += 0x1;
        l += 72 - (l % 72);
        p_text[l - 1] += 0x80;
	}
    memset(state, 0, sizeof(state));
	for(i = 0; i < l; i += 72) {
		unsigned char* block = p_text + i;
        unsigned long long C[5], D[5], tmp[5][5];
        int r;
		for(y = 0; y < 5; y ++)
			for(x = 0; x < 5; x ++)
				if(x + 5 * y < 9)
					state[x][y] ^= *(unsigned long long*)(block + (x + 5 * y) * 8);
        for(r = 0; r < 24; r ++) {
            for(x = 0; x < 5; x ++)
                C[x] = state[x][0] ^ state[x][1] ^ state[x][2] ^ state[x][3] ^ state[x][4];
            for(x = 0; x < 5; x ++)
                D[x] = C[(x - 1 + 5) % 5] ^ rightrotate_longlong(C[(x + 1) % 5], 1);
            for(x = 0; x < 5; x ++)
                for(y = 0; y < 5; y ++)
                    state[x][y] ^= D[x];
            /** rho and pi
             * the same as
             * for(x = 0; x < 5; x ++)
             *     for(x = 0; x < 5; x ++)
             *         tmp[x][y] = rightrotate_longlong(state[(x + 3 * y) % 5][x], offset[(x + 3 * y) % 5][x]);
             */
            for(x = 0; x < 5; x ++)
                for(y = 0; y < 5; y ++)
                    tmp[y][(2 * x + 3 * y) % 5] = rightrotate_longlong(state[x][y], offset[x][y]);
            for(x = 0; x < 5; x ++)
                for(y = 0; y < 5; y ++)
                    state[x][y] = tmp[x][y] ^ (~tmp[(x + 1) % 5][y] & tmp[(x + 2) % 5][y]);
            state[0][0] ^= RC[r];
        }
	}
	for(y = 0, k = 0; y < 5; y ++)
		for(x = 0; x < 5; x ++)
			if (x + 5 * y < 9 && k < 8) {
				result[k] = state[x][y];
				k++;
			}
	return 1;
}