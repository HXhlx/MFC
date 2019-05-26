#pragma once


// Deposit 对话框

class Deposit : public CDialogEx
{
	DECLARE_DYNAMIC(Deposit)

public:
	Deposit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Deposit();

// 对话框数据
	enum { IDD = IDD_DEPOSIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString passsure;
	CString password;
	CString ID;
	CListCtrl information;
	double rate;
	CComboBox time;
	CComboBox type;
	CString stype;
	CString stime;
	afx_msg void OnSelchangeTyped();
	afx_msg void OnSetfocusPassword();
	afx_msg void OnKillfocusPassword();
	afx_msg void OnKillfocusPasssure();
	afx_msg void OnMaxtextPasssure();
	double charge;
	void Rate();
	double Ttime;
	afx_msg void OnSelchangeTime();
	bool flag;
};
