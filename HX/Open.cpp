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
	, stype(_T(""))
	, sprovince2(_T(""))
	, scity2(_T(""))
	, scity1(_T(""))
{
	flag = false;
	n = -1;
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
	DDX_CBString(pDX, IDC_TYPE, stype);
	DDX_CBString(pDX, IDC_PROVINCE2, sprovince2);
	DDX_CBString(pDX, IDC_CITY2, scity2);
	DDX_CBString(pDX, IDC_CITY1, scity1);
}


BEGIN_MESSAGE_MAP(Open, CDialogEx)
	ON_CBN_SELCHANGE(IDC_PROVINCE1, &Open::OnSelchangeProvince1)
	ON_BN_CLICKED(IDC_SIGNIN, &Open::OnBnClickedSignin)
	ON_BN_CLICKED(IDC_CHANGE, &Open::OnBnClickedChange)
	ON_BN_CLICKED(IDC_DELETE, &Open::OnBnClickedDelete)
	ON_EN_SETFOCUS(IDC_PASSWORDO, &Open::OnSetfocusPasswordo)
	ON_EN_KILLFOCUS(IDC_PASSSURE, &Open::OnKillfocusPasssure)
	ON_EN_KILLFOCUS(IDC_PASSWORDO, &Open::OnKillfocusPasswordo)
	ON_CBN_SELCHANGE(IDC_TYPE, &Open::OnSelchangeType)
	ON_EN_KILLFOCUS(IDC_ID, &Open::OnKillfocusId)
	ON_NOTIFY(NM_CLICK, IDC_INFORMATION, &Open::OnClickInformation)
	ON_CBN_SELCHANGE(IDC_PROVINCE2, &Open::OnSelchangeProvince2)
END_MESSAGE_MAP()


// Open ��Ϣ�������


BOOL Open::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str[] = { "���֤��","����","��ַ","�ƶ��绰","�˺�" };
	CRect rect;
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
	scity1 = city.front();
	GetRecord("select * from client");
	information.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	information.GetClientRect(rect);
	for (int i = 0; i < 5; i++)information.InsertColumn(i, str[i], LVCFMT_CENTER, rect.right / 5);
	for (int k = 0; !m_pRecordset->adoEOF; m_pRecordset->MoveNext(), k++)
	{
		information.InsertItem(k, GetFieldValue(1));
		for (int i = 1; i < 5; i++)information.SetItemText(k, i, GetFieldValue(i + 1));
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void Open::OnSelchangeProvince1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SelchangeProvince(city1, sprovince1, scity1);
}


void Open::OnBnClickedSignin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString s1[] = { ID,name,idcard,telephone,password,passsure }, s2[] = { "��ѡ���˺�����!" ,"����������!","���������֤��!","������绰����!","����������!","��ȷ������!" }, scharge;
	scharge.Format("%.2f", charge);
	CString s3[] = { idcard,name,sprovince1 + " " + scity1,telephone,ID };
	for (int i = 0; i < 6; i++)if (s1[i] == "")
	{
		MessageBox(s2[i], "����", MB_ICONWARNING);
		return;
	}
	information.InsertItem(information.GetItemCount(), s3[0]);
	for (int i = 1; i < 5; i++)information.SetItemText(information.GetItemCount() - 1, i, s3[i]);
	GetRecord("insert into client (���֤��,����,��ַ,�ƶ��绰,�˺�,����,�������,�˻����,��������,�˺�����) values ('" + idcard + "','" + name + "','" + sprovince1 + " " + scity1 + "','" + telephone + "','" + ID + "','" + password + "'," + scharge + "," + scharge + ",'" + time.Format("%Y/%m/%d %H:%M:%S") + "','" + stype + "')");
	MessageBox("ע��ɹ�!");
}


