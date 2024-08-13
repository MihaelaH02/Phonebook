
/////////////////////////////////////////////////////////////////////////////
// CitiesView.h : interface of the CCitiesView class

#pragma once
#include "CitiesDialog.h"
#include "ListCtrlColumnsInfo.h"
#include "ManageListCtr.h"
#include "RowDataListCtrl.h"
#include "Messages.h"
#include "Flags.h"

/// <summary>
/// Клас за визуализация на регистъра с градове, наследяващ базов клас
/// </summary>
class CCitiesView : public CListView
{

// Constants
// ----------------
 

// Macros
// ----------------

protected:
	DECLARE_DYNCREATE(CCitiesView)
	DECLARE_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

protected:
	CCitiesView() noexcept;
public:
	virtual ~CCitiesView();


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за достъп до документа
	/// </summary>
	/// <returns>Връща инстанция към документа</returns>
	CCitiesDoc* GetDocument() const;

private:
	/// <summary>
	/// Метод за зареждане на всички данни от документа в лист контролата
	/// </summary>
	BOOL LoadDataInListCtrFromDoc();

	/// <summary>
	/// Метод за търсене на елементи по даден критерий
	/// </summary>
	/// <param name="recCity">Структура, по която ще се търсият записи</param>
	BOOL FilterItemsFromListCtr(const CITIES& recCity);

	/// <summary>
	/// Метод за проверка, дали броя на елементите в лист контролата отговаря на данните в документа
	/// </summary>
	/// <returns>Връща TRUE при равенство и FALSE при разминаване</returns>
	BOOL IsAllDataLoadFromDoc();

	/// <summary>
	/// Метод за сортиране на елементите в контролата по област и наименование на град
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SortItemsListCtr();

	/// <summary>
	/// Метод, който сравнява елементи
	/// </summary>
	/// <param name="lParam1">Асоцира се с първия елемент, който ще се сравнява</param>
	/// <param name="lParam2">Асоцира се с втори елемент, който ще се сравнява</param>
	/// <param name="lParamSort">Параметър обект</param>
	/// <returns>Връща се резултат то сравнението</returns>
	int static CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/// <summary>
	/// Метод, който записва всички презентационни данни от всички елементи град в нов масив
	/// </summary>
	/// <param name="oCitiesArray">Масив с градове</param>
	/// <param name="strCitiesArrayToDisplayInListCtrl">Масив с презентационни данни на всички градове</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetColumnDisplayDataArray(const CCitiesArray& oCitiesArray, CTypedPtrDataArray<CRowDataListCtrl<CITIES>>& oRowsDataArray);

	/// <summary>
	/// Метод, който записва презентационните данни на един елемент град в нов масив
	/// </summary>
	/// <param name="strCitiesArray">Масив с презентационни данни за този елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetColumnDisplayData(CRowDataListCtrl<CITIES>& oRowDataListCtrl);


// Overrides
// ----------------
public:

	/// <summary>
	// Метод, който задава особености на вюто преди съзаването му
	/// </summary>
	/// <param name="cs"></param>
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

protected:
	/// <summary>
	/// Метод, който задава особености на вюто след създаването му
	/// </summary>
	virtual void OnInitialUpdate() override;

	/// <summary>
	/// Метод, който модифицира лист контролата в зависимост от извършената опирация
	/// </summary>
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
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
	/// Метод за преглед на елемент от лест контролата
	/// </summary>
	afx_msg void ViewCityInfo();

	/// <summary>
	/// Метод за добавяне на елемент в лист контролата
	/// </summary>
	afx_msg void InsertCity();

	/// <summary>
	/// Метод за редакция на елемент в лист контролата
	/// </summary>
	afx_msg void UpdateCity();

	/// <summary>
	/// Метод за изтриване на елемент в лист контролата
	/// </summary>
	afx_msg void DeleteCity();

	/// <summary>
	/// Метод, който филтрира градовете по подаден регион
	/// </summary>
	afx_msg void FilterCitiesByRegion();

	/// <summary>
	/// Метод, който търси даден град по подадени данни
	/// </summary>
	afx_msg void FindOneCity();

	/// <summary>
	/// Метод за зареждане на всички градове
	/// </summary>
	afx_msg void ReloadCities();


// Members
// ----------------
};


#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif