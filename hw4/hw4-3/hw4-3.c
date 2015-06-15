#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AES.h"
#include "GCM.h"

int main() {
	unsigned char input[200000], result[200000], key[] = "abcdefghijklmnop";
	FILE* fp = fopen("input4-3.txt", "r");
	FILE* fq = fopen("output4-3.txt", "w");
	while(fgets(input, 200000, fp) != NULL) {
        int i;
        int l = strlen(input);
        input[l - 1] = 0;
        fprintf(fq, "Text: %s\n", input);
        
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
	}
    fclose(fp);
    fclose(fq);
	return 0;
}