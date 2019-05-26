// Closing.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Closing.h"
#include "afxdialogex.h"


// Closing �Ի���

IMPLEMENT_DYNAMIC(Closing, CDialogEx)

Closing::Closing(CWnd* pParent /*=NULL*/)
	: CDialogEx(Closing::IDD, pParent)
	, passsure(_T(""))
	, password(_T(""))
	, ID(_T(""))
{
	flag = true;
}

Closing::~Closing()
{
}

void Closing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_ID, ID);
	DDV_MaxChars(pDX, ID, 17);
}


BEGIN_MESSAGE_MAP(Closing, CDialogEx)
	ON_EN_KILLFOCUS(IDC_ID, &Closing::OnKillfocusId)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Closing::OnKillfocusPasssure)
	ON_EN_KILLFOCUS(IDC_PASSWORD, &Closing::OnKillfocusPassword)
	ON_EN_MAXTEXT(IDC_PASSSURE, &Closing::OnMaxtextPasssure)
	ON_BN_CLICKED(IDC_CLEAN, &Closing::OnBnClickedClean)
	ON_EN_SETFOCUS(IDC_PASSWORD, &Closing::OnSetfocusPassword)
END_MESSAGE_MAP()


// Closing ��Ϣ�������


void Closing::OnKillfocusId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ID.GetLength() < 17)MessageBox("������17λ�����˺�!", "����", MB_ICONWARNING);
}


void Closing::OnKillfocusPasssure()
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


void Closing::OnKillfocusPassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (password.GetLength() < 6)
	{
		if(flag)MessageBox("������6λ������!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
	}
	flag = true;
}


void Closing::OnMaxtextPasssure()
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
	GetRecord("select ����,�˺�,�������,�˻����,��������,�˺�����,���� from client where �˺�='" + ID + "'");
	if (password != GetFieldValue(6))
	{
		MessageBox("�������,����������!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	information.InsertItem(0, GetFieldValue(0));
	for (int i = 1; i < 6; i++)information.SetItemText(0, i, GetFieldValue(i));
}


BOOL Closing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	CString str[] = { "����","�˺�","�������","�˻����","��������","�˺�����" };
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 6; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 6);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Closing::OnBnClickedClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (information.GetItemCount() == 0)
	{
		MessageBox("���������û���Ϣ!", "����", MB_ICONWARNING);
		return;
	}
	if (MessageBox("ȷ������û���Ϣ?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		information.DeleteItem(0);
		GetRecord("delete from client where �˺�='" + ID + "'");
	}
}


void Closing::OnSetfocusPassword()
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
