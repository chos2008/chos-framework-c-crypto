// test.cpp
// 
// @author ada
// @version 1.0  2015-01-10

#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>

extern "C"
{
#include "openssl/applink.c"
}

#pragma comment(lib, "libeay32.lib")

#define FILE_KEY "test.key"
#define FILE_PUBLIC_KEY "test_pub.key"
#define BUFFSIZE 1024

RSA* RSA_key();
void RSA_key_write_RSAPrivateKey(const char* fn, RSA* rsa);
RSA* RSA_key_read_RSAPublicKey(RSA* rsa);
RSA* RSA_key_read_RSA_PublicKey(RSA* rsa);
void RSA_public_key_write_RSAPublicKey(const char* fn, RSA* rsa);
void RSA_public_key_write_RSA_PublicKey(const char* fn, RSA* rsa);

char * encrypt_with_key(char *str, char *key);

char * encrypt_with_fn(char *str, char *fps);

char * encrypt_with_fp(char *str, FILE* fp);

char * decrypt_with_key(char *s, char *k);

char * decrypt_with_fn(char *str,char *fps);

char * decrypt_with_fp(char *str, FILE* fp);

 
int _tmain(int argc, _TCHAR* argv[])
{
	RSA *rsa = NULL, *rsa_pk = NULL, *rsa_pkb;
    char *source="this is plain text!";
	char *ptr_en, *ptr_de;

    printf("plain text: %s\n", source);


	// RSA KEY TO GENERATE
	rsa = RSA_key();
	// WRITE RSA KEY TO FILE
	RSA_key_write_RSAPrivateKey("www.yhd.com-g.key", rsa);

	// READ PUBLIC KEY FROM RSA KEY
	rsa_pk = RSA_key_read_RSAPublicKey(rsa);

	// WRITE PUBLIC KEY TO FILE
	RSA_public_key_write_RSAPublicKey("www.yhd.com-g.pub.key", rsa_pk);
	RSA_public_key_write_RSA_PublicKey("www.yhd.com-g._pub.key", rsa_pk);

	rsa_pkb = RSA_key_read_RSA_PublicKey(rsa);

	// WRITE PUBLIC KEY TO FILE
	RSA_public_key_write_RSAPublicKey("www.yhd.com-g.pub_b.key", rsa_pkb);
	RSA_public_key_write_RSA_PublicKey("www.yhd.com-g._pub_b.key", rsa_pkb);

	char* key = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDAiZZSPEZHVnlnx6pRKEZdBP99\nGKaMikoABg2dLsMUk/zOxXLTpduuZNLxBicXLR9z7CCjUPfghFcclrWR5+hyZoAV\n0xOCd6YF9I9I7OL5Fj/GiTTjmuEm9uBxeQz6u2zl843DnDw8vwfZY+FQBDBRYic9\n+F1xPYRCQG6Hd9x9twIDAQAB\n-----END PUBLIC KEY-----\n";
	ptr_en = encrypt_with_key(source, key);
	printf("encrypt text: %s\n", ptr_en);

    ptr_en = encrypt_with_fn(source, FILE_PUBLIC_KEY);
    printf("encrypt text: %s\n", ptr_en);

	FILE *file;
    if((file = fopen(FILE_PUBLIC_KEY, "r")) != NULL) 
	{
        ptr_en = encrypt_with_fp(source, file);
		printf("encrypt text: %s\n", ptr_en);
    }

	char* pk = "-----BEGIN RSA PRIVATE KEY-----\nMIICXgIBAAKBgQDAiZZSPEZHVnlnx6pRKEZdBP99GKaMikoABg2dLsMUk/zOxXLT\npduuZNLxBicXLR9z7CCjUPfghFcclrWR5+hyZoAV0xOCd6YF9I9I7OL5Fj/GiTTj\nmuEm9uBxeQz6u2zl843DnDw8vwfZY+FQBDBRYic9+F1xPYRCQG6Hd9x9twIDAQAB\nAoGBAL9Cbc73DSEkZ6mOEERaa7tPkbRk3l1RqjznxnJT13oDn+iO/4f7hIRyp5DB\n+ebt7gark6hocDPZgudlVqy/4Ii6x6cYtW0hObcLig0+UrQJJG8huLj4Fp0mzcIf\nxAh90Bs0GeVEUp3K0FyMUL0+MT+VBnTHOnmizTIqCIJK3Z+RAkEA5AUqcyjneRsP\nRHq9k1IKK9RjiHKbV1fyF6TZGN+cE9pF8Zlbnv/3PFjBL8j+m6qSAjVD7ftaLprO\na5cQX/aW/QJBANgpy/hQcc4P7dXRbMddILsGkc/1sr078KQkgk8+gXK2aamdi1z8\nt6bCGQ7d6te1wPxnLvBgv+vpSJRJWdbt18MCQQCLG5OwOe4tdhK0ZmUtcUl/P82R\nOsoGWUL6pblEcXbYrbsqD7NTpzj/+e2x519dPIxjCHfuwf9cm1j/TmPRB7FJAkAR\n4+OtuXqxwz+74olONrbuw6xtubgBUWSpMRxX0qSECfTUxOUz3PaWJppMULGPCMvg\nF+oamudHbxdCro9w6l5hAkEAmzgmluE0SmFMvJ1jujflVGvIUKtwqQvyNg/qcCSj\nqhu+VTIyp//q/fwW5+U2JoVkx+IaIqzS8g0aDQHS0WPd+Q==\n-----END RSA PRIVATE KEY-----";
	ptr_de = decrypt_with_key(ptr_en, pk);
	printf("decrypt text(plain text): %s\n", ptr_de);

    ptr_de = decrypt_with_fn(ptr_en, FILE_KEY);
    printf("decrypt text(plain text): %s\n", ptr_de);

    if((file = fopen(FILE_KEY, "r")) != NULL) 
	{
        ptr_de = decrypt_with_fp(ptr_en, file);
		printf("decrypt text(plain text): %s\n", ptr_de);
    }

    if(ptr_en != NULL) {
        free(ptr_en);
    }
    if(ptr_de != NULL) {
        free(ptr_de);
	}
    return 0;
}

