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
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	//Подреди по азбучен ред?

	// Задаваме тип репорт на лист контролата
	CListCtrl& lscCities = GetListCtrl();
	lscCities.ModifyStyle(0, LVS_REPORT);

	//Добавяне на допълнителни стилове за лист контролата
	lscCities.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT);
	
	//Достъпваме документа
	CCitiesDoc* pCitiesDoc = GetDocument();

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscCities.InsertColumn(1, _T("City name"), LVCFMT_LEFT, 200);
	lscCities.InsertColumn(2, _T("Region"), LVCFMT_LEFT, 200);

	//Добавяме данните от таблицата в лист контролата
	for (INT_PTR i = 0; i < pCitiesDoc->GetCitiesArray().GetCount(); ++i)
	{
		CITIES *pCity = pCitiesDoc->GetCitiesArray().GetAt(i);
		AddItemInListCtr(*pCity);
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
		return;
	}

	//Достъпваме данните от колоните
	CString strItemCityName = lscCities.GetItemText(nIndexItem, 0);
	CString strItemCityRegion = lscCities.GetItemText(nIndexItem, 1);

	//Достъпваме диалога и контролите му
	CCitiesDialog oDialog = new CCitiesDialog(strItemCityName, strItemCityRegion);

	//Деактивираме контролите за редакция
	oDialog.EnableControls(TRUE);

	//Визуализираме диалога
	oDialog.DoModal();

	//Изчистване на заделената памет
	delete oDialog;
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
	int nIsSelectedIndex = GetIndexListCtr();

	//Проверка за селектиран елемент
	if (nIsSelectedIndex == -1)
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
	CITIES* pCity = (CITIES*)pHint;
	CListCtrl& lscCities = GetListCtrl();

		if(LPARAM_INSERT == lHint)
		{
			AddItemInListCtr(*pCity);
			return;
		}

		int nIndexItem = GetIndexListCtr();

		if(LPARAM_UPDATE == lHint)
		{
			//Редактираме по подаден индекс на ред данните
			lscCities.SetItemText(nIndexItem, 0, pCity->szCityName);
			lscCities.SetItemText(nIndexItem, 1, pCity->szRegion);
			return;
		}

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
	CCitiesDialog oDialog = new CCitiesDialog();

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{	
		//Променливи, които ще съдържат данните от контролите в диалога
		CString strNewItemCityName, strNewItemCityRegion;

		//Вземаме данните от контролите в диалога
		oDialog.GetControlsData(strNewItemCityName, strNewItemCityRegion);

		//Добавяме данните в документа
		if (!(GetDocument() && GetDocument()->Insert(strNewItemCityName, strNewItemCityRegion)))
		{
			AfxMessageBox(_T("Failed to insert new city."));
		}
	}

	//Почистване на заделената памет
	delete oDialog;
 }

void CCitiesView::OnContexMenuDataUpdate()
{
	//Индекс на селектирания запис
	int nIndexItem = GetIndexListCtr();

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	CITIES recCity = GetItemFromListCtr(nIndexItem);

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CCitiesDialog oDialog = new CCitiesDialog(recCity.szCityName, recCity.szRegion);

	//Проверка за натиснат бутон OK
	if (oDialog.DoModal() == IDOK)
	{
		//Достъпваме променените в контролите от диалога в нови променливи
		CString strNewItemCityName, strNewItemCityRegion;
		oDialog.GetControlsData(strNewItemCityName, strNewItemCityRegion);

		//Проверка за направени промени по данните
		if (strNewItemCityName != recCity.szCityName || strNewItemCityRegion != recCity.szRegion)
		{
			//Променяме стойностите в структурата с града
			_tcscpy_s(recCity.szCityName, strNewItemCityName);
			_tcscpy_s(recCity.szCityName, strNewItemCityRegion);

			//Редактираме данните в документа
			if (!(GetDocument() && GetDocument()->UpdateWhereID(recCity)))
			{
				AfxMessageBox(_T("Failed to update city."));
			} 
		}
	}

	//Изчистване на заделената памет
	delete oDialog;
}

void CCitiesView::OnContexMenuDataDelete()
{
	//Допълнително потвърждение за изтриване
	int result = AfxMessageBox(_T("Are you sure you want to delete data!"), MB_YESNO | MB_ICONQUESTION);
	if (result == IDNO) {
		return;
	}

	//Индекс на селектирания запис
	int nIndexItem = GetIndexListCtr();

	//Достъпваме ИД на зиписа от лист контролата по подаден индекс
	long lItemCityId = GetListCtrl().GetItemData(nIndexItem);

	//Изтриваме данните в документа
	if (!(GetDocument() && GetDocument()->Delete(lItemCityId)))
	{
		AfxMessageBox(_T("Failed to delete new city."));
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

	//Вземаме индекса на елемента
	 return lscCities.GetNextSelectedItem(oPositionCursor);
}

void CCitiesView::AddItemInListCtr(const CITIES& pCity)
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Добавяме нов елемент в лист контролата
	int nNewIndex = lscCities.InsertItem(0, pCity.szCityName);
	lscCities.SetItemText(nNewIndex, 1, pCity.szRegion);
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
	_tcscpy_s(recCity->szCityName, lscCities.GetItemText(nIndexItem, 0));
	_tcscpy_s(recCity->szRegion, lscCities.GetItemText(nIndexItem, 1));

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
