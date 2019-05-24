// Open.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Open.h"
#include "afxdialogex.h"


// Open 对话框

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


// Open 消息处理程序


BOOL Open::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	type.AddString("定期");
	type.AddString("活期");
	city1.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void Open::OnSelchangeProvince1()
{
	// TODO: 在此添加控件通知处理程序代码
	std::vector<CString>city;
	city1.ResetContent();
	UpdateData();
	GetRecord("select * from ProvinceCity where 省='" + sprovince1 + "'");
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (ID == "")
	{
		MessageBox("请选择账号类型!", "警告", MB_ICONWARNING);
		return;
	}
	if (name == "")
	{
		MessageBox("请输入姓名!", "警告", MB_ICONWARNING);
		return;
	}
	if (idcard == "")
	{
		MessageBox("请输入身份证号!", "警告", MB_ICONWARNING);
		return;
	}
	if (telephone == "")
	{
		MessageBox("请输入电话号码!", "警告", MB_ICONWARNING);
		return;
	}
	
}


void Open::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Open::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
}



void Open::OnSetfocusPasswordo()
{
	// TODO: 在此添加控件通知处理程序代码
	passsure = password = "";
	UpdateData(FALSE);
}


void Open::OnKillfocusPasssure()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (passsure != password)
	{
		if(flag)MessageBox("两次密码不一致!", "警告", MB_ICONWARNING);
		passsure = password = "";
		UpdateData(FALSE);
		return;
	}
	MessageBox("两次密码一致!", "恭喜");
}


void Open::OnKillfocusPasswordo()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (password.GetLength() < 6)
	{
		MessageBox("请输入六位数字密码!", "警告", MB_ICONWARNING);
		password = "";
		flag = false;
	}
	else flag = true;
	passsure = "";
	UpdateData(FALSE);
}
