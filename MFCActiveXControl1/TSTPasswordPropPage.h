#pragma once

// TSTPasswordPropPage.h : CTSTPasswordPropPage ����ҳ���������


// CTSTPasswordPropPage : �й�ʵ�ֵ���Ϣ������� TSTPasswordPropPage.cpp��

class CTSTPasswordPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTSTPasswordPropPage)
	DECLARE_OLECREATE_EX(CTSTPasswordPropPage)

// ���캯��
public:
	CTSTPasswordPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MFCACTIVEXCONTROL1 };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

