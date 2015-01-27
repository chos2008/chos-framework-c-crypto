// TSTPasswordCtrl.h
// <p>
// CTSTPasswordCtrl ActiveX 控件类的声明。
// 
// @author hua dan
// @version 1.0
#pragma once

#include <windows.h>
#include "CPasswordEdit.h"




// CTSTPasswordCtrl : 有关实现的信息，请参阅 TSTPasswordCtrl.cpp。

class CTSTPasswordCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTSTPasswordCtrl)

private: 
	// CEdit *edit;
	CPasswordEdit *passwordEdit;

	
// 构造函数
public:
	CTSTPasswordCtrl();

// 重写
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

// 实现
protected:
	~CTSTPasswordCtrl();

	DECLARE_OLECREATE_EX(CTSTPasswordCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CTSTPasswordCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTSTPasswordCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CTSTPasswordCtrl)		// 类型名称和杂项状态

	// 子类控件支持
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
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

