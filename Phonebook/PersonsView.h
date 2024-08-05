#pragma once

#include "EnumsListCtrColumsInfo.h"
#include "PersonsDialog.h"
#include "ManageListCtr.h"
#include "PersonsDoc.h"

// CPersonsView view

class CPersonsView : public CListView
{
// Constants
// ----------------


// Macros
// ----------------
	DECLARE_DYNCREATE(CPersonsView)
protected:
	DECLARE_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
protected:
	CPersonsView();           // protected constructor used by dynamic creation
	virtual ~CPersonsView();


// Methods
// ----------------
public:
	CPersonsDoc* GetDocument() const;
private:

	/// <summary>
	/// Метод за зареждане на всички данни от документа в лист контролата
	/// </summary>
	BOOL LoadDataInListCtrFromDoc();

	/// <summary>
	/// Метод за търсене на всички елементи по даден критерий
	/// </summary>
	/// <param name="recPerson">Структура, по която ще се търсият записи</param>
	BOOL FilterItemsFromListCtr(const PERSONS& recPerson);

	/// <summary>
	/// Метод за проверка, дали броя на елементите в лист контролата отговаря на данните в документа
	/// </summary>
	/// <returns>Връща TRUE при равенство и FALSE при разминаване</returns>
	BOOL IsAllDataLoadFromDoc();

	/// <summary>
	/// Метод за сортиране на елементите в контролата по област и имена на клиент
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SortItemsListCtr();

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
	/// <param name="strPersonsArrayToDisplayInListCtrl">Масив с презентационни данни на всички клиенти</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ConvertAllElementPersonsInfoToArrayWithDisplayData(const CTableDataArray<CPersonInfo>& oPersonsInfoArray, CTableDataArray<CTableDataArray<CString>>& strPersonsArrayToDisplayInListCtrl);

	/// <summary>
	/// Метод, който записва презентационните данни на един елемент клиент в нов масив
	/// </summary>
	/// <param name="recPerson">Еменет от тип структура с клиенти</param>
	/// <param name="strPersonArray">Масив с презентационни данни за този елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ConvertElementPersonInfoToArrayWithDisplayData(const PERSONS& recPerson, CTableDataArray<CString>& strPersonArray);


// Overrides
// ----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT & cs);

protected:
	virtual void OnInitialUpdate();

	/// <summary>
	/// Метод, който модифицира лист контролата в зависимост от извършената опирация
	/// </summary>
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Generated message map functions
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
	afx_msg void SelectPerson();

	/// <summary>
	/// Метод за добавяне на елемент в лист контролата
	/// </summary>
	afx_msg void InsertPerson();

	/// <summary>
	/// Метод за редакция на елемент в лист контролата
	/// </summary>
	afx_msg void UpdatePerson();

	/// <summary>
	/// Метод за изтриване на елемент в лист контролата
	/// </summary>
	afx_msg void DeletePerson();

	/// <summary>
	/// Метод, който търси даден град по подадени данни
	/// </summary>
	afx_msg void FindOnePerson();

	/// <summary>
	/// Метод за зареждане на всички градове
	/// </summary>
	afx_msg void ReloadPersons();

// Members
// ----------------
	
	/// <summary>
	///Член проминлива от тип клас, който ще управлява елемените в лист контролата
	/// </summary>
	CListCtrlManager<CPersonInfo> m_oManagerListCtr;

	/// <summary>
	/// 
	/// </summary>
	CAdditionInfo m_oAdditionalInfo;

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