// shuduDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shudu.h"
#include "shuduDlg.h"
#include "memory.h"
#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <stdio.h>
#include "vfw.h"
#include <windows.h> 
#pragma comment(lib,"Winmm.lib") 
#pragma comment(lib,"vfw32.lib")
//#include <string> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
DWORD k=::GetTickCount();
DWORD l;
int condition=0;//计时器条件为0
int condition_show=0;//显示解答 避免死循环而设置
int tips_switch=2;
int tips_switchs=2;//提示开关控制

int sound_new=0;//防止新建游戏与check的声音冲突而设置
int sound=2;//音效开关
int sound_switch=2;
int music=3;//音乐开关
int music_switch=2;
//int music_one=0;//防止onTimer中重复执行
//int music_two=0;

//int sound_one=0;
//int sound_two=0;

int clear_s=0;//防止清空题目声音无法播放
int read_noAnswer=0;//用来  读取外界题目 无答案的情况
CString vol;//音量大小变量

/*
	CString m_a1,m_a2,m_a3,m_a4,m_a5,m_a6,m_a7,m_a8,m_a9;
	CString m_b1,m_b2,m_b3,m_b4,m_b5,m_b6,m_b7,m_b8,m_b9;
	CString m_c1,m_c2,m_c3,m_c4,m_c5,m_c6,m_c7,m_c8,m_c9;
	CString m_d1,m_d2,m_d3,m_d4,m_d5,m_d6,m_d7,m_d8,m_d9;
	CString m_e1,m_e2,m_e3,m_e4,m_e5,m_e6,m_e7,m_e8,m_e9;
	CString m_f1,m_f2,m_f3,m_f4,m_f5,m_f6,m_f7,m_f8,m_f9;
	CString m_x1,m_x2,m_x3,m_x4,m_x5,m_x6,m_x7,m_x8,m_x9;
	CString m_y1,m_y2,m_y3,m_y4,m_y5,m_y6,m_y7,m_y8,m_y9;
	CString m_z1,m_z2,m_z3,m_z4,m_z5,m_z6,m_z7,m_z8,m_z9;//定义CString变量，读取编辑框中的数据

*/

CString FilePathName_choose=".\\Sudoku.mp3";
CString FilePathName_music=".\\Sudoku.mp3";
CString FileExtName;



//Dim V;//As Long;
//mciSendString "status movie volume", V, 0, 0 //V是获取的音量大小值。
//V = 50;
//mciSendString "setaudio movie volume to " & V, &0, 0, 0 //V是设置的音量值


	int sd[9][9]={0};//定义int数独数组
	int sd_title[9][9]={0};//定义int数独题目数组

	int sd_read[9][9]={0};

bool row[9][10];
bool col[9][10];
bool squ[9][10];
bool found;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShuduDlg dialog

