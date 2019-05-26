// Stats.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Stats.h"
#include "afxdialogex.h"


// Stats �Ի���

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


// Stats ��Ϣ�������


BOOL Stats::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	CString str[] = { "����","�˺�","���׽��","��������","����ʱ��","����ʱ��","����" };
	int n[7] = { 60,-41,-41,40,-41,-41,60 };
	information.GetClientRect(rect);
	for (int i = 0; i < 7; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 7 - n[i]);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Stats::OnSetfocusPassword()
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


void Stats::OnKillfocusPassword()
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


void Stats::OnKillfocusPasssure()
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


void Stats::OnMaxtextPasssure()
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
	GetRecord("select ����,�˺�,���׽��,��������,����ʱ��,����ʱ��,���� from activity");
	while (!m_pRecordset->adoEOF)
	{
		information.InsertItem(information.GetItemCount(), GetFieldValue(0));
		for (int i = 1; i < 7; i++)information.SetItemText(information.GetItemCount() - 1, i, GetFieldValue(i));
		m_pRecordset->MoveNext();
	}
}


void Stats::OnKillfocusId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ID.GetLength() < 17)
	{
		flag = false;
		MessageBox("������17λ�����˺�!", "����", MB_ICONWARNING);
	}
}
