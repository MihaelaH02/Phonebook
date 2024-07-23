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
		CITIES* recCity = pCitiesDoc->GetCitiesArray().GetAt(i);
		int nIndex = lscCities.InsertItem(0, recCity->szCityName);
		lscCities.SetItemText(nIndex, 1, recCity->szRegion);
		lscCities.SetItemData(nIndex, recCity->lId);
	}
}


void CCitiesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Вземаме позицията на селектирания елемент
	POSITION oPositionCursor = GetListCtrl().GetFirstSelectedItemPosition();

	//Проверка за избран елемент
	if (oPositionCursor == NULL)
	{
		return;
	}

	//Вземаме индекса на елемента
	int nIndexItem = lscCities.GetNextSelectedItem(oPositionCursor);

	//Достъпваме данните от колоните
	CString strItemCityName = lscCities.GetItemText(nIndexItem, 0);
	CString strItemCityRegion = lscCities.GetItemText(nIndexItem, 1);

	//Достъпваме диалога и контролите му
	CCitiesDialog oDialog;
	oDialog.m_strName = strItemCityName;
	oDialog.m_strRegion = strItemCityRegion;

	//Деактивираме контролите за редакция
	oDialog.EnableControls(TRUE);

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

	//Времаме позицията на селектирания елемент
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();

	//Проверка за селектиран елемент
	if (pos == NULL) 
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
	CListCtrl& lscCities = GetListCtrl();
	CITIES* pCity = (CITIES*)pHint;

		if(LPARAM_INSERT == lHint)
		{
		//Добавяме нов елемент в лист контролата
			int nNewIndex = lscCities.InsertItem(0, pCity->szCityName);
			lscCities.SetItemText(nNewIndex, 1, pCity->szRegion);
			lscCities.SetItemData(nNewIndex, pCity->lId);
			return;
		}

		//Вземаме позицията на селектирания елемент
		POSITION oPositionCursor = lscCities.GetFirstSelectedItemPosition();
		//Вземаме индекса на елемента
		int nIndexItem = lscCities.GetNextSelectedItem(oPositionCursor);

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

void CCitiesView::OnContexMenuDataInsert()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Достъпваме диалога
	CCitiesDialog oDialog;

	if (oDialog.DoModal() == IDOK)
	{
		//Достъпмаме променените в контролите от диалога
		CString strNewItemCityName, strNewItemCityRegion;
		strNewItemCityName = oDialog.m_strName;
		strNewItemCityRegion = oDialog.m_strRegion;

		//Добавяме данните в документа
		CCitiesDoc* pCitiesDoc = GetDocument();
		if (!(pCitiesDoc && pCitiesDoc->Insert(strNewItemCityName, strNewItemCityRegion)))
		{
			AfxMessageBox(_T("Failed to insert new city."));
		}
	}
 }

void CCitiesView::OnContexMenuDataUpdate()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Вземаме позицията на селектирания елемент
	POSITION oPositionCursor = lscCities.GetFirstSelectedItemPosition();

	//Вземаме индекса на елемента
	int nIndexItem = lscCities.GetNextSelectedItem(oPositionCursor);

	//Достъпваме данните от колоните
	long lItemCityId = lscCities.GetItemData(nIndexItem);
	CString strOldItemCityName = lscCities.GetItemText(nIndexItem, 0);
	CString strOldItemCityRegion = lscCities.GetItemText(nIndexItem, 1);

	//Достъпваме диалога и контролите му
	CCitiesDialog oDialog;
	oDialog.m_strName = strOldItemCityName;
	oDialog.m_strRegion = strOldItemCityRegion;

	//Проверка за натиснат бутон OK
	if (oDialog.DoModal() == IDOK)
	{
		//Достъпмаме променените в контролите от диалога
		CString strNewItemCityName, strNewItemCityRegion;
		strNewItemCityName = oDialog.m_strName;
		strNewItemCityRegion = oDialog.m_strRegion;

		//Проверка за направени промени по данните
		if (strNewItemCityName != strOldItemCityName || strNewItemCityRegion != strOldItemCityRegion)
		{
			//Редактираме данните в документа
			CCitiesDoc* pCitiesDoc = GetDocument();
			if (!(pCitiesDoc && pCitiesDoc->UpdateWhereID(lItemCityId,strNewItemCityName, strNewItemCityRegion)))
			{
				AfxMessageBox(_T("Failed to update city."));
			}
		}
	}
}

void CCitiesView::OnContexMenuDataDelete()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Вземаме позицията на селектирания елемент
	POSITION pos = lscCities.GetFirstSelectedItemPosition();

	//Вземаме индекса на елемента
	int nItem = lscCities.GetNextSelectedItem(pos);

	//Достъпваме данните от колоните
	long lItemCityId = lscCities.GetItemData(nItem);
	CString strSelectItemCityName = lscCities.GetItemText(nItem, 0);
	CString strSelectItemCityRegion = lscCities.GetItemText(nItem, 1);

	//AfxMessageBox(_T("Are you sure you want to delete data!"));
	
	//Изтриваме данните в документа
	CCitiesDoc* pCitiesDoc = GetDocument();
	if (!(pCitiesDoc && pCitiesDoc->Delete(lItemCityId)))
	{
		AfxMessageBox(_T("Failed to delete new city."));
	}
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
