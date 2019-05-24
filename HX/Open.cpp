// Open.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HX.h"
#include "Open.h"
#include "afxdialogex.h"


// Open �Ի���

IMPLEMENT_DYNAMIC(Open, CDialogEx)

Open::Open(CWnd* pParent /*=NULL*/)
	: CDialogEx(Open::IDD, pParent)
	, sprovince1(_T(""))
	, idcard(_T(""))
	, ID(_T(""))
	, name(_T(""))
	, passsure(_T(""))
	, password(_T(""))
	, phone(_T(""))
	, telephone(_T(""))
	, charge(0)
{
	flag = true;
}

Open::~Open()
{
}

void Open::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROVINCE1, province1);
	DDX_Control(pDX, IDC_PROVINCE2, province2);
	DDX_Control(pDX, IDC_CITY1, city1);
	DDX_CBString(pDX, IDC_PROVINCE1, sprovince1);
	DDX_Text(pDX, IDC_ID, idcard);
	DDV_MaxChars(pDX, idcard, 18);
	DDX_Text(pDX, IDC_IDO, ID);
	DDV_MaxChars(pDX, ID, 17);
	DDX_Control(pDX, IDC_INFORMATION, information);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_PASSSURE, passsure);
	DDV_MaxChars(pDX, passsure, 6);
	DDX_Text(pDX, IDC_PASSWORDO, password);
	DDV_MaxChars(pDX, password, 6);
	DDX_Text(pDX, IDC_PHONE, phone);
	DDV_MaxChars(pDX, phone, 14);
	DDX_Text(pDX, IDC_TELEPHONE, telephone);
	DDV_MaxChars(pDX, telephone, 14);
	DDX_Control(pDX, IDC_TYPE, type);
	DDX_Text(pDX, IDC_CHARGE, charge);
	DDV_MinMaxDouble(pDX, charge, 0, DBL_MAX);
	DDX_Control(pDX, IDC_CITY2, city2);
}


BEGIN_MESSAGE_MAP(Open, CDialogEx)
	ON_CBN_SELCHANGE(IDC_PROVINCE1, &Open::OnSelchangeProvince1)
	ON_BN_CLICKED(IDC_SIGNIN, &Open::OnBnClickedSignin)
	ON_BN_CLICKED(IDC_CHANGE, &Open::OnBnClickedChange)
	ON_BN_CLICKED(IDC_DELETE, &Open::OnBnClickedDelete)
	ON_EN_SETFOCUS(IDC_PASSWORDO, &Open::OnSetfocusPasswordo)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Open::OnKillfocusPasssure)
	ON_EN_KILLFOCUS(IDC_PASSWORDO, &Open::OnKillfocusPasswordo)
END_MESSAGE_MAP()


// Open ��Ϣ�������


BOOL Open::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	std::vector<CString>city;
	GetRecord("select * from ProvinceCity");
	sprovince1 = GetFieldValue(1);
	province.push_back(sprovince1);
	city.push_back(GetFieldValue(2));
	while (!m_pRecordset->adoEOF)
	{
		if (sprovince1 == GetFieldValue(1)) city.push_back(GetFieldValue(2));
		if (province.back() != GetFieldValue(1))province.push_back(GetFieldValue(1));
		m_pRecordset->MoveNext();
	}
	for (auto item = province.cbegin(); item != province.cend(); item++)province1.InsertString(-1, *item);
	for (auto item = city.cbegin(); item != city.cend(); item++)city1.AddString(*item);
	type.AddString("����");
	type.AddString("����");
	city1.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void Open::OnSelchangeProvince1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::vector<CString>city;
	city1.ResetContent();
	UpdateData();
	GetRecord("select * from ProvinceCity where ʡ='" + sprovince1 + "'");
	while (!m_pRecordset->adoEOF)
	{
		city.push_back(GetFieldValue(2));
		m_pRecordset->MoveNext();
	}
	for (auto item = city.cbegin(); item != city.cend(); item++)city1.AddString(*item);
	city1.SetCurSel(0);
}


void Open::OnBnClickedSignin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (ID == "")
	{
		MessageBox("��ѡ���˺�����!", "����", MB_ICONWARNING);
		return;
	}
	if (name == "")
	{
		MessageBox("����������!", "����", MB_ICONWARNING);
		return;
	}
	if (idcard == "")
	{
		MessageBox("���������֤��!", "����", MB_ICONWARNING);
		return;
	}
	if (telephone == "")
	{
		MessageBox("������绰����!", "����", MB_ICONWARNING);
		return;
	}
	
}


void Open::OnBnClickedChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Open::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void Open::OnSetfocusPasswordo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	passsure = password = "";
	UpdateData(FALSE);
}


void Open::OnKillfocusPasssure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (passsure != password)
	{
		if(flag)MessageBox("�������벻һ��!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	MessageBox("��������һ��!", "��ϲ");
}


void Open::OnKillfocusPasswordo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (password.GetLength() < 6)
	{
		MessageBox("��������λ��������!", "����", MB_ICONWARNING);
		password = "";
		flag = false;
	}
	else flag = true;
	passsure = "";
	UpdateData(FALSE);
}
