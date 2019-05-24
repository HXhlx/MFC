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
	, slimit(_T(""))
	, password(_T(""))
	, user(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIMIT, limit);
	DDX_CBString(pDX, IDC_LIMIT, slimit);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDX_Text(pDX, IDC_USER, user);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login 消息处理程序


void Login::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	while (!m_pRecordset->adoEOF)
	{
		if (slimit == GetFieldValue(1) && user == GetFieldValue(2) && password == GetFieldValue(3))break;
		m_pRecordset->MoveNext();
	}
	if (m_pRecordset->adoEOF)
	{
		MessageBox("用户名或密码错误!", "警告", MB_ICONWARNING);
		return;
	}
	CDialogEx::OnOK();
}


BOOL Login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	limit.AddString("管理员");
	limit.AddString("操作员");
	GetRecord("select * from worker");
	slimit = GetFieldValue(1);
	user = GetFieldValue(2);
	password = GetFieldValue(3);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
