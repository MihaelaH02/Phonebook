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
	ON_COMMAND(ID_CONTEXT_MENU_DATA_FILTER, &CCitiesView::FilterCitiesByRegion)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CCitiesView::FindOneCity)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CCitiesView::ReloadCities)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesView::CCitiesView() noexcept
{
}

CCitiesView::~CCitiesView()
{
}


// Overrides
// ----------------

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	//Достъп до лист контролата
	CListCtrl& lscCities = GetListCtrl();

	// Задаваме тип репорт на лист контролата
	cs.style |= LVS_REPORT | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	//Достъп до лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscCities.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscCities.InsertColumn(CITIES_LIST_CTR_COLUMN_REGION + 1, _T("Region"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);
	lscCities.InsertColumn(CITIES_LIST_CTR_COLUMN_CITY_NAME + 1, _T("City name"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);

	//Зареждане на данните от документа
	if (!LoadDataInListCtrFromDoc())
	{
		return;
	}

	//Сортировка
	if (!SortItemsListCtr())
	{
		return;
	}

	CListView::OnInitialUpdate();

}

void CCitiesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	ViewCityInfo();
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{	
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

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
	if (m_oListCtrManager.GetSelectedItemListCtrByIndex(lscCities) == -1)
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
		ViewCityInfo();
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
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = m_oListCtrManager.GetSelectedItemListCtrByIndex(lscCities);

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
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();
	//Проверка, при първоначално извикване на метода
	if (lHint == NULL)
	{
		return;
	}

	CITIES& recCity = *(CITIES*)pHint;

	//Превръщаме града в масив с стрингови данни, които ще се презентират в лист контролата
	CTableDataArray<CString> strCitiesArrayToOperateInListCtrl;
	if (!ConvertElementCitiesToArrayWithDisplayData(recCity, strCitiesArrayToOperateInListCtrl))
	{
		return ;
	}
	//Обект, който ще се обработва, ако е подаден такъв
	if (pHint == nullptr)
	{
		return;
	}

	//Проверка за изпълнение на операция добавяне на елемент
	if(OPERATIONS_WITH_DATA_FLAGS_INSERT == lHint)
	{
		//Добавяме данни
		m_oListCtrManager.ManageAddingDataInElementListCtr(lscCities, recCity, strCitiesArrayToOperateInListCtrl);
		return;
	}

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = m_oListCtrManager.FindIndexByElement(lscCities, recCity);
	if (nIndexItem == -1)
	{
		return;
	}

	//Проверка за изпълнение на операция редакция на елемент
	if(OPERATIONS_WITH_DATA_FLAGS_UPDATE == lHint)
	{
		//Редактираме, по открития индекс, данните
		m_oListCtrManager.ManageAddingDataInElementListCtr(lscCities, recCity, strCitiesArrayToOperateInListCtrl, nIndexItem);
		return;
	}	

	//Проверка за изпълнение на операция изтриване на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_DELETE == lHint)
	{

		//Изтриваме ред по поданен индекс
		m_oListCtrManager.DeleteElementListCtr(lscCities, nIndexItem);
		return;
	}

	//Сортировка
	if (!SortItemsListCtr())
	{
		return;
	}
}


// Generated message map functions
// ---------------
void CCitiesView::ViewCityInfo()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Индекс на селектирания запис
	int nIndexItem = m_oListCtrManager.GetSelectedItemListCtrByIndex(lscCities);

	//Проверка за избран елемент
	if (nIndexItem == -1)
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме данните от лист контролата
	CITIES* pCity = m_oListCtrManager.GetItemByIndex(lscCities, nIndexItem);

	//Проверка за открит елемент
	if (pCity == nullptr)
	{
		AfxMessageBox(_T("Failed to select city from list!\n Try to reload."));
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CCitiesDialog oDialog(*pCity, ENABLE_DIALOG_CTR_FLAG_NONE);

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
		if (!(GetDocument() && GetDocument()->InsertCity(recCity)))
		{
			return;
		}
	}
 }

