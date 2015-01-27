// 
// @author hua dan
// @version  1.0

#include "stdafx.h"
#include "CPasswordEdit.h"

void CPasswordEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	/*
	// LPWSTR wChar=NULL;
	if (::IsCharAlpha((WCHAR) nChar)) 
	{
		nChar = (UINT) ::CharUpper(LPWSTR(nChar));
	}
	*/
	::MessageBoxW(NULL, LPWSTR(nChar), (LPCWSTR)L" ‰»ÎÃ· æ", MB_ICONWARNING);
	DefWindowProc(WM_CHAR, nChar , MAKELPARAM (nRepCnt, nFlags ));
}