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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CCitiesView::InsertCity)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CCitiesView::UpdateCity)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CCitiesView::DeleteCity)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_FILTERBYREGION, &CCitiesView::FilterCitiesByRegion)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CCitiesView::FindOneCity)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CCitiesView::ReloadCities)
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
	cs.style |=  LVS_REPORT | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	//Достъп до лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscCities.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);
	
	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscCities.InsertColumn(CITIE_VIEW_LIST_CTR_COLUM_REGION + 1, _T("Region"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);
	lscCities.InsertColumn(CITIE_VIEW_LIST_CTR_COLUM_REGION + 1, _T("City name"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);

	//Зареждане на данните от документа
	if (!LoadDataInListCtrFromDoc())
	{
		return;
	}
}

void CCitiesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	SelectCity();
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{	
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar)
	{

	//При натискане на бутон Ctrl + I да се добави нов запис
	case 'I':
	{
		InsertCity();
		return;
	}
	break;

	//При натискане на бутон Ctrl + F да се търси запис
	case 'F':
	{
		FindOneCity();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadCities();
		return;
	}
	break;
	}

	//Другите опрерации са вързможни само ако има избран елемент
	if (GetSelectedItemListCtrByIndex() == -1)
	{
		return;
	}

	switch (nChar)
	{
	//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeleteCity();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		SelectCity();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdateCity();
		return;
	}
	break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	//Инстнация на контекстно меню
	CMenu oMenu;
	oMenu.LoadMenu(IDR_CONTEXT_MANU); 
	CMenu* pContextMenu = oMenu.GetSubMenu(0);
	if (pContextMenu == nullptr)
	{
		return;
	}

	//Индекс на селектирания запис
	int nSelectedIndex = GetSelectedItemListCtrByIndex();

	//Проверка за селектиран елемент 
	if (nSelectedIndex == -1)
	{
		//Активира само опцията за добавяне на запис
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_INSERT, MF_BYCOMMAND | MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_UPDATE, MF_BYCOMMAND | MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_DELETE, MF_BYCOMMAND | MF_GRAYED);
	}
	else 
	{
		//Деактивира само опцията за добавяне на запис
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_INSERT, MF_BYCOMMAND | MF_GRAYED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_UPDATE, MF_BYCOMMAND | MF_ENABLED);
		pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_DELETE, MF_BYCOMMAND | MF_ENABLED);
	}

	//Отваряне на контестното меню на посочената позиция
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//Проверка, при първоначално извикване на метода
	if (lHint == NULL)
	{
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = GetSelectedItemListCtrByIndex();

	//Проверка за изпълнение на операция изтриване на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_DELETE == lHint)
	{
		//Изтриваме ред по поданен индекс
		lscCities.DeleteItem(nIndexItem);
		return;
	}

	//Обект, който ще се обработва, ако е подаден такъв
	if (pHint == nullptr)
	{
		return;
	}

	CITIES& recCity = *(CITIES*)pHint;

	//Проверка за изпълнение на операция добавяне на елемент
	if(OPERATIONS_WITH_DATA_FLAGS_INSERT == lHint)
	{
		//Добавяме данни
		AddOrEditItemInListCtr(recCity);
		return;
	}

	//Проверка за изпълнение на операция редакция на елемент
	if(OPERATIONS_WITH_DATA_FLAGS_UPDATE == lHint)
	{
		//Редактираме, по открития индекс, данните
		AddOrEditItemInListCtr(recCity, nIndexItem);
		return;
	}
}


// Generated message map functions
// ---------------
void CCitiesView::SelectCity()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Индекс на селектирания запис
	int nIndexItem = GetSelectedItemListCtrByIndex();

	//Проверка за избран елемент
	if (nIndexItem == -1)
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме данните от лист контролата
	CITIES& recCity = GetItemFromListCtr(nIndexItem);

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CCitiesDialog oDialog(recCity, ENABLE_DIALOG_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CCitiesView::InsertCity()
{
	//Достъпваме диалога
	CCitiesDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	CITIES recCity;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		recCity = oDialog.GetControlsData();

		//Добавяме данните в документа
		if (!(GetDocument() && GetDocument()->Insert(recCity)))
		{
			return;
		}
	}
 }

