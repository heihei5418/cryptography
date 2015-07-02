#ifndef SM4_H

extern int SM4(unsigned char* text, unsigned char* subkey, unsigned char* result);
extern int SM4_key_expansion(unsigned char* subkey, unsigned char* key);

#endif