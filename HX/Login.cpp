// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Login.h"
#include "afxdialogex.h"


// Login �Ի���

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
	, slimit(_T(""))
	, password(_T(""))
	, user(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIMIT, limit);
	DDX_CBString(pDX, IDC_LIMIT, slimit);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDX_Text(pDX, IDC_USER, user);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login ��Ϣ�������


void Login::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while (!m_pRecordset->adoEOF)
	{
		if (slimit == GetFieldValue(1) && user == GetFieldValue(2) && password == GetFieldValue(3))break;
		m_pRecordset->MoveNext();
	}
	if (m_pRecordset->adoEOF)
	{
		MessageBox("�û������������!", "����", MB_ICONWARNING);
		return;
	}
	CDialogEx::OnOK();
}


BOOL Login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	limit.AddString("����Ա");
	limit.AddString("����Ա");
	GetRecord("select * from worker");
	slimit = GetFieldValue(1);
	user = GetFieldValue(2);
	password = GetFieldValue(3);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
