#pragma once


// Sys �Ի���

class Sys : public CDialogEx
{
	DECLARE_DYNAMIC(Sys)

public:
	Sys(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Sys();

// �Ի�������
	enum { IDD = IDD_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox limit;
	CString slimit;
	CString New;
	CString Newsure;
//	CEdit old;
	CString passsure;
	CString old;
	CString password;
	CString user;
	CListBox userlist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
//	CButton logout;
	afx_msg void OnSetfocusOld();
	afx_msg void OnSetfocusNew();
	afx_msg void OnSetfocusNewsure();
	int n;
	afx_msg void OnKillfocusUserlist();
};