CShuduDlg::CShuduDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShuduDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShuduDlg)
	m_dif = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShuduDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShuduDlg)
	DDX_Control(pDX, IDC_BUTTON_chooseMusic, m_ChooseMusic);
	DDX_Control(pDX, IDC_BUTTON_musicSwitch, m_MusicSwitch);
	DDX_Control(pDX, IDC_BUTTON_soundSwitch, m_SoundSwitch);
	DDX_Control(pDX, IDC_SLIDER_sound, m_vol);
	DDX_Control(pDX, IDC_EDIT_sound, m_sound);
	DDX_Control(pDX, IDC_EDIT_music, m_music);
	DDX_Control(pDX, IDC_EDIT_tips_OnOff, m_tipsOnOff);
	DDX_Control(pDX, IDC_EDIT_tips9, m_tips9);
	DDX_Control(pDX, IDC_EDIT_tips8, m_tips8);
	DDX_Control(pDX, IDC_EDIT_tips7, m_tips7);
	DDX_Control(pDX, IDC_EDIT_tips5, m_tips5);
	DDX_Control(pDX, IDC_EDIT_tips6, m_tips6);
	DDX_Control(pDX, IDC_EDIT_tips4, m_tips4);
	DDX_Control(pDX, IDC_EDIT_tips3, m_tips3);
	DDX_Control(pDX, IDC_EDIT_tips2, m_tips2);
	DDX_Control(pDX, IDC_EDIT_tips1, m_tips1);
	DDX_Control(pDX, IDC_EDIT_z9, m_z99);
	DDX_Control(pDX, IDC_EDIT_z8, m_z88);
	DDX_Control(pDX, IDC_EDIT_z7, m_z77);
	DDX_Control(pDX, IDC_EDIT_z6, m_z66);
	DDX_Control(pDX, IDC_EDIT_z5, m_z55);
	DDX_Control(pDX, IDC_EDIT_z4, m_z44);
	DDX_Control(pDX, IDC_EDIT_z3, m_z33);
	DDX_Control(pDX, IDC_EDIT_z2, m_z22);
	DDX_Control(pDX, IDC_EDIT_z1, m_z11);
	DDX_Control(pDX, IDC_EDIT_y9, m_y99);
	DDX_Control(pDX, IDC_EDIT_y8, m_y88);
	DDX_Control(pDX, IDC_EDIT_y7, m_y77);
	DDX_Control(pDX, IDC_EDIT_y6, m_y66);
	DDX_Control(pDX, IDC_EDIT_y5, m_y55);
	DDX_Control(pDX, IDC_EDIT_y4, m_y44);
	DDX_Control(pDX, IDC_EDIT_y3, m_y33);
	DDX_Control(pDX, IDC_EDIT_y2, m_y22);
	DDX_Control(pDX, IDC_EDIT_y1, m_y11);
	DDX_Control(pDX, IDC_EDIT_x9, m_x99);
	DDX_Control(pDX, IDC_EDIT_x8, m_x88);
	DDX_Control(pDX, IDC_EDIT_x7, m_x77);
	DDX_Control(pDX, IDC_EDIT_x6, m_x66);
	DDX_Control(pDX, IDC_EDIT_x5, m_x55);
	DDX_Control(pDX, IDC_EDIT_x4, m_x44);
	DDX_Control(pDX, IDC_EDIT_x3, m_x33);
	DDX_Control(pDX, IDC_EDIT_x2, m_x22);
	DDX_Control(pDX, IDC_EDIT_x1, m_x11);
	DDX_Control(pDX, IDC_EDIT_f9, m_f99);
	DDX_Control(pDX, IDC_EDIT_f8, m_f88);
	DDX_Control(pDX, IDC_EDIT_f7, m_f77);
	DDX_Control(pDX, IDC_EDIT_f6, m_f66);
	DDX_Control(pDX, IDC_EDIT_f5, m_f55);
	DDX_Control(pDX, IDC_EDIT_f4, m_f44);
	DDX_Control(pDX, IDC_EDIT_f3, m_f33);
	DDX_Control(pDX, IDC_EDIT_f2, m_f22);
	DDX_Control(pDX, IDC_EDIT_f1, m_f11);
	DDX_Control(pDX, IDC_EDIT_e9, m_e99);
	DDX_Control(pDX, IDC_EDIT_e8, m_e88);
	DDX_Control(pDX, IDC_EDIT_e7, m_e77);
	DDX_Control(pDX, IDC_EDIT_e6, m_e66);
	DDX_Control(pDX, IDC_EDIT_e5, m_e55);
	DDX_Control(pDX, IDC_EDIT_e4, m_e44);
	DDX_Control(pDX, IDC_EDIT_e3, m_e33);
	DDX_Control(pDX, IDC_EDIT_e2, m_e22);
	DDX_Control(pDX, IDC_EDIT_e1, m_e11);
	DDX_Control(pDX, IDC_EDIT_d9, m_d99);
	DDX_Control(pDX, IDC_EDIT_d8, m_d88);
	DDX_Control(pDX, IDC_EDIT_d7, m_d77);
	DDX_Control(pDX, IDC_EDIT_d6, m_d66);
	DDX_Control(pDX, IDC_EDIT_d5, m_d55);
	DDX_Control(pDX, IDC_EDIT_d4, m_d44);
	DDX_Control(pDX, IDC_EDIT_d3, m_d33);
	DDX_Control(pDX, IDC_EDIT_d2, m_d22);
	DDX_Control(pDX, IDC_EDIT_d1, m_d11);
	DDX_Control(pDX, IDC_EDIT_c9, m_c99);
	DDX_Control(pDX, IDC_EDIT_c8, m_c88);
	DDX_Control(pDX, IDC_EDIT_c7, m_c77);
	DDX_Control(pDX, IDC_EDIT_c6, m_c66);
	DDX_Control(pDX, IDC_EDIT_c5, m_c55);
	DDX_Control(pDX, IDC_EDIT_c4, m_c44);
	DDX_Control(pDX, IDC_EDIT_c3, m_c33);
	DDX_Control(pDX, IDC_EDIT_c2, m_c22);
	DDX_Control(pDX, IDC_EDIT_c1, m_c11);
	DDX_Control(pDX, IDC_EDIT_b9, m_b99);
	DDX_Control(pDX, IDC_EDIT_b8, m_b88);
	DDX_Control(pDX, IDC_EDIT_b7, m_b77);
	DDX_Control(pDX, IDC_EDIT_b6, m_b66);
	DDX_Control(pDX, IDC_EDIT_b5, m_b55);
	DDX_Control(pDX, IDC_EDIT_b4, m_b44);
	DDX_Control(pDX, IDC_EDIT_b3, m_b33);
	DDX_Control(pDX, IDC_EDIT_b2, m_b22);
	DDX_Control(pDX, IDC_EDIT_b1, m_b11);
	DDX_Control(pDX, IDC_EDIT_a9, m_a99);
	DDX_Control(pDX, IDC_EDIT_a8, m_a88);
	DDX_Control(pDX, IDC_EDIT_a7, m_a77);
	DDX_Control(pDX, IDC_EDIT_a6, m_a66);
	DDX_Control(pDX, IDC_EDIT_a5, m_a55);
	DDX_Control(pDX, IDC_EDIT_a4, m_a44);
	DDX_Control(pDX, IDC_EDIT_a3, m_a33);
	DDX_Control(pDX, IDC_EDIT_a2, m_a22);
	DDX_Control(pDX, IDC_EDIT_a1, m_a11);
	DDX_Control(pDX, IDC_EDIT_time, m_edtTime);
	DDX_Radio(pDX, IDC_dif, m_dif);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShuduDlg, CDialog)
	//{{AFX_MSG_MAP(CShuduDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_about, OnBUTTONabout)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_new, OnBUTTONnew)
	ON_BN_CLICKED(IDC_dif, Ondif)
	ON_BN_CLICKED(IDC_dif2, Ondif2)
	ON_BN_CLICKED(IDC_dif3, Ondif3)
	ON_BN_CLICKED(IDC_dif4, Ondif4)
	ON_EN_CHANGE(IDC_EDIT_a1, OnChangeEDITa1)
	ON_BN_CLICKED(IDC_BUTTON_show, OnBUTTONshow)
	ON_EN_SETFOCUS(IDC_EDIT_a1, OnSetfocusEDITa1)
	ON_EN_CHANGE(IDC_EDIT_a2, OnChangeEDITa2)
	ON_EN_SETFOCUS(IDC_EDIT_a2, OnSetfocusEDITa2)
	ON_EN_CHANGE(IDC_EDIT_a3, OnChangeEDITa3)
	ON_EN_SETFOCUS(IDC_EDIT_a3, OnSetfocusEDITa3)
	ON_EN_CHANGE(IDC_EDIT_a4, OnChangeEDITa4)
	ON_EN_SETFOCUS(IDC_EDIT_a4, OnSetfocusEDITa4)
	ON_EN_CHANGE(IDC_EDIT_a5, OnChangeEDITa5)
	ON_EN_SETFOCUS(IDC_EDIT_a5, OnSetfocusEDITa5)
	ON_EN_CHANGE(IDC_EDIT_a6, OnChangeEDITa6)
	ON_EN_SETFOCUS(IDC_EDIT_a6, OnSetfocusEDITa6)
	ON_EN_CHANGE(IDC_EDIT_a7, OnChangeEDITa7)
	ON_EN_SETFOCUS(IDC_EDIT_a7, OnSetfocusEDITa7)
	ON_EN_CHANGE(IDC_EDIT_a8, OnChangeEDITa8)
	ON_EN_SETFOCUS(IDC_EDIT_a8, OnSetfocusEDITa8)
	ON_EN_CHANGE(IDC_EDIT_a9, OnChangeEDITa9)
	ON_EN_SETFOCUS(IDC_EDIT_a9, OnSetfocusEDITa9)
	ON_EN_CHANGE(IDC_EDIT_b1, OnChangeEDITb1)
	ON_EN_SETFOCUS(IDC_EDIT_b1, OnSetfocusEDITb1)
	ON_EN_CHANGE(IDC_EDIT_b2, OnChangeEDITb2)
	ON_EN_SETFOCUS(IDC_EDIT_b2, OnSetfocusEDITb2)
	ON_EN_CHANGE(IDC_EDIT_b3, OnChangeEDITb3)
	ON_EN_SETFOCUS(IDC_EDIT_b3, OnSetfocusEDITb3)
	ON_EN_CHANGE(IDC_EDIT_b4, OnChangeEDITb4)
	ON_EN_SETFOCUS(IDC_EDIT_b4, OnSetfocusEDITb4)
	ON_EN_CHANGE(IDC_EDIT_b5, OnChangeEDITb5)
	ON_EN_SETFOCUS(IDC_EDIT_b5, OnSetfocusEDITb5)
	ON_EN_CHANGE(IDC_EDIT_b6, OnChangeEDITb6)
	ON_EN_SETFOCUS(IDC_EDIT_b6, OnSetfocusEDITb6)
	ON_EN_CHANGE(IDC_EDIT_b7, OnChangeEDITb7)
	ON_EN_SETFOCUS(IDC_EDIT_b7, OnSetfocusEDITb7)
	ON_EN_CHANGE(IDC_EDIT_b8, OnChangeEDITb8)
	ON_EN_SETFOCUS(IDC_EDIT_b8, OnSetfocusEDITb8)
	ON_EN_CHANGE(IDC_EDIT_b9, OnChangeEDITb9)
	ON_EN_SETFOCUS(IDC_EDIT_b9, OnSetfocusEDITb9)
	ON_EN_CHANGE(IDC_EDIT_c1, OnChangeEDITc1)
	ON_EN_CHANGE(IDC_EDIT_c2, OnChangeEDITc2)
	ON_EN_CHANGE(IDC_EDIT_c3, OnChangeEDITc3)
	ON_EN_CHANGE(IDC_EDIT_c4, OnChangeEDITc4)
	ON_EN_CHANGE(IDC_EDIT_c5, OnChangeEDITc5)
	ON_EN_CHANGE(IDC_EDIT_c6, OnChangeEDITc6)
	ON_EN_CHANGE(IDC_EDIT_c7, OnChangeEDITc7)
	ON_EN_CHANGE(IDC_EDIT_c8, OnChangeEDITc8)
	ON_EN_CHANGE(IDC_EDIT_c9, OnChangeEDITc9)
	ON_EN_CHANGE(IDC_EDIT_d1, OnChangeEDITd1)
	ON_EN_CHANGE(IDC_EDIT_d2, OnChangeEDITd2)
	ON_EN_CHANGE(IDC_EDIT_d3, OnChangeEDITd3)
	ON_EN_CHANGE(IDC_EDIT_d4, OnChangeEDITd4)
	ON_EN_CHANGE(IDC_EDIT_d5, OnChangeEDITd5)
	ON_EN_CHANGE(IDC_EDIT_d6, OnChangeEDITd6)
	ON_EN_CHANGE(IDC_EDIT_d7, OnChangeEDITd7)
	ON_EN_CHANGE(IDC_EDIT_d8, OnChangeEDITd8)
	ON_EN_CHANGE(IDC_EDIT_d9, OnChangeEDITd9)
	ON_EN_CHANGE(IDC_EDIT_e1, OnChangeEDITe1)
	ON_EN_CHANGE(IDC_EDIT_e2, OnChangeEDITe2)
	ON_EN_CHANGE(IDC_EDIT_e3, OnChangeEDITe3)
	ON_EN_CHANGE(IDC_EDIT_e4, OnChangeEDITe4)
	ON_EN_CHANGE(IDC_EDIT_e5, OnChangeEDITe5)
	ON_EN_CHANGE(IDC_EDIT_e6, OnChangeEDITe6)
	ON_EN_CHANGE(IDC_EDIT_e7, OnChangeEDITe7)
	ON_EN_CHANGE(IDC_EDIT_e8, OnChangeEDITe8)
	ON_EN_CHANGE(IDC_EDIT_e9, OnChangeEDITe9)
	ON_EN_CHANGE(IDC_EDIT_f1, OnChangeEDITf1)
	ON_EN_CHANGE(IDC_EDIT_f2, OnChangeEDITf2)
	ON_EN_CHANGE(IDC_EDIT_f3, OnChangeEDITf3)
	ON_EN_CHANGE(IDC_EDIT_f4, OnChangeEDITf4)
	ON_EN_CHANGE(IDC_EDIT_f5, OnChangeEDITf5)
	ON_EN_CHANGE(IDC_EDIT_f6, OnChangeEDITf6)
	ON_EN_CHANGE(IDC_EDIT_f7, OnChangeEDITf7)
	ON_EN_CHANGE(IDC_EDIT_f8, OnChangeEDITf8)
	ON_EN_CHANGE(IDC_EDIT_f9, OnChangeEDITf9)
	ON_EN_CHANGE(IDC_EDIT_x1, OnChangeEDITx1)
	ON_EN_CHANGE(IDC_EDIT_x2, OnChangeEDITx2)
	ON_EN_CHANGE(IDC_EDIT_x3, OnChangeEDITx3)
	ON_EN_CHANGE(IDC_EDIT_x4, OnChangeEDITx4)
	ON_EN_CHANGE(IDC_EDIT_x5, OnChangeEDITx5)
	ON_EN_CHANGE(IDC_EDIT_x6, OnChangeEDITx6)
	ON_EN_CHANGE(IDC_EDIT_x7, OnChangeEDITx7)
	ON_EN_CHANGE(IDC_EDIT_x8, OnChangeEDITx8)
	ON_EN_CHANGE(IDC_EDIT_x9, OnChangeEDITx9)
	ON_EN_CHANGE(IDC_EDIT_y1, OnChangeEDITy1)
	ON_EN_CHANGE(IDC_EDIT_y2, OnChangeEDITy2)
	ON_EN_CHANGE(IDC_EDIT_y3, OnChangeEDITy3)
	ON_EN_CHANGE(IDC_EDIT_y4, OnChangeEDITy4)
	ON_EN_CHANGE(IDC_EDIT_y5, OnChangeEDITy5)
	ON_EN_CHANGE(IDC_EDIT_y6, OnChangeEDITy6)
	ON_EN_CHANGE(IDC_EDIT_y7, OnChangeEDITy7)
	ON_EN_CHANGE(IDC_EDIT_y8, OnChangeEDITy8)
	ON_EN_CHANGE(IDC_EDIT_y9, OnChangeEDITy9)
	ON_EN_CHANGE(IDC_EDIT_z1, OnChangeEDITz1)
	ON_EN_CHANGE(IDC_EDIT_z2, OnChangeEDITz2)
	ON_EN_CHANGE(IDC_EDIT_z3, OnChangeEDITz3)
	ON_EN_CHANGE(IDC_EDIT_z4, OnChangeEDITz4)
	ON_EN_CHANGE(IDC_EDIT_z5, OnChangeEDITz5)
	ON_EN_CHANGE(IDC_EDIT_z6, OnChangeEDITz6)
	ON_EN_CHANGE(IDC_EDIT_z7, OnChangeEDITz7)
	ON_EN_CHANGE(IDC_EDIT_z8, OnChangeEDITz8)
	ON_EN_CHANGE(IDC_EDIT_z9, OnChangeEDITz9)
	ON_EN_SETFOCUS(IDC_EDIT_c1, OnSetfocusEDITc1)
	ON_EN_SETFOCUS(IDC_EDIT_c2, OnSetfocusEDITc2)
	ON_EN_SETFOCUS(IDC_EDIT_c3, OnSetfocusEDITc3)
	ON_EN_SETFOCUS(IDC_EDIT_c4, OnSetfocusEDITc4)
	ON_EN_SETFOCUS(IDC_EDIT_c5, OnSetfocusEDITc5)
	ON_EN_SETFOCUS(IDC_EDIT_c6, OnSetfocusEDITc6)
	ON_EN_SETFOCUS(IDC_EDIT_c7, OnSetfocusEDITc7)
	ON_EN_SETFOCUS(IDC_EDIT_c8, OnSetfocusEDITc8)
	ON_EN_SETFOCUS(IDC_EDIT_c9, OnSetfocusEDITc9)
	ON_EN_SETFOCUS(IDC_EDIT_d1, OnSetfocusEDITd1)
	ON_EN_SETFOCUS(IDC_EDIT_d2, OnSetfocusEDITd2)
	ON_EN_SETFOCUS(IDC_EDIT_d3, OnSetfocusEDITd3)
	ON_EN_SETFOCUS(IDC_EDIT_d4, OnSetfocusEDITd4)
	ON_EN_SETFOCUS(IDC_EDIT_d5, OnSetfocusEDITd5)
	ON_EN_SETFOCUS(IDC_EDIT_d6, OnSetfocusEDITd6)
	ON_EN_SETFOCUS(IDC_EDIT_d7, OnSetfocusEDITd7)
	ON_EN_SETFOCUS(IDC_EDIT_d8, OnSetfocusEDITd8)
	ON_EN_SETFOCUS(IDC_EDIT_d9, OnSetfocusEDITd9)
	ON_EN_SETFOCUS(IDC_EDIT_e1, OnSetfocusEDITe1)
	ON_EN_SETFOCUS(IDC_EDIT_e2, OnSetfocusEDITe2)
	ON_EN_SETFOCUS(IDC_EDIT_e3, OnSetfocusEDITe3)
	ON_EN_SETFOCUS(IDC_EDIT_e4, OnSetfocusEDITe4)
	ON_EN_SETFOCUS(IDC_EDIT_e5, OnSetfocusEDITe5)
	ON_EN_SETFOCUS(IDC_EDIT_e6, OnSetfocusEDITe6)
	ON_EN_SETFOCUS(IDC_EDIT_e7, OnSetfocusEDITe7)
	ON_EN_SETFOCUS(IDC_EDIT_e8, OnSetfocusEDITe8)
	ON_EN_SETFOCUS(IDC_EDIT_e9, OnSetfocusEDITe9)
	ON_EN_SETFOCUS(IDC_EDIT_f1, OnSetfocusEDITf1)
	ON_EN_SETFOCUS(IDC_EDIT_f2, OnSetfocusEDITf2)
	ON_EN_SETFOCUS(IDC_EDIT_f3, OnSetfocusEDITf3)
	ON_EN_SETFOCUS(IDC_EDIT_f4, OnSetfocusEDITf4)
	ON_EN_SETFOCUS(IDC_EDIT_f5, OnSetfocusEDITf5)
	ON_EN_SETFOCUS(IDC_EDIT_f6, OnSetfocusEDITf6)
	ON_EN_SETFOCUS(IDC_EDIT_f7, OnSetfocusEDITf7)
	ON_EN_SETFOCUS(IDC_EDIT_f8, OnSetfocusEDITf8)
	ON_EN_SETFOCUS(IDC_EDIT_f9, OnSetfocusEDITf9)
	ON_EN_SETFOCUS(IDC_EDIT_x1, OnSetfocusEDITx1)
	ON_EN_SETFOCUS(IDC_EDIT_x2, OnSetfocusEDITx2)
	ON_EN_SETFOCUS(IDC_EDIT_x3, OnSetfocusEDITx3)
	ON_EN_SETFOCUS(IDC_EDIT_x4, OnSetfocusEDITx4)
	ON_EN_SETFOCUS(IDC_EDIT_x5, OnSetfocusEDITx5)
	ON_EN_SETFOCUS(IDC_EDIT_x6, OnSetfocusEDITx6)
	ON_EN_SETFOCUS(IDC_EDIT_x7, OnSetfocusEDITx7)
	ON_EN_SETFOCUS(IDC_EDIT_x8, OnSetfocusEDITx8)
	ON_EN_SETFOCUS(IDC_EDIT_x9, OnSetfocusEDITx9)
	ON_EN_SETFOCUS(IDC_EDIT_y1, OnSetfocusEDITy1)
	ON_EN_SETFOCUS(IDC_EDIT_y2, OnSetfocusEDITy2)
	ON_EN_SETFOCUS(IDC_EDIT_y3, OnSetfocusEDITy3)
	ON_EN_SETFOCUS(IDC_EDIT_y4, OnSetfocusEDITy4)
	ON_EN_SETFOCUS(IDC_EDIT_y5, OnSetfocusEDITy5)
	ON_EN_SETFOCUS(IDC_EDIT_y6, OnSetfocusEDITy6)
	ON_EN_SETFOCUS(IDC_EDIT_y7, OnSetfocusEDITy7)
	ON_EN_SETFOCUS(IDC_EDIT_y8, OnSetfocusEDITy8)
	ON_EN_SETFOCUS(IDC_EDIT_y9, OnSetfocusEDITy9)
	ON_EN_SETFOCUS(IDC_EDIT_z1, OnSetfocusEDITz1)
	ON_EN_SETFOCUS(IDC_EDIT_z2, OnSetfocusEDITz2)
	ON_EN_SETFOCUS(IDC_EDIT_z3, OnSetfocusEDITz3)
	ON_EN_SETFOCUS(IDC_EDIT_z4, OnSetfocusEDITz4)
	ON_EN_SETFOCUS(IDC_EDIT_z5, OnSetfocusEDITz5)
	ON_EN_SETFOCUS(IDC_EDIT_z6, OnSetfocusEDITz6)
	ON_EN_SETFOCUS(IDC_EDIT_z7, OnSetfocusEDITz7)
	ON_EN_SETFOCUS(IDC_EDIT_z8, OnSetfocusEDITz8)
	ON_EN_SETFOCUS(IDC_EDIT_z9, OnSetfocusEDITz9)
	ON_BN_CLICKED(IDC_BUTTON_save, OnBUTTONsave)
	ON_BN_CLICKED(IDC_BUTTON_clear, OnBUTTONclear)
	ON_BN_CLICKED(IDC_BUTTON_tipsoff, OnBUTTON_tipsSwitch)
	ON_BN_CLICKED(IDC_BUTTON_read, OnBUTTONread)
	ON_BN_CLICKED(IDC_BUTTON_chooseMusic, OnBUTTONchooseMusic)
	ON_BN_CLICKED(IDC_BUTTON_musicSwitch, OnBUTTONmusicSwitch)
	ON_BN_CLICKED(IDC_BUTTON_soundSwitch, OnBUTTONsoundSwitch)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_sound, OnCustomdrawSLIDERsound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShuduDlg message handlers

