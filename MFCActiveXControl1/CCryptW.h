// 
// 
// @author aga
// @version  1.0  2015-01-20

#include<stdio.h>

#ifndef C_WND_CRYPT
#define C_WND_CRYPT

char * encrypt_with_key(char *str, char *key);

char * encrypt_with_fn(char *str, char *fps);

char * encrypt_with_fp(char *str, FILE* fp);

char * decrypt_with_key(char *s, char *k);

char * decrypt_with_fn(char *str,char *fps);

char * decrypt_with_fp(char *str, FILE* fp);

#endif;