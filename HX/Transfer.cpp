// Transfer.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Transfer.h"
#include "afxdialogex.h"


// Transfer 对话框

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


// Transfer 消息处理程序
