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
};
