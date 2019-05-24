
// HXView.cpp : CHXView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HX.h"
#endif

#include "HXDoc.h"
#include "HXView.h"
#include "Open.h"
#include "Closing.h"
#include "Deposit.h"
#include "Withdrawal.h"
#include "Transfer.h"
#include "Stats.h"
#include "Sys.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHXView

IMPLEMENT_DYNCREATE(CHXView, CView)

BEGIN_MESSAGE_MAP(CHXView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHXView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CLOSING, &CHXView::OnClosing)
	ON_COMMAND(ID_OPEN, &CHXView::OnOpen)
	ON_COMMAND(ID_DEPOSIT, &CHXView::OnDeposit)
	ON_COMMAND(ID_STATS, &CHXView::OnStats)
	ON_COMMAND(ID_SYSTEM, &CHXView::OnSystem)
	ON_COMMAND(ID_TRANSFER, &CHXView::OnTransfer)
	ON_COMMAND(ID_WITHDRAWAL, &CHXView::OnWithdrawal)
END_MESSAGE_MAP()

// CHXView 构造/析构

CHXView::CHXView()
{
	// TODO: 在此处添加构造代码

}

CHXView::~CHXView()
{
}

BOOL CHXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHXView 绘制

void CHXView::OnDraw(CDC* /*pDC*/)
{
	CHXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CHXView 打印


void CHXView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHXView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHXView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHXView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHXView 诊断

#ifdef _DEBUG
void CHXView::AssertValid() const
{
	CView::AssertValid();
}

void CHXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHXDoc* CHXView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHXDoc)));
	return (CHXDoc*)m_pDocument;
}
#endif //_DEBUG


// CHXView 消息处理程序


BOOL CHXView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	Bitmap bmp(rect.Width(), rect.Height());
	Graphics bmpGraphics(&bmp);
	bmpGraphics.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush  brushBlack(Color(255, 255, 255));
	CString bkimg = "background.jpg";
	Image bkmain(bkimg.AllocSysString());
	bmpGraphics.DrawImage(&bkmain, 0, 0, rect.Width(), rect.Height());
	Graphics graphics(pDC->m_hDC);
	CachedBitmap cachedBmp(&bmp, &graphics);
	graphics.DrawCachedBitmap(&cachedBmp, 0, 0);
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}


void CHXView::OnClosing()
{
	// TODO: 在此添加命令处理程序代码
	Closing closing;
	closing.DoModal();
}


void CHXView::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	Open open;
	open.DoModal();
}


void CHXView::OnDeposit()
{
	// TODO: 在此添加命令处理程序代码
	Deposit deposit;
	deposit.DoModal();
}


void CHXView::OnStats()
{
	// TODO: 在此添加命令处理程序代码
	Stats stats;
	stats.DoModal();
}


void CHXView::OnSystem()
{
	// TODO: 在此添加命令处理程序代码
	Sys sys;
	sys.DoModal();
}


void CHXView::OnTransfer()
{
	// TODO: 在此添加命令处理程序代码
	Transfer transfer;
	transfer.DoModal();
}


void CHXView::OnWithdrawal()
{
	// TODO: 在此添加命令处理程序代码
	Withdrawal withdrawal;
	withdrawal.DoModal();
}
