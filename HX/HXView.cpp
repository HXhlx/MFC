
// HXView.cpp : CHXView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CHXView ����/����

CHXView::CHXView()
{
	// TODO: �ڴ˴���ӹ������

}

CHXView::~CHXView()
{
}

BOOL CHXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CHXView ����

void CHXView::OnDraw(CDC* /*pDC*/)
{
	CHXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CHXView ��ӡ


void CHXView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CHXView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CHXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CHXView ���

#ifdef _DEBUG
void CHXView::AssertValid() const
{
	CView::AssertValid();
}

void CHXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHXDoc* CHXView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHXDoc)));
	return (CHXDoc*)m_pDocument;
}
#endif //_DEBUG


// CHXView ��Ϣ�������


BOOL CHXView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
	Closing closing;
	closing.DoModal();
}


void CHXView::OnOpen()
{
	// TODO: �ڴ���������������
	Open open;
	open.DoModal();
}


void CHXView::OnDeposit()
{
	// TODO: �ڴ���������������
	Deposit deposit;
	deposit.DoModal();
}


void CHXView::OnStats()
{
	// TODO: �ڴ���������������
	Stats stats;
	stats.DoModal();
}


void CHXView::OnSystem()
{
	// TODO: �ڴ���������������
	Sys sys;
	sys.DoModal();
}


void CHXView::OnTransfer()
{
	// TODO: �ڴ���������������
	Transfer transfer;
	transfer.DoModal();
}


void CHXView::OnWithdrawal()
{
	// TODO: �ڴ���������������
	Withdrawal withdrawal;
	withdrawal.DoModal();
}
