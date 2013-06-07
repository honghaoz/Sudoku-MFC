// shudu.h : main header file for the SHUDU application
//

#if !defined(AFX_SHUDU_H__C60F2C75_C91D_4910_B76C_1799BA097B50__INCLUDED_)
#define AFX_SHUDU_H__C60F2C75_C91D_4910_B76C_1799BA097B50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShuduApp:
// See shudu.cpp for the implementation of this class
//

class CShuduApp : public CWinApp
{
public:
	CShuduApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShuduApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShuduApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUDU_H__C60F2C75_C91D_4910_B76C_1799BA097B50__INCLUDED_)
