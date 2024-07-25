
/////////////////////////////////////////////////////////////////////////////
// CitiesView.h : interface of the CCitiesView class

#define LIST_CONTROL_HEADER_WIDTH 200
#define LIST_CONTROL_NUMBER_COLUMN_CITY_NAME 0
#define LIST_CONTROL_NUMBER_COLUMN_CITY_REGION 1

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
	CITIES GetItemFromListCtr(const int nIndex);

	/// <summary>
	/// Метод за достъп до индекс на селектиран елемент от лист констролата
	/// </summary>
	/// <returns>Връща индекс на елемент от лист контролата</returns>
	int GetIndexListCtr();

	/// <summary>
	/// Метод за променяне на селектирания елемент
	/// </summary>
	void ChangeSelectItemListCtr();

// Overrides
// ----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void OnInitialUpdate();

	/// <summary>
	/// Метод, който модифицира лист контролата в зависимост от извършената опирация
	/// </summary>
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();

	/// <summary>
	/// Метод, който управлява действия свързани с дясно натискане на бетона на мишката
	/// </summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с ляво натискане на бетона на мишката
	/// </summary>
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с визуализацията на контекстно меню
	/// </summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с  натискане на бетон от клавиатурата
	/// </summary>
	/// <param name="nChar"></param>
	/// <param name="nRepCnt"></param>
	/// <param name="nFlags"></param>
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// Метод за селект на запис от лест контролата
	/// </summary>
	afx_msg void OperationSelectData();

	/// <summary>
	/// Метод за добавяне на запис в лист контролата
	/// </summary>
	afx_msg void OperationInsertData();

	/// <summary>
	/// Метод за редакция на запис в лист контролата
	/// </summary>
	afx_msg void OperationUpdateData();

	/// <summary>
	/// Метод за изтриване на зипис в лист контролата
	/// </summary>
	afx_msg void OperationDeleteData();


// Members
// ----------------
};


#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif