#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SHA1.h"
#include "SHA2.h"
#include "SHA3.h"

int main() {
	unsigned char input[10000];
    unsigned resultSHA1[5], resultSHA2[8];
	FILE* fp = fopen("input4-1.txt", "r");
	FILE* fq = fopen("output4-1.txt", "w");
	while(fscanf(fp, "%s", input) != EOF) {
        int i;
        SHA1(input, resultSHA1);
        SHA2(input, resultSHA2);
        fprintf(fq, "Text: %s\n", input);
        fprintf(fq, "SHA1: ");
        for(i = 0; i < 5; i ++)
            fprintf(fq, "%08x", resultSHA1[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SHA2: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSHA2[i]);
        fprintf(fq, "\n");
	}
    fclose(fp);
    fclose(fq);
	return 0;
}