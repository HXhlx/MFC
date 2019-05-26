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
	flag = true;
	n = -1;
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
	ON_EN_KILLFOCUS(IDC_ID, &Withdrawal::OnKillfocusId)
	ON_BN_CLICKED(IDC_CLEAN, &Withdrawal::OnBnClickedClean)
	ON_NOTIFY(NM_CLICK, IDC_INFORMATION, &Withdrawal::OnClickInformation)
END_MESSAGE_MAP()


// Withdrawal 消息处理程序


BOOL Withdrawal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	CString str[] = { "姓名","账号","取款金额","交易时间" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 4; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 4);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Withdrawal::OnSetfocusPassword()
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


void Withdrawal::OnKillfocusPassword()
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


void Withdrawal::OnKillfocusPasssure()
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


void Withdrawal::OnMaxtextPasssure()
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
	CString scharge, ccharge, name = GetFieldValue(0);
	COleDateTime time = COleDateTime::GetCurrentTime();
	ccharge.Format("%.2f", atof(GetFieldValue(2)) - charge);
	scharge.Format("%.2f", charge);
	GetRecord("update client set 账户余额=" + ccharge + " where 账号='" + ID + "'");
	GetRecord("insert into activity (姓名,账号,交易金额,交易时间,操作) values ('" + name + "','" + ID + "','" + scharge + "','" + time.Format("%Y/%m/%d %H:%M:%S") + "','取款')");
	GetRecord("select 姓名,账号,交易金额,交易时间 from activity where 操作='取款'");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 4; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Withdrawal::OnKillfocusId()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ID.GetLength() < 17)
	{
		flag = false;
		MessageBox("请输入17位银行账号!", "警告", MB_ICONWARNING);
	}
}


void Withdrawal::OnBnClickedClean()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n < 0)MessageBox("请选择要删除的用户!", "警告", MB_ICONWARNING);
	else
	{
		GetRecord("delete from activity where 交易时间 = #" + information.GetItemText(n, 3) + "# and 账号='" + information.GetItemText(n, 1) + "' and 操作='取款'");
		information.DeleteItem(n);
	}
}


void Withdrawal::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	n = pNMItemActivate->iItem;
	*pResult = 0;
}