BOOL CShuduDlg::OnInitDialog()
{	
	tips_switch=tips_switchs%2;
	sound_switch=sound%2;
	music_switch=music%2;
//	m_sound.SetWindowText("开");
//	m_music.SetWindowText("开");

//	PlaySound("SystemStart",NULL,SND_ALIAS|SND_ASYNC);
//	if(music==0) PlaySound(".\\Sudoku.wav",NULL, SND_ASYNC|SND_NODEFAULT );
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_about),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	for(int ii=0;ii<9;ii++)
		for(int jj=0;jj<9;jj++) sd_title[ii][jj]=-1;


	CDialog::OnInitDialog();
	m_tips1.SetReadOnly(true);
	m_tips2.SetReadOnly(true);
	m_tips3.SetReadOnly(true);
	m_tips4.SetReadOnly(true);
	m_tips5.SetReadOnly(true);
	m_tips6.SetReadOnly(true);
	m_tips7.SetReadOnly(true);
	m_tips8.SetReadOnly(true);
	m_tips9.SetReadOnly(true);//提示框只读


	CFont f;
	f.CreatePointFont(120,"");
	m_a11.SetFont(&f);
	m_a22.SetFont(&f);
	m_a33.SetFont(&f);
	m_a44.SetFont(&f);
	m_a55.SetFont(&f);
	m_a66.SetFont(&f);
	m_a77.SetFont(&f);
	m_a88.SetFont(&f);
	m_a99.SetFont(&f);

	m_b11.SetFont(&f);
	m_b22.SetFont(&f);
	m_b33.SetFont(&f);
	m_b44.SetFont(&f);
	m_b55.SetFont(&f);
	m_b66.SetFont(&f);
	m_b77.SetFont(&f);
	m_b88.SetFont(&f);
	m_b99.SetFont(&f);

	m_c11.SetFont(&f);
	m_c22.SetFont(&f);
	m_c33.SetFont(&f);
	m_c44.SetFont(&f);
	m_c55.SetFont(&f);
	m_c66.SetFont(&f);
	m_c77.SetFont(&f);
	m_c88.SetFont(&f);
	m_c99.SetFont(&f);

	m_d11.SetFont(&f);
	m_d22.SetFont(&f);
	m_d33.SetFont(&f);
	m_d44.SetFont(&f);
	m_d55.SetFont(&f);
	m_d66.SetFont(&f);
	m_d77.SetFont(&f);
	m_d88.SetFont(&f);
	m_d99.SetFont(&f);

	m_e11.SetFont(&f);
	m_e22.SetFont(&f);
	m_e33.SetFont(&f);
	m_e44.SetFont(&f);
	m_e55.SetFont(&f);
	m_e66.SetFont(&f);
	m_e77.SetFont(&f);
	m_e88.SetFont(&f);
	m_e99.SetFont(&f);

	m_f11.SetFont(&f);
	m_f22.SetFont(&f);
	m_f33.SetFont(&f);
	m_f44.SetFont(&f);
	m_f55.SetFont(&f);
	m_f66.SetFont(&f);
	m_f77.SetFont(&f);
	m_f88.SetFont(&f);
	m_f99.SetFont(&f);

	m_x11.SetFont(&f);
	m_x22.SetFont(&f);
	m_x33.SetFont(&f);
	m_x44.SetFont(&f);
	m_x55.SetFont(&f);
	m_x66.SetFont(&f);
	m_x77.SetFont(&f);
	m_x88.SetFont(&f);
	m_x99.SetFont(&f);

	m_y11.SetFont(&f);
	m_y22.SetFont(&f);
	m_y33.SetFont(&f);
	m_y44.SetFont(&f);
	m_y55.SetFont(&f);
	m_y66.SetFont(&f);
	m_y77.SetFont(&f);
	m_y88.SetFont(&f);
	m_y99.SetFont(&f);

	m_z11.SetFont(&f);
	m_z22.SetFont(&f);
	m_z33.SetFont(&f);
	m_z44.SetFont(&f);
	m_z55.SetFont(&f);
	m_z66.SetFont(&f);
	m_z77.SetFont(&f);
	m_z88.SetFont(&f);
	m_z99.SetFont(&f);//设置字体大小


	m_a11.LimitText(1);
	m_a22.LimitText(1);
	m_a33.LimitText(1);
	m_a44.LimitText(1);
	m_a55.LimitText(1);
	m_a66.LimitText(1);
	m_a77.LimitText(1);
	m_a88.LimitText(1);
	m_a99.LimitText(1);

	m_b11.LimitText(1);
	m_b22.LimitText(1);
	m_b33.LimitText(1);
	m_b44.LimitText(1);
	m_b55.LimitText(1);
	m_b66.LimitText(1);
	m_b77.LimitText(1);
	m_b88.LimitText(1);
	m_b99.LimitText(1);

	m_c11.LimitText(1);
	m_c22.LimitText(1);
	m_c33.LimitText(1);
	m_c44.LimitText(1);
	m_c55.LimitText(1);
	m_c66.LimitText(1);
	m_c77.LimitText(1);
	m_c88.LimitText(1);
	m_c99.LimitText(1);

	m_d11.LimitText(1);
	m_d22.LimitText(1);
	m_d33.LimitText(1);
	m_d44.LimitText(1);
	m_d55.LimitText(1);
	m_d66.LimitText(1);
	m_d77.LimitText(1);
	m_d88.LimitText(1);
	m_d99.LimitText(1);

	m_e11.LimitText(1);
	m_e22.LimitText(1);
	m_e33.LimitText(1);
	m_e44.LimitText(1);
	m_e55.LimitText(1);
	m_e66.LimitText(1);
	m_e77.LimitText(1);
	m_e88.LimitText(1);
	m_e99.LimitText(1);

	m_f11.LimitText(1);
	m_f22.LimitText(1);
	m_f33.LimitText(1);
	m_f44.LimitText(1);
	m_f55.LimitText(1);
	m_f66.LimitText(1);
	m_f77.LimitText(1);
	m_f88.LimitText(1);
	m_f99.LimitText(1);

	m_x11.LimitText(1);
	m_x22.LimitText(1);
	m_x33.LimitText(1);
	m_x44.LimitText(1);
	m_x55.LimitText(1);
	m_x66.LimitText(1);
	m_x77.LimitText(1);
	m_x88.LimitText(1);
	m_x99.LimitText(1);

	m_y11.LimitText(1);
	m_y22.LimitText(1);
	m_y33.LimitText(1);
	m_y44.LimitText(1);
	m_y55.LimitText(1);
	m_y66.LimitText(1);
	m_y77.LimitText(1);
	m_y88.LimitText(1);
	m_y99.LimitText(1);

	m_z11.LimitText(1);
	m_z22.LimitText(1);
	m_z33.LimitText(1);
	m_z44.LimitText(1);
	m_z55.LimitText(1);
	m_z66.LimitText(1);
	m_z77.LimitText(1);
	m_z88.LimitText(1);
	m_z99.LimitText(1);//设置输入字符数限制



			
//	BOOL CSliderCtrlDlg::OnInitDialog()
//　　{
m_vol.SetRange(0,1000);
m_vol.SetPageSize(100);
m_vol.SetLineSize(50);
m_vol.SetPos(800);

	vol.Format("%d",1000-m_vol.GetPos());
//　　return TRUE; // return TRUE unless you set the focus to a control
//　　}
		
		


	m_music.SetWindowText("关");
	m_sound.SetWindowText("开");

	SetTimer(1,10,NULL);
	((CButton *)GetDlgItem(IDC_dif))->SetCheck(TRUE);//选上

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShuduDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShuduDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShuduDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShuduDlg::OnBUTTONabout() 
{
	// TODO: Add your control notification handler code here
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_about),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	
}

void CShuduDlg::tips(int h, int l)
{
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_setfocus),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	if(tips_switch==1){
		int i=0,j=0;
		bool b_1=false,b_2=false,b_3=false,b_4=false,b_5=false,b_6=false,b_7=false,b_8=false,b_9=false;
		for(j=l;i<9;i++){
			if(i==h && j==l) continue;
			if(sd_read[i][j]==1) b_1=true;
			if(sd_read[i][j]==2) b_2=true;
			if(sd_read[i][j]==3) b_3=true;
			if(sd_read[i][j]==4) b_4=true;
			if(sd_read[i][j]==5) b_5=true;
			if(sd_read[i][j]==6) b_6=true;
			if(sd_read[i][j]==7) b_7=true;
			if(sd_read[i][j]==8) b_8=true;
			if(sd_read[i][j]==9) b_9=true;
		}
		j=0;
		for(i=h;j<9;j++){
			if(i==h && j==l) continue;
			if(sd_read[i][j]==1) b_1=true;
			if(sd_read[i][j]==2) b_2=true;
			if(sd_read[i][j]==3) b_3=true;
			if(sd_read[i][j]==4) b_4=true;
			if(sd_read[i][j]==5) b_5=true;
			if(sd_read[i][j]==6) b_6=true;
			if(sd_read[i][j]==7) b_7=true;
			if(sd_read[i][j]==8) b_8=true;
			if(sd_read[i][j]==9) b_9=true;
		}

		int part;
		if(0<=h && h<=2 && 0<=l && l<=2) part=1;
		if(0<=h && h<=2 && 3<=l && l<=5) part=2;
		if(0<=h && h<=2 && 6<=l && l<=8) part=3;
		if(3<=h && h<=5 && 0<=l && l<=2) part=4;
		if(3<=h && h<=5 && 3<=l && l<=5) part=5;
		if(3<=h && h<=5 && 6<=l && l<=8) part=6;
		if(6<=h && h<=8 && 0<=l && l<=2) part=7;
		if(6<=h && h<=8 && 3<=l && l<=5) part=8;
		if(6<=h && h<=8 && 6<=l && l<=8) part=9;

		if(part==1){
			for(i=0;i<=2;i++)
				for(j=0;j<=2;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}

		if(part==2){
			for(i=0;i<=2;i++)
				for(j=3;j<=5;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==3){
			for(i=0;i<=2;i++)
				for(j=6;j<=8;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==4){
			for(i=3;i<=5;i++)
				for(j=0;j<=2;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==5){
			for(i=3;i<=5;i++)
				for(j=3;j<=5;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==6){
			for(i=3;i<=5;i++)
				for(j=6;j<=8;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==7){
			for(i=6;i<=8;i++)
				for(j=0;j<=2;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==8){
			for(i=6;i<=8;i++)
				for(j=3;j<=5;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}
		if(part==9){
			for(i=6;i<=8;i++)
				for(j=6;j<=8;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==1) b_1=true;
					if(sd_read[i][j]==2) b_2=true;
					if(sd_read[i][j]==3) b_3=true;
					if(sd_read[i][j]==4) b_4=true;
					if(sd_read[i][j]==5) b_5=true;
					if(sd_read[i][j]==6) b_6=true;
					if(sd_read[i][j]==7) b_7=true;
					if(sd_read[i][j]==8) b_8=true;
					if(sd_read[i][j]==9) b_9=true;
				}
		}

		if(b_1==true) m_tips1.SetWindowText("×");
		else m_tips1.SetWindowText("1");

		if(b_2==true) m_tips2.SetWindowText("×");
		else m_tips2.SetWindowText("2");

		if(b_3==true) m_tips3.SetWindowText("×");
		else m_tips3.SetWindowText("3");

		if(b_4==true) m_tips4.SetWindowText("×");
		else m_tips4.SetWindowText("4");

		if(b_5==true) m_tips5.SetWindowText("×");
		else m_tips5.SetWindowText("5");

		if(b_6==true) m_tips6.SetWindowText("×");
		else m_tips6.SetWindowText("6");

		if(b_7==true) m_tips7.SetWindowText("×");
		else m_tips7.SetWindowText("7");

		if(b_8==true) m_tips8.SetWindowText("×");
		else m_tips8.SetWindowText("8");

		if(b_9==true) m_tips9.SetWindowText("×");
		else m_tips9.SetWindowText("9");
		}
		else {
			m_tips1.SetWindowText("×");
			m_tips2.SetWindowText("×");
			m_tips3.SetWindowText("×");
			m_tips4.SetWindowText("×");
			m_tips5.SetWindowText("×");
			m_tips6.SetWindowText("×");
			m_tips7.SetWindowText("×");
			m_tips8.SetWindowText("×");
			m_tips9.SetWindowText("×");
			m_tipsOnOff.SetWindowText("关");
		}
}

void CShuduDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*	if(sound_switch==0){

		if(music_switch==0 && music_one==0){
			PlaySound(".\\Sudoku.wav",NULL, SND_ASYNC|SND_NODEFAULT|SND_LOOP);
			music_one=1;
		}
		if(music_switch==1 && music_two==0 ){
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_soundSwitch),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
			music_two=1;
		}
	}
	else if(sound_one==0){
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_soundSwitch),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		sound_one=1;
	}
*/


	if(condition==0) l=0;
	else if(condition==1) l=::GetTickCount()-k;
	else l=l;	//获取毫秒级数目
	CString time;
	int hm=l/3600000; //hm为小时数
	CString strhm;
	if(hm<10)
		strhm.Format("0%d:",hm);
	else
		strhm.Format("%d:",hm);
	int ms=(l-3600000*hm)/60000; //ms为分钟数
	CString strms;
	if(ms<10)
		strms.Format("0%d:",ms);
	else
		strms.Format("%d:",ms);

	int se=(l-3600000*hm-60000*ms)/1000; //se为秒数（除以1000是因为k精确到毫秒）
		CString strse;
	if(se<10)
		strse.Format("0%d",se);
	else
		strse.Format("%d",se);

	time=strhm+strms+strse; //输出时、分、秒
	m_edtTime.SetWindowText(time);
	m_edtTime.SetReadOnly(TRUE);

		bool check=true;
		for(int ii=0;ii<=8;ii++)
			for(int jj=0;jj<=8;jj++){
				if(sd_read[ii][jj]==0) check=false;
			}

			if(condition_show!=2 && condition==2){
				condition=3;				
				MessageBox("你选择了[显示解答]，用时:"+time,"显示解答！",MB_OK);
				condition_show=2;
			}

			if(check && condition!=3){
				condition=3;
				if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_win),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
				MessageBox("恭喜你，本题目你已完成，用时:"+time,"恭喜你，成功啦！",MB_OK);
			}
			


	CDialog::OnTimer(nIDEvent);
}

void CShuduDlg::Ondif() 
{
	// TODO: Add your control notification handler code here
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_dif),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	m_dif=0;//难度：菜鸟	
}

void CShuduDlg::Ondif2() 
{
	// TODO: Add your control notification handler code here
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_dif),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	m_dif=1;//中等
}

