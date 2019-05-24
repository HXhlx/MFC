// Withdrawal.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Withdrawal.h"
#include "afxdialogex.h"


// Withdrawal 对话框

IMPLEMENT_DYNAMIC(Withdrawal, CDialogEx)

Withdrawal::Withdrawal(CWnd* pParent /*=NULL*/)
	: CDialogEx(Withdrawal::IDD, pParent)
{

}

Withdrawal::~Withdrawal()
{
}

void Withdrawal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Withdrawal, CDialogEx)
END_MESSAGE_MAP()


// Withdrawal 消息处理程序
