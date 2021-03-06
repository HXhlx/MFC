#pragma once
#include <vector>


// Open 对话框

class Open : public CDialogEx
{
	DECLARE_DYNAMIC(Open)

public:
	Open(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Open();

	// 对话框数据
	enum { IDD = IDD_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool flag;
	int n;
	virtual BOOL OnInitDialog();
	COleDateTime time;
	CComboBox province1;
	CComboBox province2;
	CComboBox city1;
	CString sprovince1;
	std::vector<CString>province;
	afx_msg void OnSelchangeProvince1();
	CString idcard;
	CString ID;
	CListCtrl information;
	CString name;
	CString passsure;
	CString password;
	CString phone;
	CString telephone;
	CComboBox type;
	double charge;
	CComboBox city2;
	afx_msg void OnBnClickedSignin();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnSetfocusPasswordo();
	afx_msg void OnKillfocusPasssure();
	afx_msg void OnKillfocusPasswordo();
	afx_msg void OnSelchangeType();
	CString stype;
	afx_msg void OnKillfocusId();
	afx_msg void OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult);
	CString sprovince2;
	CString scity2;
	CString scity1;
	afx_msg void OnSelchangeProvince2();
	void SelchangeProvince(CComboBox&, CString&, CString&);
};
