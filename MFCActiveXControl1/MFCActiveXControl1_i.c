

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Fri Jan 23 23:04:52 2015
 */
/* Compiler settings for MFCActiveXControl1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_MFCActiveXControl1Lib,0x1979A998,0x33B8,0x4C5D,0x92,0x6E,0x63,0x5A,0x22,0xD0,0xC5,0x8E);


MIDL_DEFINE_GUID(IID, DIID__DMFCActiveXControl1,0x8888A2FD,0x974F,0x44BB,0x84,0xE4,0x9F,0x24,0xF6,0x70,0xFE,0xA2);


MIDL_DEFINE_GUID(IID, DIID__DMFCActiveXControl1Events,0x944EC20E,0x29AE,0x4B48,0xAE,0x66,0xF5,0x32,0xB3,0xE5,0x04,0x18);


MIDL_DEFINE_GUID(CLSID, CLSID_MFCActiveXControl1,0xCEB620A2,0x3B64,0x4247,0xA9,0x71,0x49,0xC7,0x08,0xC5,0x1E,0xBF);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



