//
// #author chos-framework
// #version 1.0

#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#include <conio.h>
#include <atlenc.h>

#pragma comment (lib, "advapi32")

#ifndef RSA_WIN32
#define RSA_WIN32

typedef struct {
	HCRYPTPROV hCryptProv; // handle to a cryptographic service provider (CSP)

	HCRYPTKEY hCryptKey;
	BYTE * keyData;
	int keyDataLen;
} B_RSAW;

typedef struct 
{
	char *keyData;
	int keDataLen;
} RSAW;

B_RSAW* RSA_key_w();

B_RSAW* RSA_key_read_RSAPublicKey_w(B_RSAW* rsa);

void RSA_key_write_RSAPrivateKey_W(const char* fn, B_RSAW* rsa);

void RSA_key_write_RSAPrivateKey_base64_W(const char* fn, B_RSAW* rsa);

void RSA_key_write_RSAPublicKey_W(const char* fn, B_RSAW* rsa);

void RSA_key_write_RSAPublicKey_base64_W(const char* fn, B_RSAW* rsa);

void RSA_free_win32(B_RSAW *rsa);


char * encrypt_with_key(char *str, char *key);


char * decrypt_with_key(char *s, char *k);

#endif;