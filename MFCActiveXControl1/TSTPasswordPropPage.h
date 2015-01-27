#pragma once

// TSTPasswordPropPage.h : CTSTPasswordPropPage 属性页类的声明。


// CTSTPasswordPropPage : 有关实现的信息，请参阅 TSTPasswordPropPage.cpp。

class CTSTPasswordPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTSTPasswordPropPage)
	DECLARE_OLECREATE_EX(CTSTPasswordPropPage)

// 构造函数
public:
	CTSTPasswordPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MFCACTIVEXCONTROL1 };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

