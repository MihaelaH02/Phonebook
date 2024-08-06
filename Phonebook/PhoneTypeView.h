#pragma once

#include "EnumsListCtrColumsInfo.h"
#include "PhonetypesDialog.h"
#include "ManageListCtr.h"
#include "PhoneTypesDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypeView view

class CPhoneTypeView : public CListView
{
// Constants
// ----------------


// Macros
// ----------------
	DECLARE_DYNCREATE(CPhoneTypeView)
protected:
	DECLARE_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
protected:
	CPhoneTypeView();         
	virtual ~CPhoneTypeView();


// Methods
// ----------------
public:
	CPhoneTypesDoc* GetDocument() const;
private:

	/// <summary>
	/// Метод за зареждане на всички данни от документа в лист контролата
	/// </summary>
	BOOL LoadDataInListCtrFromDoc();

	/// <summary>
	/// Метод за проверка, дали броя на елементите в лист контролата отговаря на данните в документа
	/// </summary>
	/// <returns>Връща TRUE при равенство и FALSE при разминаване</returns>
	BOOL IsAllDataLoadFromDoc();

	/// <summary>
	/// Метод за сортиране на елементите в контролата по тип телефон
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
	/// <param name="oPhonetypesArray">Масив с типове телефони</param>
	/// <param name="strPhonetypesArrayToDisplayInListCtrl">Масив с презентационни данни на всички типове телефони</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ConvertAllElementsPhoneTypesToArrayWithDisplayData(const CTableDataArray<PHONE_TYPES>& oPhonetypesArray, CTableDataArray<CTableDataArray<CString>>& strPhonetypesArrayToDisplayInListCtrl);

	/// <summary>
	/// Метод, който записва презентационните данни на един елемент тип телефон в нов масив
	/// </summary>
	/// <param name="recPhoneType">Еменет от тип структура с типове телефони</param>
	/// <param name="strPhoneType">Масив с презентационни данни за този елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ConvertElementPhoneTypeToArrayWithDisplayData(const PHONE_TYPES& recPhoneType, CTableDataArray<CString>& strPhoneType);



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


	// Generated message map functions
public:
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
	afx_msg void SelectPhoneType();

	/// <summary>
	/// Метод за добавяне на елемент в лист контролата
	/// </summary>
	afx_msg void InsertPhoneType();

	/// <summary>
	/// Метод за редакция на елемент в лист контролата
	/// </summary>
	afx_msg void UpdatePhoneType();

	/// <summary>
	/// Метод за изтриване на елемент в лист контролата
	/// </summary>
	afx_msg void DeletePhoneType();

	/// <summary>
	/// Метод, който търси даден клиент по егн
	/// </summary>
	afx_msg void FindPhoneType();

	/// <summary>
	/// Метод за зареждане на всички градове
	/// </summary>
	afx_msg void ReloadPhoneTypes();

// Members
// ----------------

	/// <summary>
	///Член проминлива от тип клас, който ще управлява елемените в лист контролата
	/// </summary>
	CListCtrlManager<PHONE_TYPES> m_oManagerListCtr;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

};