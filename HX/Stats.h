#pragma once


// Stats �Ի���

class Stats : public CDialogEx
{
	DECLARE_DYNAMIC(Stats)

public:
	Stats(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Stats();

// �Ի�������
	enum { IDD = IDD_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
