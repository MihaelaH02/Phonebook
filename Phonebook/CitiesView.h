
/////////////////////////////////////////////////////////////////////////////
// CitiesView.h : interface of the CCitiesView class


#pragma once
#include "CitiesDialog.h"

class CCitiesView : public CListView
{
// Constants
// ----------------
 

// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CCitiesView)


// Constructor / Destructor
// ----------------
protected:
	CCitiesView() noexcept;// create from serialization only
public:
	virtual ~CCitiesView();


// Methods
// ----------------
public:
	CCitiesDoc* GetDocument() const;


// Overrides
// ----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void OnInitialUpdate(); // called first time after construct

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContexMenuDataInsert();
	afx_msg void OnContexMenuDataUpdate();
	afx_msg void OnContexMenuDataDelete();


// Members
// ----------------
};


#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif