// Stats.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Stats.h"
#include "afxdialogex.h"


// Stats 对话框

IMPLEMENT_DYNAMIC(Stats, CDialogEx)

Stats::Stats(CWnd* pParent /*=NULL*/)
	: CDialogEx(Stats::IDD, pParent)
	, passsure(_T(""))
	, password(_T(""))
	, ID(_T(""))
{
	flag = true;
}

Stats::~Stats()
{
}

void Stats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Text(pDX, IDC_ID, ID);
}


BEGIN_MESSAGE_MAP(Stats, CDialogEx)
	ON_EN_SETFOCUS(IDC_PASSWORD, &Stats::OnSetfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSWORD, &Stats::OnKillfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Stats::OnKillfocusPasssure)
	ON_EN_MAXTEXT(IDC_PASSSURE, &Stats::OnMaxtextPasssure)
	ON_EN_KILLFOCUS(IDC_ID, &Stats::OnKillfocusId)
END_MESSAGE_MAP()


// Stats 消息处理程序


BOOL Stats::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CRect rect;
	CString str[] = { "姓名","账号","交易金额","交易类型","交易时间","到期时间","操作" };
	int n[7] = { 60,-41,-41,40,-41,-41,60 };
	information.GetClientRect(rect);
	for (int i = 0; i < 7; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 7 - n[i]);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Stats::OnSetfocusPassword()
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


void Stats::OnKillfocusPassword()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (password.GetLength() < 6)
	{
		if (flag)MessageBox("请输入6位数密码!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
	}
	flag = true;
}


void Stats::OnKillfocusPasssure()
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


void Stats::OnMaxtextPasssure()
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
	GetRecord("select 姓名,账号,账户余额,密码 from client where 账号='" + ID + "'");
	if (password != GetFieldValue(3))
	{
		MessageBox("密码错误,请重新输入!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	GetRecord("select 姓名,账号,交易金额,交易类型,交易时间,到期时间,操作 from activity");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 7; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Stats::OnKillfocusId()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ID.GetLength() < 17)
	{
		flag = false;
		MessageBox("请输入17位银行账号!", "警告", MB_ICONWARNING);
	}
}