void CShuduDlg::Ondif3() 
{
	// TODO: Add your control notification handler code here
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_dif),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	m_dif=2;//较难


	
}

void CShuduDlg::Ondif4() 
{
	// TODO: Add your control notification handler code here
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_dif),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	m_dif=3;//骨灰
/*
	HWND hmci1,hmci2;                 //声明mci窗口句柄； 
    CString str1,str2;
    str1=".\\牡丹江.wma";           //*.mpe等也可
    str2=".\\crayon_dreams.wav";
    hmci1=MCIWndCreate(NULL,NULL,0,str1);
    hmci2=MCIWndCreate(NULL,NULL,0,str2);
    MCIWndPlay(hmci1);          //播放文件；
    MCIWndPlay(hmci2);
*/	
//	CString lpstrCommand;
//	lpstrCommand.Format("setaudio NOWMUSIC volume to %d",1000);   
//	mciSendString(lpstrCommand.GetBuffer(0),NULL,0,0);
//	mciSendString("setaudio NOWMUSIC volume to 1000",0,0,0);
}

void CShuduDlg::check(int h, int l, CEdit &m_check)//本函数用于检查输入的数字是否为0或者重复，如果如此将禁止输入
{
	int i=0,j=0;
	bool b_check=false;
	CString cs_check;
	m_check.GetWindowText(cs_check);
	int i_check=atoi(cs_check);

	for(j=l;i<=8;i++){
		if(i==h && j==l) continue;
		if(sd_read[i][j]==i_check) b_check=true;
	}
		j=0;
	for(i=h;j<9;j++){
		if(i==h && j==l) continue;
		if(sd_read[i][j]==i_check) b_check=true;
	}

		int part;
		if(0<=h && h<=2 && 0<=l && l<=2) part=1;
		if(0<=h && h<=2 && 3<=l && l<=5) part=2;
		if(0<=h && h<=2 && 6<=l && l<=8) part=3;
		if(3<=h && h<=5 && 0<=l && l<=2) part=4;
		if(3<=h && h<=5 && 3<=l && l<=5) part=5;
		if(3<=h && h<=5 && 6<=l && l<=8) part=6;
		if(6<=h && h<=8 && 0<=l && l<=2) part=7;
		if(6<=h && h<=8 && 3<=l && l<=5) part=8;
		if(6<=h && h<=8 && 6<=l && l<=8) part=9;

		if(part==1){
			for(i=0;i<=2;i++)
				for(j=0;j<=2;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}

		if(part==2){
			for(i=0;i<=2;i++)
				for(j=3;j<=5;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==3){
			for(i=0;i<=2;i++)
				for(j=6;j<=8;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==4){
			for(i=3;i<=5;i++)
				for(j=0;j<=2;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==5){
			for(i=3;i<=5;i++)
				for(j=3;j<=5;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==6){
			for(i=3;i<=5;i++)
				for(j=6;j<=8;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==7){
			for(i=6;i<=8;i++)
				for(j=0;j<=2;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==8){
			for(i=6;i<=8;i++)
				for(j=3;j<=5;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		if(part==9){
			for(i=6;i<=8;i++)
				for(j=6;j<=8;j++){
					if(i==h && j==l) continue;
					if(sd_read[i][j]==i_check) b_check=true;
				}
		}
		
		if(b_check || i_check==0){
			if(sound_new==0 && sound_switch==0 && clear_s==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_checkWrong),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
			m_check.SetSel(0,-1,false);
			m_check.Clear();

		}
		else if(sound_new==0 && sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_checkRight),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		//以上部分用于检查重复数字和0
	

}

/*
void CShuduDlg::RealAll()//将编辑框的值读入到CString中，目前未利用
{
	m_a11.GetWindowText(m_a1);
	m_a22.GetWindowText(m_a2);
	m_a33.GetWindowText(m_a3);
	m_a44.GetWindowText(m_a4);
	m_a55.GetWindowText(m_a5);
	m_a66.GetWindowText(m_a6);
	m_a77.GetWindowText(m_a7);
	m_a88.GetWindowText(m_a8);
	m_a99.GetWindowText(m_a9);

	m_b11.GetWindowText(m_b1);
	m_b22.GetWindowText(m_b2);
	m_b33.GetWindowText(m_b3);
	m_b44.GetWindowText(m_b4);
	m_b55.GetWindowText(m_b5);
	m_b66.GetWindowText(m_b6);
	m_b77.GetWindowText(m_b7);
	m_b88.GetWindowText(m_b8);
	m_b99.GetWindowText(m_b9);

	m_c11.GetWindowText(m_c1);
	m_c22.GetWindowText(m_c2);
	m_c33.GetWindowText(m_c3);
	m_c44.GetWindowText(m_c4);
	m_c55.GetWindowText(m_c5);
	m_c66.GetWindowText(m_c6);
	m_c77.GetWindowText(m_c7);
	m_c88.GetWindowText(m_c8);
	m_c99.GetWindowText(m_c9);

	m_d11.GetWindowText(m_d1);
	m_d22.GetWindowText(m_d2);
	m_d33.GetWindowText(m_d3);
	m_d44.GetWindowText(m_d4);
	m_d55.GetWindowText(m_d5);
	m_d66.GetWindowText(m_d6);
	m_d77.GetWindowText(m_d7);
	m_d88.GetWindowText(m_d8);
	m_d99.GetWindowText(m_d9);

	m_e11.GetWindowText(m_e1);
	m_e22.GetWindowText(m_e2);
	m_e33.GetWindowText(m_e3);
	m_e44.GetWindowText(m_e4);
	m_e55.GetWindowText(m_e5);
	m_e66.GetWindowText(m_e6);
	m_e77.GetWindowText(m_e7);
	m_e88.GetWindowText(m_e8);
	m_e99.GetWindowText(m_e9);

	m_f11.GetWindowText(m_f1);
	m_f22.GetWindowText(m_f2);
	m_f33.GetWindowText(m_f3);
	m_f44.GetWindowText(m_f4);
	m_f55.GetWindowText(m_f5);
	m_f66.GetWindowText(m_f6);
	m_f77.GetWindowText(m_f7);
	m_f88.GetWindowText(m_f8);
	m_f99.GetWindowText(m_f9);

	m_x11.GetWindowText(m_x1);
	m_x22.GetWindowText(m_x2);
	m_x33.GetWindowText(m_x3);
	m_x44.GetWindowText(m_x4);
	m_x55.GetWindowText(m_x5);
	m_x66.GetWindowText(m_x6);
	m_x77.GetWindowText(m_x7);
	m_x88.GetWindowText(m_x8);
	m_x99.GetWindowText(m_x9);

	m_y11.GetWindowText(m_y1);
	m_y22.GetWindowText(m_y2);
	m_y33.GetWindowText(m_y3);
	m_y44.GetWindowText(m_y4);
	m_y55.GetWindowText(m_y5);
	m_y66.GetWindowText(m_y6);
	m_y77.GetWindowText(m_y7);
	m_y88.GetWindowText(m_y8);
	m_y99.GetWindowText(m_y9);

	m_z11.GetWindowText(m_z1);
	m_z22.GetWindowText(m_z2);
	m_z33.GetWindowText(m_z3);
	m_z44.GetWindowText(m_z4);
	m_z55.GetWindowText(m_z5);
	m_z66.GetWindowText(m_z6);
	m_z77.GetWindowText(m_z7);
	m_z88.GetWindowText(m_z8);
	m_z99.GetWindowText(m_z9);

}
*/

void CShuduDlg::read(int h, int l, CEdit &read)//将编辑框中的值读入到sd_read数组相应的位置
{
	CString cs_read;
	read.GetWindowText(cs_read);
	sd_read[h][l]=atoi(cs_read);
}

void CShuduDlg::OnBUTTONnew() //新建游戏，用于生成题目等一系列操作
{
	// TODO: Add your control notification handler code here
	OnBUTTONclear();
	condition=1;
	k=::GetTickCount(); //计时器清零
	sound_new=1;

//|SND_LOOP
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_new),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
//重新初始化提示开关，设置为关
	tips_switch=2;
	tips_switchs=2;//提示开关控制
	tips_switch=tips_switchs%2;
	m_tipsOnOff.SetWindowText("关");
	m_tips1.SetWindowText("×");
	m_tips2.SetWindowText("×");
	m_tips3.SetWindowText("×");
	m_tips4.SetWindowText("×");
	m_tips5.SetWindowText("×");
	m_tips6.SetWindowText("×");
	m_tips7.SetWindowText("×");
	m_tips8.SetWindowText("×");
	m_tips9.SetWindowText("×");

//随机生成sd[][]数组
	srand((unsigned)time(NULL)); //随便调用一次。
	memset(row, 0, sizeof(row));
	memset(col, 0, sizeof(col));
	memset(squ, 0, sizeof(squ));
	found = false;	
	generate(0, 0);                    //随机生成数独矩阵sd[][]
//挖空！生成sd_title
	bool b_dif;

	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			if(m_dif==0) b_dif=(rand()%9==8 || rand()%9==7 || rand()%9==6 || rand()%9==5);
			if(m_dif==1) b_dif=(rand()%9==8 || rand()%9==7 || rand()%9==6 || rand()%9==5 || rand()%9==4);
			if(m_dif==2) b_dif=(rand()%9==8 || rand()%9==7 || rand()%9==6 || rand()%9==5 || rand()%9==4 || rand()%9==3);
			if(m_dif==3) b_dif=(rand()%9==8 || rand()%9==7 || rand()%9==6 || rand()%9==5 || rand()%9==4 || rand()%9==3 || rand()%9==2 || rand()%9==1 || rand()%9==0);

			if(b_dif) sd_title[i][j]=0;
			else sd_title[i][j]=sd[i][j];

		}

	for(int x=0;x<9;x++)
		for(int y=0;y<9;y++){
			sd_read[x][y]=sd_title[x][y];
		}//复制title到read中

	setReadOnly();
	sound_new=0;
	read_noAnswer=0;
//sndPlaySound ("c:\\music.wav",SND_ASYNC);

//	CString a;
//	int b=0;
//	a.Format("%d",b);
//	a.Format("%d",sd[2][2]);
//	m_a99.SetWindowText(a);//直接输出整型数！！！


}

void CShuduDlg::OnBUTTONshow() //显示解答，同时控制计时器停止
{
	// TODO: Add your control notification handler code here
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_show),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);


	if(read_noAnswer==0){
	sound_new=1;
	bool b_show=true;
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++){
				if(sd[i][j]==0) b_show=false;break;
			}
	
	if(b_show){

	condition=2;//控制计时器停止
	condition_show=0;
	show(0,0,m_a11);
	show(0,1,m_a22);
	show(0,2,m_a33);
	show(1,0,m_a44);
	show(1,1,m_a55);
	show(1,2,m_a66);
	show(2,0,m_a77);
	show(2,1,m_a88);
	show(2,2,m_a99);

	show(0,3,m_b11);
	show(0,4,m_b22);
	show(0,5,m_b33);
	show(1,3,m_b44);
	show(1,4,m_b55);
	show(1,5,m_b66);
	show(2,3,m_b77);
	show(2,4,m_b88);
	show(2,5,m_b99);

	show(0,6,m_c11);
	show(0,7,m_c22);
	show(0,8,m_c33);
	show(1,6,m_c44);
	show(1,7,m_c55);
	show(1,8,m_c66);
	show(2,6,m_c77);
	show(2,7,m_c88);
	show(2,8,m_c99);

	show(3,0,m_d11);
	show(3,1,m_d22);
	show(3,2,m_d33);
	show(4,0,m_d44);
	show(4,1,m_d55);
	show(4,2,m_d66);
	show(5,0,m_d77);
	show(5,1,m_d88);
	show(5,2,m_d99);

	show(3,3,m_e11);
	show(3,4,m_e22);
	show(3,5,m_e33);
	show(4,3,m_e44);
	show(4,4,m_e55);
	show(4,5,m_e66);
	show(5,3,m_e77);
	show(5,4,m_e88);
	show(5,5,m_e99);

	show(3,6,m_f11);
	show(3,7,m_f22);
	show(3,8,m_f33);
	show(4,6,m_f44);
	show(4,7,m_f55);
	show(4,8,m_f66);
	show(5,6,m_f77);
	show(5,7,m_f88);
	show(5,8,m_f99);

	show(6,0,m_x11);
	show(6,1,m_x22);
	show(6,2,m_x33);
	show(7,0,m_x44);
	show(7,1,m_x55);
	show(7,2,m_x66);
	show(8,0,m_x77);
	show(8,1,m_x88);
	show(8,2,m_x99);

	show(6,3,m_y11);
	show(6,4,m_y22);
	show(6,5,m_y33);
	show(7,3,m_y44);
	show(7,4,m_y55);
	show(7,5,m_y66);
	show(8,3,m_y77);
	show(8,4,m_y88);
	show(8,5,m_y99);

	show(6,6,m_z11);
	show(6,7,m_z22);
	show(6,8,m_z33);
	show(7,6,m_z44);
	show(7,7,m_z55);
	show(7,8,m_z66);
	show(8,6,m_z77);
	show(8,7,m_z88);
	show(8,8,m_z99);
	sound_new=0;
	}
	else 
		MessageBox("无题目，请先选择[新建游戏]","题目为空",MB_OK);
		sound_new=0;
	}
	else MessageBox("题目为外部题目，无答案","答案为空",MB_OK);
}


void CShuduDlg::OnChangeEDITa1() 
{
	check(0,0,m_a11);//判断数字是否重复，重复将不可输入重复的数字！
	read(0,0,m_a11);
}

void CShuduDlg::OnSetfocusEDITa1() 
{
	tips(0,0);//提示框显示可选数字	
}

void CShuduDlg::OnChangeEDITa2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	check(0,1,m_a22);
	read(0,1,m_a22);
	
}

void CShuduDlg::OnSetfocusEDITa2() 
{
	// TODO: Add your control notification handler code here
	tips(0,1);
}

void CShuduDlg::OnChangeEDITa3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,2,m_a33);
	read(0,2,m_a33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa3() 
{
	// TODO: Add your control notification handler code here
	tips(0,2);
}

void CShuduDlg::OnChangeEDITa4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,0,m_a44);
	read(1,0,m_a44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa4() 
{
	// TODO: Add your control notification handler code here
	tips(1,0);
}

void CShuduDlg::OnChangeEDITa5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,1,m_a55);
	read(1,1,m_a55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa5() 
{
	// TODO: Add your control notification handler code here
	tips(1,1);
}

void CShuduDlg::OnChangeEDITa6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,2,m_a66);
	read(1,2,m_a66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa6() 
{
	// TODO: Add your control notification handler code here
	tips(1,2);
}

void CShuduDlg::OnChangeEDITa7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,0,m_a77);
	read(2,0,m_a77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa7() 
{
	// TODO: Add your control notification handler code here
	tips(2,0);
}

void CShuduDlg::OnChangeEDITa8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,1,m_a88);
	read(2,1,m_a88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa8() 
{
	// TODO: Add your control notification handler code here
	tips(2,1);
}

void CShuduDlg::OnChangeEDITa9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,2,m_a99);
	read(2,2,m_a99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITa9() 
{
	// TODO: Add your control notification handler code here
	tips(2,2);
}

void CShuduDlg::OnChangeEDITb1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,3,m_b11);
	read(0,3,m_b11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb1() 
{
	// TODO: Add your control notification handler code here
	tips(0,3);
}

void CShuduDlg::OnChangeEDITb2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,4,m_b22);
	read(0,4,m_b22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb2() 
{
	// TODO: Add your control notification handler code here
	tips(0,4);
}

void CShuduDlg::OnChangeEDITb3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,5,m_b33);
	read(0,5,m_b33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb3() 
{
	// TODO: Add your control notification handler code here
	tips(0,5);
}

void CShuduDlg::OnChangeEDITb4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,3,m_b44);
	read(1,3,m_b44);

	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb4() 
{
	// TODO: Add your control notification handler code here
	tips(1,3);	
}

void CShuduDlg::OnChangeEDITb5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,4,m_b55);
	read(1,4,m_b55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb5() 
{
	// TODO: Add your control notification handler code here
	tips(1,4);
}

void CShuduDlg::OnChangeEDITb6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,5,m_b66);
	read(1,5,m_b66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb6() 
{
	// TODO: Add your control notification handler code here
	tips(1,5);
}

void CShuduDlg::OnChangeEDITb7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,3,m_b77);
	read(2,3,m_b77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb7() 
{
	// TODO: Add your control notification handler code here
	tips(2,3);
}

void CShuduDlg::OnChangeEDITb8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,4,m_b88);
	read(2,4,m_b88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb8() 
{
	// TODO: Add your control notification handler code here
	tips(2,4);
}

void CShuduDlg::OnChangeEDITb9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,5,m_b99);
	read(2,5,m_b99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITb9() 
{
	// TODO: Add your control notification handler code here
	tips(2,5);
}

void CShuduDlg::OnChangeEDITc1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,6,m_c11);
	read(0,6,m_c11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,7,m_c22);
	read(0,7,m_c22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(0,8,m_c33);
	read(0,8,m_c33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,6,m_c44);
	read(1,6,m_c44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,7,m_c55);
	read(1,7,m_c55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(1,8,m_c66);
	read(1,8,m_c66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,6,m_c77);
	read(2,6,m_c77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,7,m_c88);
	read(2,7,m_c88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITc9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(2,8,m_c99);
	read(2,8,m_c99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,0,m_d11);
	read(3,0,m_d11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,1,m_d22);
	read(3,1,m_d22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,2,m_d33);
	read(3,2,m_d33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,0,m_d44);
	read(4,0,m_d44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,1,m_d55);
	read(4,1,m_d55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,2,m_d66);
	read(4,2,m_d66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,0,m_d77);
	read(5,0,m_d77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,1,m_d88);
	read(5,1,m_d88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITd9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,2,m_d99);
	read(5,2,m_d99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,3,m_e11);
	read(3,3,m_e11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,4,m_e22);
	read(3,4,m_e22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,5,m_e33);
	read(3,5,m_e33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,3,m_e44);
	read(4,3,m_e44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,4,m_e55);
	read(4,4,m_e55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,5,m_e66);
	read(4,5,m_e66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,3,m_e77);
	read(5,3,m_e77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,4,m_e88);
	read(5,4,m_e88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITe9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,5,m_e99);
	read(5,5,m_e99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,6,m_f11);
	read(3,6,m_f11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,7,m_f22);
	read(3,7,m_f22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(3,8,m_f33);
	read(3,8,m_f33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,6,m_f44);
	read(4,6,m_f44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,7,m_f55);
	read(4,7,m_f55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(4,8,m_f66);
	read(4,8,m_f66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,6,m_f77);
	read(5,6,m_f77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,7,m_f88);
	read(5,7,m_f88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITf9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(5,8,m_f99);
	read(5,8,m_f99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,0,m_x11);
	read(6,0,m_x11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,1,m_x22);
	read(6,1,m_x22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,2,m_x33);
	read(6,2,m_x33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,0,m_x44);
	read(7,0,m_x44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,1,m_x55);
	read(7,1,m_x55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,2,m_x66);
	read(7,2,m_x66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,0,m_x77);
	read(8,0,m_x77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,1,m_x88);
	read(8,1,m_x88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITx9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,2,m_x99);
	read(8,2,m_x99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,3,m_y11);
	read(6,3,m_y11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,4,m_y22);
	read(6,4,m_y22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,5,m_y33);
	read(6,5,m_y33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,3,m_y44);
	read(7,3,m_y44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,4,m_y55);
	read(7,4,m_y55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,5,m_y66);
	read(7,5,m_y66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,3,m_y77);
	read(8,3,m_y77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,4,m_y88);
	read(8,4,m_y88);
	
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITy9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,5,m_y99);
	read(8,5,m_y99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,6,m_z11);
	read(6,6,m_z11);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,7,m_z22);
	read(6,7,m_z22);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(6,8,m_z33);
	read(6,8,m_z33);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,6,m_z44);
	read(7,6,m_z44);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,7,m_z55);
	read(7,7,m_z55);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(7,8,m_z66);
	read(7,8,m_z66);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,6,m_z77);
	read(8,6,m_z77);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,7,m_z88);
	read(8,7,m_z88);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnChangeEDITz9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	check(8,8,m_z99);
	read(8,8,m_z99);
	// TODO: Add your control notification handler code here
	
}

