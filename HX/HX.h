
// HX.h : HX Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CHXApp:
// �йش����ʵ�֣������ HX.cpp
//

class CHXApp : public CWinAppEx
{
public:
	CHXApp();
	_ConnectionPtr m_pConnection;
	ULONG_PTR m_token;
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
extern void GetRecord(const CString SQL);//��ȡ��¼��
extern CString  GetFieldValue(long index);//ȡ��¼���ֶ���Ϣ