#ifndef MODE_H

typedef int (*FUNTYPE)(unsigned char*, unsigned char*);

extern int CBC(unsigned char* text, unsigned char* result, FUNTYPE encrypt_func);
extern int OFB(unsigned char* text, unsigned char* result, FUNTYPE encrypt_func);
extern int CTR(unsigned char* text, unsigned char* result, FUNTYPE encrypt_func);

#endif