void CShuduDlg::OnSetfocusEDITc1() 
{
	// TODO: Add your control notification handler code here
	tips(0,6);
}

void CShuduDlg::OnSetfocusEDITc2() 
{
	// TODO: Add your control notification handler code here
	tips(0,7);
	
}


void CShuduDlg::OnSetfocusEDITc3() 
{
	// TODO: Add your control notification handler code here
	tips(0,8);
}

void CShuduDlg::OnSetfocusEDITc4() 
{
	// TODO: Add your control notification handler code here
	tips(1,6);
}

void CShuduDlg::OnSetfocusEDITc5() 
{
	// TODO: Add your control notification handler code here
	tips(1,7);
}

void CShuduDlg::OnSetfocusEDITc6() 
{
	// TODO: Add your control notification handler code here
	tips(1,8);
}

void CShuduDlg::OnSetfocusEDITc7() 
{
	// TODO: Add your control notification handler code here
	tips(2,6);
}

void CShuduDlg::OnSetfocusEDITc8() 
{
	// TODO: Add your control notification handler code here
	tips(2,7);
}

void CShuduDlg::OnSetfocusEDITc9() 
{
	// TODO: Add your control notification handler code here
	tips(2,8);
}

void CShuduDlg::OnSetfocusEDITd1() 
{
	// TODO: Add your control notification handler code here
	tips(3,0);
}
void CShuduDlg::OnSetfocusEDITd2() 
{
	// TODO: Add your control notification handler code here
	tips(3,1);
}

void CShuduDlg::OnSetfocusEDITd3() 
{
	// TODO: Add your control notification handler code here
	tips(3,2);
}
void CShuduDlg::OnSetfocusEDITd4() 
{
	// TODO: Add your control notification handler code here
	tips(4,0);
}

void CShuduDlg::OnSetfocusEDITd5() 
{
	// TODO: Add your control notification handler code here
	tips(4,1);
}
void CShuduDlg::OnSetfocusEDITd6() 
{
	// TODO: Add your control notification handler code here
	tips(4,2);
}
void CShuduDlg::OnSetfocusEDITd7() 
{
	// TODO: Add your control notification handler code here
	tips(5,0);
}
void CShuduDlg::OnSetfocusEDITd8() 
{
	// TODO: Add your control notification handler code here
	tips(5,1);
}
void CShuduDlg::OnSetfocusEDITd9() 
{
	// TODO: Add your control notification handler code here
	tips(5,2);
}
void CShuduDlg::OnSetfocusEDITe1() 
{
	// TODO: Add your control notification handler code here
	tips(3,3);
}

void CShuduDlg::OnSetfocusEDITe2() 
{
	// TODO: Add your control notification handler code here
	tips(3,4);
}

void CShuduDlg::OnSetfocusEDITe3() 
{
	// TODO: Add your control notification handler code here
	tips(3,5);
}

void CShuduDlg::OnSetfocusEDITe4() 
{
	// TODO: Add your control notification handler code here
	tips(4,3);
}

void CShuduDlg::OnSetfocusEDITe5() 
{
	// TODO: Add your control notification handler code here
	tips(4,4);
}

void CShuduDlg::OnSetfocusEDITe6() 
{
	// TODO: Add your control notification handler code here
	tips(4,5);
}

void CShuduDlg::OnSetfocusEDITe7() 
{
	// TODO: Add your control notification handler code here
	tips(5,3);
}

void CShuduDlg::OnSetfocusEDITe8() 
{
	// TODO: Add your control notification handler code here
	tips(5,4);
}

void CShuduDlg::OnSetfocusEDITe9() 
{
	// TODO: Add your control notification handler code here
	tips(5,5);
}

