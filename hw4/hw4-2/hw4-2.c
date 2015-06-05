#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DES.h"
#include "AES.h"
#include "SM4.h"
#include "mode.h"

int main() {
	unsigned char input[200000], result[200000], key[] = "abcdefghijklmnop";
	FILE* fp = fopen("input4-2.txt", "r");
	FILE* fq = fopen("output4-2.txt", "w");
	while(fgets(input, 200000, fp) != NULL) {
        int i;
        int l = strlen(input);
        input[l - 1] = 0;
        fprintf(fq, "Text: %s\n", input);
        
        CBC(input, key, result, DES, DES_key_expansion, 8);
        fprintf(fq, "DES-CBC: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CBC(input, key, result, AES_128, AES_128_key_expansion, 16);
        fprintf(fq, "AES-128-CBC: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CBC(input, key, result, AES_192, AES_192_key_expansion, 16);
        fprintf(fq, "AES-192-CBC: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CBC(input, key, result, AES_256, AES_256_key_expansion, 16);
        fprintf(fq, "AES-256-CBC: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CBC(input, key, result, SM4, SM4_key_expansion, 16);
        fprintf(fq, "SM4-CBC: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        OFB(input, key, result, DES, DES_key_expansion, 8);
        fprintf(fq, "DES-OFB: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        OFB(input, key, result, AES_128, AES_128_key_expansion, 16);
        fprintf(fq, "AES-128-OFB: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        OFB(input, key, result, AES_192, AES_192_key_expansion, 16);
        fprintf(fq, "AES-192-OFB: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        OFB(input, key, result, AES_256, AES_256_key_expansion, 16);
        fprintf(fq, "AES-256-OFB: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        OFB(input, key, result, SM4, SM4_key_expansion, 16);
        fprintf(fq, "SM4-OFB: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CTR(input, key, result, DES, DES_key_expansion, 8);
        fprintf(fq, "DES-CTR: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CTR(input, key, result, AES_128, AES_128_key_expansion, 16);
        fprintf(fq, "AES-128-CTR: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CTR(input, key, result, AES_192, AES_192_key_expansion, 16);
        fprintf(fq, "AES-192-CTR: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CTR(input, key, result, AES_256, AES_256_key_expansion, 16);
        fprintf(fq, "AES-256-CTR: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
        
        CTR(input, key, result, SM4, SM4_key_expansion, 16);
        fprintf(fq, "SM4-CTR: ");
        for(i = 0; i < l; i ++)
            fprintf(fq, "%02x", result[i]);
        fprintf(fq, "\n");
	}
    fclose(fp);
    fclose(fq);
	return 0;
}