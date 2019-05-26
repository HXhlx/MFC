// Transfer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Transfer.h"
#include "afxdialogex.h"


// Transfer �Ի���

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


// Transfer ��Ϣ�������


BOOL Transfer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	CString str[] = { "ת���˺�����","ת���˺�","ת���˺�����","ת���˺�","���׽��","����ʱ��" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 6; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 6);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Transfer::OnSetfocusPassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (idg == "")
	{
		flag = false;
		MessageBox("�������˺�!", "����", MB_ICONWARNING);
		return;
	}
	passsure = password = "";
	UpdateData(FALSE);
}


void Transfer::OnKillfocusPassword()
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


void Transfer::OnKillfocusPasssure()
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


void Transfer::OnMaxtextPasssure()
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
	GetRecord("select ����,�˺�,�˻����,���� from client where �˺�='" + idg + "'");
	if (password != GetFieldValue(3))
	{
		MessageBox("�������,����������!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	CString scharge, ccharge, namee = GetFieldValue(0);
	COleDateTime time = COleDateTime::GetCurrentTime();
	ccharge.Format("%.2f", atof(GetFieldValue(2)) - charge);
	scharge.Format("%.2f", charge);
	GetRecord("update client set �˻����=" + ccharge + " where �˺�='" + idg + "'");
	GetRecord("insert into activity (����,�˺�,���׽��,����ʱ��,����,ת���˺�����,ת���˺�) values ('" + namee + "','" + idg + "','" + scharge + "',#" + time.Format("%Y/%m/%d %H:%M:%S") + "#,'ת��','"+name+"','"+ide+"')");
	GetRecord("select ת���˺�����,ת���˺�,����,�˺�,���׽��,����ʱ�� from activity where ����='ת��'");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 6; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Transfer::OnKillfocusIde()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ide.GetLength() < 17)
	{
		flag = false;
		MessageBox("������17λ�����˺�!", "����", MB_ICONWARNING);
	}
}


void Transfer::OnKillfocusIdg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (idg.GetLength() < 17)
	{
		flag = false;
		MessageBox("������17λ�����˺�!", "����", MB_ICONWARNING);
	}
}


void Transfer::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	n = pNMItemActivate->iItem;
	*pResult = 0;
}


void Transfer::OnBnClickedClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n < 0)MessageBox("��ѡ��Ҫɾ�����û�!", "����", MB_ICONWARNING);
	else
	{
		GetRecord("delete from activity where ����ʱ�� = #" + information.GetItemText(n, 5) + "# and �˺�='" + information.GetItemText(n, 3) + "' and ����='ת��'");
		information.DeleteItem(n);
	}
}
