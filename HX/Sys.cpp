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
	, slimit(_T(""))
	, New(_T(""))
	, Newsure(_T(""))
	, passsure(_T(""))
	, old(_T(""))
	, password(_T(""))
	, user(_T(""))
{

	n = LB_ERR;
}

Sys::~Sys()
{
}

void Sys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIMIT, limit);
	DDX_CBString(pDX, IDC_LIMIT, slimit);
	DDX_Text(pDX, IDC_NEW, New);
	DDX_Text(pDX, IDC_NEWSURE, Newsure);
	//  DDX_Control(pDX, IDC_OLD, old);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDX_Text(pDX, IDC_OLD, old);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDX_Text(pDX, IDC_USER, user);
	DDX_Control(pDX, IDC_USERLIST, userlist);
	//  DDX_Control(pDX, IDC_LOGOUT, logout);
}


BEGIN_MESSAGE_MAP(Sys, CDialogEx)
	ON_BN_CLICKED(IDC_LOGOUT, &Sys::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_ADD, &Sys::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_CHANGE, &Sys::OnBnClickedChange)
	ON_EN_SETFOCUS(IDC_OLD, &Sys::OnSetfocusOld)
	ON_EN_SETFOCUS(IDC_NEW, &Sys::OnSetfocusNew)
	ON_EN_SETFOCUS(IDC_NEWSURE, &Sys::OnSetfocusNewsure)
	ON_LBN_KILLFOCUS(IDC_USERLIST, &Sys::OnKillfocusUserlist)
END_MESSAGE_MAP()


// Sys 消息处理程序


BOOL Sys::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	limit.AddString("管理员");
	limit.AddString("操作员");
	slimit = "管理员";
	GetRecord("select * from worker");
	while (!m_pRecordset->adoEOF)
	{
		userlist.AddString(GetFieldValue(2) + "(" + GetFieldValue(1) + ")");
		m_pRecordset->MoveNext();
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Sys::OnBnClickedLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n != LB_ERR && MessageBox("确定要注销吗?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		CString username;
		userlist.GetText(n, username);
		GetRecord("delete from worker where 用户名='" + username.Left(username.Find("(")) + "'");
		userlist.DeleteString(n);
	}
	else MessageBox("请选择用户!", "警告", MB_ICONWARNING);
}


void Sys::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString str[] = { user,password,passsure }, s[] = { "请输入用户名!","请输入密码!","请确认密码!" };
	for (int i = 0; i < 3; i++)if (str[i] == "")
	{
		MessageBox(s[i], "提示", MB_ICONWARNING);
		return;
	}
	if (passsure != password)
	{
		MessageBox("密码不一致,请重新输入!", "提示", MB_ICONWARNING);
		passsure = password = "";
		UpdateData();
		return;
	}
	userlist.AddString(user + "(" + password + ")");
	GetRecord("insert into worker(账号权限,用户名,密码) values('" + slimit + "','" + user + "','" + password + "'");
}


void Sys::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (old == "" || New == "" || Newsure == "")
	{
		MessageBox("请输入密码!", "提示", MB_ICONWARNING);
		return;
	}
	if (New != Newsure)
	{
		MessageBox("两次密码不一致!", "提示", MB_ICONWARNING);
		old = New = Newsure = "";
		UpdateData(FALSE);
		return;
	}
	CString name;
	userlist.GetText(n, name);
	GetRecord("select 密码 from worker where 用户名='" + name.Left(name.Find("(")) + "'");
	if (GetFieldValue(0) != old)
	{
		MessageBox("密码错误!", "提示", MB_ICONWARNING);
		old = New = Newsure = "";
		UpdateData(FALSE);
		return;
	}
	if (MessageBox("确认修改?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL)return;
	GetRecord("update worker set 密码='" + New + "' where 用户名='" + name.Left(name.Find("(")) + "'");
	MessageBox("修改成功!");
}


void Sys::OnSetfocusOld()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n == LB_ERR)MessageBox("请选择用户!", "警告", MB_ICONWARNING);
}


void Sys::OnSetfocusNew()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n == LB_ERR)MessageBox("请选择用户!", "警告", MB_ICONWARNING);
}


void Sys::OnSetfocusNewsure()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n == LB_ERR)MessageBox("请选择用户!", "警告", MB_ICONWARNING);
}


void Sys::OnKillfocusUserlist()
{
	// TODO: 在此添加控件通知处理程序代码
	n = userlist.GetCurSel();
}
