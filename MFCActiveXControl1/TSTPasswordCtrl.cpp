// TSTPasswordCtrl.cpp : CTSTPasswordCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "MFCActiveXControl1.h"
#include "TSTPasswordCtrl.h"
#include "TSTPasswordPropPage.h"
#include "afxdialogex.h"

#include <atlconv.h>
#include <string.h>

#include "CCrypt.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define IDC_EDIT 10101

IMPLEMENT_DYNCREATE(CTSTPasswordCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CTSTPasswordCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CTSTPasswordCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CTSTPasswordCtrl, COleControl)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "AddFun", dispidAddFun, AddFun, VT_I4, VTS_I4 VTS_I4)
	//DISP_FUNCTION_ID(CTSTPasswordCtrl, "encode", dispidencode, encode, VT_PI1, VTS_PI1)
	//DISP_FUNCTION_ID(CTSTPasswordCtrl, "encode", dispidencode, encode, VT_PI1, VTS_PI1 VTS_I4)
	//DISP_FUNCTION_ID(CTSTPasswordCtrl, "encode", dispidencode, encode, VT_PI1, VTS_PI1 VTS_I4)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "encode", dispidencode, encode, VT_BSTR, VTS_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CTSTPasswordCtrl, "password", dispidpassword, m_password, OnpasswordChanged, VT_BSTR)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "value", dispidvalue, value, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "_GetPassword", dispid_GetPassword, _GetPassword, VT_BSTR, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CTSTPasswordCtrl, "Version", dispidVersion, m_Version, OnVersionChanged, VT_BSTR)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "_GetVersion", dispid_GetVersion, _GetVersion, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "_Encrypt", dispid_Encrypt, _Encrypt, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CTSTPasswordCtrl, "_Decrypt", dispid_Decrypt, _Decrypt, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CTSTPasswordCtrl, COleControl)
	EVENT_CUSTOM_ID("Ev_Init", eventidEv_Init, Ev_Init, VTS_I4)
END_EVENT_MAP()

// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CTSTPasswordCtrl, 1)
	PROPPAGEID(CTSTPasswordPropPage::guid)
END_PROPPAGEIDS(CTSTPasswordCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CTSTPasswordCtrl, "MFCACTIVEXCONTRO.TSTPasswordCtrl.1",
	0xceb620a2, 0x3b64, 0x4247, 0xa9, 0x71, 0x49, 0xc7, 0x8, 0xc5, 0x1e, 0xbf)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CTSTPasswordCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DMFCActiveXControl1 = { 0x8888A2FD, 0x974F, 0x44BB, { 0x84, 0xE4, 0x9F, 0x24, 0xF6, 0x70, 0xFE, 0xA2 } };
const IID IID_DMFCActiveXControl1Events = { 0x944EC20E, 0x29AE, 0x4B48, { 0xAE, 0x66, 0xF5, 0x32, 0xB3, 0xE5, 0x4, 0x18 } };

// 控件类型信息

static const DWORD _dwMFCActiveXControl1OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTSTPasswordCtrl, IDS_MFCACTIVEXCONTROL1, _dwMFCActiveXControl1OleMisc)



	HHOOK hHook;

// CTSTPasswordCtrl::CTSTPasswordCtrlFactory::UpdateRegistry -
// 添加或移除 CTSTPasswordCtrl 的系统注册表项

BOOL CTSTPasswordCtrl::CTSTPasswordCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MFCACTIVEXCONTROL1,
			IDB_MFCACTIVEXCONTROL1,
			afxRegApartmentThreading,
			_dwMFCActiveXControl1OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CTSTPasswordCtrl::CTSTPasswordCtrl - 构造函数

CTSTPasswordCtrl::CTSTPasswordCtrl()
{
	//::MessageBoxW(NULL, (LPCWSTR)L"CTSTPasswordCtrl()", (LPCWSTR)L"提示", MB_ICONWARNING);

	InitializeIIDs(&IID_DMFCActiveXControl1, &IID_DMFCActiveXControl1Events);
	// TODO: 在此初始化控件的实例数据。
	
    //::MessageBoxW(NULL, (LPCWSTR)L"设置钩子", (LPCWSTR)L"提示", MB_ICONWARNING);
	//*
	hHook = SetWindowsHookExW(WH_GETMESSAGE, 
		::GetMsgProc, 
		NULL, 
		GetCurrentThreadId());
	//*/
}

