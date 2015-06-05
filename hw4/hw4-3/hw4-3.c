#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AES.h"
#include "GCM.h"

int main() {
	unsigned char input[200000], result[200000], t[32], key[] = "abcdefghijklmnop";
	FILE* fp = fopen("input4-3.txt", "r");
	FILE* fq = fopen("output4-3.txt", "w");
	while(fgets(input, 200000, fp) != NULL) {
        int i;
        int l = strlen(input);
        input[l - 1] = 0;
        fprintf(fq, "Text: %s\n", input);
        
        GCM(input, key, result, t, AES_128, AES_128_key_expansion, 16);
        fprintf(fq, "AES-128-GCM: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\nAuth: ");
        for(i = 0; i < 16; i ++)
            fprintf(fq, "%02x", t[i]);
        fprintf(fq, "\n");
        
        GCM(input, key, result, t, AES_192, AES_192_key_expansion, 16);
        fprintf(fq, "AES-192-GCM: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\nAuth: ");
        for(i = 0; i < 16; i ++)
            fprintf(fq, "%02x", t[i]);
        fprintf(fq, "\n");
        
        GCM(input, key, result, t, AES_256, AES_256_key_expansion, 16);
        fprintf(fq, "AES-256-GCM: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\nAuth: ");
        for(i = 0; i < 16; i ++)
            fprintf(fq, "%02x", t[i]);
        fprintf(fq, "\n");
	}
    fclose(fp);
    fclose(fq);
	return 0;
}