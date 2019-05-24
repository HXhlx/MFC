// Deposit.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Deposit.h"
#include "afxdialogex.h"


// Deposit 对话框

IMPLEMENT_DYNAMIC(Deposit, CDialogEx)

Deposit::Deposit(CWnd* pParent /*=NULL*/)
	: CDialogEx(Deposit::IDD, pParent)
{

}

Deposit::~Deposit()
{
}

void Deposit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Deposit, CDialogEx)
END_MESSAGE_MAP()


// Deposit 消息处理程序
