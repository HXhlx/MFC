#pragma once


// Closing 对话框

class Closing : public CDialogEx
{
	DECLARE_DYNAMIC(Closing)

public:
	Closing(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Closing();

// 对话框数据
	enum { IDD = IDD_CLOSING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