void RSA_key_write_RSAPrivateKey(const char* fn, RSA* rsa) {
	FILE *fp = NULL;
	fp = fopen(fn, "w");
	if (fp == NULL) {
	    fprintf(stderr,"%s open error", fn);
	}
	printf("file %s opened...\n", fn);
	PEM_write_RSAPrivateKey(fp, rsa, NULL, NULL, 512, NULL, NULL);
	fclose(fp);
}

RSA* RSA_key_read_RSAPublicKey(RSA* rsa) {
	
	BIO *bio = NULL;
	RSA* pk = NULL;

    bio = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPublicKey(bio, rsa);
	if((pk = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL))==NULL) {
		ERR_print_errors_fp(stdout);
        return NULL;
	}
	return pk;
}

RSA* RSA_key_read_RSA_PublicKey(RSA* rsa) {
	
	BIO *bio = NULL;
	RSA* pk = NULL;

    bio = BIO_new(BIO_s_mem());
	PEM_write_bio_RSA_PUBKEY(bio, rsa);
	if((pk = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL))==NULL) {
		ERR_print_errors_fp(stdout);
        return NULL;
	}
	return pk;
}

void RSA_public_key_write_RSAPublicKey(const char* fn, RSA* rsa) {
	FILE* fp = NULL;
    fp = fopen(fn, "w");
	if (fp == NULL) {
	    fprintf(stderr,"%s open error", fn);
        return;
	}
	printf("file %s opened...\n", fn);
	PEM_write_RSAPublicKey(fp, rsa);
	fclose(fp);
}

