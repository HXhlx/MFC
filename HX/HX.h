
// HX.h : HX 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CHXApp:
// 有关此类的实现，请参阅 HX.cpp
//

class CHXApp : public CWinAppEx
{
public:
	CHXApp();
	_ConnectionPtr m_pConnection;
	ULONG_PTR m_token;
// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHXApp theApp;
extern _RecordsetPtr m_pRecordset;
extern void GetRecord(const CString SQL);//获取记录集
extern CString  GetFieldValue(long index);//取记录集字段信息