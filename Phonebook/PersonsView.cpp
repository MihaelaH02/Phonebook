#include "pch.h"
#include "Phonebook.h"
#include "PersonsView.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView.cpp : implementation of the CCitiesView class

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CPersonsView::InsertPersonInfo)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CPersonsView::UpdatePersonInfo)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CPersonsView::DeletePersonInfo)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CPersonsView::ReloadPersonsInfo)
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
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_REGION, _T("Region: "), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);

	//Зареждане на данните от документа в лист контролата
	if (!LoadPersonsInListCtrFromDoc())
	{
		return;
	}

	//Сортировка на елементите в лист контролата
	if (!SortPersonsInListCtr())
	{
		return;
	}

	CListView::OnInitialUpdate();

}
 
void CPersonsView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция преглед на информацията за клиент
	ViewPersonInfo();
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
		InsertPersonInfo();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadPersonsInfo();
		return;
	}
	break;
	}

	//Другите опрерации са възможни само ако има избран елемент
	if (m_oManagerListCtr.GetIndexSelectedItemListCtrl(lscPersons) == -1)
	{
		return;
	}

	switch (nChar)
	{
	//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeletePersonInfo();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		ViewPersonInfo();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdatePersonInfo();

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
	int nSelectedIndex = m_oManagerListCtr.GetIndexSelectedItemListCtrl(lscPersons);

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

	//Деактивиране на операциите за търсене и филтрация на елементи от лист контролата
	pContextMenu->EnableMenuItem(ID_CONTEXT_MANU_DATA_FIND, MF_BYCOMMAND | MF_GRAYED);
	pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_FILTER, MF_BYCOMMAND | MF_GRAYED);

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

	//Проверка за обект, който ще се обработва
	if (pHint == nullptr)
	{
		return;
	}

	//Достъп до обект, който се е модифицирал
	PERSONS& oPerson = *(PERSONS*)pHint;

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = m_oManagerListCtr.GetIndexSelectedItemListCtrl(lscPersons);

	//Проверка за изпълнение на операция изтриване на елемент
	if (lHint == OPERATIONS_WITH_DATA_FLAGS_DELETE)
	{
		//Изтриваме ред по поданен индекс
		if (!m_oManagerListCtr.DeleteElementListCtr(lscPersons, nIndexItem))
		{
			AfxMessageBox(_T("Failed to delete element in list!\n Try to reload."));
			return;
		}
	}
	else
	{
		//Превръщаме клиента в масив със стрингови данни, които ще се презентират в лист контролата
		CTableDataArray<CString> strPersonArrayToOperateInListCtrl;
		if (!ConvertToDisplayDataInListCtrl(oPerson, strPersonArrayToOperateInListCtrl))
		{
			AfxMessageBox(_T("Failed to process data of new element in list!\n Try to reload."));
			return;
		}

		//Добавяме или редактираме елемент в лист контролата, както и индекс ако има такъв
		if (!m_oManagerListCtr.ManageAddOrEditElementListCtr(lscPersons, oPerson, strPersonArrayToOperateInListCtrl, nIndexItem))
		{
			AfxMessageBox(_T("Failed to renew data in list!\n Try to reload."));
			return;
		}
	}

	//Сортировка на елементите в лист контролата след направен промени
	if (!SortPersonsInListCtr())
	{
		return;
	}
}


// Generated message map functions
// ---------------