// CTSTPasswordCtrl::~CTSTPasswordCtrl - 析构函数

CTSTPasswordCtrl::~CTSTPasswordCtrl()
{
	// TODO: 在此清理控件的实例数据。
}

void CTSTPasswordCtrl::initPasswordEditCtrl()
{
	//*
	CRect rect(0, 0, 150, 24);
	passwordEdit = new CPasswordEdit;
	// ES_PASSWORD
	// ES_OEMCONVERT
	passwordEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | UDS_ALIGNLEFT, rect, this, IDC_EDIT);
	//edit->setw
	//edit->UpdateData(
	//CRect btnRect(0,0,150,25);
	//edit->MoveWindow(btnRect);
	//edit->SetPasswordChar('*');
	//edit->SetPasswordChar('.');
	passwordEdit->ShowWindow(SW_SHOW);
	
	//passwordEdit->SubclassDlgItem(IDC_EDIT, this);
	//passwordEdit->SubclassWindow(this->GetSafeHwnd());
	//LPTSTR str;
	//edit->GetWindowTextW(str, 16);
	//*/
}


int CTSTPasswordCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	 

    if (COleControl::OnCreate(lpCreateStruct) == -1) 
    {
        return -1;
    }

	::MessageBoxW(NULL, (LPCWSTR)L"OnCreate(LPCREATESTRUCT lpCreateStruct)", (LPCWSTR)L"提示", MB_ICONWARNING);
    return 0;
}

void CTSTPasswordCtrl::InitializeIIDs(const IID* piidPrimary, const IID* piidEvents) 
{
	COleControl::InitializeIIDs(piidPrimary, piidEvents);

	//::MessageBoxW(NULL, (LPCWSTR)L"InitializeIIDs(const IID* piidPrimary, const IID* piidEvents)", (LPCWSTR)L"提示", MB_ICONWARNING);

	//initPasswordEditCtrl();

}


void CTSTPasswordCtrl::SetInitialSize(int cx, int cy) 
{
	COleControl::SetInitialSize(cx, cy);

	::MessageBoxW(NULL, (LPCWSTR)L"SetInitialSize(int cx, int cy)", (LPCWSTR)L"提示", MB_ICONWARNING);
}

BOOL CTSTPasswordCtrl::PreTranslateMessage(MSG* pMsg)
{
	CWnd *hWnd = GetDlgItem(IDC_EDIT);
	HWND hwnd = hWnd->GetSafeHwnd();
	if(WM_CHAR == pMsg->message  && pMsg->hwnd == GetDlgItem(IDC_EDIT)->GetSafeHwnd())
	{
		TCHAR ch = (TCHAR)pMsg->wParam;
		::MessageBoxW(NULL, LPWSTR(ch), (LPCWSTR)L"-->", MB_ICONWARNING);
		if((ch >='0' && ch <='9'))
			return CWnd::PreTranslateMessage(pMsg);
		if(ch >= 'A' && ch <= 'F')
			return CWnd::PreTranslateMessage(pMsg);
		if(ch >= 'a' && ch <= 'f')
			return CWnd::PreTranslateMessage(pMsg);
		return true;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CTSTPasswordCtrl::OnWindowlessMessage( UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult ) {
	//MessageBox.Show("");
	
	char *s = new char[4];
	memset(s, 0, 4);
	_itoa(msg, s, 10);
	wchar_t* ws = new wchar_t[4];
	mbstowcs (ws, s, 4);
	// ::MessageBoxW(NULL, ws, (LPCWSTR)L"提示1", MB_ICONWARNING);
	/**/
	return COleControl::OnWindowlessMessage(msg, wParam, lParam, plResult);
}

LRESULT CTSTPasswordCtrl::WindowProc(
		UINT message,
		WPARAM wParam,
		LPARAM lParam 
		) {
	char *s = new char[4];
	memset(s, 0, 4);
	_itoa(message, s, 10);
	wchar_t* ws = new wchar_t[4];
	mbstowcs (ws, s, 4);
	//::MessageBoxW(NULL, ws, (LPCWSTR)L"提示2", MB_ICONWARNING);

	/*
	switch ( message )
   {
     case WM_INITDIALOG:
		 
         hHook = SetWindowsHookExW( WH_GETMESSAGE, ::GetMsgProc,
                                   NULL, GetCurrentThreadId() );
         return TRUE;

     case WM_COMMAND:
		 
         if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
         {
            //DestroyWindow( hwndDlg );
            //hwndDllDlg = NULL;
         }
         return TRUE;

     case WM_DESTROY:
	
         UnhookWindowsHookEx( hHook );
         return FALSE;
   }
   //return FALSE;
   */
	return COleControl::WindowProc(message, wParam, lParam);
}

// CTSTPasswordCtrl::OnDraw - 绘图函数

void CTSTPasswordCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;


	DoSuperclassPaint(pdc, rcBounds);
}

// CTSTPasswordCtrl::DoPropExchange - 持久性支持

void CTSTPasswordCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);//(LPCWSTR)L"明文"
	//_istlower(
	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
	PX_String(pPX, L"Version", this->m_Version, L"");
	PX_String(pPX, L"password", this->m_password, L"default password");
}