void CShuduDlg::OnSetfocusEDITf1() 
{
	// TODO: Add your control notification handler code here
	tips(3,6);
}
void CShuduDlg::OnSetfocusEDITf2() 
{
	// TODO: Add your control notification handler code here
	tips(3,7);
}
void CShuduDlg::OnSetfocusEDITf3() 
{
	// TODO: Add your control notification handler code here
	tips(3,8);
}
void CShuduDlg::OnSetfocusEDITf4() 
{
	// TODO: Add your control notification handler code here
	tips(4,6);
}
void CShuduDlg::OnSetfocusEDITf5() 
{
	// TODO: Add your control notification handler code here
	tips(4,7);
}
void CShuduDlg::OnSetfocusEDITf6() 
{
	// TODO: Add your control notification handler code here
	tips(4,8);
}
void CShuduDlg::OnSetfocusEDITf7() 
{
	// TODO: Add your control notification handler code here
	tips(5,6);
}
void CShuduDlg::OnSetfocusEDITf8() 
{
	// TODO: Add your control notification handler code here
	tips(5,7);
}
void CShuduDlg::OnSetfocusEDITf9() 
{
	// TODO: Add your control notification handler code here
	tips(5,8);
}

void CShuduDlg::OnSetfocusEDITx1() 
{
	// TODO: Add your control notification handler code here
	tips(6,0);
}
void CShuduDlg::OnSetfocusEDITx2() 
{
	// TODO: Add your control notification handler code here
	tips(6,1);
}
void CShuduDlg::OnSetfocusEDITx3() 
{
	// TODO: Add your control notification handler code here
	tips(6,2);
}
void CShuduDlg::OnSetfocusEDITx4() 
{
	// TODO: Add your control notification handler code here
	tips(7,0);
}
void CShuduDlg::OnSetfocusEDITx5() 
{
	// TODO: Add your control notification handler code here
	tips(7,1);
}
void CShuduDlg::OnSetfocusEDITx6() 
{
	// TODO: Add your control notification handler code here
	tips(7,2);
}
void CShuduDlg::OnSetfocusEDITx7() 
{
	// TODO: Add your control notification handler code here
	tips(8,0);
}
void CShuduDlg::OnSetfocusEDITx8() 
{
	// TODO: Add your control notification handler code here
	tips(8,1);
}
void CShuduDlg::OnSetfocusEDITx9() 
{
	// TODO: Add your control notification handler code here
	tips(8,2);
}
void CShuduDlg::OnSetfocusEDITy1() 
{
	// TODO: Add your control notification handler code here
	tips(6,3);
}
void CShuduDlg::OnSetfocusEDITy2() 
{
	// TODO: Add your control notification handler code here
	tips(6,4);
}
void CShuduDlg::OnSetfocusEDITy3() 
{
	// TODO: Add your control notification handler code here
	tips(6,5);
}
void CShuduDlg::OnSetfocusEDITy4() 
{
	// TODO: Add your control notification handler code here
	tips(7,3);
}
void CShuduDlg::OnSetfocusEDITy5() 
{
	// TODO: Add your control notification handler code here
	tips(7,4);
}
void CShuduDlg::OnSetfocusEDITy6() 
{
	// TODO: Add your control notification handler code here
	tips(7,5);
}
void CShuduDlg::OnSetfocusEDITy7() 
{
	// TODO: Add your control notification handler code here
	tips(8,3);
}
void CShuduDlg::OnSetfocusEDITy8() 
{
	// TODO: Add your control notification handler code here
	tips(8,4);
}
void CShuduDlg::OnSetfocusEDITy9() 
{
	// TODO: Add your control notification handler code here
	tips(8,5);
}
void CShuduDlg::OnSetfocusEDITz1() 
{
	// TODO: Add your control notification handler code here
	tips(6,6);
}
void CShuduDlg::OnSetfocusEDITz2() 
{
	// TODO: Add your control notification handler code here
	tips(6,7);
}
void CShuduDlg::OnSetfocusEDITz3() 
{
	// TODO: Add your control notification handler code here
	tips(6,8);
}
void CShuduDlg::OnSetfocusEDITz4() 
{
	// TODO: Add your control notification handler code here
	tips(7,6);
}
void CShuduDlg::OnSetfocusEDITz5() 
{
	// TODO: Add your control notification handler code here
	tips(7,7);
}
void CShuduDlg::OnSetfocusEDITz6() 
{
	// TODO: Add your control notification handler code here
	tips(7,8);
}
void CShuduDlg::OnSetfocusEDITz7() 
{
	// TODO: Add your control notification handler code here
	tips(8,6);
}
void CShuduDlg::OnSetfocusEDITz8() 
{
	// TODO: Add your control notification handler code here
	tips(8,7);
}
void CShuduDlg::OnSetfocusEDITz9() 
{
	// TODO: Add your control notification handler code here
	tips(8,8);
}

void CShuduDlg::OnBUTTONsave() //保存当前题目，用户做出的结果和答案
{
	// TODO: Add your control notification handler code here

	CString FilePathName="0";
	CFileDialog dlg(false,".txt","Sudoku.txt",OFN_OVERWRITEPROMPT,"Txt Files (*.txt)|*.txt|Data Files (*.dat)|*.dat|All Files (*.*)|*.*||");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	dlg.m_ofn.lpstrInitialDir=_T(".\\"); //这里就设置了对话框的默认目录
	if(dlg.DoModal()==IDOK) FilePathName=dlg.GetPathName();

	bool b_save=true;
	for(int aa=0;aa<=8;aa++)
		for(int bb=0;bb<=8;bb++){ if(sd_title[aa][bb]==-1) b_save=false; break;}	

	if(b_save && FilePathName!="0"){
				
			ofstream ofile;
			ofile.open(FilePathName);

			ofile<<"Sudoku:"<<endl;

			for(int ii=0;ii<=8;ii++){
				for(int jj=0;jj<=8;jj++){
					ofile<<sd_title[ii][jj]<<"  ";
				}
			ofile<<endl;
			}
		ofile<<"*********************************以上内容用于程序读取题目。"<<endl;

	ofile<<"数独题目："<<endl<<"  ";
	for(int i=0;i<=8;i++)
		for(int j=0;j<=8;j++){		
			if((j==0 && i==3) || (j==0 && i==6)) ofile<<"————————————"<<endl<<"  ";
			if(sd_title[i][j]!=0) ofile<<sd_title[i][j]<<"  ";
			else ofile<<"__ ";

			if(j==2 || j==5) ofile<<"| ";
			if((j==8 && i==2) ||(j==8 && i==5)) ofile<<endl;
			else if(j==8 && i==8) ofile<<endl<<endl;
			else if(j==8) ofile<<endl<<"  ";
		}
	ofile<<"您所做的结果："<<endl<<"  ";
	for(int a=0;a<=8;a++)
		for(int b=0;b<=8;b++){		
			if((b==0 && a==3) || (b==0 && a==6)) ofile<<"————————————"<<endl<<"  ";
			if(sd_read[a][b]!=0) ofile<<sd_read[a][b]<<"  ";
			else ofile<<"__ ";
			if(b==2 || b==5) ofile<<"| ";
			if((b==8 && a==2) ||(b==8 && a==5) ) ofile<<endl;
			else if(b==8 && a==8) ofile<<endl<<endl;
			else if(b==8) ofile<<endl<<"  ";		}

		if(read_noAnswer==0){
	ofile<<"答案为："<<endl<<"  ";
	for(int x=0;x<=8;x++)
		for(int y=0;y<=8;y++){		
			if((y==0 && x==3) || (y==0 && x==6)) ofile<<"————————————"<<endl<<"  ";
			if(sd[x][y]!=0) ofile<<sd[x][y]<<"  ";
			else ofile<<"__ ";
			if(y==2 || y==5) ofile<<"| ";
			if((y==8 && x==2) ||(y==8 && x==5)) ofile<<endl;
			else if(y==8) ofile<<endl<<"  ";		
		}	
		}
		else ofile<<"无答案"<<endl;
		ofile.close();
		MessageBox("保存成功！该题目及答案已保存到"+FilePathName,"保存文件成功",MB_OK);	
		}

	else if(b_save==false) MessageBox("保存失败！题目未生成，请重新生成题目","保存文件失败",MB_OK);	
	else MessageBox("保存失败！未选择路经，请重新选择","保存文件失败",MB_OK);	
}

void CShuduDlg::clear(CEdit &clear)//本函数用于 清空一个CEdit框的值
{
	clear.SetSel(0,-1,false);
	clear.Clear();
}

void CShuduDlg::OnBUTTONclear() //清空sd_title中所有0值所对应的 控制框的值
{
	// TODO: Add your control notification handler code here
	clear_s=1;
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_clean),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	if(sd_title[0][0]==0) clear(m_a11);
	if(sd_title[0][1]==0) clear(m_a22);
	if(sd_title[0][2]==0) clear(m_a33);
	if(sd_title[1][0]==0) clear(m_a44);
	if(sd_title[1][1]==0) clear(m_a55);
	if(sd_title[1][2]==0) clear(m_a66);
	if(sd_title[2][0]==0) clear(m_a77);
	if(sd_title[2][1]==0) clear(m_a88);
	if(sd_title[2][2]==0) clear(m_a99);

	if(sd_title[0][3]==0) clear(m_b11);
	if(sd_title[0][4]==0) clear(m_b22);
	if(sd_title[0][5]==0) clear(m_b33);
	if(sd_title[1][3]==0) clear(m_b44);
	if(sd_title[1][4]==0) clear(m_b55);
	if(sd_title[1][5]==0) clear(m_b66);
	if(sd_title[2][3]==0) clear(m_b77);
	if(sd_title[2][4]==0) clear(m_b88);
	if(sd_title[2][5]==0) clear(m_b99);

	if(sd_title[0][6]==0) clear(m_c11);
	if(sd_title[0][7]==0) clear(m_c22);
	if(sd_title[0][8]==0) clear(m_c33);
	if(sd_title[1][6]==0) clear(m_c44);
	if(sd_title[1][7]==0) clear(m_c55);
	if(sd_title[1][8]==0) clear(m_c66);
	if(sd_title[2][6]==0) clear(m_c77);
	if(sd_title[2][7]==0) clear(m_c88);
	if(sd_title[2][8]==0) clear(m_c99);

	if(sd_title[3][0]==0) clear(m_d11);
	if(sd_title[3][1]==0) clear(m_d22);
	if(sd_title[3][2]==0) clear(m_d33);
	if(sd_title[4][0]==0) clear(m_d44);
	if(sd_title[4][1]==0) clear(m_d55);
	if(sd_title[4][2]==0) clear(m_d66);
	if(sd_title[5][0]==0) clear(m_d77);
	if(sd_title[5][1]==0) clear(m_d88);
	if(sd_title[5][2]==0) clear(m_d99);

	if(sd_title[3][3]==0) clear(m_e11);
	if(sd_title[3][4]==0) clear(m_e22);
	if(sd_title[3][5]==0) clear(m_e33);
	if(sd_title[4][3]==0) clear(m_e44);
	if(sd_title[4][4]==0) clear(m_e55);
	if(sd_title[4][5]==0) clear(m_e66);
	if(sd_title[5][3]==0) clear(m_e77);
	if(sd_title[5][4]==0) clear(m_e88);
	if(sd_title[5][5]==0) clear(m_e99);

	if(sd_title[3][6]==0) clear(m_f11);
	if(sd_title[3][7]==0) clear(m_f22);
	if(sd_title[3][8]==0) clear(m_f33);
	if(sd_title[4][6]==0) clear(m_f44);
	if(sd_title[4][7]==0) clear(m_f55);
	if(sd_title[4][8]==0) clear(m_f66);
	if(sd_title[5][6]==0) clear(m_f77);
	if(sd_title[5][7]==0) clear(m_f88);
	if(sd_title[5][8]==0) clear(m_f99);

	if(sd_title[6][0]==0) clear(m_x11);
	if(sd_title[6][1]==0) clear(m_x22);
	if(sd_title[6][2]==0) clear(m_x33);
	if(sd_title[7][0]==0) clear(m_x44);
	if(sd_title[7][1]==0) clear(m_x55);
	if(sd_title[7][2]==0) clear(m_x66);
	if(sd_title[8][0]==0) clear(m_x77);
	if(sd_title[8][1]==0) clear(m_x88);
	if(sd_title[8][2]==0) clear(m_x99);

	if(sd_title[6][3]==0) clear(m_y11);
	if(sd_title[6][4]==0) clear(m_y22);
	if(sd_title[6][5]==0) clear(m_y33);
	if(sd_title[7][3]==0) clear(m_y44);
	if(sd_title[7][4]==0) clear(m_y55);
	if(sd_title[7][5]==0) clear(m_y66);
	if(sd_title[8][3]==0) clear(m_y77);
	if(sd_title[8][4]==0) clear(m_y88);
	if(sd_title[8][5]==0) clear(m_y99);

	if(sd_title[6][6]==0) clear(m_z11);
	if(sd_title[6][7]==0) clear(m_z22);
	if(sd_title[6][8]==0) clear(m_z33);
	if(sd_title[7][6]==0) clear(m_z44);
	if(sd_title[7][7]==0) clear(m_z55);
	if(sd_title[7][8]==0) clear(m_z66);
	if(sd_title[8][6]==0) clear(m_z77);
	if(sd_title[8][7]==0) clear(m_z88);
	if(sd_title[8][8]==0) clear(m_z99);
	clear_s=0;

}



void CShuduDlg::show(int h,int l,CEdit &show)//用于显示sd数组的值，在显示解答函数用利用
{
	CString a;
	a.Format("%d",sd[h][l]);
	show.SetWindowText(a);
}

