// win32-test.cpp : 定义控制台应用程序的入口点。
// 
// Defines the entry point for the console 
// application.

#include "stdafx.h"


#include "encrypt.h"
#include "rsa-win32.h"




int _tmain(int argc, _TCHAR* argv[])
{
	/*
    if(argc < 3)
    {
        _tprintf(TEXT("Usage: <example.exe> <source file> ")
            TEXT("<destination file> | <password>\n"));
        _tprintf(TEXT("<password> is optional.\n"));
        _tprintf(TEXT("Press any key to exit."));
        _gettch();
        return 1;
    }
	*/

	B_RSAW *rsa = RSA_key_w();

	char *fn = "D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\win32-test\\www.yhd.com-g-win.key";
	RSA_key_write_RSAPrivateKey_W(fn, rsa);

	char *fn2 = "D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\win32-test\\www.yhd.com-g-2-win.key";
	RSA_key_write_RSAPrivateKey_base64_W(fn2, rsa);

	B_RSAW *_rsa = RSA_key_read_RSAPublicKey_w(rsa);

	char *fn_pubkey = "D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\win32-test\\www.yhd.com-g_pubkey-win.key";
	RSA_key_write_RSAPublicKey_W(fn_pubkey, _rsa);

	char *fn_pubkey2 = "D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\win32-test\\www.yhd.com-g-2_pubkey-win.key";
	RSA_key_write_RSAPublicKey_base64_W(fn_pubkey2, _rsa);

	RSA_free_win32(rsa);
	//RSA_free_win32(_rsa);

	/*
    LPTSTR pszSource = NULL; 
    LPTSTR pszDestination = NULL; 
    LPTSTR pszPassword = NULL;

	pszSource = L"D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\win32-test\\plain-text.txt";
	pszDestination = L"D:\\home\\workspace1\\tst_edit\\MFCActiveXControl1\\win32-test\\encrypt-text.txt";
	pszPassword = L"yihaodian";

    //---------------------------------------------------------------
    // Call EncryptFile to do the actual encryption.
    if(MyEncryptFile(pszSource, pszDestination, pszPassword))
    {
        _tprintf(
            TEXT("Encryption of the file %s was successful. \n"), 
            pszSource);
        _tprintf(
            TEXT("The encrypted data is in file %s.\n"), 
            pszDestination);
    }
    else
    {
        MyHandleError(
            TEXT("Error encrypting file!\n"), 
            GetLastError()); 
    }
	*/
    return 0;
}
