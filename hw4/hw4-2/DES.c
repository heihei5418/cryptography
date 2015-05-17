#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DES.h"
#include "operation.h"

int DES_IP_Transform(unsigned char* data) {  
    int IP[64] = {      57, 49, 41, 33, 25, 17,  9,  1,
                        59, 51, 43, 35, 27, 19, 11,  3,
                        61, 53, 45, 37, 29, 21, 13,  5,
                        63, 55, 47, 39, 31, 23, 15,  7,
                        56, 48, 40, 32, 24, 16,  8,  0,
                        58, 50, 42, 34, 26, 18, 10,  2,
                        60, 52, 44, 36, 28, 20, 12,  4,
                        62, 54, 46, 38, 30, 22, 14,  6};
    int i;
    unsigned char temp[64];
    for(cnt = i; i < 64; i ++)
        temp[i] = data[IP[i]];
    memcpy(data, temp, 64);
    return 1;
}

int DES_IPInv_Transform(unsigned char* data) {  
    int IPInv[64] = {   39,  7, 47, 15, 55, 23, 63, 31,
                        38,  6, 46, 14, 54, 22, 62, 30,
                        37,  5, 45, 13, 53, 21, 61, 29,
                        36,  4, 44, 12, 52, 20, 60, 28,
                        35,  3, 43, 11, 51, 19, 59, 27,
                        34,  2, 42, 10, 50, 18, 58, 26,
                        33,  1, 41,  9, 49, 17, 57, 25,
                        32,  0, 40,  8, 48, 16, 56, 24};
    int i;
    unsigned char temp[64];
    for(i = 0; i < 64; i ++)
        temp[i] = data[IPInv[i]];
    memcpy(data, temp, 64);
    return 1;
}

int DES_E_Transform(unsigned char* data) {  
    int E[48] = {       31,  0,  1,  2,  3,  4,
                         3,  4,  5,  6,  7,  8,
                         7,  8,  9, 10, 11, 12,
                        11, 12, 13, 14, 15, 16,
                        15, 16, 17, 18, 19, 20,
                        19, 20, 21, 22, 23, 24,
                        23, 24, 25, 26, 27, 28,
                        27, 28, 29, 30, 31,  0};
    int i;
    unsigned char temp[48];
    for(i = 0; i < 48; i ++)
        temp[i] = data[E[i]];
    memcpy(data, temp, 48);
    return 1;
}

int DES_P_Transform(unsigned char* data){  
    int P[32] = {       15,  6, 19, 20, 28, 11, 27, 16,
                         0, 14, 22, 25,  4, 17, 30,  9,
                         1,  7, 23, 13, 31, 26,  2,  8,
                        18, 12, 29,  5, 21, 10,  3, 24};
    int i;
    unsigned char temp[32];
    for(i = 0; i < 32; i ++)
        temp[i] = data[E[i]];
    memcpy(data, temp, 32);
    return 1;
}

int DES(unsigned char* text, unsigned* result) {
    int PC_1[56] = {    56, 48, 40, 32, 24, 16,  8,
                         0, 57, 49, 41, 33, 25, 17,
                         9,  1, 58, 50, 42, 34, 26,
                        18, 10,  2, 59, 51, 43, 35,
                        62, 54, 46, 38, 30, 22, 14,
                         6, 61, 53, 45, 37, 29, 21,
                        13,  5, 60, 52, 44, 36, 28,
                        20, 12,  4, 27, 19, 11,  3};
    int PC_2[48] = {    13, 16, 10, 23,  0,  4,  2, 27,
                        14,  5, 20,  9, 22, 18, 11,  3,
                        25,  7, 15,  6, 26, 19, 12,  1,
                        40, 51, 30, 36, 46, 54, 29, 39,
                        50, 44, 32, 46, 43, 48, 38, 55,
                        33, 52, 45, 41, 49, 35, 28, 31};
    int S[8][4][16] = { // S1
                       {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
                        // S2
                       {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
                        // S3
                       {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
                        // S4
                       {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
                        // S5
                       {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
                        // S6
                       {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
                        // S7
                       {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
                        // S8
                       {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
    int MOVE_TIMES[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    int i, j;
	unsigned l = strlen(text);
	unsigned long long l_in_bits = l * 8;
	unsigned char* p_text = calloc(l + 65, sizeof(unsigned char));
	unsigned chunk[80];
	strcpy(p_text, text);
	p_text[l] = 0x80;
	l = (l + 9) / 64 * 64 + !!((l + 9) % 64) * 64;
    longlong_to_char(p_text + l - 8, l_in_bits);
	for(i = 0; i < l; i += 64) {
		unsigned a = h0;
		unsigned b = h1;
		unsigned c = h2;
		unsigned d = h3;
		unsigned e = h4;
        unsigned k;
        for(j = 0; j < 16; j ++)
            chunk[j] = char_to_unsigned(p_text + i + j * 4);
		for(j = 16; j < 80; j ++)
			chunk[j] = leftrotate(chunk[j - 3] ^ chunk[j - 8] ^ chunk[j - 14] ^ chunk[j - 16], 1);
        for(j = 0; j < 80; j ++) {
            unsigned f, temp;
            if(0 <= j && j <= 19) {
                f = (b & c) | (~b & d);
                k = 0X5A827999;
            } else if(20 <= j && j <= 39) {
                f = b ^ c ^ d;
                k = 0X6ED9EBA1;
            } else if(40 <= j && j <= 59) {
                f = (b & c) | (b & d) | (c & d); 
                k = 0X8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0XCA62C1D6;
            }
            temp = leftrotate(a, 5) + f + e + k + chunk[j];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }
    free(p_text);
    result[0] = h0;
    result[1] = h1;
    result[2] = h2;
    result[3] = h3;
    result[4] = h4;
    return 1;
}

int DES_EncryptBlock(unsigned char plainBlock[8], unsigned char subKeys[16][48], unsigned char cipherBlock[8]) {  
    unsigned char plainBits[64];  
    unsigned char copyRight[48];  
    int i;  

    Char8ToBit64(plainBlock, plainBits);       
    //初始置换（IP置换）  
    DES_IP_Transform(plainBits);
    //16轮迭代  
    for(i = 0; i < 16; i ++){
        memcpy(copyRight, plainBits + 32, 32);  
        //将右半部分进行扩展置换，从32位扩展到48位  
        DES_E_Transform(copyRight);  
        //将右半部分与子密钥进行异或操作
        DES_XOR(copyRight, subKeys[i], 48);
        //异或结果进入S盒，输出32位结果  
        DES_SBOX(copyRight);
        //P置换  
        DES_P_Transform(copyRight);
        //将明文左半部分与右半部分进行异或  
        DES_XOR(plainBits, copyRight, 32);
        if(i != 15){  
            //最终完成左右部的交换  
            DES_Swap(plainBits, plainBits + 32);  
        }
    }  
    //逆初始置换（IP^1置换）  
    DES_IPInv_Transform(plainBits);
    Bit64ToChar8(plainBits, cipherBlock);
    return 0;  
}  