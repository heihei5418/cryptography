#ifndef GCM_H

typedef int (*ENCRYPT_FUNC)(unsigned char*, unsigned char*, unsigned char*);
typedef int (*KEY_FUNC)(unsigned char*, unsigned char*);

extern int GCM(unsigned char* text, unsigned char* key, unsigned char* result, unsigned char* t, ENCRYPT_FUNC encrypt_func, KEY_FUNC key_func, int block_size);

#endif