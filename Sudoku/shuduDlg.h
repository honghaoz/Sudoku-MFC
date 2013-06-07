// shuduDlg.h : header file
//

#if !defined(AFX_SHUDUDLG_H__20E6459E_ADEA_45BF_9F53_BDFAA86636A7__INCLUDED_)
#define AFX_SHUDUDLG_H__20E6459E_ADEA_45BF_9F53_BDFAA86636A7__INCLUDED_

#include "CButton.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShuduDlg dialog

class CShuduDlg : public CDialog
{
// Construction
public:
	void tips(int,int);
	CShuduDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShuduDlg)
	enum { IDD = IDD_SHUDU_DIALOG };
	CCButton	m_ChooseMusic;
	CCButton	m_MusicSwitch;
	CCButton	m_SoundSwitch;
	CSliderCtrl	m_vol;
	CEdit	m_sound;
	CEdit	m_music;
	CEdit	m_tipsOnOff;
	CEdit	m_tips9;
	CEdit	m_tips8;
	CEdit	m_tips7;
	CEdit	m_tips5;
	CEdit	m_tips6;
	CEdit	m_tips4;
	CEdit	m_tips3;
	CEdit	m_tips2;
	CEdit	m_tips1;
	CEdit	m_z99;
	CEdit	m_z88;
	CEdit	m_z77;
	CEdit	m_z66;
	CEdit	m_z55;
	CEdit	m_z44;
	CEdit	m_z33;
	CEdit	m_z22;
	CEdit	m_z11;
	CEdit	m_y99;
	CEdit	m_y88;
	CEdit	m_y77;
	CEdit	m_y66;
	CEdit	m_y55;
	CEdit	m_y44;
	CEdit	m_y33;
	CEdit	m_y22;
	CEdit	m_y11;
	CEdit	m_x99;
	CEdit	m_x88;
	CEdit	m_x77;
	CEdit	m_x66;
	CEdit	m_x55;
	CEdit	m_x44;
	CEdit	m_x33;
	CEdit	m_x22;
	CEdit	m_x11;
	CEdit	m_f99;
	CEdit	m_f88;
	CEdit	m_f77;
	CEdit	m_f66;
	CEdit	m_f55;
	CEdit	m_f44;
	CEdit	m_f33;
	CEdit	m_f22;
	CEdit	m_f11;
	CEdit	m_e99;
	CEdit	m_e88;
	CEdit	m_e77;
	CEdit	m_e66;
	CEdit	m_e55;
	CEdit	m_e44;
	CEdit	m_e33;
	CEdit	m_e22;
	CEdit	m_e11;
	CEdit	m_d99;
	CEdit	m_d88;
	CEdit	m_d77;
	CEdit	m_d66;
	CEdit	m_d55;
	CEdit	m_d44;
	CEdit	m_d33;
	CEdit	m_d22;
	CEdit	m_d11;
	CEdit	m_c99;
	CEdit	m_c88;
	CEdit	m_c77;
	CEdit	m_c66;
	CEdit	m_c55;
	CEdit	m_c44;
	CEdit	m_c33;
	CEdit	m_c22;
	CEdit	m_c11;
	CEdit	m_b99;
	CEdit	m_b88;
	CEdit	m_b77;
	CEdit	m_b66;
	CEdit	m_b55;
	CEdit	m_b44;
	CEdit	m_b33;
	CEdit	m_b22;
	CEdit	m_b11;
	CEdit	m_a99;
	CEdit	m_a88;
	CEdit	m_a77;
	CEdit	m_a66;
	CEdit	m_a55;
	CEdit	m_a44;
	CEdit	m_a33;
	CEdit	m_a22;
	CEdit	m_a11;
	CEdit	m_edtTime;
	int		m_dif;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShuduDlg)
	public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShuduDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONabout();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBUTTONnew();
	afx_msg void Ondif();
	afx_msg void Ondif2();
	afx_msg void Ondif3();
	afx_msg void Ondif4();
	afx_msg void OnChangeEDITa1();
	afx_msg void OnBUTTONshow();
	afx_msg void OnSetfocusEDITa1();
	afx_msg void OnChangeEDITa2();
	afx_msg void OnSetfocusEDITa2();
	afx_msg void OnChangeEDITa3();
	afx_msg void OnSetfocusEDITa3();
	afx_msg void OnChangeEDITa4();
	afx_msg void OnSetfocusEDITa4();
	afx_msg void OnChangeEDITa5();
	afx_msg void OnSetfocusEDITa5();
	afx_msg void OnChangeEDITa6();
	afx_msg void OnSetfocusEDITa6();
	afx_msg void OnChangeEDITa7();
	afx_msg void OnSetfocusEDITa7();
	afx_msg void OnChangeEDITa8();
	afx_msg void OnSetfocusEDITa8();
	afx_msg void OnChangeEDITa9();
	afx_msg void OnSetfocusEDITa9();
	afx_msg void OnChangeEDITb1();
	afx_msg void OnSetfocusEDITb1();
	afx_msg void OnChangeEDITb2();
	afx_msg void OnSetfocusEDITb2();
	afx_msg void OnChangeEDITb3();
	afx_msg void OnSetfocusEDITb3();
	afx_msg void OnChangeEDITb4();
	afx_msg void OnSetfocusEDITb4();
	afx_msg void OnChangeEDITb5();
	afx_msg void OnSetfocusEDITb5();
	afx_msg void OnChangeEDITb6();
	afx_msg void OnSetfocusEDITb6();
	afx_msg void OnChangeEDITb7();
	afx_msg void OnSetfocusEDITb7();
	afx_msg void OnChangeEDITb8();
	afx_msg void OnSetfocusEDITb8();
	afx_msg void OnChangeEDITb9();
	afx_msg void OnSetfocusEDITb9();
	afx_msg void OnChangeEDITc1();
	afx_msg void OnChangeEDITc2();
	afx_msg void OnChangeEDITc3();
	afx_msg void OnChangeEDITc4();
	afx_msg void OnChangeEDITc5();
	afx_msg void OnChangeEDITc6();
	afx_msg void OnChangeEDITc7();
	afx_msg void OnChangeEDITc8();
	afx_msg void OnChangeEDITc9();
	afx_msg void OnChangeEDITd1();
	afx_msg void OnChangeEDITd2();
	afx_msg void OnChangeEDITd3();
	afx_msg void OnChangeEDITd4();
	afx_msg void OnChangeEDITd5();
	afx_msg void OnChangeEDITd6();
	afx_msg void OnChangeEDITd7();
	afx_msg void OnChangeEDITd8();
	afx_msg void OnChangeEDITd9();
	afx_msg void OnChangeEDITe1();
	afx_msg void OnChangeEDITe2();
	afx_msg void OnChangeEDITe3();
	afx_msg void OnChangeEDITe4();
	afx_msg void OnChangeEDITe5();
	afx_msg void OnChangeEDITe6();
	afx_msg void OnChangeEDITe7();
	afx_msg void OnChangeEDITe8();
	afx_msg void OnChangeEDITe9();
	afx_msg void OnChangeEDITf1();
	afx_msg void OnChangeEDITf2();
	afx_msg void OnChangeEDITf3();
	afx_msg void OnChangeEDITf4();
	afx_msg void OnChangeEDITf5();
	afx_msg void OnChangeEDITf6();
	afx_msg void OnChangeEDITf7();
	afx_msg void OnChangeEDITf8();
	afx_msg void OnChangeEDITf9();
	afx_msg void OnChangeEDITx1();
	afx_msg void OnChangeEDITx2();
	afx_msg void OnChangeEDITx3();
	afx_msg void OnChangeEDITx4();
	afx_msg void OnChangeEDITx5();
	afx_msg void OnChangeEDITx6();
	afx_msg void OnChangeEDITx7();
	afx_msg void OnChangeEDITx8();
	afx_msg void OnChangeEDITx9();
	afx_msg void OnChangeEDITy1();
	afx_msg void OnChangeEDITy2();
	afx_msg void OnChangeEDITy3();
	afx_msg void OnChangeEDITy4();
	afx_msg void OnChangeEDITy5();
	afx_msg void OnChangeEDITy6();
	afx_msg void OnChangeEDITy7();
	afx_msg void OnChangeEDITy8();
	afx_msg void OnChangeEDITy9();
	afx_msg void OnChangeEDITz1();
	afx_msg void OnChangeEDITz2();
	afx_msg void OnChangeEDITz3();
	afx_msg void OnChangeEDITz4();
	afx_msg void OnChangeEDITz5();
	afx_msg void OnChangeEDITz6();
	afx_msg void OnChangeEDITz7();
	afx_msg void OnChangeEDITz8();
	afx_msg void OnChangeEDITz9();
	afx_msg void OnSetfocusEDITc1();
	afx_msg void OnSetfocusEDITc2();
	afx_msg void OnSetfocusEDITc3();
	afx_msg void OnSetfocusEDITc4();
	afx_msg void OnSetfocusEDITc5();
	afx_msg void OnSetfocusEDITc6();
	afx_msg void OnSetfocusEDITc7();
	afx_msg void OnSetfocusEDITc8();
	afx_msg void OnSetfocusEDITc9();
	afx_msg void OnSetfocusEDITd1();
	afx_msg void OnSetfocusEDITd2();
	afx_msg void OnSetfocusEDITd3();
	afx_msg void OnSetfocusEDITd4();
	afx_msg void OnSetfocusEDITd5();
	afx_msg void OnSetfocusEDITd6();
	afx_msg void OnSetfocusEDITd7();
	afx_msg void OnSetfocusEDITd8();
	afx_msg void OnSetfocusEDITd9();
	afx_msg void OnSetfocusEDITe1();
	afx_msg void OnSetfocusEDITe2();
	afx_msg void OnSetfocusEDITe3();
	afx_msg void OnSetfocusEDITe4();
	afx_msg void OnSetfocusEDITe5();
	afx_msg void OnSetfocusEDITe6();
	afx_msg void OnSetfocusEDITe7();
	afx_msg void OnSetfocusEDITe8();
	afx_msg void OnSetfocusEDITe9();
	afx_msg void OnSetfocusEDITf1();
	afx_msg void OnSetfocusEDITf2();
	afx_msg void OnSetfocusEDITf3();
	afx_msg void OnSetfocusEDITf4();
	afx_msg void OnSetfocusEDITf5();
	afx_msg void OnSetfocusEDITf6();
	afx_msg void OnSetfocusEDITf7();
	afx_msg void OnSetfocusEDITf8();
	afx_msg void OnSetfocusEDITf9();
	afx_msg void OnSetfocusEDITx1();
	afx_msg void OnSetfocusEDITx2();
	afx_msg void OnSetfocusEDITx3();
	afx_msg void OnSetfocusEDITx4();
	afx_msg void OnSetfocusEDITx5();
	afx_msg void OnSetfocusEDITx6();
	afx_msg void OnSetfocusEDITx7();
	afx_msg void OnSetfocusEDITx8();
	afx_msg void OnSetfocusEDITx9();
	afx_msg void OnSetfocusEDITy1();
	afx_msg void OnSetfocusEDITy2();
	afx_msg void OnSetfocusEDITy3();
	afx_msg void OnSetfocusEDITy4();
	afx_msg void OnSetfocusEDITy5();
	afx_msg void OnSetfocusEDITy6();
	afx_msg void OnSetfocusEDITy7();
	afx_msg void OnSetfocusEDITy8();
	afx_msg void OnSetfocusEDITy9();
	afx_msg void OnSetfocusEDITz1();
	afx_msg void OnSetfocusEDITz2();
	afx_msg void OnSetfocusEDITz3();
	afx_msg void OnSetfocusEDITz4();
	afx_msg void OnSetfocusEDITz5();
	afx_msg void OnSetfocusEDITz6();
	afx_msg void OnSetfocusEDITz7();
	afx_msg void OnSetfocusEDITz8();
	afx_msg void OnSetfocusEDITz9();
	afx_msg void OnBUTTONsave();
	afx_msg void OnBUTTONclear();
	afx_msg void OnBUTTON_tipsSwitch();
	afx_msg void OnBUTTONread();
	virtual void OnOK();
	afx_msg void OnBUTTONchooseMusic();
	afx_msg void OnBUTTONmusicSwitch();
	afx_msg void OnBUTTONsoundSwitch();
	afx_msg void OnCustomdrawSLIDERsound(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void generate(int,int);
	int part(int,int);
	void show_title(int,int,CEdit &);
	void setReadOnly();
	void show(int,int,CEdit &);
	void clear(CEdit &);
	void read(int,int,CEdit &);
	void RealAll();
	void check(int,int,CEdit &);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUDUDLG_H__20E6459E_ADEA_45BF_9F53_BDFAA86636A7__INCLUDED_)
