// Open.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Open.h"
#include "afxdialogex.h"


// Open 对话框

IMPLEMENT_DYNAMIC(Open, CDialogEx)

Open::Open(CWnd* pParent /*=NULL*/)
	: CDialogEx(Open::IDD, pParent)
{

}

Open::~Open()
{
}

void Open::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Open, CDialogEx)
END_MESSAGE_MAP()


// Open 消息处理程序