void CCitiesView::UpdateCity()
{
	//Достъп до индекса на селектирания запис
	int nIndexItem = GetSelectedItemListCtrByIndex();

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	CITIES& recCity = GetItemFromListCtr(nIndexItem);

	//Запазваме ид-то на записа
	long lId = recCity.lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CCitiesDialog oDialog(recCity);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() == IDOK)
	{
		//Присвояваме ноивте данни от контролите в диалога със старото ид
		recCity = oDialog.GetControlsData();
		recCity.lId = lId;

		//Редактираме данните в документа като подаваме стуртура с обновени данни
		if (!(GetDocument() && GetDocument()->UpdateCity(recCity)))
		{
			return;
		}
	}
}

void CCitiesView::DeleteCity()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(_T("Are you sure you want to delete data?"), MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO) 
	{
		return;
	}

	//Достъпваме индекса на селектирания запис
	int nIndexItem = GetSelectedItemListCtrByIndex();

	//Достъпваме селектирания запис
	CITIES& recCity = GetItemFromListCtr(nIndexItem);

	//Достъпваме ИД на записа от лист контролата по подаден индекс
	long lItemCityId = recCity.lId;

	if (lItemCityId == NULL)
	{
		AfxMessageBox(_T("Failed to select id of data from list!"));
		return;
	}

	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->Delete(lItemCityId)))
	{
		return;
	}
}

void CCitiesView::FilterCitiesByRegion()
{
	//Достъпваме диалога
	CCitiesDialog oDialog(ENABLE_DIALOG_CTR_FLAG_ONLY_REGION);

	//Нова структура, която ще съдържа данни за новия запис
	CITIES recCity;

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		recCity = oDialog.GetControlsData();

		//Филтрираме елементите от лист контролата
		if (!FilterItemsFromListCtr(recCity))
		{
			return;
		}
	}
}

void CCitiesView::FindOneCity()
{
	//Достъпваме диалога
	CCitiesDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	CITIES recCity;

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		recCity = oDialog.GetControlsData();

		//Филтрираме елементите от лист контролата
		if (!FilterItemsFromListCtr(recCity))
		{
			return;
		}
	}
}

void CCitiesView::ReloadCities()
{
	//Зареждане на всички данни
	if (!LoadDataInListCtrFromDoc())
	{
		return;
	}
}

// Methods
// ---------------

int CCitiesView::GetSelectedItemListCtrByIndex() 
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Вземаме позицията на селектирания елемент
	POSITION oPositionCursor = lscCities.GetFirstSelectedItemPosition();
	if (oPositionCursor == NULL)
	{
		return -1;
	}

	//Връщаме индекса на елемента или -1 ако няма такъв
	 return lscCities.GetNextSelectedItem(oPositionCursor);
}

BOOL CCitiesView::AddOrEditItemInListCtr(const CITIES& recCity, int nOldIndexExistingElement)
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Ако е подаден индекс на стар елемент да се изтрие
	if (nOldIndexExistingElement != -1)
	{
		//Премахваме елемент от лист контролата
		if (!lscCities.DeleteItem(nOldIndexExistingElement))
		{
			return FALSE;
		}
	}

	//Указател към елемента
	CITIES* pCity = new CITIES;
	*pCity = recCity;

	if (pCity == nullptr)
	{
		return FALSE;
	}

	//Правим структура, като задаваме индекс(последния), текст в първа колона и параметър(указател към структура)
	LVITEM lvItem = {0};
	lvItem.mask = LVIF_TEXT | LVIF_PARAM;
	lvItem.iItem = lscCities.GetItemCount();
	lvItem.pszText = pCity->szRegion;
	lvItem.lParam = (LPARAM)pCity;

	//Добавяме елемент
	lscCities.InsertItem(&lvItem);

	//Добавяне на данни и във второта колона по генерирания индекс
	if (!lscCities.SetItemText(lvItem.iItem, CITIE_VIEW_LIST_CTR_COLUM_CITY_NAME, pCity->szCityName))
	{
		return FALSE;
	};

	//Сортираме по азбучен ред при всяка промяна
	if (!SortItemsListCtr())
	{
		return FALSE;
	}

	return TRUE;
}

