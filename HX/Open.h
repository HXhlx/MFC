#pragma once


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
};
