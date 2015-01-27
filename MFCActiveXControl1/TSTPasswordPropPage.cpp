// TSTPasswordPropPage.cpp : CTSTPasswordPropPage 属性页类的实现。

#include "stdafx.h"
#include "MFCActiveXControl1.h"
#include "TSTPasswordPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CTSTPasswordPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CTSTPasswordPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CTSTPasswordPropPage, "MFCACTIVEXCONT.TSTPasswordPropPage.1",
	0xe90b69f2, 0x6771, 0x4139, 0xa4, 0x3c, 0xe7, 0x6b, 0xff, 0x87, 0x18, 0x23)

// CTSTPasswordPropPage::CTSTPasswordPropPageFactory::UpdateRegistry -
// 添加或移除 CTSTPasswordPropPage 的系统注册表项

BOOL CTSTPasswordPropPage::CTSTPasswordPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCACTIVEXCONTROL1_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CTSTPasswordPropPage::CTSTPasswordPropPage - 构造函数

CTSTPasswordPropPage::CTSTPasswordPropPage() :
	COlePropertyPage(IDD, IDS_MFCACTIVEXCONTROL1_PPG_CAPTION)
{
}

// CTSTPasswordPropPage::DoDataExchange - 在页和属性间移动数据

void CTSTPasswordPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CTSTPasswordPropPage 消息处理程序
