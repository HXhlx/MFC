#pragma once


// Transfer �Ի���

class Transfer : public CDialogEx
{
	DECLARE_DYNAMIC(Transfer)

public:
	Transfer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Transfer();

// �Ի�������
	enum { IDD = IDD_TRANSFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
