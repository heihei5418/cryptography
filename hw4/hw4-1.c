#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SHA1.h"
#include "SHA2.h"
#include "SHA3.h"

int main() {
	unsigned char input[200000];
    unsigned resultSHA1[5], resultSHA2[8], resultSHA3[8], resultSM3[8];
	FILE* fp = fopen("input4-1.txt", "r");
	FILE* fq = fopen("output4-1.txt", "w");
	while(fgets(input, 200000, fp) != NULL) {
        int i;
        int l = strlen(input);
        input[l - 1] = 0;
        SHA1(input, resultSHA1);
        SHA2(input, resultSHA2);
        SHA3(input, resultSHA3);
        SM3(input, resultSM3);
        fprintf(fq, "Text: %s\n", input);
        fprintf(fq, "SHA1: ");
        for(i = 0; i < 5; i ++)
            fprintf(fq, "%08x", resultSHA1[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA2: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSHA2[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA3: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSHA3[i]);
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