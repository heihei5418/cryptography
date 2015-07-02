#ifndef OPERATION_H

extern unsigned leftrotate(unsigned x, int i);
extern unsigned rightrotate(unsigned x, int i);
extern unsigned long long leftrotate_longlong(unsigned long long x, int i);
extern unsigned long long rightrotate_longlong(unsigned long long x, int i);
extern unsigned char* longlong_to_char(unsigned char* str, unsigned long long x);
extern unsigned char* unsigned_to_char(unsigned char* str, unsigned x);
extern unsigned char_to_unsigned(unsigned char* str);
extern unsigned long long char_to_longlong(unsigned char* str);
extern unsigned char* byte_to_bit(unsigned char* bit, unsigned char* byte);
extern unsigned char* bit_to_byte(unsigned char* byte, unsigned char* bit);

#endif