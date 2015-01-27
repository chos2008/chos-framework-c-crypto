#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>




#if ! defined C_OPEN_SSL_CRYPT


//#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "libeay32MD.lib")


#define C_OPEN_SSL_CRYPT
#define FILE_KEY "D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\MFCActiveXControl1\\test.key"
#define FILE_PUBLIC_KEY "D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\MFCActiveXControl1\\test_pub.key"
#define BUFFSIZE 1024

//extern "C"
//{

char * encrypt_with_key(char *str, char *key);

char * encrypt_with_fn(char *str, char *fps);

char * encrypt_with_fp(char *str, FILE* fp);

char * decrypt_with_key(char *s, char *k);

char * decrypt_with_fn(char *str,char *fps);

char * decrypt_with_fp(char *str, FILE* fp);
//}
#endif;
