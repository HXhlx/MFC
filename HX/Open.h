#pragma once


// Open �Ի���

class Open : public CDialogEx
{
	DECLARE_DYNAMIC(Open)

public:
	Open(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Open();

// �Ի�������
	enum { IDD = IDD_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
