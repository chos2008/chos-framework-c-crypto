// APIs of encrypt and decrypt
// <p>
// 
// @author ada
// @version  1.0

#include "stdafx.h"

#include "CCrypt.h"

//#ifndef _OPENSSL_Applink 
extern "C"
{
#include "openssl/applink.c"
}
//#endif;

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
	CString strResult3(fps);
	LPWSTR enStr=new wchar_t[strResult3.GetLength()+1]; 
	wcscpy(enStr, T2W((LPTSTR) strResult3.AllocSysString()));
	::MessageBoxW(NULL, enStr, (LPCWSTR)L"к╫т©нд╪Ч", MB_ICONWARNING);

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