void RSA_public_key_write_RSA_PublicKey(const char* fn, RSA* rsa) {
	FILE* fp = NULL;
    fp = fopen(fn, "w");
	if (fp == NULL) {
	    fprintf(stderr,"%s open error", fn);
        return;
	}
	printf("file %s opened...\n", fn);
	PEM_write_RSA_PUBKEY(fp, rsa);
	fclose(fp);
}

RSA* RSA_key() {
	RSA* rsa = NULL; // RSA_new();
	// BIGNUM * e = BN_new();
	unsigned long ue = RSA_3;

	printf("RSA_generate_key\n");
	rsa = RSA_generate_key(1024, ue, NULL, NULL);
	printf("RSA_generate_key return\n");

	//int rt = RSA_generate_key_ex(rsa, 1024, e, NULL);
	//unsigned long error = ERR_get_error();
	//printf("error: %ld\n", error);
	return rsa;
}

char *encrypt_with_key(char *str, char *key) {
	// read public key from the specific string -- with char * from memory
#undef OPENSSL_NO_BIO 

	BIO *bio = NULL;
	RSA *p_rsa = NULL;
	int flen, rsa_len;
	char *p_en = NULL;

	if ((bio = BIO_new_mem_buf(key, -1)) == NULL) // read public key from string
    {
        perror("BIO_new_mem_buf failed!");
    }
	if((p_rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL))==NULL) {
		ERR_print_errors_fp(stdout);
        return NULL;
	}







    flen = strlen(str);
    rsa_len = RSA_size(p_rsa);
    p_en = (char *) malloc(rsa_len + 1);
    memset(p_en, 0, rsa_len + 1);
    if(RSA_public_encrypt(rsa_len, (unsigned char *) str, (unsigned char *) p_en, p_rsa, RSA_NO_PADDING) < 0) {
        return NULL;
    }
	BIO_free(bio);
    RSA_free(p_rsa);
	return p_en;
}

// encript string with the specific key
// #str  the string to be encript
// #fps  the file name of key
char *encrypt_with_fn(char *str, char *fps) {
    char *p_en = NULL;
    FILE *file;
    if((file = fopen(fps, "r")) == NULL) {
        perror("open key file error");
        return NULL;    
    }
	p_en = encrypt_with_fp(str, file);
	fclose(file);
	return p_en;
}

