// TSTPasswordCtrl.h
// <p>
// CTSTPasswordCtrl ActiveX �ؼ����������
// 
// @author hua dan
// @version 1.0
#pragma once

#include <windows.h>
#include "CPasswordEdit.h"




// CTSTPasswordCtrl : �й�ʵ�ֵ���Ϣ������� TSTPasswordCtrl.cpp��

class CTSTPasswordCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTSTPasswordCtrl)

private: 
	// CEdit *edit;
	CPasswordEdit *passwordEdit;

	
// ���캯��
public:
	CTSTPasswordCtrl();

// ��д
public:
	//HHOOK getHHook();
	void initPasswordEditCtrl();

	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void InitializeIIDs(const IID* piidPrimary, const IID* piidEvents);
	void SetInitialSize(int cx, int cy);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnWindowlessMessage( UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult );

	virtual LRESULT WindowProc(
		UINT message,
		WPARAM wParam,
		LPARAM lParam 
	);

	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CTSTPasswordCtrl();

	DECLARE_OLECREATE_EX(CTSTPasswordCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CTSTPasswordCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTSTPasswordCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CTSTPasswordCtrl)		// �������ƺ�����״̬

	// ����ؼ�֧��
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispid_Decrypt = 9L,
		dispid_Encrypt = 8L,
		eventidEv_Init = 1L,
		dispid_GetVersion = 7L,
		dispidVersion = 6,
		dispid_GetPassword = 5L,
		dispidvalue = 4L,
		dispidpassword = 3,
		dispidencode = 2L,
		dispidAddFun = 1L
	};
protected:
	LONG AddFun(LONG num1, LONG num2);

	BSTR encode(LPCTSTR password);
	void OnpasswordChanged(void);
	CString m_password;
	BSTR value(void);
	BSTR _GetPassword(void);
	void OnVersionChanged(void);
	CString m_Version;
	BSTR _GetVersion(void);

	void Ev_Init(LONG Status)
	{
		FireEvent(eventidEv_Init, EVENT_PARAM(VTS_I4), Status);
	}
	BSTR _Encrypt(void);
	BSTR _Decrypt(void);
};

LRESULT FAR PASCAL GetMsgProc(int code, WPARAM wParam, LPARAM lParam);

