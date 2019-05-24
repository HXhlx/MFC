// Closing.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Closing.h"
#include "afxdialogex.h"


// Closing 对话框

IMPLEMENT_DYNAMIC(Closing, CDialogEx)

Closing::Closing(CWnd* pParent /*=NULL*/)
	: CDialogEx(Closing::IDD, pParent)
{

}

Closing::~Closing()
{
}

void Closing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Closing, CDialogEx)
END_MESSAGE_MAP()


// Closing 消息处理程序
