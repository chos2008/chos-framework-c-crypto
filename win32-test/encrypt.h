#include <windows.h>

#define KEYLENGTH  0x00800000
#define ENCRYPT_ALGORITHM CALG_RC4 
#define ENCRYPT_BLOCK_SIZE 8 

bool MyEncryptFile(
    LPTSTR szSource, 
    LPTSTR szDestination, 
    LPTSTR szPassword);

void MyHandleError(
    LPTSTR psz, 
    int nErrorNumber);