// CTSTPasswordCtrl::OnResetState - 将控件重置为默认状态

void CTSTPasswordCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}


// CTSTPasswordCtrl::AboutBox - 向用户显示“关于”框

void CTSTPasswordCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_MFCACTIVEXCONTROL1);
	dlgAbout.DoModal();
}


// CTSTPasswordCtrl::PreCreateWindow - 修改 CreateWindowEx 的参数

BOOL CTSTPasswordCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("EDIT");
	return COleControl::PreCreateWindow(cs);
}

// CTSTPasswordCtrl::IsSubclassedControl - 这是一个子类控件

BOOL CTSTPasswordCtrl::IsSubclassedControl()
{
	
	return TRUE;
}

// CTSTPasswordCtrl::OnOcmCommand - 处理命令消息

LRESULT CTSTPasswordCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);

	// TODO: 在此接通 wNotifyCode。

	return 0;
}


// CTSTPasswordCtrl 消息处理程序


LONG CTSTPasswordCtrl::AddFun(LONG num1, LONG num2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	/*
	::MessageBox(NULL, 
		(LPCWSTR)L"Resource not available\nDo you want to try again?",
        (LPCWSTR)L"提示", 
		MB_ICONWARNING);
	*/
	// TODO: 在此添加调度处理程序代码

	initPasswordEditCtrl();
	// 控件初始化成功之后， 触发Ev_Init事件. 参数Status为0表示正常。
	Ev_Init(0);
	return num1 + num2;
}
/*
HHOOK CTSTPasswordCtrl::getHHook() {
	return this->hHook;
}
*/

//LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
LRESULT FAR PASCAL GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam) {
    LPMSG lpMsg = (LPMSG) lParam;
	//CTSTPasswordCtrl* hwnd = (CTSTPasswordCtrl*) lpMsg->hwnd;

	char *s = new char[4];
	memset(s, 0, 4);
	_itoa(lpMsg->message, s, 10);
	wchar_t* ws = new wchar_t[4];
	mbstowcs (ws, s, 4);

	

    if ( nCode >= 0 && PM_REMOVE == wParam )
    {
        // Don't translate non-input events.
        // WM_KEYFIRST 0x0100(256)
	    // WM_KEYDOWN 0x0100(256)
	    // WM_KEYUP 0x0101(257)
	    // WM_CHAR 0x0102(258)
	    // WM_KEYLAST 0x0109(265)
	    UINT uInt;
        if ( (lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST) )
        {
			//::MessageBoxW(NULL, LPWSTR(lpMsg->message), (LPCWSTR)L"提示3", MB_ICONWARNING);
		    //::MessageBoxW(NULL, ws, (LPCWSTR)L"提示3", MB_ICONWARNING);
            if (IsDialogMessageW(lpMsg->hwnd, lpMsg))
            {
                // The value returned from this hookproc is ignored, 
                // and it cannot be used to tell Windows the message has been handled.
                // To avoid further processing, convert the message to WM_NULL 
                // before returning.
			    if (lpMsg->message == WM_KEYDOWN || lpMsg->message == WM_KEYUP) {
				    lpMsg->message = WM_NULL;
				    lpMsg->lParam  = 0;
				    lpMsg->wParam  = 0;
				} else {
					
					
				}
			}
        }
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
	//return false;
}




BSTR CTSTPasswordCtrl::value(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//CString strResult;
	::MessageBox(NULL, 
        (LPCWSTR)L"Resource not available", 
        (LPCWSTR)L"提示", 
        MB_ICONWARNING);
	CString cstr("jx.vovo.11-28");
	CWnd *pWnd = GetDlgItem(IDC_EDIT);
	if (pWnd == NULL) 
	{
		::MessageBox(NULL, 
			(LPCWSTR)L"获取密码控件失败", 
			(LPCWSTR)L"提示", 
			MB_ICONWARNING);
		return cstr.AllocSysString();
	}
	pWnd->GetWindowText(cstr);

	// TODO: 在此添加调度处理程序代码
	
	::MessageBoxW(NULL, cstr.AllocSysString(), (LPCWSTR)L"value", MB_ICONWARNING);
	return cstr.AllocSysString();
}


/*
CHAR* CTSTPasswordCtrl::encode(CHAR* password, LONG size)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	// size_t si ;
	wchar_t* ws = (wchar_t*) malloc((size_t) size);
	mbstowcs (ws, password, (size_t) size);
	::MessageBoxW(NULL, ws, (LPCWSTR)L"提示1", MB_ICONWARNING);
	return 0;
}
*/



BSTR CTSTPasswordCtrl::encode(LPCTSTR password)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	::MessageBoxW(NULL, password, (LPCWSTR)L"明文", MB_ICONWARNING);

	CString strResult(password);
	::MessageBoxW(NULL, strResult.AllocSysString(), (LPCWSTR)L"明文-1", MB_ICONWARNING);
	
	
	char *pBuffer = "jx.vovo.11-28";// (LPSTR) (LPCTSTR) strResult;
	CString strResult2(pBuffer);
	::MessageBoxW(NULL, strResult2.AllocSysString(), (LPCWSTR)L"明文-2", MB_ICONWARNING);

	char *pBuffer2 = "jx.vovo.11-28";// (LPSTR) (LPCTSTR) strResult;
	CString strResult2_1(pBuffer2);// = _T("jx.vovo.11-28");
	//strResult2_1.Format(_T("%s"), pBuffer2);
	USES_CONVERSION;
	// #define A2CW(lpa) ((LPCWSTR)A2W(lpa))
	// LPCSTR pwcStr = A2CW((LPCSTR) strResult2_1);

	LPWSTR pwStr=new wchar_t[strResult2_1.GetLength()+1]; 
	wcscpy(pwStr, T2W((LPTSTR) strResult2_1.AllocSysString()));
	::MessageBoxW(NULL, pwStr, (LPCWSTR)L"加密2-1", MB_ICONWARNING);

	char* key = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDAiZZSPEZHVnlnx6pRKEZdBP99\nGKaMikoABg2dLsMUk/zOxXLTpduuZNLxBicXLR9z7CCjUPfghFcclrWR5+hyZoAV\n0xOCd6YF9I9I7OL5Fj/GiTTjmuEm9uBxeQz6u2zl843DnDw8vwfZY+FQBDBRYic9\n+F1xPYRCQG6Hd9x9twIDAQAB\n-----END PUBLIC KEY-----\n";
	

	char *ptr_en = encrypt_with_key(pBuffer, key);
	if (ptr_en == NULL) {
		::MessageBoxW(NULL, (LPCWSTR)L"加密信息为null", (LPCWSTR)L"加密信息", MB_ICONWARNING);
	}
	FILE *file1;
    if((file1 = fopen("D:\\home\\workspace1\\tst_edit\\encrypt-text.txt", "w")) == NULL) 
	{
        perror("error to open key from file");
		
        return NULL;
    }
	fprintf(file1,"%s", ptr_en);
	fclose(file1);


	//CString strResult3;
	//strResult3.Format(_T("%s"), ptr_en);
	//BSTR bstr = strResult3.AllocSysString();
	//::MessageBoxW(NULL, bstr, (LPCWSTR)L"加密-密文", MB_ICONWARNING);
	CString strResult3(ptr_en);
	LPWSTR enStr=new wchar_t[strResult3.GetLength()+1]; 
	wcscpy(enStr, T2W((LPTSTR) strResult3.AllocSysString()));
	::MessageBoxW(NULL, enStr, (LPCWSTR)L"加密-密文", MB_ICONWARNING);
	

	char* pk = "-----BEGIN RSA PRIVATE KEY-----\nMIICXgIBAAKBgQDAiZZSPEZHVnlnx6pRKEZdBP99GKaMikoABg2dLsMUk/zOxXLT\npduuZNLxBicXLR9z7CCjUPfghFcclrWR5+hyZoAV0xOCd6YF9I9I7OL5Fj/GiTTj\nmuEm9uBxeQz6u2zl843DnDw8vwfZY+FQBDBRYic9+F1xPYRCQG6Hd9x9twIDAQAB\nAoGBAL9Cbc73DSEkZ6mOEERaa7tPkbRk3l1RqjznxnJT13oDn+iO/4f7hIRyp5DB\n+ebt7gark6hocDPZgudlVqy/4Ii6x6cYtW0hObcLig0+UrQJJG8huLj4Fp0mzcIf\nxAh90Bs0GeVEUp3K0FyMUL0+MT+VBnTHOnmizTIqCIJK3Z+RAkEA5AUqcyjneRsP\nRHq9k1IKK9RjiHKbV1fyF6TZGN+cE9pF8Zlbnv/3PFjBL8j+m6qSAjVD7ftaLprO\na5cQX/aW/QJBANgpy/hQcc4P7dXRbMddILsGkc/1sr078KQkgk8+gXK2aamdi1z8\nt6bCGQ7d6te1wPxnLvBgv+vpSJRJWdbt18MCQQCLG5OwOe4tdhK0ZmUtcUl/P82R\nOsoGWUL6pblEcXbYrbsqD7NTpzj/+e2x519dPIxjCHfuwf9cm1j/TmPRB7FJAkAR\n4+OtuXqxwz+74olONrbuw6xtubgBUWSpMRxX0qSECfTUxOUz3PaWJppMULGPCMvg\nF+oamudHbxdCro9w6l5hAkEAmzgmluE0SmFMvJ1jujflVGvIUKtwqQvyNg/qcCSj\nqhu+VTIyp//q/fwW5+U2JoVkx+IaIqzS8g0aDQHS0WPd+Q==\n-----END RSA PRIVATE KEY-----";
	
	char* ptr_de = decrypt_with_key(ptr_en, pk);
	FILE *file;
    if((file = fopen("D:\\home\\workspace1\\tst_edit\\decrypt-plain.txt", "w")) == NULL) 
	{
        perror("error to open key from file");
		
        return NULL;
    }
	fprintf(file,"%s", ptr_de);
	fclose(file);

	CString strResult4(ptr_de);
	LPWSTR deStr=new wchar_t[strResult4.GetLength()+1]; 
	wcscpy(deStr, T2W((LPTSTR) strResult4.AllocSysString()));
	::MessageBoxW(NULL, deStr, (LPCWSTR)L"解密-明文", MB_ICONWARNING);
	
	return strResult4.AllocSysString();
}

BSTR CTSTPasswordCtrl::_Encrypt(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: 在此添加调度处理程序代码

	return strResult.AllocSysString();
}

BSTR CTSTPasswordCtrl::_Decrypt(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: 在此添加调度处理程序代码

	return strResult.AllocSysString();
}

void CTSTPasswordCtrl::OnpasswordChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码

	SetModifiedFlag();
}


BSTR CTSTPasswordCtrl::_GetPassword(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//CString strResult;

	// TODO: 在此添加调度处理程序代码
	USES_CONVERSION;

	LPWSTR pwStr=new wchar_t[this->m_password.GetLength()+1]; 
	wcscpy(pwStr, T2W((LPTSTR) this->m_password.AllocSysString()));
	::MessageBoxW(NULL, pwStr, (LPCWSTR)L"m_password", MB_ICONWARNING);

	return this->m_password.AllocSysString();
}


void CTSTPasswordCtrl::OnVersionChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码

	SetModifiedFlag();
}


BSTR CTSTPasswordCtrl::_GetVersion(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//CString strResult;

	// TODO: 在此添加调度处理程序代码

	return this->m_Version.AllocSysString();
}


