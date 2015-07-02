#ifndef AES_H

extern int AES_128(unsigned char* text, unsigned char* subkey, unsigned char* result);
extern int AES_192(unsigned char* text, unsigned char* subkey, unsigned char* result);
extern int AES_256(unsigned char* text, unsigned char* subkey, unsigned char* result);
extern int AES_128_key_expansion(unsigned char* subkey, unsigned char* key);
extern int AES_192_key_expansion(unsigned char* subkey, unsigned char* key);
extern int AES_256_key_expansion(unsigned char* subkey, unsigned char* key);

#endif