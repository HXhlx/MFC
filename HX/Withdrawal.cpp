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
END_MESSAGE_MAP()


// Withdrawal ��Ϣ�������


BOOL Withdrawal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Withdrawal::OnSetfocusPassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Withdrawal::OnKillfocusPassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Withdrawal::OnKillfocusPasssure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Withdrawal::OnMaxtextPasssure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