char *encrypt_with_fp(char *str, FILE* fp) 
{
	RSA *p_rsa = NULL;
	int flen, rsa_len;
	char *p_en = NULL;

	// PEM_read_RSA_PUBKEY: 
	// DECLARE_PEM_rw(RSA_PUBKEY, RSA)
	// 
	// #define DECLARE_PEM_rw(name, type) DECLARE_PEM_read(name, type) DECLARE_PEM_write(name, type)
	// 
	// #define DECLARE_PEM_read(name, type) DECLARE_PEM_read_bio(name, type) DECLARE_PEM_read_fp(name, type)
	// #define DECLARE_PEM_write(name, type) DECLARE_PEM_write_bio(name, type) DECLARE_PEM_write_fp(name, type)
	// 
	// // #define DECLARE_PEM_read_bio(name, type) type *PEM_read_bio_##name(BIO *bp, type **x, pem_password_cb *cb, void *u);
	// #define DECLARE_PEM_read_bio(name, type) /**/
	// // #define DECLARE_PEM_read_fp(name, type) /**/
	// #define DECLARE_PEM_read_fp(name, type) type *PEM_read_##name(FILE *fp, type **x, pem_password_cb *cb, void *u);
	// 
	// // #define DECLARE_PEM_write_bio(name, type) int PEM_write_bio_##name(BIO *bp, type *x);
	// #define DECLARE_PEM_write_bio(name, type) /**/
	// // #define DECLARE_PEM_write_fp(name, type) int PEM_write_##name(FILE *fp, type *x);
	// #define DECLARE_PEM_write_fp(name, type) /**/
	//
	//
	// DECLARE_PEM_rw(RSA_PUBKEY, RSA)
	// 
	// DECLARE_PEM_read(RSA_PUBKEY, RSA) DECLARE_PEM_write(RSA_PUBKEY, RSA)
	// 
	// DECLARE_PEM_read_bio(RSA_PUBKEY, RSA) DECLARE_PEM_read_fp(RSA_PUBKEY, RSA) DECLARE_PEM_write_bio(RSA_PUBKEY, RSA) DECLARE_PEM_write_fp(RSA_PUBKEY, RSA)
    // 
	// /**/
	// RSA *PEM_read_RSA_PUBKEY(FILE *fp, RSA **x, pem_password_cb *cb, void *u);
	// /**/
	// /**/
	//
	//
	// RSA *PEM_read_bio_RSA_PUBKEY(BIO *bp, RSA **x, pem_password_cb *cb, void *u);
	// /**/
	// /**/
	// /**/

	// read public key from the specific string -- with char * from memory
	if((p_rsa = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL)) == NULL) 
	{
    //if((p_rsa=PEM_read_RSAPublicKey(file,NULL,NULL,NULL))==NULL){
        ERR_print_errors_fp(stdout);
        return NULL;
    }

    flen = strlen(str);
    rsa_len = RSA_size(p_rsa);
    p_en = (char *) malloc(rsa_len + 1);
    memset(p_en, 0, rsa_len + 1);
    if(RSA_public_encrypt(rsa_len, (unsigned char *) str, (unsigned char *) p_en, p_rsa, RSA_NO_PADDING) < 0) {
        return NULL;
    }
    RSA_free(p_rsa);
    return p_en;
}

char * decrypt_with_key(char *s, char *k) 
{
	char *p_de = NULL;
	RSA *p_rsa = NULL;
	int rsa_len;
	// read public key from the specific string -- with char * from memory
#undef OPENSSL_NO_BIO 

	BIO *bio;
	if ((bio = BIO_new_mem_buf(k, -1)) == NULL) // read key from string
    {
        perror("BIO_new_mem_buf failed!");
		return NULL;
    }
	if((p_rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL)) == NULL) {
		ERR_print_errors_fp(stdout);
        return NULL;
	}


    rsa_len=RSA_size(p_rsa);
    p_de = (char *) malloc(rsa_len + 1);
    memset(p_de,0,rsa_len+1);
    if(RSA_private_decrypt(rsa_len, (unsigned char *) s, (unsigned char*) p_de, p_rsa, RSA_NO_PADDING) < 0) {
        return NULL;
    }
    RSA_free(p_rsa);
    return p_de;
}

// decript string with the specific key
// #str  the string to be decript
// #fps  the file name of key
char * decrypt_with_fn(char *str, char *fps) 
{
    char *p_de;
    FILE *file;
    if((file = fopen(fps, "r")) == NULL) 
	{
        perror("error to open key from file");
        return NULL;
    }

	p_de = decrypt_with_fp(str, file);
    fclose(file);
    return p_de;
}

// decript string with the specific key
// #str  the string to be decript
// #fps  the file name of key
char * decrypt_with_fp(char *str, FILE* fp) 
{
    RSA *p_rsa = NULL;
	char *p_de = NULL;
    int rsa_len;

    if((p_rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL) 
	{
        ERR_print_errors_fp(stdout);
        return NULL;
    }

	rsa_len = RSA_size(p_rsa);
    p_de = (char *) malloc(rsa_len + 1);
    memset(p_de, 0, rsa_len + 1);
    if(RSA_private_decrypt(rsa_len, (unsigned char *) str, (unsigned char *) p_de, p_rsa, RSA_NO_PADDING) < 0) 
	{
        return NULL;
    }
    RSA_free(p_rsa);
    return p_de;
}