#pragma once


// Closing �Ի���

class Closing : public CDialogEx
{
	DECLARE_DYNAMIC(Closing)

public:
	Closing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Closing();

// �Ի�������
	enum { IDD = IDD_CLOSING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
