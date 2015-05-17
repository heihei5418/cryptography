#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DES.h"
#include "AES.h"
#include "SM4.h"

int main() {
	unsigned char input[200000];
    unsigned resultDES[8], resultAES[8], resultSM4[8];
	FILE* fp = fopen("input4-2.txt", "r");
	FILE* fq = fopen("output4-2.txt", "w");
	while(fgets(input, 200000, fp) != NULL) {
        int i;
        int l = strlen(input);
        input[l - 1] = 0;
        DES(input, resultDES);
        AES(input, resultAES);
        SM4(input, resultSM4);
        fprintf(fq, "Text: %s\n", input);
        fprintf(fq, "DES: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultDES[i]);
        fprintf(fq, "\n");
        fprintf(fq, "AES: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultAES[i]);
        fprintf(fq, "\n");
        fprintf(fq, "SM4: ");
        for(i = 0; i < 8; i ++)
            fprintf(fq, "%08x", resultSM4[i]);
        fprintf(fq, "\n");
	}
    fclose(fp);
    fclose(fq);
	return 0;
}