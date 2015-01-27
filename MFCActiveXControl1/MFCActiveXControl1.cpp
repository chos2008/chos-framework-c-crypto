// MFCActiveXControl1.cpp : CMFCActiveXControl1App �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "MFCActiveXControl1.h"
#include "Cathelp.h"
#include "objsafe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CMFCActiveXControl1App theApp;

const GUID CDECL _tlid = { 0x1979A998, 0x33B8, 0x4C5D, { 0x92, 0x6E, 0x63, 0x5A, 0x22, 0xD0, 0xC5, 0x8E } };

const CATID CLSID_SafeItem = {0xceb620a2, 0x3b64, 0x4247, {0xa9, 0x71, 0x49, 0xc7, 0x8, 0xc5, 0x1e, 0xbf}};

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CMFCActiveXControl1App::InitInstance - DLL ��ʼ��

BOOL CMFCActiveXControl1App::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
		
		
	}

	return bInit;
}



// CMFCActiveXControl1App::ExitInstance - DLL ��ֹ

int CMFCActiveXControl1App::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	HRESULT hr;    // HResult used by Safety Functions


	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	// Mark the control as safe for initializing.
                                             
    hr = CreateComponentCategory(CATID_SafeForInitializing, 
         L"Controls safely initializable from persistent data!");
    if (FAILED(hr))
      return hr;
 
    hr = RegisterCLSIDInCategory(CLSID_SafeItem, 
         CATID_SafeForInitializing);
    if (FAILED(hr))
        return hr;
 
    // Mark the control as safe for scripting.
 
    hr = CreateComponentCategory(CATID_SafeForScripting, 
                                 L"Controls safely  scriptable!");
    if (FAILED(hr))
        return hr;
 
    hr = RegisterCLSIDInCategory(CLSID_SafeItem, 
                        CATID_SafeForScripting);
    if (FAILED(hr))
        return hr;

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	// ɾ���ؼ���ʼ����ȫ���.   
    HRESULT hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);  

	if (FAILED(hr))  
        return hr;  

	// ɾ���ؼ��ű���ȫ���   
    hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);  

    if (FAILED(hr))  
        return hr;  

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