void CShuduDlg::setReadOnly()//本函数用于设置只读与否，并在sd_title中所有值非0的位置设置只读并显示该值，否则清空并取消只读
{
	if(sd_title[0][0]!=0) {m_a11.SetReadOnly(true);show_title(0,0,m_a11);}
	else m_a11.SetReadOnly(false);clear(m_a11);

	if(sd_title[0][1]!=0) {m_a22.SetReadOnly(true);show_title(0,1,m_a22);}
	else m_a22.SetReadOnly(false);clear(m_a22);

	if(sd_title[0][2]!=0) {m_a33.SetReadOnly(true);show_title(0,2,m_a33);}
	else m_a33.SetReadOnly(false);clear(m_a33);

	if(sd_title[1][0]!=0) {m_a44.SetReadOnly(true);show_title(1,0,m_a44);}
	else m_a44.SetReadOnly(false);clear(m_a44);

	if(sd_title[1][1]!=0) {m_a55.SetReadOnly(true);show_title(1,1,m_a55);}
	else m_a55.SetReadOnly(false);clear(m_a55);

	if(sd_title[1][2]!=0) {m_a66.SetReadOnly(true);show_title(1,2,m_a66);}
	else m_a66.SetReadOnly(false);clear(m_a66);

	if(sd_title[2][0]!=0) {m_a77.SetReadOnly(true);show_title(2,0,m_a77);}
	else m_a77.SetReadOnly(false);clear(m_a77);

	if(sd_title[2][1]!=0) {m_a88.SetReadOnly(true);show_title(2,1,m_a88);}
	else m_a88.SetReadOnly(false);clear(m_a88);

	if(sd_title[2][2]!=0) {m_a99.SetReadOnly(true);show_title(2,2,m_a99);}
	else m_a99.SetReadOnly(false);clear(m_a99);


	if(sd_title[0][3]!=0) {m_b11.SetReadOnly(true);show_title(0,3,m_b11);}
	else m_b11.SetReadOnly(false);clear(m_b11);

	if(sd_title[0][4]!=0) {m_b22.SetReadOnly(true);show_title(0,4,m_b22);}
	else m_b22.SetReadOnly(false);clear(m_b22);

	if(sd_title[0][5]!=0) {m_b33.SetReadOnly(true);show_title(0,5,m_b33);}
	else m_b33.SetReadOnly(false);clear(m_b33);

	if(sd_title[1][3]!=0) {m_b44.SetReadOnly(true);show_title(1,3,m_b44);}
	else m_b44.SetReadOnly(false);clear(m_b44);

	if(sd_title[1][4]!=0) {m_b55.SetReadOnly(true);show_title(1,4,m_b55);}
	else m_b55.SetReadOnly(false);clear(m_b55);

	if(sd_title[1][5]!=0) {m_b66.SetReadOnly(true);show_title(1,5,m_b66);}
	else m_b66.SetReadOnly(false);clear(m_b66);

	if(sd_title[2][3]!=0) {m_b77.SetReadOnly(true);show_title(2,3,m_b77);}
	else m_b77.SetReadOnly(false);clear(m_b77);

	if(sd_title[2][4]!=0) {m_b88.SetReadOnly(true);show_title(2,4,m_b88);}
	else m_b88.SetReadOnly(false);clear(m_b88);

	if(sd_title[2][5]!=0) {m_b99.SetReadOnly(true);show_title(2,5,m_b99);}
	else m_b99.SetReadOnly(false);clear(m_b99);



	if(sd_title[0][6]!=0) {m_c11.SetReadOnly(true);show_title(0,6,m_c11);}
	else m_c11.SetReadOnly(false);clear(m_c11);

	if(sd_title[0][7]!=0) {m_c22.SetReadOnly(true);show_title(0,7,m_c22);}
	else m_c22.SetReadOnly(false);clear(m_c22);

	if(sd_title[0][8]!=0) {m_c33.SetReadOnly(true);show_title(0,8,m_c33);}
	else m_c33.SetReadOnly(false);clear(m_c33);

	if(sd_title[1][6]!=0) {m_c44.SetReadOnly(true);show_title(1,6,m_c44);}
	else m_c44.SetReadOnly(false);clear(m_c44);

	if(sd_title[1][7]!=0) {m_c55.SetReadOnly(true);show_title(1,7,m_c55);}
	else m_c55.SetReadOnly(false);clear(m_c55);

	if(sd_title[1][8]!=0) {m_c66.SetReadOnly(true);show_title(1,8,m_c66);}
	else m_c66.SetReadOnly(false);clear(m_c66);

	if(sd_title[2][6]!=0) {m_c77.SetReadOnly(true);show_title(2,6,m_c77);}
	else m_c77.SetReadOnly(false);clear(m_c77);

	if(sd_title[2][7]!=0) {m_c88.SetReadOnly(true);show_title(2,7,m_c88);}
	else m_c88.SetReadOnly(false);clear(m_c88);

	if(sd_title[2][8]!=0) {m_c99.SetReadOnly(true);show_title(2,8,m_c99);}
	else m_c99.SetReadOnly(false);clear(m_c99);


	if(sd_title[3][0]!=0) {m_d11.SetReadOnly(true);show_title(3,0,m_d11);}
	else m_d11.SetReadOnly(false);clear(m_d11);

	if(sd_title[3][1]!=0) {m_d22.SetReadOnly(true);show_title(3,1,m_d22);}
	else m_d22.SetReadOnly(false);clear(m_d22);

	if(sd_title[3][2]!=0) {m_d33.SetReadOnly(true);show_title(3,2,m_d33);}
	else m_d33.SetReadOnly(false);clear(m_d33);

	if(sd_title[4][0]!=0) {m_d44.SetReadOnly(true);show_title(4,0,m_d44);}
	else m_d44.SetReadOnly(false);clear(m_d44);

	if(sd_title[4][1]!=0) {m_d55.SetReadOnly(true);show_title(4,1,m_d55);}
	else m_d55.SetReadOnly(false);clear(m_d55);

	if(sd_title[4][2]!=0) {m_d66.SetReadOnly(true);show_title(4,2,m_d66);}
	else m_d66.SetReadOnly(false);clear(m_d66);

	if(sd_title[5][0]!=0) {m_d77.SetReadOnly(true);show_title(5,0,m_d77);}
	else m_d77.SetReadOnly(false);clear(m_d77);

	if(sd_title[5][1]!=0) {m_d88.SetReadOnly(true);show_title(5,1,m_d88);}
	else m_d88.SetReadOnly(false);clear(m_d88);

	if(sd_title[5][2]!=0) {m_d99.SetReadOnly(true);show_title(5,2,m_d99);}
	else m_d99.SetReadOnly(false);clear(m_d99);



	if(sd_title[3][3]!=0) {m_e11.SetReadOnly(true);show_title(3,3,m_e11);}
	else m_e11.SetReadOnly(false);clear(m_e11);

	if(sd_title[3][4]!=0) {m_e22.SetReadOnly(true);show_title(3,4,m_e22);}
	else m_e22.SetReadOnly(false);clear(m_e22);

	if(sd_title[3][5]!=0) {m_e33.SetReadOnly(true);show_title(3,5,m_e33);}
	else m_e33.SetReadOnly(false);clear(m_e33);

	if(sd_title[4][3]!=0) {m_e44.SetReadOnly(true);show_title(4,3,m_e44);}
	else m_e44.SetReadOnly(false);clear(m_e44);

	if(sd_title[4][4]!=0) {m_e55.SetReadOnly(true);show_title(4,4,m_e55);}
	else m_e55.SetReadOnly(false);clear(m_e55);

	if(sd_title[4][5]!=0) {m_e66.SetReadOnly(true);show_title(4,5,m_e66);}
	else m_e66.SetReadOnly(false);clear(m_e66);

	if(sd_title[5][3]!=0) {m_e77.SetReadOnly(true);show_title(5,3,m_e77);}
	else m_e77.SetReadOnly(false);clear(m_e77);

	if(sd_title[5][4]!=0) {m_e88.SetReadOnly(true);show_title(5,4,m_e88);}
	else m_e88.SetReadOnly(false);clear(m_e88);

	if(sd_title[5][5]!=0) {m_e99.SetReadOnly(true);show_title(5,5,m_e99);}
	else m_e99.SetReadOnly(false);clear(m_e99);



	if(sd_title[3][6]!=0) {m_f11.SetReadOnly(true);show_title(3,6,m_f11);}
	else m_f11.SetReadOnly(false);clear(m_f11);

	if(sd_title[3][7]!=0) {m_f22.SetReadOnly(true);show_title(3,7,m_f22);}
	else m_f22.SetReadOnly(false);clear(m_f22);

	if(sd_title[3][8]!=0) {m_f33.SetReadOnly(true);show_title(3,8,m_f33);}
	else m_f33.SetReadOnly(false);clear(m_f33);

	if(sd_title[4][6]!=0) {m_f44.SetReadOnly(true);show_title(4,6,m_f44);}
	else m_f44.SetReadOnly(false);clear(m_f44);

	if(sd_title[4][7]!=0) {m_f55.SetReadOnly(true);show_title(4,7,m_f55);}
	else m_f55.SetReadOnly(false);clear(m_f55);

	if(sd_title[4][8]!=0) {m_f66.SetReadOnly(true);show_title(4,8,m_f66);}
	else m_f66.SetReadOnly(false);clear(m_f66);

	if(sd_title[5][6]!=0) {m_f77.SetReadOnly(true);show_title(5,6,m_f77);}
	else m_f77.SetReadOnly(false);clear(m_f77);

	if(sd_title[5][7]!=0) {m_f88.SetReadOnly(true);show_title(5,7,m_f88);}
	else m_f88.SetReadOnly(false);clear(m_f88);

	if(sd_title[5][8]!=0) {m_f99.SetReadOnly(true);show_title(5,8,m_f99);}
	else m_f99.SetReadOnly(false);clear(m_f99);



	if(sd_title[6][0]!=0) {m_x11.SetReadOnly(true);show_title(6,0,m_x11);}
	else m_x11.SetReadOnly(false);clear(m_x11);

	if(sd_title[6][1]!=0) {m_x22.SetReadOnly(true);show_title(6,1,m_x22);}
	else m_x22.SetReadOnly(false);clear(m_x22);

	if(sd_title[6][2]!=0) {m_x33.SetReadOnly(true);show_title(6,2,m_x33);}
	else m_x33.SetReadOnly(false);clear(m_x33);

	if(sd_title[7][0]!=0) {m_x44.SetReadOnly(true);show_title(7,0,m_x44);}
	else m_x44.SetReadOnly(false);clear(m_x44);

	if(sd_title[7][1]!=0) {m_x55.SetReadOnly(true);show_title(7,1,m_x55);}
	else m_x55.SetReadOnly(false);clear(m_x55);

	if(sd_title[7][2]!=0) {m_x66.SetReadOnly(true);show_title(7,2,m_x66);}
	else m_x66.SetReadOnly(false);clear(m_x66);

	if(sd_title[8][0]!=0) {m_x77.SetReadOnly(true);show_title(8,0,m_x77);}
	else m_x77.SetReadOnly(false);clear(m_x77);

	if(sd_title[8][1]!=0) {m_x88.SetReadOnly(true);show_title(8,1,m_x88);}
	else m_x88.SetReadOnly(false);clear(m_x88);

	if(sd_title[8][2]!=0) {m_x99.SetReadOnly(true);show_title(8,2,m_x99);}
	else m_x99.SetReadOnly(false);clear(m_x99);



	if(sd_title[6][3]!=0) {m_y11.SetReadOnly(true);show_title(6,3,m_y11);}
	else m_y11.SetReadOnly(false);clear(m_y11);

	if(sd_title[6][4]!=0) {m_y22.SetReadOnly(true);show_title(6,4,m_y22);}
	else m_y22.SetReadOnly(false);clear(m_y22);

	if(sd_title[6][5]!=0) {m_y33.SetReadOnly(true);show_title(6,5,m_y33);}
	else m_y33.SetReadOnly(false);clear(m_y33);

	if(sd_title[7][3]!=0) {m_y44.SetReadOnly(true);show_title(7,3,m_y44);}
	else m_y44.SetReadOnly(false);clear(m_y44);

	if(sd_title[7][4]!=0) {m_y55.SetReadOnly(true);show_title(7,4,m_y55);}
	else m_y55.SetReadOnly(false);clear(m_y55);

	if(sd_title[7][5]!=0) {m_y66.SetReadOnly(true);show_title(7,5,m_y66);}
	else m_y66.SetReadOnly(false);clear(m_y66);

	if(sd_title[8][3]!=0) {m_y77.SetReadOnly(true);show_title(8,3,m_y77);}
	else m_y77.SetReadOnly(false);clear(m_y77);

	if(sd_title[8][4]!=0) {m_y88.SetReadOnly(true);show_title(8,4,m_y88);}
	else m_y88.SetReadOnly(false);clear(m_y88);

	if(sd_title[8][5]!=0) {m_y99.SetReadOnly(true);show_title(8,5,m_y99);}
	else m_y99.SetReadOnly(false);clear(m_y99);


	if(sd_title[6][6]!=0) {m_z11.SetReadOnly(true);show_title(6,6,m_z11);}
	else m_z11.SetReadOnly(false);clear(m_z11);

	if(sd_title[6][7]!=0) {m_z22.SetReadOnly(true);show_title(6,7,m_z22);}
	else m_z22.SetReadOnly(false);clear(m_z22);

	if(sd_title[6][8]!=0) {m_z33.SetReadOnly(true);show_title(6,8,m_z33);}
	else m_z33.SetReadOnly(false);clear(m_z33);

	if(sd_title[7][6]!=0) {m_z44.SetReadOnly(true);show_title(7,6,m_z44);}
	else m_z44.SetReadOnly(false);clear(m_z44);

	if(sd_title[7][7]!=0) {m_z55.SetReadOnly(true);show_title(7,7,m_z55);}
	else m_z55.SetReadOnly(false);clear(m_z55);

	if(sd_title[7][8]!=0) {m_z66.SetReadOnly(true);show_title(7,8,m_z66);}
	else m_z66.SetReadOnly(false);clear(m_z66);

	if(sd_title[8][6]!=0) {m_z77.SetReadOnly(true);show_title(8,6,m_z77);}
	else m_z77.SetReadOnly(false);clear(m_z77);

	if(sd_title[8][7]!=0) {m_z88.SetReadOnly(true);show_title(8,7,m_z88);}
	else m_z88.SetReadOnly(false);clear(m_z88);

	if(sd_title[8][8]!=0) {m_z99.SetReadOnly(true);show_title(8,8,m_z99);}
	else m_z99.SetReadOnly(false);clear(m_z99);


}

