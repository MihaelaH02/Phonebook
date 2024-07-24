#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CitiesDoc.h"
#include "CitiesView.h"
#include "Resource.h"

#define LIST_CONTROL_HEADER_WIDTH 200
#define LIST_CONTROL_NUMBER_COLUMN_CITY_NAME 0
#define LIST_CONTROL_NUMBER_COLUMN_CITY_REGION 1


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CitiesView.cpp : implementation of the CCitiesView class

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CCitiesView::OnContexMenuDataInsert)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CCitiesView::OnContexMenuDataUpdate)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CCitiesView::OnContexMenuDataDelete)

END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesView::CCitiesView() noexcept
{
	// TODO: add construction code here

}

CCitiesView::~CCitiesView()
{
}


// Overrides
// ----------------

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Задаваме тип репорт на лист контролата
	cs.style |=  LVS_REPORT; 

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& lscCities = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscCities.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT);
	
	//Достъпваме документа
	CCitiesDoc* pCitiesDoc = GetDocument();

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscCities.InsertColumn(1, _T("City name"), LVCFMT_LEFT, LIST_CONTROL_HEADER_WIDTH);
	lscCities.InsertColumn(2, _T("Region"), LVCFMT_LEFT, LIST_CONTROL_HEADER_WIDTH);

	//Добавяме данните от таблицата в лист контролата
	for (INT_PTR i = 0; i < pCitiesDoc->GetCitiesArray().GetCount(); ++i)
	{
		CITIES& pCity = *pCitiesDoc->GetCitiesArray().GetAt(i);
		AddItemInListCtr(pCity);
	}
}

void CCitiesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Индекс на селектирания запис
	int nIndexItem = GetIndexListCtr();

	//Проверка за избран елемент
	if (nIndexItem == -1)
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме данните от колоните
	CString strItemCityName = lscCities.GetItemText(nIndexItem, LIST_CONTROL_NUMBER_COLUMN_CITY_NAME);
	CString strItemCityRegion = lscCities.GetItemText(nIndexItem, LIST_CONTROL_NUMBER_COLUMN_CITY_REGION);

	//Проверка за предадени стойносит от диалога
	if (strItemCityName.IsEmpty() || strItemCityRegion.IsEmpty())
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CCitiesDialog oDialog(NULL,strItemCityName, strItemCityRegion, FALSE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{	
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	//Инстнация на контекстно меню
	CMenu oMenu;
	oMenu.LoadMenu(IDR_CONTEXT_MANU); 
	CMenu* pContextMenu = oMenu.GetSubMenu(0);

	//Индекс на селектирания запис
	int nSelectedIndex = GetIndexListCtr();

	//Проверка за селектиран елемент 
	if (nSelectedIndex == -1)
	{
		//Активираме само опзията за добавяне на запис
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_INSERT, MF_BYCOMMAND | MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_UPDATE, MF_BYCOMMAND | MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_DELETE, MF_BYCOMMAND | MF_GRAYED);
	}
	else 
	{
		//Деактивираме опцията за добавяне на запис
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_INSERT, MF_BYCOMMAND | MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_UPDATE, MF_BYCOMMAND | MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_DELETE, MF_BYCOMMAND | MF_ENABLED);
	}

	//Отваряне на контестното меню на посочената позиция
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

/*#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU1, point.x, point.y, this, TRUE);
#endif*/
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//Обект, който ще се обработва
	CITIES* pCity = (CITIES*)pHint;

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Проверка за изпълнение на опирация добавяне на елемент
	if(LPARAM_INSERT == lHint)
	{
		AddItemInListCtr(*pCity);
		return;
	}

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = GetIndexListCtr();

	//Проверка за изпълнение на опирация редакция на елемент
	if(LPARAM_UPDATE == lHint)
	{
		//Редактираме, по открития индекс, данните
		lscCities.SetItemText(nIndexItem, LIST_CONTROL_NUMBER_COLUMN_CITY_NAME, pCity->szCityName);
		lscCities.SetItemText(nIndexItem, LIST_CONTROL_NUMBER_COLUMN_CITY_REGION, pCity->szRegion);
		return;
	}

	//Проверка за изпълнение на опирация изтриване на елемент
	if(LPARAM_DELETE == lHint)
	{
		//Изтриваме ред по поданен индекс
		lscCities.DeleteItem(nIndexItem);
		return;
	}	
}


// Generated message map functions
// ---------------

