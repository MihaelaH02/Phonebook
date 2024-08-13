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
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_FIRSTNAME, PERSONS_LIST_CTRL_COLUMN_FIRSTNAME_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_LASTNAME, PERSONS_LIST_CTRL_COLUMN_LASTNAME_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_EGN, PERSONS_LIST_CTRL_COLUMN_EGN_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);
	lscPersons.InsertColumn(PERSONS_LIST_CTR_COLUMN_REGION, PERSONS_LIST_CTRL_COLUMN_REGION_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);

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
	///Член проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

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
	if (oManagerListCtr.GetIndexSelectedItem(lscPersons) == -1)
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
	///Проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = oManagerListCtr.GetIndexSelectedItem(lscPersons);

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
	if (lHint == NULL || lHint == OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		return;
	}

	///Член проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = oManagerListCtr.GetIndexSelectedItem(lscPersons);

	//Проверка за изпълнение на операция изтриване на елемент
	if (lHint == OPERATIONS_WITH_DATA_FLAGS_DELETE)
	{
		//Изтриваме ред по поданен индекс
		if (!oManagerListCtr.RemoveElement(lscPersons, nIndexItem))
		{
			AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		}
		return;
	}

	//Проверка за обект, който ще се обработва
	if (pHint == nullptr)
	{
		return;
	}

	//Достъп до обект, който се е модифицирал
	PERSONS& recPerson = *(PERSONS*)pHint;

	//Превръщаме клиента в масив със стрингови данни, които ще се презентират в лист контролата
	CRowDataListCtrl <PERSONS> oRowData;
	oRowData.SetData(recPerson);
	if (!SetColumnDisplayData(oRowData))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Проверка за изпълнение на операция добавяне или редактиране на елемент
	if (!oManagerListCtr.AddOrEditElement(lscPersons, oRowData, nIndexItem))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	AfxMessageBox(OK_MSG_SUCCESSFUL_OPERATION);

	//Сортировка на елементите в лист контролата след направен промени
	if (!SortPersonsInListCtr())
	{
		AfxMessageBox(ERROR_MGS_FAIL_SORT_LIST_CTRL);
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
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
		return;
	}

	///Проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме селектирания клиент от лист контролата
	PERSONS* pPerson = oManagerListCtr.GetSelectedItem(lscPersons);

	if (pPerson == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъпваме вссички данни за селектирания клиент
	CPersonDBModel oPersonDBModel;
	if (!pPersonDoc->SelectPerson(pPerson->lId, oPersonDBModel))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPersonsDialog oDialog(oPersonDBModel, pPersonDoc->GetAdditionalModels(), ENABLE_DIALOG_CITIES_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPersonsView::InsertPersonInfo()
{
	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
		return;
	}

	//Достъпваме диалога
	CPersonsDialog oDialog(pPersonDoc->GetAdditionalModels());

	//Нова структура, която ще съдържа данни за новия запис
	CPersonDBModel oPersonDBModel;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Вземаме данните от контролите от диалога
	if (!oDialog.GetControlsData(oPersonDBModel))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Добавяме данните в документа
	if (!(GetDocument() && GetDocument()->ProcessPerson(oPersonDBModel, OPERATIONS_WITH_DATA_FLAGS_INSERT)))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPersonsView::UpdatePersonInfo()
{
	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
		return;
	}

	///Проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме селектирания клиент от лист контролата
	PERSONS* pPerson = oManagerListCtr.GetSelectedItem(lscPersons);

	if (pPerson == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъпваме всички данни за селектирания клиент
	CPersonDBModel oPersonDBModel;
	if (!pPersonDoc->SelectPerson(pPerson->lId, oPersonDBModel))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPersonsDialog oDialog(oPersonDBModel, pPersonDoc->GetAdditionalModels());

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Присвояваме ноивте данни от диалога
	if (!oDialog.GetControlsData(oPersonDBModel))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Проверка дали всички модификации направени по списъка с телефонни номера съдържат ИД на съответния клиент
	if (!oPersonDBModel.SetPhoneNumbersPersonId())
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Редактираме данните в документа като подаваме стуртура с обновени данни
	if (!(GetDocument() && GetDocument()->ProcessPerson(oPersonDBModel, OPERATIONS_WITH_DATA_FLAGS_UPDATE)))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPersonsView::DeletePersonInfo()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(WARNING_MSG_DELETE_DATA, MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	///Проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме селектирания клиент от лист контролата
	PERSONS* pPerson = oManagerListCtr.GetSelectedItem(lscPersons);

	if (pPerson == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
		return;
	}

	//Достъпваме всички данни за селектирания клиент
	CPersonDBModel oPersonDBModel;

	if (!pPersonDoc->SelectPerson(pPerson->lId, oPersonDBModel))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Преместваме телефонните му номера в групата за изтрити
	CPhoneNumbersMap* pPhoneNumbersOperationsMap = &oPersonDBModel.GetPhoneNumbers();
	if (pPhoneNumbersOperationsMap == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	if (!pPhoneNumbersOperationsMap->ChangeValuesToOperation(OPERATIONS_WITH_DATA_FLAGS_DELETE))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return ;
	}
	
	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->ProcessPerson(oPersonDBModel, OPERATIONS_WITH_DATA_FLAGS_DELETE)))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
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
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
		return;
	}

	//Сортировка на обновените данни в лист контролата
	if (!SortPersonsInListCtr())
	{
		AfxMessageBox(ERROR_MGS_FAIL_SORT_LIST_CTRL);
		return;
	}
}


