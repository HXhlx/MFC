#pragma once


// Deposit �Ի���

class Deposit : public CDialogEx
{
	DECLARE_DYNAMIC(Deposit)

public:
	Deposit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Deposit();

// �Ի�������
	enum { IDD = IDD_DEPOSIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
