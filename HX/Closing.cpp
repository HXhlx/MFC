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
	, passsure(_T(""))
	, password(_T(""))
	, ID(_T(""))
{
	flag = true;
}

Closing::~Closing()
{
}

void Closing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_ID, ID);
	DDV_MaxChars(pDX, ID, 17);
}


BEGIN_MESSAGE_MAP(Closing, CDialogEx)
	ON_EN_KILLFOCUS(IDC_ID, &Closing::OnKillfocusId)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Closing::OnKillfocusPasssure)
	ON_EN_KILLFOCUS(IDC_PASSWORD, &Closing::OnKillfocusPassword)
	ON_EN_MAXTEXT(IDC_PASSSURE, &Closing::OnMaxtextPasssure)
	ON_BN_CLICKED(IDC_CLEAN, &Closing::OnBnClickedClean)
	ON_EN_SETFOCUS(IDC_PASSWORD, &Closing::OnSetfocusPassword)
END_MESSAGE_MAP()


// Closing 消息处理程序


void Closing::OnKillfocusId()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ID.GetLength() < 17)MessageBox("请输入17位银行账号!", "警告", MB_ICONWARNING);
}


void Closing::OnKillfocusPasssure()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (passsure.GetLength() < 6)
	{
		MessageBox("请输入6位数密码!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
	}
}


void Closing::OnKillfocusPassword()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (password.GetLength() < 6)
	{
		if(flag)MessageBox("请输入6位数密码!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
	}
	flag = true;
}


void Closing::OnMaxtextPasssure()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (passsure != password)
	{
		MessageBox("两次密码不一致!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	GetRecord("select 姓名,账号,开户金额,账户余额,开户日期,账号类型,密码 from client where 账号='" + ID + "'");
	if (password != GetFieldValue(6))
	{
		MessageBox("密码错误,请重新输入!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	information.InsertItem(0, GetFieldValue(0));
	for (int i = 1; i < 6; i++)information.SetItemText(0, i, GetFieldValue(i));
}


BOOL Closing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	CString str[] = { "姓名","账号","开户金额","账户余额","开户日期","账号类型" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 6; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 6);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Closing::OnBnClickedClean()
{
	// TODO: 在此添加控件通知处理程序代码
	if (information.GetItemCount() == 0)
	{
		MessageBox("请先完善用户信息!", "警告", MB_ICONWARNING);
		return;
	}
	if (MessageBox("确认清除用户信息?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		information.DeleteItem(0);
		GetRecord("delete from client where 账号='" + ID + "'");
	}
}


void Closing::OnSetfocusPassword()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ID == "")
	{
		flag = false;
		MessageBox("请输入账号!", "警告", MB_ICONWARNING);
		return;
	}
	passsure = password = "";
	UpdateData(FALSE);
}
