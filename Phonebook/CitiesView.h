
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
private:
	/// <summary>
	/// Метод за добавяне на елемент към лист контролата
	/// </summary>
	/// <param name="pCity">Параметър оти тип структура град, с данни които да се добавят</param>
	void AddItemInListCtr(const CITIES& pCity);

	/// <summary>
	/// Метод за достъп до елемент в лист контролата
	/// </summary>
	/// <param name="nIndex">Параметър за индекс, по който ще се търси елемента</param>
	/// <returns>Връща обект от тип структура за градове</returns>
	CITIES& GetItemFromListCtr(const int nIndex);

	/// <summary>
	/// Метод за достъп до индекс на селектиран елемент от лист констролата
	/// </summary>
	/// <returns>Връща индекс на елемент от лист контролата</returns>
	int GetIndexListCtr();


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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
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