void CPersonsView::ViewPersonInfo()
{
	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(_T("Failed to load data!\n Try to reload."));
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме селектирания клиент от лист контролата
	PERSONS* pPerson = m_oManagerListCtr.GetSelectedItemListCtrl(lscPersons);

	if (pPerson == nullptr)
	{
		AfxMessageBox(_T("Failed to select client from list!\n Try to reload."));
		return;
	}

	//Достъпваме вссички данни за селектирания клиент
	CPersonInfo oPersonInfo;
	if (!pPersonDoc->GetPersonInfoByPersonId(pPerson->lId, oPersonInfo))
	{
		AfxMessageBox(_T("Failed to select data from list!\n Try to reload."));
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPersonsDialog oDialog(oPersonInfo, pPersonDoc->GetAdditionalPersonInfo(), ENABLE_DIALOG_CITIES_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPersonsView::InsertPersonInfo()
{
	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(_T("Failed to load data!\n Try to reload."));
		return;
	}

	//Достъпваме диалога
	CPersonsDialog oDialog(pPersonDoc->GetAdditionalPersonInfo());

	//Нова структура, която ще съдържа данни за новия запис
	CPersonInfo oPersonInfo;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Вземаме данните от контролите от диалога
	if (!oDialog.GetControlsData(oPersonInfo))
	{
		AfxMessageBox(_T("Failed to process data form dialog!\nTry again later."));
		return;
	}

	//Добавяме данните в документа
	if (!(GetDocument() && GetDocument()->ManagePersonInfo(oPersonInfo, OPERATIONS_WITH_DATA_FLAGS_INSERT)))
	{
		return;
	}
}

void CPersonsView::UpdatePersonInfo()
{
	LPARAM lFlagOperationToPerson = OPERATIONS_WITH_DATA_FLAGS_UPDATE;

	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(_T("Failed to load data!\n Try to reload."));
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме селектирания клиент от лист контролата
	PERSONS* pPerson = m_oManagerListCtr.GetSelectedItemListCtrl(lscPersons);

	if (pPerson == nullptr)
	{
		AfxMessageBox(_T("Failed to select client from list!\n Try to reload."));
		return;
	}

	//Достъпваме всички данни за селектирания клиент
	CPersonInfo oPersonInfo;
	if (!pPersonDoc->GetPersonInfoByPersonId(pPerson->lId, oPersonInfo))
	{
		AfxMessageBox(_T("Failed to select data from list!\n Try to reload."));
		return;
	}

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPersonsDialog oDialog(oPersonInfo, pPersonDoc->GetAdditionalPersonInfo());

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}
	//Присвояваме ноивте данни от диалога
	if (!oDialog.GetControlsData(oPersonInfo))
	{
		AfxMessageBox(_T("Failed to process data form dialog!\nTry again later."));
		return;
	}

	//Добавяме ИД на клиента към обновените му данни
	oPersonInfo.SetIdPerson(pPerson->lId);

	//Проверка за направен промяна по данните на клиента
	if (oPersonInfo.GetPerson() == *pPerson)
	{
		lFlagOperationToPerson = OPERATIONS_WITH_DATA_FLAGS_READED;
	}

	//Проверка дали всички модификации направени по списъка с телефонни номера съдържат ИД на съответния клиент
	if (!oPersonInfo.CheckAndConnectAllPhoneNumbersWithPersonId())
	{
		AfxMessageBox(_T("Failed to process data form dialog!\nTry again later."));
		return;
	}

	//Редактираме данните в документа като подаваме стуртура с обновени данни
	if (!(GetDocument() && GetDocument()->ManagePersonInfo(oPersonInfo, lFlagOperationToPerson)))
	{
		return;
	}
}

void CPersonsView::DeletePersonInfo()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(_T("Are you sure you want to delete data?"), MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме селектирания клиент от лист контролата
	PERSONS* pPerson = m_oManagerListCtr.GetSelectedItemListCtrl(lscPersons);

	if (pPerson == nullptr)
	{
		AfxMessageBox(_T("Failed to select client from list!\n Try to reload."));
		return;
	}

	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(_T("Failed to load data!\n Try to reload."));
		return;
	}

	//Достъпваме всички данни за селектирания клиент
	CPersonInfo oPersonInfo;

	if (!pPersonDoc->GetPersonInfoByPersonId(pPerson->lId, oPersonInfo))
	{
		AfxMessageBox(_T("Failed to select data from list!\n Try to reload."));
		return;
	}

	//Преместваме телефонните му номера в групата за изтрити
	CPhoneNumbersMap* pPhoneNumbersMap = &oPersonInfo.GetPhoneNumbers();
	if (pPhoneNumbersMap == nullptr)
	{
		AfxMessageBox(_T("Failed to select data from list!\n Try to reload."));
		return;
	}

	if (!pPhoneNumbersMap->MoveActiveValuesIntoKey(OPERATIONS_WITH_DATA_FLAGS_DELETE))
	{
		AfxMessageBox(_T("Failed to select data from list!\n Try to reload."));
		return ;
	}
	
	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->ManagePersonInfo(oPersonInfo, OPERATIONS_WITH_DATA_FLAGS_DELETE)))
	{
		return;
	}
}

void CPersonsView::ReloadPersonsInfo()
{
	//Проверка дали всички данни от елемента са заредени в лест контролата
	if (IsAllPersonsLoadFromDoc())
	{
		return;
	}

	//Зареждане на всички данни
	if (!LoadPersonsInListCtrFromDoc())
	{
		return;
	}

	//Сортировка на обновените данни в лист контролата
	SortPersonsInListCtr();
}


// Methods
// ---------------

BOOL CPersonsView::LoadPersonsInListCtrFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме документа към текущия изглед
	CPersonsDoc* pPersonsDoc = GetDocument();

	//Проверка за открит документ
	if (pPersonsDoc == nullptr)
	{
		return FALSE;
	}

	//Инстанция на масив, който ще съдържа всички клиенти и техната информация
	CPersonsArray oPersonsInfoArray;
	if (!pPersonsDoc->GetAllPersons(oPersonsInfoArray))
	{
		return FALSE;
	}

	//Запълваме масив с всички презентационни данни на всички елементи
	CTableDataArray<CTableDataArray<CString>> strPersonsArrayToOperateInListCtrl;
	if (!ConvertAllElementsPersonsToArrayWithDisplayData(oPersonsInfoArray, strPersonsArrayToOperateInListCtrl))
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

