// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Login.h"
#include "afxdialogex.h"


// Login 对话框

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
END_MESSAGE_MAP()


// Login 消息处理程序
