// PersonsView.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsView.h"



/////////////////////////////////////////////////////////////////////////////
// CPersonsView.cpp : implementation of the CCitiesView class

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsView::CPersonsView()
{

}

CPersonsView::~CPersonsView()
{
}


// Overrides
// ----------------
BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Задаваме тип репорт на лист контролата
	cs.style |= LVS_REPORT | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

void CPersonsView::OnInitialUpdate()
{
	//Достъп до лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscPersons.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_FIRSTNAME, _T("First name"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_LASTNAME, _T("Last name"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_EGN, _T("EGN "), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);
	//lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_REGION, _T("Region: "), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);

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
 
void CPersonsView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	SelectPerson();
}

void CPersonsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	switch (nChar)
	{

		//При натискане на бутон Ctrl + I да се добави нов запис
	case 'I':
	{
		InsertPerson();
		return;
	}
	break;

	//При натискане на бутон Ctrl + F да се търси запис
	case 'F':
	{
		FindOnePerson();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadPersons();
		return;
	}
	break;
	}

	//Другите опрерации са вързможни само ако има избран елемент
	if (m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPersons) == -1)
	{
		return;
	}

	switch (nChar)
	{
		//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeletePerson();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		SelectPerson();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdatePerson();
		return;
	}
	break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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
	CListCtrl& lscPersons = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPersons);

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

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//Проверка, при първоначално извикване на метода
	if (lHint == NULL)
	{
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Обект, който ще се обработва, ако е подаден такъв
	if (pHint == nullptr)
	{
		return;
	}

	CPersonInfo& oPersonInfo = *(CPersonInfo*)pHint;

	//Превръщаме града в масив с стрингови данни, които ще се презентират в лист контролата
	CTableDataArray<CString> strPersonArrayToOperateInListCtrl;
	if (!ConvertElementPersonInfoToArrayWithDisplayData(oPersonInfo.GetPerson(), strPersonArrayToOperateInListCtrl))
	{
		return;
	}


	//Проверка за изпълнение на операция добавяне на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_INSERT == lHint)
	{
		//Добавяме данни
		m_oManagerListCtr.ManageAddingDataInElementListCtr(lscPersons, oPersonInfo, strPersonArrayToOperateInListCtrl);
		return;
	}

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = m_oManagerListCtr.FindIndexByElement(lscPersons, oPersonInfo);
	if (nIndexItem == -1)
	{
		return;
	}

	//Проверка за изпълнение на операция редакция на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_UPDATE == lHint)
	{
		//Редактираме, по открития индекс, данните
		m_oManagerListCtr.ManageAddingDataInElementListCtr(lscPersons, oPersonInfo, strPersonArrayToOperateInListCtrl, nIndexItem);
		return;
	}

	//Проверка за изпълнение на операция изтриване на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_DELETE == lHint)
	{

		//Изтриваме ред по поданен индекс
		m_oManagerListCtr.DeleteElementListCtr(lscPersons, nIndexItem);
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

void CPersonsView::SelectPerson()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Индекс на селектирания запис
	int nIndexItem = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPersons);

	//Проверка за избран елемент
	if (nIndexItem == -1)
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме данните от лист контролата
	CPersonInfo& oPersonInfo = m_oManagerListCtr.GetItemFromListCtr(lscPersons, nIndexItem);

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPersonsDialog oDialog(oPersonInfo,m_oAdditionalInfo, ENABLE_DIALOG_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPersonsView::InsertPerson()
{
	//Достъпваме диалога
	CPersonsDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	CPersonInfo oPersonInfo;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		oDialog.GetControlsData(oPersonInfo);

		//Добавяме данните в документа
		if (!(GetDocument() && GetDocument()->ManagePersonInfo(oPersonInfo, OPERATIONS_WITH_DATA_FLAGS_INSERT)))
		{
			return;
		}
	}
}

void CPersonsView::UpdatePerson()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъп до индекса на селектирания запис
	int nIndexItem = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPersons);

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	CPersonInfo& oPersonInfo = m_oManagerListCtr.GetItemFromListCtr(lscPersons, nIndexItem);

	//Запазваме ид-то на записа
	long lId = oPersonInfo.GetPerson().lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPersonsDialog oDialog(oPersonInfo,m_oAdditionalInfo);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() == IDOK)
	{
		//Присвояваме ноивте данни от контролите в диалога със старото ид
		oDialog.GetControlsData(oPersonInfo);
		oPersonInfo.SetIdPerson(lId);

		//Редактираме данните в документа като подаваме стуртура с обновени данни
		if (!(GetDocument() && GetDocument()->ManagePersonInfo(oPersonInfo, OPERATIONS_WITH_DATA_FLAGS_UPDATE)))
		{
			return;
		}
	}
}

void CPersonsView::DeletePerson()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(_T("Are you sure you want to delete data?"), MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPerson = GetListCtrl();

	//Достъпваме индекса на селектирания запис
	int nIndexItem = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPerson);

	//Достъпваме селектирания запис
	CPersonInfo& oPersonInfo = m_oManagerListCtr.GetItemFromListCtr(lscPerson, nIndexItem);

	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->ManagePersonInfo(oPersonInfo, OPERATIONS_WITH_DATA_FLAGS_DELETE)))
	{
		return;
	}
}

