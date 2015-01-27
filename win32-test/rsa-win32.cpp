//
// #author ada
// #version 1.0

#include "stdafx.h"
#include "rsa-win32.h"

B_RSAW* RSA_key_read_RSAPrivateKey_w(B_RSAW* rsa) 
{
	if (rsa == NULL) 
	{
		return NULL;
	}
	HCRYPTKEY hKey = rsa->hCryptKey;
	DWORD dwTempPriLen;
	int r = CryptExportKey(hKey, NULL, PRIVATEKEYBLOB, NULL, NULL, &dwTempPriLen);


	BYTE *pbTempPriData = (BYTE *)malloc(dwTempPriLen+1);
	r = CryptExportKey(hKey, NULL, PRIVATEKEYBLOB, NULL, pbTempPriData, &dwTempPriLen);

	rsa->keyData = pbTempPriData;
	rsa->keyDataLen = dwTempPriLen;
	return rsa;
}

B_RSAW* RSA_key_read_RSAPublicKey_w(B_RSAW* rsa) 
{
	if (rsa == NULL) 
	{
		return NULL;
	}
	HCRYPTKEY hKey = rsa->hCryptKey;
	DWORD dwTempPriLen;
	int r = CryptExportKey(hKey, NULL, PUBLICKEYBLOB, NULL, NULL, &dwTempPriLen);


	BYTE *pbTempPriData = (BYTE *)malloc(dwTempPriLen+1);
	r = CryptExportKey(hKey, NULL, PUBLICKEYBLOB, NULL, pbTempPriData, &dwTempPriLen);

	B_RSAW *_rsa = (B_RSAW *) malloc(sizeof(B_RSAW));
	memset(_rsa, 0, sizeof(B_RSAW));
	memcpy(_rsa, rsa, sizeof(B_RSAW));
	_rsa->keyData = pbTempPriData;
	_rsa->keyDataLen = dwTempPriLen;
	return _rsa;
}

B_RSAW* RSA_key_w() 
{
	B_RSAW *rsa = (B_RSAW *) malloc(sizeof(B_RSAW));
	HCRYPTPROV hCryptProv = NULL; // handle to a cryptographic service provider (CSP)
	//---------------------------------------------------------------
    // Get the handle to the default provider. 
	// #param pszProvider  Cryptographic Provider Names
	//     MS_ENHANCED_PROV  "Microsoft Enhanced Cryptographic Provider v1.0"
	CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_DELETEKEYSET);
    if(CryptAcquireContext(
        &hCryptProv, 
		NULL, 
        MS_ENHANCED_PROV, // "Microsoft Enhanced Cryptographic Provider v1.0"
        PROV_RSA_FULL, 
        CRYPT_NEWKEYSET))
    {
		rsa->hCryptProv = hCryptProv;
        _tprintf(TEXT("A cryptographic provider has been acquired. \n"));
    }
    else
    {
        return NULL;
    }

	HCRYPTKEY hKey;// handle of the key
	if(CryptGenKey(
          hCryptProv, 
          AT_KEYEXCHANGE, 
          CRYPT_EXPORTABLE, 
          &hKey))
	{
		rsa->hCryptKey = hKey;
		printf("A session key has been created.\n");
	}
	else
	{
		printf("Error during CryptGenKey.\n");
		exit(1);
	}
	return RSA_key_read_RSAPrivateKey_w(rsa);
}

void RSA_key_write_RSAPrivateKey_W(const char* fn, B_RSAW* rsa) 
{
	FILE *fp = NULL;
	fp = fopen(fn, "wb");
	if (fp == NULL) {
	    fprintf(stderr,"%s open error", fn);
	}
	printf("file %s opened...\n", fn);
	fwrite(rsa->keyData, 1, rsa->keyDataLen+1, fp);
	fclose(fp);
}

RSAW* RSA_key_base64_w(B_RSAW *rsa) 
{
	int len = Base64EncodeGetRequiredLength(rsa->keyDataLen, ATL_BASE64_FLAG_NONE);
	LPSTR szDest = (LPSTR) malloc(len + 1);
	memset(szDest, 0, len + 1);
	
	Base64Encode(rsa->keyData, rsa->keyDataLen, szDest, &len, ATL_BASE64_FLAG_NONE );

	
	
	RSAW *_rsa = (RSAW *) malloc(sizeof(RSAW));
	_rsa->keyData = szDest;
	_rsa->keDataLen = len + 1;
	return _rsa;
}

void RSA_key_write_RSAPrivateKey_base64_W(const char* fn, B_RSAW* rsa)
{
	RSAW *_rsa = RSA_key_base64_w(rsa);
	FILE *fp2 = NULL;

	fp2 = fopen(fn, "wb");
	if (fp2 == NULL) 
	{
	    fprintf(stderr,"%s open error", fn);
        return;
	}
	//fwrite(rsa->keyData, 1, rsa->keyDataLen+1, fp);
	fprintf(fp2, "%s", _rsa->keyData);
	//fclose(fp);
	fclose(fp2);
	free(_rsa);
}

void RSA_key_write_RSAPublicKey_W(const char* fn, B_RSAW* rsa) 
{
	FILE *fp = NULL;
	fp = fopen(fn, "wb");
	if (fp == NULL) {
	    fprintf(stderr,"%s open error", fn);
	}
	printf("file %s opened...\n", fn);
	fwrite(rsa->keyData, 1, rsa->keyDataLen+1, fp);
	fclose(fp);
}

void RSA_key_write_RSAPublicKey_base64_W(const char* fn, B_RSAW* rsa)
{
	RSAW *_rsa = RSA_key_base64_w(rsa);
	FILE *fp2 = NULL;

	fp2 = fopen(fn, "wb");
	if (fp2 == NULL) 
	{
	    fprintf(stderr,"%s open error", fn);
        return;
	}
	//fwrite(rsa->keyData, 1, rsa->keyDataLen+1, fp);
	fprintf(fp2, "%s", _rsa->keyData);
	//fclose(fp);
	fclose(fp2);
	free(_rsa);
}

void RSA_free_win32(B_RSAW *rsa)
{
	if (rsa == NULL) 
	{
		return;
	}
	free(rsa->keyData);
	rsa->keyData = NULL;
	//  When you have finished using the key, free the resource.
	HCRYPTKEY hCryptKey = rsa->hCryptKey;
	if (! CryptDestroyKey(hCryptKey)) 
	{
		DWORD error = GetLastError();
		if (error == ERROR_BUSY) 
		{
			printf("Warn: The key is currently being used.\n");
		}
		else 
		{
			printf("Error: during CryptDestroyKey, error: %d.\n", error); 
		}
	}

	HCRYPTPROV hCryptProv = rsa->hCryptProv;
	if (! CryptReleaseContext(hCryptProv, 0)) 
	{
		DWORD error = GetLastError();
		if (error == ERROR_BUSY) 
		//if (error == ERROR_INVALID_PARAMETER) 
		{
			printf("Warn: The context is currently being used by another process.\n");
		}
		else 
		{
			printf("Error: during CryptReleaseContext, error: %d.\n", error); 
		}
	}
}

char * encrypt_with_key(char *str, char *key)
{
	return NULL;
}


char * decrypt_with_key(char *s, char *k)
{
	return NULL;
}