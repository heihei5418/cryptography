#ifndef DES_H

extern int DES(unsigned char* text, unsigned char* subkey, unsigned char* result);
extern int DES_key_expansion(unsigned char* subkey, unsigned char* key);

#endif