// Methods
// ---------------

BOOL CPersonsView::LoadPersonsInListCtrFromDoc()
{
	///Проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

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
	CPersonsArray oPersonsInfoArray = pPersonsDoc->GetPersons();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTypedPtrDataArray<CRowDataListCtrl<PERSONS>> oRowsData;
	if (!SetColumnDisplayDataArray(oPersonsInfoArray, oRowsData))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!oManagerListCtr.LoadDataFromResource(lscPersons,oRowsData))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsView::IsAllPersonsLoadFromDoc()
{
	///Проминлива от тип клас, който ще управлява елемените в лист контролата
	CListCtrlManager<PERSONS> oManagerListCtr;

	//Инстанция на лист контролата
	CListCtrl& lscPersons = GetListCtrl();

	//Достъпваме документа
	CPersonsDoc* pPersonsDoc = GetDocument();

	if (pPersonsDoc == nullptr)
	{
		return FALSE;
	}

	//Проверка дали броя на елементите в лист контролата отгоравя на данните от документа
	if(!oManagerListCtr.IsAllDataLoadFromResourse(lscPersons, pPersonsDoc->GetPersonsArrayCount()))
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
	if (!lscPersons.SortItems(CompareFunc, (LPARAM)this))
	{
		return FALSE;
	}

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
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
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
	CITIES* pCity1 = pPersonDoc->GetAdditionalModels().GetCityById(pPerson1->lIdCity);
	CITIES* pCity2 = pPersonDoc->GetAdditionalModels().GetCityById(pPerson2->lIdCity);

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

BOOL CPersonsView::SetColumnDisplayData(CRowDataListCtrl<PERSONS>& oRowData)
{
	const PERSONS& recPerson = oRowData.GetData();

	//Добавяме първи елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(recPerson.szFirstName) == -1)
	{
		return FALSE;
	}

	//Добавяме втори елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(recPerson.szLastName) == -1)
	{
		return FALSE;
	}

	//Добавяме трети елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(recPerson.szEGN) == -1)
	{
		return FALSE;
	}

	//Достъп до данни от документа
	CPersonsDoc* pPersonDoc = GetDocument();
	if (pPersonDoc == nullptr)
	{
		AfxMessageBox(ERROR_MGS_FAIL_LOAD_DATA);
		return FALSE;
	}

	//Достъпваме града на клиента по подадено ид
	CITIES* pCity = pPersonDoc->GetAdditionalModels().GetCityById(recPerson.lIdCity);

	//Проверка за открит обект
	if (pCity == nullptr)
	{
		return FALSE;
	}

	//Добавяме четвърти елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(pCity->szRegion) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsView::SetColumnDisplayDataArray(const CPersonsArray& oPersonsInfoArray, CTypedPtrDataArray<CRowDataListCtrl<PERSONS>>& oRowsDataArray)
{
	//Преминаваме през висчки елементи на масива с данни 
	for (INT_PTR nIndex = 0; nIndex < oPersonsInfoArray.GetCount(); nIndex++)
	{
		//Достъпваме информацията за един клиент от масива
		PERSONS* recOnePerson = oPersonsInfoArray.GetAt(nIndex);
		if (recOnePerson == nullptr)
		{
			return FALSE;
		}

		//Инициализираме  масив, който ще съдържа всички презентационни данни на елемента	//Добавяме първи елемент, който ще се презентира
		CRowDataListCtrl<PERSONS> oRowData;
		oRowData.SetData(*recOnePerson);
		if (!SetColumnDisplayData(oRowData))
		{
			return FALSE;
		}

		//Добавяме масива с презентационни данни към масива с всички данни за всички елементи
		if (oRowsDataArray.AddElement(oRowData) == -1)
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
