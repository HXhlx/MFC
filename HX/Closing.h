#pragma once


// Closing �Ի���

class Closing : public CDialogEx
{
	DECLARE_DYNAMIC(Closing)

public:
	Closing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Closing();

// �Ի�������
	enum { IDD = IDD_CLOSING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillfocusId();
	afx_msg void OnKillfocusPasssure();
	afx_msg void OnKillfocusPassword();
	afx_msg void OnMaxtextPasssure();
	CString passsure;
	CString password;
	CListCtrl information;
	CString ID;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClean();
	afx_msg void OnSetfocusPassword();
	bool flag;
};
