// Transfer.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Transfer.h"
#include "afxdialogex.h"


// Transfer 对话框

IMPLEMENT_DYNAMIC(Transfer, CDialogEx)

Transfer::Transfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Transfer::IDD, pParent)
	, passsure(_T(""))
	, password(_T(""))
	, idg(_T(""))
	, ide(_T(""))
	, charge(0)
	, name(_T(""))
{
	flag = true;
	n = -1;
}

Transfer::~Transfer()
{
}

void Transfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Text(pDX, IDC_IDG, idg);
	DDV_MaxChars(pDX, idg, 17);
	DDX_Text(pDX, IDC_IDE, ide);
	DDV_MaxChars(pDX, ide, 17);
	DDX_Text(pDX, IDC_CHARGE, charge);
	DDX_Text(pDX, IDC_NAME, name);
}


BEGIN_MESSAGE_MAP(Transfer, CDialogEx)
	ON_EN_SETFOCUS(IDC_PASSWORD, &Transfer::OnSetfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSWORD, &Transfer::OnKillfocusPassword)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Transfer::OnKillfocusPasssure)
	ON_EN_MAXTEXT(IDC_PASSSURE, &Transfer::OnMaxtextPasssure)
	ON_EN_KILLFOCUS(IDC_IDE, &Transfer::OnKillfocusIde)
	ON_EN_KILLFOCUS(IDC_IDG, &Transfer::OnKillfocusIdg)
	ON_NOTIFY(NM_CLICK, IDC_INFORMATION, &Transfer::OnClickInformation)
	ON_BN_CLICKED(IDC_CLEAN, &Transfer::OnBnClickedClean)
END_MESSAGE_MAP()


// Transfer 消息处理程序


BOOL Transfer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	CString str[] = { "转入账号姓名","转入账号","转出账号姓名","转出账号","交易金额","交易时间" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 6; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 6);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Transfer::OnSetfocusPassword()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (idg == "")
	{
		flag = false;
		MessageBox("请输入账号!", "警告", MB_ICONWARNING);
		return;
	}
	passsure = password = "";
	UpdateData(FALSE);
}


void Transfer::OnKillfocusPassword()
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


void Transfer::OnKillfocusPasssure()
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


void Transfer::OnMaxtextPasssure()
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
	GetRecord("select 姓名,账号,账户余额,密码 from client where 账号='" + idg + "'");
	if (password != GetFieldValue(3))
	{
		MessageBox("密码错误,请重新输入!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	CString scharge, ccharge, namee = GetFieldValue(0);
	COleDateTime time = COleDateTime::GetCurrentTime();
	ccharge.Format("%.2f", atof(GetFieldValue(2)) - charge);
	scharge.Format("%.2f", charge);
	GetRecord("update client set 账户余额=" + ccharge + " where 账号='" + idg + "'");
	GetRecord("insert into activity (姓名,账号,交易金额,交易时间,操作,转入账号姓名,转入账号) values ('" + namee + "','" + idg + "','" + scharge + "',#" + time.Format("%Y/%m/%d %H:%M:%S") + "#,'转账','"+name+"','"+ide+"')");
	GetRecord("select 转入账号姓名,转入账号,姓名,账号,交易金额,交易时间 from activity where 操作='转账'");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 6; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Transfer::OnKillfocusIde()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ide.GetLength() < 17)
	{
		flag = false;
		MessageBox("请输入17位银行账号!", "警告", MB_ICONWARNING);
	}
}


void Transfer::OnKillfocusIdg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (idg.GetLength() < 17)
	{
		flag = false;
		MessageBox("请输入17位银行账号!", "警告", MB_ICONWARNING);
	}
}


void Transfer::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	n = pNMItemActivate->iItem;
	*pResult = 0;
}


void Transfer::OnBnClickedClean()
{
	// TODO: 在此添加控件通知处理程序代码
	if (n < 0)MessageBox("请选择要删除的用户!", "警告", MB_ICONWARNING);
	else
	{
		GetRecord("delete from activity where 交易时间 = #" + information.GetItemText(n, 5) + "# and 账号='" + information.GetItemText(n, 3) + "' and 操作='转账'");
		information.DeleteItem(n);
	}
}
