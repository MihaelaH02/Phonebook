#pragma once

#include "ListCtrlColumnsInfo.h"
#include "PersonsDialog.h"
#include "ManageListCtr.h"
#include "PersonsDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView view

/// <summary>
/// Клас за визуализация на регистъра с клиенти, наследяващ базов клас
/// </summary>
class CPersonsView : public CListView
{

// Constants
// ----------------


// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CPersonsView)

	DECLARE_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

protected:
	CPersonsView(); 
	virtual ~CPersonsView();


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за достъп до документа
	/// </summary>
	/// <returns>Връща указател към документа</returns>
	CPersonsDoc* GetDocument() const;

private:
	/// <summary>
	/// Метод за зареждане на всички данни от документа в лист контролата
	/// </summary>
	BOOL LoadPersonsInListCtrFromDoc();

	/// <summary>
	/// Метод за проверка, дали броя на елементите в лист контролата отговаря на данните в документа
	/// </summary>
	/// <returns>Връща TRUE при равенство и FALSE при разминаване</returns>
	BOOL IsAllPersonsLoadFromDoc();

	/// <summary>
	/// Метод за сортиране на елементите в контролата по област и имена на клиент
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SortPersonsInListCtr();

	/// <summary>
	/// Метод, който сравнява елементи
	/// </summary>
	/// <param name="lParam1">Асоцира се с първия елемент, който ще се сравнява</param>
	/// <param name="lParam2">Асоцира се с втори елемент, който ще се сравнява</param>
	/// <param name="lParamSort">Параметър, който приложението си генерира </param>
	/// <returns>Връща се резултат то сравнението</returns>
	int static CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/// <summary>
	/// Метод, който записва всички презентационни данни от всички елементи тип клиент в нов масив
	/// </summary>
	/// <param name="oPersonsArray">Масив с клиенти</param>
	/// <param name="oRowsDataArray">Масив с презентационни данни на всички клиенти</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetColumnDisplayDataArray(const CPersonsArray& oPersonsArray, CTypedPtrDataArray<CRowDataListCtrl<PERSONS>>& oRowsDataArray);

	/// <summary>
	/// Метод, който записва презентационните данни на един елемент клиент в нов масив
	/// </summary>
	/// <param name="oRowData">Масив с презентационни данни за този елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetColumnDisplayData(CRowDataListCtrl<PERSONS>& oRowData);


// Overrides
// ----------------

public:
	/// <summary>
	// Метод, който задава особености на вюто преди съзаването му
	/// </summary>
	virtual BOOL PreCreateWindow(CREATESTRUCT & cs) override;

protected:
	/// <summary>
	/// Метод, който задава особености на вюто след създаването му
	/// </summary>
	virtual void OnInitialUpdate() override;

	/// <summary>
	/// Метод, който модифицира лист контролата в зависимост от извършената опирация
	/// </summary>
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
	

// Generated message map functions
// ----------------

	/// <summary>
	/// Метод, който управлява действия свързани с дясно натискане на бутона на мишката
	/// </summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с ляво натискане на бутона на мишката
	/// </summary>
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с визуализацията на контекстно меню
	/// </summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с натискане на бутон от клавиатурата
	/// </summary>
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


public:
	/// <summary>
	/// Метод за селект на елемент от лест контролата
	/// </summary>
	afx_msg void ViewPersonInfo();

	/// <summary>
	/// Метод за добавяне на елемент в лист контролата
	/// </summary>
	afx_msg void InsertPersonInfo();

	/// <summary>
	/// Метод за редакция на елемент в лист контролата
	/// </summary>
	afx_msg void UpdatePersonInfo();

	/// <summary>
	/// Метод за изтриване на елемент в лист контролата
	/// </summary>
	afx_msg void DeletePersonInfo();

	/// <summary>
	/// Метод за зареждане на всички клиенти
	/// </summary>
	afx_msg void ReloadPersonsInfo();


// Members
// ----------------

	
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CPersonsDoc* CPersonsView::GetDocument() const
{
	return reinterpret_cast<CPersonsDoc*>(m_pDocument);
}
#endif