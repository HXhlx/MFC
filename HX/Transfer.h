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
};
