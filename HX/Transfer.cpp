// Transfer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Transfer.h"
#include "afxdialogex.h"


// Transfer �Ի���

IMPLEMENT_DYNAMIC(Transfer, CDialogEx)

Transfer::Transfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Transfer::IDD, pParent)
{

}

Transfer::~Transfer()
{
}

void Transfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Transfer, CDialogEx)
END_MESSAGE_MAP()


// Transfer ��Ϣ�������
