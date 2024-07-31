
/////////////////////////////////////////////////////////////////////////////
// CitiesView.h : interface of the CCitiesView class

#pragma once
#include "CitiesDialog.h"
#include "EnumsListCtrColumsInfo.h"

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
	CCitiesView() noexcept;
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
	/// <param name="pCity">Параметър от тип структура град, с данни които да се добавят</param>
	/// <param name="nIndex">Параметър за индекс, по който ще се редактират данни в контролата</param>
	void AddOrEditItemInListCtr(const CITIES& pCity, int nOldIndexExistingElement = -1);

	/// <summary>
	/// Метод за достъп до елемент в лист контролата
	/// </summary>
	/// <param name="nIndex">Параметър за индекс, по който ще се търси елемента</param>
	/// <returns>Връща обект от тип структура за градове</returns>
	CITIES GetItemFromListCtr(const int nIndex);

	/// <summary>
	/// Метод за достъп до индекс на селектиран елемент от лист контролата
	/// </summary>
	/// <returns>Връща индекс на елемент от лист контролата</returns>
	int GetSelectedItemListCtrByIndex();

	/// <summary>
	/// Метод за зареждане на всички данни от документа в лист контролата
	/// </summary>
	void LoadDataInListCtrFromDoc();

	/// <summary>
	/// Метод за търсене на всички елементи по даден критерий
	/// </summary>
	/// <param name="recCity">Структура, по която ще се търсият записи</param>
	void FindItemsFromListCtr(const CITIES& recCity);

	/// <summary>
	/// Метод за проверка, дали броя на елементите в лист контролата отговаря на данните в документа
	/// </summary>
	/// <returns>Връща TRUE при равенство и FALSE при разминаване</returns>
	BOOL IsAllDataLoadFromDoc();

	/// <summary>
	/// Метод за сортиране на елементите в контролата по област и наименование на град
	/// </summary>
	void SortItemsListCtr();

	/// <summary>
	/// Метод, който сравнява елементи
	/// </summary>
	/// <param name="lParam1">Асоцира се с първия елемент, който ще се сравнява</param>
	/// <param name="lParam2">Асоцира се с втори елемент, който ще се сравнява</param>
	/// <param name="lParamSort">Параметър, който приложението си генерира </param>
	/// <returns>Връща се резултат то сравнението</returns>
	int static CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);


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


	DECLARE_MESSAGE_MAP()

public:
	/// <summary>
	/// Метод за селект на елемент от лест контролата
	/// </summary>
	afx_msg void SelectCityListCtr();

	/// <summary>
	/// Метод за добавяне на елемент в лист контролата
	/// </summary>
	afx_msg void InsertCityListCtrl();

	/// <summary>
	/// Метод за редакция на елемент в лист контролата
	/// </summary>
	afx_msg void UpdateCityListCtr();

	/// <summary>
	/// Метод за изтриване на елемент в лист контролата
	/// </summary>
	afx_msg void DeleteCityListCtr();

	/// <summary>
	/// Метод, който филтрира градовете по подаден регион
	/// </summary>
	/// <param name="strRegion">Променлива стринг, по който ще се филтрират градовете</param>
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