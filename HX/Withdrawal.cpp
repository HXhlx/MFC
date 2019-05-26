// Withdrawal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Withdrawal.h"
#include "afxdialogex.h"


// Withdrawal �Ի���

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


// Withdrawal ��Ϣ�������


BOOL Withdrawal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	CString str[] = { "����","�˺�","ȡ����","����ʱ��" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 4; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 4);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Withdrawal::OnSetfocusPassword()
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


void Withdrawal::OnKillfocusPassword()
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


void Withdrawal::OnKillfocusPasssure()
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


void Withdrawal::OnMaxtextPasssure()
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
	CString scharge, ccharge, name = GetFieldValue(0);
	COleDateTime time = COleDateTime::GetCurrentTime();
	ccharge.Format("%.2f", atof(GetFieldValue(2)) - charge);
	scharge.Format("%.2f", charge);
	GetRecord("update client set �˻����=" + ccharge + " where �˺�='" + ID + "'");
	GetRecord("insert into activity (����,�˺�,���׽��,����ʱ��,����) values ('" + name + "','" + ID + "','" + scharge + "','" + time.Format("%Y/%m/%d %H:%M:%S") + "','ȡ��')");
	GetRecord("select ����,�˺�,���׽��,����ʱ�� from activity where ����='ȡ��'");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 4; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Withdrawal::OnKillfocusId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ID.GetLength() < 17)
	{
		flag = false;
		MessageBox("������17λ�����˺�!", "����", MB_ICONWARNING);
	}
}


void Withdrawal::OnBnClickedClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n < 0)MessageBox("��ѡ��Ҫɾ�����û�!", "����", MB_ICONWARNING);
	else
	{
		GetRecord("delete from activity where ����ʱ�� = #" + information.GetItemText(n, 3) + "# and �˺�='" + information.GetItemText(n, 1) + "' and ����='ȡ��'");
		information.DeleteItem(n);
	}
}


void Withdrawal::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	n = pNMItemActivate->iItem;
	*pResult = 0;
}
