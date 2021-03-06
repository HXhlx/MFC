#pragma once


// Withdrawal 对话框

class Withdrawal : public CDialogEx
{
	DECLARE_DYNAMIC(Withdrawal)

public:
	Withdrawal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Withdrawal();

// 对话框数据
	enum { IDD = IDD_WITHDRAWAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString ID;
	CListCtrl information;
	CString passsure;
	CString password;
	double charge;
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusPassword();
	afx_msg void OnKillfocusPassword();
	afx_msg void OnKillfocusPasssure();
	afx_msg void OnMaxtextPasssure();
	bool flag;
	afx_msg void OnKillfocusId();
	afx_msg void OnBnClickedClean();
	int n;
	afx_msg void OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult);
};
