#pragma once


// Sys 对话框

class Sys : public CDialogEx
{
	DECLARE_DYNAMIC(Sys)

public:
	Sys(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sys();

// 对话框数据
	enum { IDD = IDD_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