CITIES& CCitiesView::GetItemFromListCtr(const int nIndexItem)
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Нов обект от тип структура с градове
	CITIES* pCity = (CITIES*)(lscCities.GetItemData(nIndexItem));

	if (pCity != nullptr)
	{
		//Връщаме пълната структура
		return *pCity;
	}
}

BOOL CCitiesView::LoadDataInListCtrFromDoc()
{//Вариант за проверка на остналото и само да се добавят липсите от масива

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Изтриваве на всички останали данни
	if (!lscCities.DeleteAllItems())
	{
		return FALSE;
	}

	//Достъпваме документа
	CCitiesDoc* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
	{
		return FALSE;
	}
	
	const CCitiesArray& oCitiesArray = pCitiesDoc->GetCitiesArray();

	//Добавяме данните от таблицата в лист контролата
	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); ++i)
	{
		CITIES* pCity = oCitiesArray.GetAt(i);
		if (pCity == nullptr)
		{
			return FALSE;
		}

		if (!AddOrEditItemInListCtr(*pCity)) 
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CCitiesView::FilterItemsFromListCtr(const CITIES& recCity)
{
	//Проверка дали всички данни от документа са налични
	if (!IsAllDataLoadFromDoc())
	{
		if (!LoadDataInListCtrFromDoc())
		{
			return FALSE;
		}
	}

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	CString strRegionToFind = recCity.szRegion;
	CString strCityNameToFind = recCity.szCityName;

	int nListCrtCountItems = lscCities.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		CString strCurrentRegion = lscCities.GetItemText(nIndex, CITIE_VIEW_LIST_CTR_COLUM_REGION);

		if (strRegionToFind != strCurrentRegion)
		{
			if (!lscCities.DeleteItem(nIndex))
			{
				return FALSE;
			}

			continue;
		}
		if (strCityNameToFind.IsEmpty())
		{
			continue;
		}

		CString strCurrentName = lscCities.GetItemText(nIndex, CITIE_VIEW_LIST_CTR_COLUM_CITY_NAME);
		if (strCityNameToFind != strCurrentName)
		{
			if (!lscCities.DeleteItem(nIndex))
			{
				return FALSE;
			}
			continue;
		}
	}

	return TRUE;
}

BOOL CCitiesView::IsAllDataLoadFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Достъпваме документа
	CCitiesDoc* pCitiesDoc = GetDocument();

	if (pCitiesDoc == nullptr)
	{
		return FALSE;
	}

	//Проверка дали броя на елементите, в лест контролата, е еднакъв с този в документа
	if (lscCities.GetItemCount() != pCitiesDoc->GetCitiesArrayElementsCount())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCitiesView::SortItemsListCtr()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Изпълняваме метод за сортиране по азбучен ред
	lscCities.SortItems(CompareFunc, 0);

	return TRUE;
}

int CALLBACK CCitiesView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// Достъпваме указателите от подадените параметри
	CITIES* pCity1 = (CITIES*)lParam1;
	CITIES* pCity2 = (CITIES*)lParam2;

	//Проверяваме дали укацателите не са нулеви
	if (pCity1 == nullptr || pCity2 == nullptr) {
		return 0;
	}

	// Първо сравняваме регионите 
	int nResult = _tcscmp(pCity1->szRegion, pCity2->szRegion);

	// Ако са еднакви сравняваме градовете
	if (nResult == 0) 
	{
		nResult = _tcscmp(pCity1->szCityName, pCity2->szCityName);
	}

	//Връщаме резултата от сравнението
	return nResult;
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