#pragma once


// Sys �Ի���

class Sys : public CDialogEx
{
	DECLARE_DYNAMIC(Sys)

public:
	Sys(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Sys();

// �Ի�������
	enum { IDD = IDD_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
