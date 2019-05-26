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
	, ID(_T(""))
	, passsure(_T(""))
	, password(_T(""))
	, charge(0)
{

}

Withdrawal::~Withdrawal()
{
}

void Withdrawal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, ID);
	DDV_MaxChars(pDX, ID, 17);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Text(pDX, IDC_CHARGE, charge);
}


BEGIN_MESSAGE_MAP(Withdrawal, CDialogEx)
	ON_EN_SETFOCUS(IDC_PASSWORD, &Withdrawal::OnSetfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSWORD, &Withdrawal::OnKillfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Withdrawal::OnKillfocusPasssure)
	ON_EN_MAXTEXT(IDC_PASSSURE, &Withdrawal::OnMaxtextPasssure)
END_MESSAGE_MAP()


// Withdrawal 消息处理程序


BOOL Withdrawal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Withdrawal::OnSetfocusPassword()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Withdrawal::OnKillfocusPassword()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Withdrawal::OnKillfocusPasssure()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Withdrawal::OnMaxtextPasssure()
{
	// TODO: 在此添加控件通知处理程序代码
}
