// Stats.cpp : 实现文件
//

#include "stdafx.h"
#include "HX.h"
#include "Stats.h"
#include "afxdialogex.h"


// Stats 对话框

IMPLEMENT_DYNAMIC(Stats, CDialogEx)

Stats::Stats(CWnd* pParent /*=NULL*/)
	: CDialogEx(Stats::IDD, pParent)
{

}

Stats::~Stats()
{
}

void Stats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Stats, CDialogEx)
END_MESSAGE_MAP()


// Stats 消息处理程序