void CPersonsView::FindOnePerson()
{
	//Достъпваме диалога
	CPersonsDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	CPersonInfo oPersonInfo;

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		oDialog.GetControlsData(oPersonInfo);

		//Филтрираме елементите от лист контролата
		if (!FilterItemsFromListCtr(oPersonInfo.GetPerson()))
		{
			return;
		}
	}
}

void CPersonsView::ReloadPersons()
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

BOOL CPersonsView::LoadDataInListCtrFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме документа
	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
	{
		return FALSE;
	}
	const CTableDataArray<CPersonInfo>& oPersonsInfoArray = pPersonsDoc->GetPersonInfo();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTableDataArray<CTableDataArray<CString>> strPersonsArrayToOperateInListCtrl;

	if (!ConvertAllElementPersonsInfoToArrayWithDisplayData(oPersonsInfoArray, strPersonsArrayToOperateInListCtrl))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!m_oManagerListCtr.LoadDataInListCtrFromResourse(lscPersons, oPersonsInfoArray, strPersonsArrayToOperateInListCtrl))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsView::FilterItemsFromListCtr(const PERSONS& recPerson)
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
	CListCtrl& lscPersons = GetListCtrl();

	/*CString strFirstNameToFind = recPerson.szRegion;
	CString strCityNameToFind = recPerson.szCityName;

	int nListCrtCountItems = lscPersons.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		CString strCurrentRegion = lscPersons.GetItemText(nIndex, CITIES_LIST_CTR_COLUMN_REGION);

		if (strFirstNameToFind != strCurrentRegion)
		{
			if (!lscPersons.DeleteItem(nIndex))
			{
				return FALSE;
			}

			continue;
		}
		if (strCityNameToFind.IsEmpty())
		{
			continue;
		}

		CString strCurrentName = lscPersons.GetItemText(nIndex, CITIES_LIST_CTR_COLUMN_CITY_NAME);
		if (strCityNameToFind != strCurrentName)
		{
			if (!lscPersons.DeleteItem(nIndex))
			{
				return FALSE;
			}
			continue;
		}
	}*/

	return TRUE;
}

BOOL CPersonsView::IsAllDataLoadFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме документа
	CPersonsDoc* pPersonsDoc = GetDocument();

	if (pPersonsDoc == nullptr)
	{
		return FALSE;
	}

	//връщаме резултата за успех или не
	return m_oManagerListCtr.IsAllDataLoadFromResourse(lscPersons, pPersonsDoc->GetPersonsArrayElementsCount());
}

BOOL CPersonsView::SortItemsListCtr()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Изпълняваме метод за сортиране по азбучен ред
	lscPersons.SortItems(CompareFunc, 0);

	return TRUE;
}

int CALLBACK CPersonsView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// Достъпваме указателите от подадените параметри
	PERSONS* pPerson1 = (PERSONS*)lParam1;
	PERSONS* pPerson2 = (PERSONS*)lParam2;

	//Проверяваме дали указателите за нулеви
	if (pPerson1 == nullptr || pPerson2 == nullptr) {
		return 0;
	}

	// Първо сравняваме първите им имена 
	int nResult = _tcscmp(pPerson1->szFirstName, pPerson2->szFirstName);

	// Ако са еднакви сравняваме вторите им имена
	if (nResult == 0)
	{
		nResult = _tcscmp(pPerson1->szLastName, pPerson2->szLastName);
	}

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPersonsView::ConvertElementPersonInfoToArrayWithDisplayData(const PERSONS& recPerson, CTableDataArray<CString>& strPersonArray)
{
	//Добавяме първи елемент, който ще се презентира
	if (strPersonArray.AddElement(recPerson.szFirstName) == -1)
	{
		return FALSE;
	}

	if (strPersonArray.AddElement(recPerson.szLastName) == -1)
	{
		return FALSE;
	}

	if (strPersonArray.AddElement(recPerson.szEGN) == -1)
	{
		return FALSE;
	}

	/*CString strCity = m_oAdditionalInfo.FindInArrayById(recPerson.lId);
	if (!strPersonArray.AddElement(strCity))
	{
		return FALSE;
	}*/

	return TRUE;
}

BOOL CPersonsView::ConvertAllElementPersonsInfoToArrayWithDisplayData(const CTableDataArray<CPersonInfo>& oPersonsInfoArray, CTableDataArray<CTableDataArray<CString>>& strPersonsArrayToDisplayInListCtrl)
{
	//Преминаваме през висчки елементи на масива с данни 
	for (INT_PTR nIndex = 0; nIndex < oPersonsInfoArray.GetCount(); nIndex++)
	{
		//Достъпваме информацията за един клиент от масива
		CPersonInfo* oOneElementPersonInfoArray = oPersonsInfoArray.GetAt(nIndex);
		if (oOneElementPersonInfoArray == nullptr)
		{
			return FALSE;
		}

		//Достъпваме елемента, който ще се извежда в лист контролата
		PERSONS recPerson = oOneElementPersonInfoArray->GetPerson();

		//Инициализираме масив, който ще съдържа данните от елемента, който ще се презентира
		CTableDataArray<CString> strArrayOneElement;
		if (!ConvertElementPersonInfoToArrayWithDisplayData(recPerson, strArrayOneElement))
		{
			return FALSE;
		}

		//Добавяме масива с презентационни данни към масива с всички данни за всички елементи
		if (strPersonsArrayToDisplayInListCtrl.AddElement(strArrayOneElement) == -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}


// CPersonsView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG

CPersonsDoc* CPersonsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}


// CPersonsView message handlers
