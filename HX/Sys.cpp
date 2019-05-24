// Sys.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Sys.h"
#include "afxdialogex.h"


// Sys 对话框

IMPLEMENT_DYNAMIC(Sys, CDialogEx)

Sys::Sys(CWnd* pParent /*=NULL*/)
	: CDialogEx(Sys::IDD, pParent)
{

}

Sys::~Sys()
{
}

void Sys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Sys, CDialogEx)
END_MESSAGE_MAP()


// Sys 消息处理程序
