
// HXView.h : CHXView 类的接口
//

#pragma once


class CHXView : public CView
{
protected: // 仅从序列化创建
	CHXView();
	DECLARE_DYNCREATE(CHXView)

// 特性
public:
	CHXDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHXView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClosing();
	afx_msg void OnOpen();
	afx_msg void OnDeposit();
	afx_msg void OnStats();
	afx_msg void OnSystem();
	afx_msg void OnTransfer();
	afx_msg void OnWithdrawal();
};

#ifndef _DEBUG  // HXView.cpp 中的调试版本
inline CHXDoc* CHXView::GetDocument() const
   { return reinterpret_cast<CHXDoc*>(m_pDocument); }
#endif

