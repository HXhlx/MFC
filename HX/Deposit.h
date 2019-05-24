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
};