void CCitiesView::UpdateCity()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Достъп до индекса на селектирания запис
	int nIndexItem = m_oListCtrManager.GetSelectedItemListCtrByIndex(lscCities);

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	CITIES* pCity = m_oListCtrManager.GetItemByIndex(lscCities, nIndexItem);

	//Проверка за открит елемент
	if (pCity == nullptr)
	{
		AfxMessageBox(_T("Failed to select city from list!\n Try to reload."));
		return;
	}

	//Запазваме ид-то на записа
	long lId = pCity->lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CCitiesDialog oDialog(*pCity);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() == IDOK)
	{
		//Присвояваме ноивте данни от контролите в диалога със старото ид
		*pCity = oDialog.GetControlsData();
		pCity->lId = lId;

		//Редактираме данните в документа като подаваме стуртура с обновени данни
		if (!(GetDocument() && GetDocument()->UpdateCity(*pCity)))
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

	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Достъпваме индекса на селектирания запис
	int nIndexItem = m_oListCtrManager.GetSelectedItemListCtrByIndex(lscCities);

	//Достъпваме селектирания запис
	CITIES* pCity = m_oListCtrManager.GetItemByIndex(lscCities,nIndexItem);

	//Проверка за открит елемент
	if (pCity == nullptr)
	{
		AfxMessageBox(_T("Failed to select city from list!\n Try to reload."));
		return;
	}

	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->DeleteCity(*pCity)))
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

	//Филтрираме зареденото
	SortItemsListCtr();
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

	//Сортировка на зареденото
	SortItemsListCtr();
}

// Methods
// ---------------

BOOL CCitiesView::LoadDataInListCtrFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscCities = GetListCtrl();

	//Достъпваме документа
	CCitiesDoc* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
	{
		return FALSE;
	}
	const CCitiesArray& oCitiesArray = pCitiesDoc->GetCitiesArray();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTableDataArray<CTableDataArray<CString>> strCitiesArrayToOperateInListCtrl;

	if (!ConvertAllElementCitiesToArrayWithDisplayData(oCitiesArray, strCitiesArrayToOperateInListCtrl))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!m_oListCtrManager.LoadDataInListCtrFromResourse(lscCities, oCitiesArray, strCitiesArrayToOperateInListCtrl))
	{
		return FALSE;
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
		CString strCurrentRegion = lscCities.GetItemText(nIndex, CITIES_LIST_CTR_COLUMN_REGION);

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

		CString strCurrentName = lscCities.GetItemText(nIndex, CITIES_LIST_CTR_COLUMN_CITY_NAME);
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

	//връщаме резултата за успех или не
	if (!m_oListCtrManager.IsAllDataLoadFromResourse(lscCities, pCitiesDoc->GetCitiesArrayCount()))
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

BOOL CCitiesView::ConvertElementCitiesToArrayWithDisplayData(const CITIES recCity, CTableDataArray<CString>& strCitiesArray)
{
	//Добавяме първи елемент, който ще се презентира
	if (strCitiesArray.AddElement(recCity.szRegion) == -1)
	{
		return FALSE;
	}

	//Добавяме втори елемент, който ще се презентира
	if (strCitiesArray.AddElement(recCity.szCityName) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCitiesView::ConvertAllElementCitiesToArrayWithDisplayData(const CCitiesArray& oCitiesArray, CTableDataArray<CTableDataArray<CString>>& strCitiesArrayToPresentInListCtrl)
{
	//Преминаваме през висчки елементи на масива с данни за градове
	for (INT_PTR nIndex = 0; nIndex < oCitiesArray.GetCount(); nIndex++)
	{
		//Достъпваме елемента, който ще се извежда в лист контролата
		CITIES* recCity = oCitiesArray.GetAt(nIndex);
		if (recCity == nullptr)
		{
			return FALSE;
		}

		//Инициализираме масив, който ще съдържа данните от елемента, който ще се презентира
		CTableDataArray<CString> strArrayOneElement;
		if (!ConvertElementCitiesToArrayWithDisplayData(*recCity, strArrayOneElement))
		{
			return FALSE;
		}

		//Добавяме масива с презентационни данни съм масива с всички данни на всички елементи
		if (strCitiesArrayToPresentInListCtrl.AddElement(strArrayOneElement) == -1)
		{
			return FALSE;
		}
	}
	return TRUE;
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