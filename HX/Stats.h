#pragma once


// Stats 对话框

class Stats : public CDialogEx
{
	DECLARE_DYNAMIC(Stats)

public:
	Stats(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Stats();

// 对话框数据
	enum { IDD = IDD_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl information;
	CString passsure;
	CString password;
	CString ID;
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusPassword();
	afx_msg void OnKillfocusPassword();
	afx_msg void OnKillfocusPasssure();
	afx_msg void OnMaxtextPasssure();
	afx_msg void OnKillfocusId();
	bool flag;
};