void Open::OnBnClickedChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (n < 0)
	{
		MessageBox("��ѡ��Ҫ�޸ĵ���Ϣ!", "����", MB_ICONWARNING);
		return;
	}
	if (phone == "")
	{
		MessageBox("�绰����Ϊ��!", "����", MB_ICONWARNING);
		return;
	}
	information.SetItemText(n, 2, sprovince2 + " " + scity2);
	information.SetItemText(n, 3, phone);
	GetRecord("update client set ��ַ='" + sprovince2 + " " + scity2 + "',�ƶ��绰='" + phone + "' where �˺�='" + information.GetItemText(n, 4) + "'");
	MessageBox("�޸ĳɹ�!");
}


void Open::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (n < 0)
	{
		MessageBox("��ѡ��Ҫɾ������Ϣ!", "����", MB_ICONWARNING);
		return;
	}
	if (MessageBox("ȷ��Ҫɾ������Ϣ?", "", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL)return;
	GetRecord("delete from client where �˺�='" + information.GetItemText(n, 4) + "'");
	information.DeleteItem(n);
}



void Open::OnSetfocusPasswordo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	passsure = password = "";
	UpdateData(FALSE);
}


void Open::OnKillfocusPasssure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (passsure != password)
	{
		if (flag)MessageBox("�������벻һ��!", "����", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		flag = false;
	}
}


void Open::OnKillfocusPasswordo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (password.GetLength() < 6)
	{
		MessageBox("��������λ��������!", "����", MB_ICONWARNING);
		password = "";
	}
	flag = true;
	passsure = "";
	UpdateData(FALSE);
}


void Open::OnSelchangeType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	unsigned t = 1;
	CString str, st;
	ID = "";
	time = COleDateTime::GetCurrentTime();
	if (stype == "����")ID += "622752";
	else ID += "409666";
	ID += time.Format("%Y%m%d");
	for (int i = information.GetItemCount() - 1; i >= 0; i--)
	{
		str = information.GetItemText(i, 4);
		if (str.Left(6) == ID.Left(6) && str.Mid(6, 8) == time.Format("%Y%m%d"))
		{
			t = atoi(str.Right(3)) + 1;
			break;
		}
	}
	st.Format("%03d", t);
	ID += st;
	UpdateData(FALSE);
}


void Open::OnKillfocusId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (idcard.GetLength() < 18)
	{
		MessageBox("������18λ���֤��!", "����", MB_ICONWARNING);
		idcard = "";
		UpdateData(FALSE);
	}
}


void Open::OnClickInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	n = pNMItemActivate->iItem;
	province2.ResetContent();
	city2.ResetContent();
	if (n >= 0)
	{
		std::vector<CString>city;
		CString provincecity;
		provincecity = information.GetItemText(n, 2);
		int space = provincecity.Find(" ", 0);
		sprovince2 = provincecity.Left(space);
		scity2 = provincecity.Right(provincecity.GetLength() - space - 1);
		GetRecord("select * from ProvinceCity where ʡ='" + sprovince2 + "'");
		while (!m_pRecordset->adoEOF)
		{
			city.push_back(GetFieldValue(2));
			m_pRecordset->MoveNext();
		}
		for (auto item = province.cbegin(); item != province.cend(); item++)province2.AddString(*item);
		for (auto item = city.cbegin(); item != city.cend(); item++)city2.AddString(*item);
		phone = information.GetItemText(n, 3);
		UpdateData(FALSE);
	}
	*pResult = 0;
}


void Open::OnSelchangeProvince2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SelchangeProvince(city2, sprovince2, scity2);
}

void Open::SelchangeProvince(CComboBox& City, CString& SProvince, CString& SCity)
{
	std::vector<CString>city;
	City.ResetContent();
	UpdateData();
	GetRecord("select * from ProvinceCity where ʡ='" + SProvince + "'");
	while (!m_pRecordset->adoEOF)
	{
		city.push_back(GetFieldValue(2));
		m_pRecordset->MoveNext();
	}
	for (auto item = city.cbegin(); item != city.cend(); item++)City.AddString(*item);
	SCity = city.front();
	UpdateData(FALSE);
}
