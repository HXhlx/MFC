#pragma once


// Withdrawal �Ի���

class Withdrawal : public CDialogEx
{
	DECLARE_DYNAMIC(Withdrawal)

public:
	Withdrawal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Withdrawal();

// �Ի�������
	enum { IDD = IDD_WITHDRAWAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