void CShuduDlg::show_title(int h, int l, CEdit &show_t)//本函数用于显示sd_title中某位置的数字
{
	CString a;
	a.Format("%d",sd_title[h][l]);
	show_t.SetWindowText(a);

}


int CShuduDlg::part(int h, int l)//判断参数位置为第几部分
{
	int part=0;
	if(0<=h && h<=2 && 0<=l && l<=2) return part=1;
	if(0<=h && h<=2 && 3<=l && l<=5) return part=2;
	if(0<=h && h<=2 && 6<=l && l<=8) return part=3;
	if(3<=h && h<=5 && 0<=l && l<=2) return part=4;
	if(3<=h && h<=5 && 3<=l && l<=5) return part=5;
	if(3<=h && h<=5 && 6<=l && l<=8) return part=6;
	if(6<=h && h<=8 && 0<=l && l<=2) return part=7;
	if(6<=h && h<=8 && 3<=l && l<=5) return part=8;
	if(6<=h && h<=8 && 6<=l && l<=8) return part=9;
	else return -1;
}

void CShuduDlg::OnBUTTON_tipsSwitch() 
{
	// TODO: Add your control notification handler code here
	if(tips_switch==0){
		m_tipsOnOff.SetWindowText("开");
		if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_tipson),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	}
	else{
		m_tipsOnOff.SetWindowText("关");
		if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_tipsoff),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	}
	tips_switchs++;
	tips_switch=tips_switchs%2;
	m_tips1.SetWindowText("×");
	m_tips2.SetWindowText("×");
	m_tips3.SetWindowText("×");
	m_tips4.SetWindowText("×");
	m_tips5.SetWindowText("×");
	m_tips6.SetWindowText("×");
	m_tips7.SetWindowText("×");
	m_tips8.SetWindowText("×");
	m_tips9.SetWindowText("×");

}

void CShuduDlg::OnBUTTONread()//本函数用于读取外界题目，并开始游戏！
{
	// TODO: Add your control notification handler code here
	CString FilePathName;
	CFileDialog dlg(true,".txt","Sudoku.txt",OFN_OVERWRITEPROMPT,"Txt Files (*.txt)|*.txt|Data Files (*.dat)|*.dat|All Files (*.*)|*.*||");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	dlg.m_ofn.lpstrInitialDir=_T(".\\"); //这里就设置了对话框的默认目录
	if(dlg.DoModal()==IDOK)
		FilePathName=dlg.GetPathName();
	ifstream ifile;
	ifile.open(FilePathName);
	char c_read[7];
	
	for(int r=0;r<7;r++) ifile>>c_read[r];
	ifile.get();

	bool b_read=true;
	if(c_read[0]!='S') {b_read=false;goto SSS;}
	if(c_read[1]!='u') {b_read=false;goto SSS;}
	if(c_read[2]!='d') {b_read=false;goto SSS;}
	if(c_read[3]!='o') {b_read=false;goto SSS;}
	if(c_read[4]!='k') {b_read=false;goto SSS;}
	if(c_read[5]!='u') {b_read=false;goto SSS;}
	if(c_read[6]!=':') {b_read=false;goto SSS;}

SSS:
	if(b_read)
	{

	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++) ifile>>sd_title[i][j];

	ifile.close();
	read_noAnswer=1;

//	bool b_read=true;
//	for(int ii=0;ii<9;ii++)
//		for(int jj=0;jj<9;jj++){
//			if(sd_title[ii][jj]==-1) b_read=false;break;
//		}
	
//	if(b_read){
		MessageBox("读取成功，游戏开始","读取成功",MB_OK);
	
//重复new中的操作
	OnBUTTONclear();
	condition=1;
	k=::GetTickCount(); //计时器清零
//重新初始化提示开关，设置为关
	tips_switch=2;
	tips_switchs=2;//提示开关控制
	tips_switch=tips_switchs%2;
	m_tipsOnOff.SetWindowText("关");
	m_tips1.SetWindowText("×");
	m_tips2.SetWindowText("×");
	m_tips3.SetWindowText("×");
	m_tips4.SetWindowText("×");
	m_tips5.SetWindowText("×");
	m_tips6.SetWindowText("×");
	m_tips7.SetWindowText("×");
	m_tips8.SetWindowText("×");
	m_tips9.SetWindowText("×");


	for(int x=0;x<9;x++)
		for(int y=0;y<9;y++){
			sd_read[x][y]=sd_title[x][y];
		}//复制title到read中

	setReadOnly();
	}
	else 
		MessageBox("读取失败，请重新读取","读取失败",MB_OK);
 
}

//问题：如何在程序中添加一个数据文件，用于保存题目，
//需要 添加一个 读入题目 按钮，并实现读入功能，可以读入如下几种格式（如何判断这几种格式，并调用相应的函数去读取）

/*

708010003100500000000008020024301800000020106800000000000206040230080000640000500

7 0 8 0 1 0 0 0 3 1 0 0 5 0 0 0 0 0 0 0 0 0 0 8 0 2 0 0 2 4 3 0 1 8 0 0 0 0 0 0 2 0 1 0 6 8 0 0 0 0 0 0 0 0 0 0 0 2 0 6 0 4 0 2 3 0 0 8 0 0 0 0 6 4 0 0 0 0 5 0 0 

708010003
100500000
000008020
024301800
000020106
800000000
000206040
230080000
640000500


7 0 8 0 1 0 0 0 3 
1 0 0 5 0 0 0 0 0 
0 0 0 0 0 8 0 2 0 
0 2 4 3 0 1 8 0 0 
0 0 0 0 2 0 1 0 6 
8 0 0 0 0 0 0 0 0 
0 0 0 2 0 6 0 4 0 
2 3 0 0 8 0 0 0 0 
6 4 0 0 0 0 5 0 0 


7  0  8  | 0  1  0  | 0  0  3  
1  0  0  | 5  0  0  | 0  0  0  
0  0  0  | 0  0  8  | 0  2  0  
---------------------------
0  2  4  | 3  0  1  | 8  0  0  
0  0  0  | 0  2  0  | 1  0  6  
8  0  0  | 0  0  0  | 0  0  0  
---------------------------
0  0  0  | 2  0  6  | 0  4  0  
2  3  0  | 0  8  0  | 0  0  0  
6  4  0  | 0  0  0  | 5  0  0  

*/

//需实现数据文件随机读取题目

//或者：如何将题目生成的空白 分成4个等级，（随机数，概率问题）


void CShuduDlg::generate(int i, int j)
{
	if (j == 9)
        generate(i+1, 0);
    if (i == 9 )
    {
        found = true;
        return;
    }
    
    int num;
    int squPos;
    bool flag = false;
    num = rand()%9;
    squPos = i / 3 * 3 + j / 3;
    for (int k=0; k<9; k++)
    {
        num = num % 9 + 1;
        if (!((row[i][num]) || (col[j][num]) || (squ[squPos][num])))
        {
            sd[i][j] = num;
            row[i][num] = true;
            col[j][num] = true;
            squ[squPos][num] = true;
            generate(i, j+1);
            if (found)
                return;
            row[i][num] = false;
            col[j][num] = false;
            squ[squPos][num] = false;
        }
    }
    
    return;

}

void CShuduDlg::OnOK()
{
	// TODO: Add extra validation here
//	PlaySound("SystemStart",NULL,SND_ALIAS|SND_ASYNC);
//	Sleep(3000);

	CDialog::OnOK();
}

void CShuduDlg::OnBUTTONchooseMusic() 
{
	// TODO: Add your control notification handler code here
	FilePathName_music=FilePathName_choose;
	FileExtName;
	if(sound_switch==1) MessageBox("如需播放背景音乐，请将[音效开关]与[音乐开关]打开","请打开音效和音乐",MB_OK);
	else if(music_switch==1) MessageBox("如需播放背景音乐，请将[音乐开关]打开","请打开音乐",MB_OK);
	else{
		CFileDialog dlg(true,".mp3","",OFN_OVERWRITEPROMPT,"Audio Files (*.mp3,*.wma,*.wav)|*.mp3;*.wma;*.wav|All Files (*.*)|*.*||");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
		dlg.m_ofn.lpstrInitialDir=_T(".\\"); //这里就设置了对话框的默认目录
		if(dlg.DoModal()==IDOK){
			FilePathName_choose=dlg.GetPathName();
			FileExtName=dlg.GetFileExt();		
		}

		if(FilePathName_choose!=FilePathName_music){
			if(FileExtName=="wav"){
				mciSendString("Close "+FilePathName_music,0,0,NULL);
				mciSendString("play "+FilePathName_choose,0,0,NULL);
				vol.Format("%d",1000-m_vol.GetPos());
				mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
			}
			else{
				mciSendString("Close "+FilePathName_music,0,0,NULL);
				mciSendString("play "+FilePathName_choose+" repeat",0,0,NULL);
				vol.Format("%d",1000-m_vol.GetPos());
				mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
			}

		}

	}
	
}

void CShuduDlg::OnBUTTONmusicSwitch() 
{
	// TODO: Add your control notification handler code here
	music++;
	music_switch=music%2;
//	music_one=0;
//	music_two=0;

	if(sound_switch==0){
		m_sound.SetWindowText("开");
	}
	else{
		m_sound.SetWindowText("关");
	}
	
	if(sound_switch==0 && music_switch==0){
		m_music.SetWindowText("开");

			if(FileExtName=="wav"){
//				mciSendString("Close "+FilePathName_music,0,0,NULL);
				mciSendString("play "+FilePathName_choose,0,0,NULL);
				vol.Format("%d",1000-m_vol.GetPos());
				mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
			}
			else{
//				mciSendString("Close "+FilePathName_music,0,0,NULL);
				mciSendString("play "+FilePathName_choose+" repeat",0,0,NULL);
				vol.Format("%d",1000-m_vol.GetPos());
				mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
			}
	}
	else{
		m_music.SetWindowText("关");

//		if(FilePathName_choose!=FilePathName_music){
				mciSendString("pause "+FilePathName_music,0,0,NULL);
//		}
//		else 
			mciSendString("pause "+FilePathName_choose,0,0,NULL);

		
	}}

void CShuduDlg::OnBUTTONsoundSwitch() 
{
	// TODO: Add your control notification handler code here
	sound++;
	sound_switch=sound%2;
//	sound_one=0;
	if(sound_switch==0){
		m_sound.SetWindowText("开");
		if(music_switch==0){
			m_music.SetWindowText("开");
			if(FileExtName=="wav"){
//				mciSendString("Close "+FilePathName_music,0,0,NULL);
				mciSendString("play "+FilePathName_choose,0,0,NULL);
				vol.Format("%d",1000-m_vol.GetPos());
				mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
			}
			else{
//				mciSendString("Close "+FilePathName_music,0,0,NULL);
				mciSendString("play "+FilePathName_choose+" repeat",0,0,NULL);
				vol.Format("%d",1000-m_vol.GetPos());
				mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
			}
		}
		else m_music.SetWindowText("关");
	}
	else{
		m_sound.SetWindowText("关");
		m_music.SetWindowText("关");
		mciSendString("pause "+FilePathName_choose,0,0,NULL);
		mciSendString("pause "+FilePathName_music,0,0,NULL);
	}
}

void CShuduDlg::OnCustomdrawSLIDERsound(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	vol.Format("%d",1000-m_vol.GetPos());
	mciSendString("setaudio "+FilePathName_choose+" volume to "+vol,0,0,NULL);
	mciSendString("setaudio "+FilePathName_music+" volume to "+vol,0,0,NULL);
	*pResult = 0;
}

void CShuduDlg::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	CAboutDlg dlgAbout;
//	dlgAbout.OnOK();
	if(sound_switch==0) PlaySound(MAKEINTRESOURCE(IDR_WAVE_about),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	
	dlgAbout.DoModal();

	
//	CDialog::WinHelp(dwData, nCmd);
}
