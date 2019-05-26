// Sys.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Sys.h"
#include "afxdialogex.h"


// Sys �Ի���

IMPLEMENT_DYNAMIC(Sys, CDialogEx)

Sys::Sys(CWnd* pParent /*=NULL*/)
	: CDialogEx(Sys::IDD, pParent)
	, slimit(_T(""))
	, New(_T(""))
	, Newsure(_T(""))
	, passsure(_T(""))
	, old(_T(""))
	, password(_T(""))
	, user(_T(""))
{

	n = LB_ERR;
}

Sys::~Sys()
{
}

void Sys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIMIT, limit);
	DDX_CBString(pDX, IDC_LIMIT, slimit);
	DDX_Text(pDX, IDC_NEW, New);
	DDX_Text(pDX, IDC_NEWSURE, Newsure);
	//  DDX_Control(pDX, IDC_OLD, old);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDX_Text(pDX, IDC_OLD, old);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDX_Text(pDX, IDC_USER, user);
	DDX_Control(pDX, IDC_USERLIST, userlist);
	//  DDX_Control(pDX, IDC_LOGOUT, logout);
}


BEGIN_MESSAGE_MAP(Sys, CDialogEx)
	ON_BN_CLICKED(IDC_LOGOUT, &Sys::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_ADD, &Sys::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_CHANGE, &Sys::OnBnClickedChange)
	ON_EN_SETFOCUS(IDC_OLD, &Sys::OnSetfocusOld)
	ON_EN_SETFOCUS(IDC_NEW, &Sys::OnSetfocusNew)
	ON_EN_SETFOCUS(IDC_NEWSURE, &Sys::OnSetfocusNewsure)
	ON_LBN_KILLFOCUS(IDC_USERLIST, &Sys::OnKillfocusUserlist)
END_MESSAGE_MAP()


// Sys ��Ϣ�������


BOOL Sys::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	limit.AddString("����Ա");
	limit.AddString("����Ա");
	slimit = "����Ա";
	GetRecord("select * from worker");
	while (!m_pRecordset->adoEOF)
	{
		userlist.AddString(GetFieldValue(2) + "(" + GetFieldValue(1) + ")");
		m_pRecordset->MoveNext();
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Sys::OnBnClickedLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n != LB_ERR && MessageBox("ȷ��Ҫע����?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		CString username;
		userlist.GetText(n, username);
		GetRecord("delete from worker where �û���='" + username.Left(username.Find("(")) + "'");
		userlist.DeleteString(n);
	}
	else MessageBox("��ѡ���û�!", "����", MB_ICONWARNING);
}


void Sys::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString str[] = { user,password,passsure }, s[] = { "�������û���!","����������!","��ȷ������!" };
	for (int i = 0; i < 3; i++)if (str[i] == "")
	{
		MessageBox(s[i], "��ʾ", MB_ICONWARNING);
		return;
	}
	if (passsure != password)
	{
		MessageBox("���벻һ��,����������!", "��ʾ", MB_ICONWARNING);
		passsure = password = "";
		UpdateData();
		return;
	}
	userlist.AddString(user + "(" + password + ")");
	GetRecord("insert into worker(�˺�Ȩ��,�û���,����) values('" + slimit + "','" + user + "','" + password + "'");
}


void Sys::OnBnClickedChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (old == "" || New == "" || Newsure == "")
	{
		MessageBox("����������!", "��ʾ", MB_ICONWARNING);
		return;
	}
	if (New != Newsure)
	{
		MessageBox("�������벻һ��!", "��ʾ", MB_ICONWARNING);
		old = New = Newsure = "";
		UpdateData(FALSE);
		return;
	}
	CString name;
	userlist.GetText(n, name);
	GetRecord("select ���� from worker where �û���='" + name.Left(name.Find("(")) + "'");
	if (GetFieldValue(0) != old)
	{
		MessageBox("�������!", "��ʾ", MB_ICONWARNING);
		old = New = Newsure = "";
		UpdateData(FALSE);
		return;
	}
	if (MessageBox("ȷ���޸�?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL)return;
	GetRecord("update worker set ����='" + New + "' where �û���='" + name.Left(name.Find("(")) + "'");
	MessageBox("�޸ĳɹ�!");
}


void Sys::OnSetfocusOld()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n == LB_ERR)MessageBox("��ѡ���û�!", "����", MB_ICONWARNING);
}


void Sys::OnSetfocusNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n == LB_ERR)MessageBox("��ѡ���û�!", "����", MB_ICONWARNING);
}


void Sys::OnSetfocusNewsure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n == LB_ERR)MessageBox("��ѡ���û�!", "����", MB_ICONWARNING);
}


void Sys::OnKillfocusUserlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	n = userlist.GetCurSel();
}
