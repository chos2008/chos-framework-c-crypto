//
//
// @author aga
// @version 1.0  2015-01-20

#include <windows.h>
#include <wincrypt.h>
#include "CCryptW.h"

char * encrypt_with_key(char *str, char *key) {
	HCRYPTPROV phProv = NULL;
	LPCTSTR pszContainer = L"KeyContainer";
	if(CryptAcquireContext(
		&phProv,               // handle to the CSP
		pszContainer,                  // container name 
		NULL,                      // use the default provider
		PROV_RSA_FULL,             // provider type
		0))                        // flag values
	{
		printf("A cryptographic context with the %s key container \n", pszContainer);
		printf("has been acquired.\n\n");
	}
	else
	{
		if (GetLastError() == NTE_BAD_KEYSET) 
		{
			if(CryptAcquireContext(
				&phProv, 
				pszContainer, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_NEWKEYSET)) 
			{
				printf("A new key container has been created.\n");
			}
			else
			{
				printf("Could not create a new key container.\n");
				exit(1);
			}
		}
		else
		{
			printf("A cryptographic service handle could not be acquired.\n");
			exit(1);
		}
	}

	HCRYPTKEY hPubKey;
	if(CryptImportKey(
		phProv,
        pbKeyBlob,
        dwBlobLen,
        0,
        0,
        &hPubKey))
    {
        printf("The key has been imported.\n");
    }
    else
    {
        printf("Public key import failed.\n");
        return FALSE;
    }
	//CryptEncrypt(

	if (CryptReleaseContext(hCryptProv,0))
	{
		printf("The handle has been released.\n");
	}
	else
	{
		printf("The handle could not be released.\n");
	}
	return NULL;
}

char * encrypt_with_fn(char *str, char *fps) 
{
	return NULL;
}

char * encrypt_with_fp(char *str, FILE* fp)
{
	return NULL;
}

char * decrypt_with_key(char *s, char *k)
{
	return NULL;
}

char * decrypt_with_fn(char *str,char *fps)
{
	return NULL;
}

char * decrypt_with_fp(char *str, FILE* fp)
{
	return NULL;
}