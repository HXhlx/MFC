// Deposit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Deposit.h"
#include "afxdialogex.h"


// Deposit �Ի���

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


// Deposit ��Ϣ�������


BOOL Deposit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	CString t[] = { "������","����","һ��","����","����" };
	type.AddString("����");
	type.AddString("����");
	for (size_t i = 0; i < 5; i++)time.InsertString(i, t[i]);
	stype = "����";
	stime = "������";
	CString str[] = { "����","�˺�","������","��������","����ʱ��","����ʱ��" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 6; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 6);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Deposit::OnSelchangeTyped()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (stype == "����")time.EnableWindow(FALSE);
	else time.EnableWindow(TRUE);
	Rate();
}


void Deposit::OnSetfocusPassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ID == "")
	{
		flag = false;
		MessageBox("�������˺�!", "����", MB_ICONWARNING);
		return;
	}
	passsure = password = "";
	UpdateData(FALSE);
}


void Deposit::OnKillfocusPassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (password.GetLength() < 6)
	{
		if (flag)MessageBox("������6λ������!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
	}
	flag = true;
}


void Deposit::OnKillfocusPasssure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (passsure.GetLength() < 6)
	{
		MessageBox("������6λ������!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
	}
}


void Deposit::OnMaxtextPasssure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (passsure != password)
	{
		MessageBox("�������벻һ��!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	GetRecord("select ����,�˺�,�˻����,���� from client where �˺�='" + ID + "'");
	if (password != GetFieldValue(3))
	{
		MessageBox("�������,����������!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	COleDateTimeSpan timespan(long(365 * Ttime), 0, 0, 0);
	COleDateTime timestart = COleDateTime::GetCurrentTime(), timend = timestart + timespan;
	CString scharge, ccharge, name = GetFieldValue(0);
	scharge.Format("%.2f", charge);
	ccharge.Format("%.2f", atof(GetFieldValue(2)) + charge);
	GetRecord("update client set �˻����=" + ccharge + " where �˺�='" + ID + "'");
	GetRecord("insert into activity (����,�˺�,���׽��,��������,����ʱ��,����ʱ��,����) values ('" + name + "','" + ID + "','" + scharge + "','" + stype + "','" + timestart.Format("%Y/%m/%d %H:%M:%S") + "','" + timend.Format("%Y/%m/%d %H:%M:%S") + "','���')");
	GetRecord("select ����,�˺�,���׽��,��������,����ʱ��,����ʱ�� from activity where ����='���'");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 6; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Deposit::Rate()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CString st[] = { "������","����","һ��","����","����" };
	double ra[] = { 0.0235,0.0255,0.0275,0.0335,0.04 }, Tt[] = { 0.25,0.5,1,2,3 };
	if (stype == "����")
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	Rate();
}


void Deposit::OnKillfocusId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ID.GetLength() < 17)
	{
		flag = false;
		MessageBox("������17λ�����˺�!", "����", MB_ICONWARNING);
	}
}


void Deposit::OnBnClickedClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n < 0)MessageBox("��ѡ��Ҫɾ�����û�!", "����", MB_ICONWARNING);
	else
	{
		GetRecord("delete from activity where ����ʱ��='" + information.GetItemText(n, 4) + "' and �˺�='" + information.GetItemText(n, 1) + "' and ����='���'");
		information.DeleteItem(n);
	}
}


void Deposit::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	n = pNMItemActivate->iItem;
	*pResult = 0;
}
