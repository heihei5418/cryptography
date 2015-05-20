#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SHA1.h"
#include "SHA2_256.h"
#include "SHA2_512.h"
#include "SHA3_256.h"
#include "SHA3_512.h"
#include "SM3.h"

int main() {
	unsigned char input[200000];
    unsigned resultSHA1[5], resultSHA2_256[8], resultSHA3_256[8], resultSHA3_256[8], resultSM3[8];
    unsigned long long resultSHA2_512[8];
	FILE* fp = fopen("input4-1.txt", "r");
	FILE* fq = fopen("output4-1.txt", "w");
	while(fgets(input, 200000, fp) != NULL) {
        int i;
        int l = strlen(input);
        input[l - 1] = 0;
        SHA1(input, resultSHA1);
        SHA2_256(input, resultSHA2_256);
        SHA2_512(input, resultSHA2_512);
        SHA3_256(input, resultSHA3_256);
        SHA3_512(input, resultSHA3_512);
        SM3(input, resultSM3);
        fprintf(fq, "Text: %s\n", input);
        fprintf(fq, "SHA1: ");
        for(i = 0; i < 5; i ++)
            fprintf(fq, "%08x", resultSHA1[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA2-256: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSHA2_256[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA2-512: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%016x", resultSHA2_512[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA3-256: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSHA3_256[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA3-512: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSHA3_512[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SM3: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSM3[i]);
        fprintf(fq, "\n");
	}
    fclose(fp);
    fclose(fq);
	return 0;
}