BOOL CPersonsView::IsAllPersonsLoadFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме документа
	CPersonsDoc* pPersonsDoc = GetDocument();

	if (pPersonsDoc == nullptr)
	{
		return FALSE;
	}

	//Проверка дали броя на елементите в лист контролата отгоравя на данните от документа
	if(! m_oManagerListCtr.IsAllDataLoadFromResourse(lscPersons, pPersonsDoc->GetPersonsInfoArrayElementsCount()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsView::SortPersonsInListCtr()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Изпълняваме метод за сортиране първо по регион и след това по имена на клиентите
	lscPersons.SortItems(CompareFunc, 0);

	return TRUE;
}

int CALLBACK CPersonsView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{	//Инстанция на изгледа, с която ще достъпваме нестатични член променливи
	CPersonsView* pPersonsView = (CPersonsView*)lParamSort;
	if (pPersonsView == nullptr)
	{
		return 0;
	}

	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = pPersonsView->GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(_T("Failed to load data!\n Try to reload."));
		return 0;
	}

	//Достъпваме указателите от подадените параметри
	PERSONS* pPerson1 = (PERSONS*)lParam1;
	PERSONS* pPerson2 = (PERSONS*)lParam2;

	//Проверяваме дали указателите за нулеви
	if (pPerson1 == nullptr || pPerson2 == nullptr) 
	{
		return 0;
	}

	//Провенливи, които съдържат градовете на клиентите
	CITIES* pCity1 = pPersonDoc->GetAdditionalPersonInfo().FindCityInArrayById(pPerson1->lIdCity);
	CITIES* pCity2 = pPersonDoc->GetAdditionalPersonInfo().FindCityInArrayById(pPerson2->lIdCity);

	if (pCity1 == nullptr || pCity2 == nullptr)
	{
		return 0;
	}

	// Първо сравняваме област 
	int nResult = _tcscmp(pCity1->szRegion, pCity2->szRegion);

	// Ако са еднакви сравняваме първите им имена 
	if (nResult == 0)
	{
		nResult = _tcscmp(pPerson1->szFirstName, pPerson2->szFirstName);
	}

	// Ако са еднакви сравняваме фамилиите им 
	if (nResult == 0)
	{
		nResult = _tcscmp(pPerson1->szLastName, pPerson2->szLastName);
	}

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPersonsView::ConvertToDisplayDataInListCtrl(const PERSONS& recPerson, CTableDataArray<CString>& strPersonArray)
{
	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(_T("Failed to load data!\n Try to reload."));
		return FALSE;
	}

	//Добавяме първи елемент, който ще се презентира
	if (strPersonArray.AddElement(recPerson.szFirstName) == -1)
	{
		return FALSE;
	}

	//Добавяме втори елемент, който ще се презентира
	if (strPersonArray.AddElement(recPerson.szLastName) == -1)
	{
		return FALSE;
	}

	//Добавяме трети елемент, който ще се презентира
	if (strPersonArray.AddElement(recPerson.szEGN) == -1)
	{
		return FALSE;
	}

	//Достъпваме града на клиента по подадено ид
	CITIES* pCity = pPersonDoc->GetAdditionalPersonInfo().FindCityInArrayById(recPerson.lIdCity);

	//Проверка за открит обект
	if (pCity == nullptr)
	{
		return FALSE;
	}

	//Добавяме четвърти елемент, който ще се презентира
	if (strPersonArray.AddElement(pCity->szRegion) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsView::ConvertAllElementsPersonsToArrayWithDisplayData(const CPersonsArray& oPersonsInfoArray, CTableDataArray<CTableDataArray<CString>>& strPersonsArrayToDisplayInListCtrl)
{
	//Преминаваме през висчки елементи на масива с данни 
	for (INT_PTR nIndex = 0; nIndex < oPersonsInfoArray.GetCount(); nIndex++)
	{
		//Достъпваме информацията за един клиент от масива
		PERSONS* recOnePersonArray = oPersonsInfoArray.GetAt(nIndex);
		if (recOnePersonArray == nullptr)
		{
			return FALSE;
		}

		//Инициализираме  масив, който ще съдържа всички презентационни данни на елемента	//Добавяме първи елемент, който ще се презентира
		CTableDataArray<CString> strArrayOneElement;
		if (!ConvertToDisplayDataInListCtrl(*recOnePersonArray, strArrayOneElement))
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
