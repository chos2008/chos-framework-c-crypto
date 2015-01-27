// edit control for password
// 
// @author hua dan
// @version 1.0  

#include "stdafx.h"
//#include <windows.h>

#if ! defined C_PASSWORD_EDIT
#define C_PASSWORD_EDIT
class CPasswordEdit : public CEdit 
{
public:
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif;