// Deposit.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Deposit.h"
#include "afxdialogex.h"


// Deposit 对话框

IMPLEMENT_DYNAMIC(Deposit, CDialogEx)

Deposit::Deposit(CWnd* pParent /*=NULL*/)
	: CDialogEx(Deposit::IDD, pParent)
	, passsure(_T(""))
	, password(_T(""))
	, ID(_T(""))
	, rate(0.0235)
	, stype(_T(""))
	, stime(_T(""))
	, charge(0)
{
	flag = true;
	Ttime = 0.25;
	n = -1;
}

Deposit::~Deposit()
{
}

void Deposit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Text(pDX, IDC_ID, ID);
	DDV_MaxChars(pDX, ID, 17);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_RATE, rate);
	DDX_Control(pDX, IDC_TIME, time);
	DDX_Control(pDX, IDC_TYPED, type);
	DDX_CBString(pDX, IDC_TYPED, stype);
	DDX_CBString(pDX, IDC_TIME, stime);
	DDX_Text(pDX, IDC_CHARGE, charge);
}


BEGIN_MESSAGE_MAP(Deposit, CDialogEx)
	ON_CBN_SELCHANGE(IDC_TYPED, &Deposit::OnSelchangeTyped)
	ON_EN_SETFOCUS(IDC_PASSWORD, &Deposit::OnSetfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSWORD, &Deposit::OnKillfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Deposit::OnKillfocusPasssure)
	ON_EN_MAXTEXT(IDC_PASSSURE, &Deposit::OnMaxtextPasssure)
	ON_CBN_SELCHANGE(IDC_TIME, &Deposit::OnSelchangeTime)
	ON_EN_KILLFOCUS(IDC_ID, &Deposit::OnKillfocusId)
	ON_BN_CLICKED(IDC_CLEAN, &Deposit::OnBnClickedClean)
	ON_NOTIFY(NM_CLICK, IDC_INFORMATION, &Deposit::OnClickInformation)
END_MESSAGE_MAP()


// Deposit 消息处理程序


BOOL Deposit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	CString t[] = { "三个月","半年","一年","两年","三年" };
	type.AddString("活期");
	type.AddString("定期");
	for (size_t i = 0; i < 5; i++)time.InsertString(i, t[i]);
	stype = "定期";
	stime = "三个月";
	CString str[] = { "姓名","账号","存入金额","存入类型","交易时间","到期时间" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 6; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 6);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Deposit::OnSelchangeTyped()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (stype == "活期")time.EnableWindow(FALSE);
	else time.EnableWindow(TRUE);
	Rate();
}


void Deposit::OnSetfocusPassword()
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


void Deposit::OnKillfocusPassword()
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


void Deposit::OnKillfocusPasssure()
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


void Deposit::OnMaxtextPasssure()
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
	COleDateTimeSpan timespan(long(365 * Ttime), 0, 0, 0);
	COleDateTime timestart = COleDateTime::GetCurrentTime(), timend = timestart + timespan;
	CString scharge, ccharge, name = GetFieldValue(0);
	scharge.Format("%.2f", charge);
	ccharge.Format("%.2f", atof(GetFieldValue(2)) + charge);
	GetRecord("update client set 账户余额=" + ccharge + " where 账号='" + ID + "'");
	GetRecord("insert into activity (姓名,账号,交易金额,交易类型,交易时间,到期时间,操作) values ('" + name + "','" + ID + "','" + scharge + "','" + stype + "','" + timestart.Format("%Y/%m/%d %H:%M:%S") + "','" + timend.Format("%Y/%m/%d %H:%M:%S") + "','存款')");
	GetRecord("select 姓名,账号,交易金额,交易类型,交易时间,到期时间 from activity where 操作='存款'");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 6; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Deposit::Rate()
{
	// TODO: 在此处添加实现代码.
	CString st[] = { "三个月","半年","一年","两年","三年" };
	double ra[] = { 0.0235,0.0255,0.0275,0.0335,0.04 }, Tt[] = { 0.25,0.5,1,2,3 };
	if (stype == "活期")
	{
		rate = 0.0035;
		Ttime = 0;
	}
	else for (int i = 0; i < 5; i++)if (stime == st[i])
	{
		Ttime = Tt[i];
		rate = ra[i];
		break;
	}
	UpdateData(FALSE);
}


void Deposit::OnSelchangeTime()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	Rate();
}


void Deposit::OnKillfocusId()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ID.GetLength() < 17)
	{
		flag = false;
		MessageBox("请输入17位银行账号!", "警告", MB_ICONWARNING);
	}
}


void Deposit::OnBnClickedClean()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n < 0)MessageBox("请选择要删除的用户!", "警告", MB_ICONWARNING);
	else
	{
		GetRecord("delete from activity where 交易时间='" + information.GetItemText(n, 4) + "' and 账号='" + information.GetItemText(n, 1) + "' and 操作='存款'");
		information.DeleteItem(n);
	}
}


void Deposit::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	n = pNMItemActivate->iItem;
	*pResult = 0;
}
