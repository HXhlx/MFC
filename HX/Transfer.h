#pragma once


// Transfer 对话框

class Transfer : public CDialogEx
{
	DECLARE_DYNAMIC(Transfer)

public:
	Transfer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Transfer();

// 对话框数据
	enum { IDD = IDD_TRANSFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl information;
//	CString namee;
//	CString nameg;
	CString passsure;
	CString password;
	CString idg;
	CString ide;
	double charge;
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusPassword();
	afx_msg void OnKillfocusPassword();
	afx_msg void OnKillfocusPasssure();
	afx_msg void OnMaxtextPasssure();
	afx_msg void OnKillfocusIde();
	afx_msg void OnKillfocusIdg();
	afx_msg void OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult);
	bool flag;
	int n;
	afx_msg void OnBnClickedClean();
	CString name;
};