void CCitiesView::OnContexMenuDataInsert()
{
	//Достъпваме диалога
	CCitiesDialog oDialog;

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{	
		//Променливи, които ще съдържат данните от контролите от диалога
		CString strNewItemCityName, strNewItemCityRegion;

		//Вземаме данните от контролите от диалога
		oDialog.GetControlsData(strNewItemCityName, strNewItemCityRegion);

		//Проверка за предадени стойносит от диалога
		if (strNewItemCityName.IsEmpty() || strNewItemCityRegion.IsEmpty())
		{
			AfxMessageBox(_T("Failed to select index of data from list!"));
			return;
		}

		//Добавяме данните в документа
		if (!(GetDocument() && GetDocument()->Insert(strNewItemCityName, strNewItemCityRegion)))
		{
			AfxMessageBox(_T("Failed to insert new city."));
		}
	}
 }

void CCitiesView::OnContexMenuDataUpdate()
{
	//Достъп до индекса на селектирания запис
	int nIndexItem = GetIndexListCtr();

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	CITIES* recCity = &GetItemFromListCtr(nIndexItem);

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CCitiesDialog oDialog(NULL, recCity->szCityName, recCity->szRegion);

	//Проверка за натиснат бутон OK
	if (oDialog.DoModal() == IDOK)
	{
		//Достъпваме променените в контролите от диалога в нови променливи
		CString strNewItemCityName, strNewItemCityRegion;
		oDialog.GetControlsData(strNewItemCityName, strNewItemCityRegion);

		//Проверка за предадени стойносит от диалога
		if (strNewItemCityName.IsEmpty() || strNewItemCityRegion.IsEmpty())
		{
			AfxMessageBox(_T("Failed to select index of data from list!"));
			return;
		}

		//Проверка за направени промени по данните
		if (strNewItemCityName == recCity->szCityName && strNewItemCityRegion == recCity->szRegion)
		{
			return;
		}

		//Променяме стойностите в структурата с града
		_tcscpy_s(recCity->szCityName, strNewItemCityName);
		_tcscpy_s(recCity->szCityName, strNewItemCityRegion);

		//Редактираме данните в документа като подаваме стуртура с обновени данни
		if (!(GetDocument() && GetDocument()->UpdateWhereID(*recCity)))
		{
			AfxMessageBox(_T("Failed to update city."));
		} 
	}
}

void CCitiesView::OnContexMenuDataDelete()
{
	//Допълнително потвърждение за изтриване
	int result = AfxMessageBox(_T("Are you sure you want to delete data!"), MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (result == IDNO) 
	{
		return;
	}

	//Достъпваме индекса на селектирания запис
	int nIndexItem = GetIndexListCtr();

	//Проверка за успешен селект на индекс
	if (nIndexItem == NULL)
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме ИД на записа от лист контролата по подаден индекс
	long lItemCityId = GetListCtrl().GetItemData(nIndexItem);

	if (lItemCityId == NULL)
	{
		AfxMessageBox(_T("Failed to select id of data from list!"));
		return;
	}

	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->Delete(lItemCityId)))
	{
		AfxMessageBox(_T("Failed to delete new city."));
		return;
	}
}

void CCitiesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//При натискане на бутон Delete
	if (nChar == VK_DELETE) 
	{
		OnContexMenuDataDelete();
	}
}

// Methods
// ---------------

int CCitiesView::GetIndexListCtr() 
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Вземаме позицията на селектирания елемент
	POSITION oPositionCursor = lscCities.GetFirstSelectedItemPosition();

	//Връщаме индекса на елемента или -1 ако няма такъв
	 return lscCities.GetNextSelectedItem(oPositionCursor);
}

void CCitiesView::AddItemInListCtr(const CITIES& pCity)
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Добавяме нов елемент в лист контролата
	int nNewIndex = lscCities.InsertItem(LIST_CONTROL_NUMBER_COLUMN_CITY_NAME, pCity.szCityName);
	lscCities.SetItemText(nNewIndex, LIST_CONTROL_NUMBER_COLUMN_CITY_REGION, pCity.szRegion);
	lscCities.SetItemData(nNewIndex, pCity.lId);
}

CITIES& CCitiesView::GetItemFromListCtr(const int nIndexItem)
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Нов обект от тип структура с градове
	CITIES* recCity = new CITIES();

	//Задаване на стойности от лист контролата към стуктурата с градове
	recCity->lId = lscCities.GetItemData(nIndexItem);
	_tcscpy_s(recCity->szCityName, lscCities.GetItemText(nIndexItem, LIST_CONTROL_NUMBER_COLUMN_CITY_NAME));
	_tcscpy_s(recCity->szRegion, lscCities.GetItemText(nIndexItem, LIST_CONTROL_NUMBER_COLUMN_CITY_REGION));

	//Връщаме пълната структура
	return *recCity;
}


// CCitiesView diagnostics
#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG
