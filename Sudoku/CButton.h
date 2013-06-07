#if !defined(AFX_CBUTTON_H__E6DE31CC_13D5_4866_B132_ADE1BE14CDDF__INCLUDED_)
#define AFX_CBUTTON_H__E6DE31CC_13D5_4866_B132_ADE1BE14CDDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCButton window

class CCButton : public CButton
{
// Construction
public:
	CCButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCButton();
	CRgn   m_rgn;
	CPoint m_ptCentre;
	CPoint m_ptLeft;
	CPoint m_ptRight;
	int    m_nRadius;
	BOOL   m_bDrawDashedFocusCircle;
	BOOL   m_bStretch;


	// Generated message map functions
protected:
	//{{AFX_MSG(CCButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBUTTON_H__E6DE31CC_13D5_4866_B132_ADE1BE14CDDF__INCLUDED_)
