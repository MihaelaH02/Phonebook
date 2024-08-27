#include "pch.h"
#include "Phonebook.h"
#include "PersonTypesView.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonTypeView

IMPLEMENT_DYNCREATE(CPersonTypesView, CListView)

BEGIN_MESSAGE_MAP(CPersonTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CPersonTypesView::InsertPersonType)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CPersonTypesView::UpdatePersonType)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CPersonTypesView::DeletePersonType)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CPersonTypesView::FindPersonType)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CPersonTypesView::ReloadPersonTypes)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
CPersonTypesView::CPersonTypesView()
{

}

CPersonTypesView::~CPersonTypesView()
{
}

// Overrides
// ----------------

CPersonTypesDoc* CPersonTypesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonTypesDoc)));
	return (CPersonTypesDoc*)m_pDocument;
}

BOOL CPersonTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Задаваме тип репорт на лист контролата
	cs.style |= LVS_REPORT | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

void CPersonTypesView::OnInitialUpdate()
{
	//Достъп до лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscPersonTypes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscPersonTypes.InsertColumn(PERSON_TYPES_LIST_STR_COLUMN_PERSON_TYPES, PERSON_TYPES_LIST_CTRL_COLUMN_PERSON_TYPE_TITLE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);

	//Зареждане на данните от документа
	if (!LoadDataInListCtrFromDoc())
	{
		return;
	}

	//Сортировка на заредените данни
	if (!SortItemsListCtr())
	{
		return;
	}

	CListView::OnInitialUpdate();

}

void CPersonTypesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	ViewPersonType();
}

void CPersonTypesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonTypesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	switch (nChar)
	{

		//При натискане на бутон Ctrl + I да се добави нов запис
	case 'I':
	{
		InsertPersonType();
		return;
	}
	break;

	//При натискане на бутон Ctrl + F да се търси запис
	case 'F':
	{
		FindPersonType();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadPersonTypes();
		return;
	}
	break;
	}

	//Другите опрерации са вързможни само ако има избран елемент
	if (oListCtrManager.GetIndexSelectedItem(lscPersonTypes) == -1)
	{
		return;
	}

	switch (nChar)
	{
		//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeletePersonType();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		ViewPersonType();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdatePersonType();
		return;
	}
	break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPersonTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	//Инстнация на контекстно меню
	CMenu oMenu;
	oMenu.LoadMenu(IDR_CONTEXT_MANU);
	CMenu* pContextMenu = oMenu.GetSubMenu(0);
	if (pContextMenu == nullptr)
	{
		return;
	}
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = oListCtrManager.GetIndexSelectedItem(lscPersonTypes);

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

	//Операция за филтрация не е активна
	pContextMenu->EnableMenuItem(ID_CONTEXT_MENU_DATA_FILTER, MF_BYCOMMAND | MF_GRAYED);

	//Отваряне на контестното меню на посочената позиция
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPersonTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//Проверка, при първоначално извикване на метода
	if (lHint == NULL)
	{
		return;
	}

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Обект, който ще се обработва
	if (pHint == nullptr)
	{
		return;
	}

	//Елемент
	PERSON_TYPES& oPersonType = *(PERSON_TYPES*)pHint;

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = oListCtrManager.GetIndexSelectedItem(lscPersonTypes);

	if (lHint == OPERATIONS_WITH_DATA_FLAGS_DELETE)
	{
		//Изтриваме ред по поданен индекс
		if (!oListCtrManager.RemoveElement(lscPersonTypes, nIndexItem))
		{
			AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		}
		return;
	}

	//Превръщаме типа телефон в масив със стрингови данни, които ще се презентират в лист контролата
	CRowDataListCtrl <PERSON_TYPES> oRowData;
	oRowData.SetData(oPersonType);
	if (!SetColumnDisplayData(oRowData))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Редактираме, по открития индекс, данните или добавяме елемент при липса на индекс
	if (!oListCtrManager.AddOrEditElement(lscPersonTypes, oRowData, nIndexItem))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	AfxMessageBox(OK_MSG_SUCCESSFUL_OPERATION);

	//Сортировка на обновените елементи
	if (!SortItemsListCtr())
	{
		AfxMessageBox(ERROR_MGS_FAIL_SORT_LIST_CTRL);
		return;
	}
}


// Generated message map functions
// ---------------

void CPersonTypesView::ViewPersonType()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Достъпваме данните от лист контролата
	PERSON_TYPES* pPersonTypes = oListCtrManager.GetSelectedItem(lscPersonTypes);

	//Проверка за открит елемент
	if (pPersonTypes == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPersonTypesDialog oDialog(*pPersonTypes, ENABLE_DIALOG_CITIES_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPersonTypesView::InsertPersonType()
{
	//Достъпваме диалога
	CPersonTypesDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	PERSON_TYPES oPersonTypes;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Вземаме данните от контролите от диалога
	if (!oDialog.GetControlsData(oPersonTypes))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Добавяме данните в документа
	if (!GetDocument() || !GetDocument()->InsertPersonType(oPersonTypes))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPersonTypesView::UpdatePersonType()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	PERSON_TYPES* pPersonType = oListCtrManager.GetSelectedItem(lscPersonTypes);

	//Проверка за открит елемент
	if (pPersonType == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Запазваме ид-то на записа
	long lId = pPersonType->lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPersonTypesDialog oDialog(*pPersonType);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Присвояваме ноивте данни от контролите в диалога със старото ид
	if (!oDialog.GetControlsData(*pPersonType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	pPersonType->lId = lId;

	//Редактираме данните в документа като подаваме стуртура с обновени данни
	if (!GetDocument() || !GetDocument()->UpdatePersonType(*pPersonType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPersonTypesView::DeletePersonType()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(WARNING_MSG_DELETE_DATA, MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Достъпваме селектирания запис
	PERSON_TYPES* pPersonType = oListCtrManager.GetSelectedItem(lscPersonTypes);

	//Проверка за открит елемент
	if (pPersonType == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Изтриваме данните в документа по намереното ИД
	if (!GetDocument() || !GetDocument()->DeletePersonType(*pPersonType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPersonTypesView::FindPersonType()
{

	//Проверка дали всички данни от документа са налични
	if (!IsAllDataLoadFromDoc())
	{
		if (!LoadDataInListCtrFromDoc())
		{
			return;
		}
	}

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPersonTypesDialog oDialog;

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	PERSON_TYPES recPersonType;

	//Присвояваме ноивте данни от контролите в диалога със старото ид
	if (!oDialog.GetControlsData(recPersonType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);

		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	int nListCrtCountItems = lscPersonTypes.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		CString strCurrentPersonType = lscPersonTypes.GetItemText(nIndex, PERSON_TYPES_LIST_STR_COLUMN_PERSON_TYPES);

		if (_tcscmp(recPersonType.czPersonType, strCurrentPersonType) != 0)
		{
			if (!lscPersonTypes.DeleteItem(nIndex))
			{
				AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
				return;
			}
			continue;
		}
	}
}

void CPersonTypesView::ReloadPersonTypes()
{
	//Зареждане на всички данни
	if (!LoadDataInListCtrFromDoc())
	{
		AfxMessageBox(ERROR_MSG_FAIL_RELOAD_LIST_CTRL);
		return;
	}

	//Сортировка на зареденото
	if (!SortItemsListCtr())
	{
		AfxMessageBox(ERROR_MGS_FAIL_SORT_LIST_CTRL);
		return;
	}
}


// Methods
// ---------------
BOOL CPersonTypesView::LoadDataInListCtrFromDoc()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Достъпваме документа
	CPersonTypesDoc* pPersonTypesDoc = GetDocument();
	if (pPersonTypesDoc == nullptr)
	{
		return FALSE;
	}

	const CPersonTypesArray& oPersonTypesArray = pPersonTypesDoc->GetPersonTypesArray();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTypedPtrDataArray<CRowDataListCtrl<PERSON_TYPES>> oRowsDataListCtrlArray;

	if (!SetColumnDisplayDataArray(oPersonTypesArray, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!oListCtrManager.LoadDataFromResource(lscPersonTypes, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonTypesView::IsAllDataLoadFromDoc()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PERSON_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Достъпваме документа
	CPersonTypesDoc* pPersonTypesDoc = GetDocument();

	if (pPersonTypesDoc == nullptr)
	{
		return FALSE;
	}

	//връщаме резултата за успех или не
	if (!oListCtrManager.IsAllDataLoadFromResourse(lscPersonTypes, pPersonTypesDoc->GetPersonTypesArrayCount()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonTypesView::SortItemsListCtr()
{
	//Инстанция на лист контролата
	CListCtrl& lscPersonTypes = GetListCtrl();

	//Изпълняваме метод за сортиране по азбучен ред
	lscPersonTypes.SortItems(CompareFunc, 0);

	return TRUE;
}

int CALLBACK CPersonTypesView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// Достъпваме указателите от подадените параметри
	PERSON_TYPES* pPersonType1 = (PERSON_TYPES*)lParam1;
	PERSON_TYPES* pPersonType2 = (PERSON_TYPES*)lParam2;

	//Проверяваме дали указателите за нулеви
	if (pPersonType1 == nullptr || pPersonType2 == nullptr) {
		return 0;
	}

	// Първо сравняваме първите им имена 
	int nResult = _tcscmp(pPersonType1->czPersonType, pPersonType2->czPersonType);

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPersonTypesView::SetColumnDisplayData(CRowDataListCtrl<PERSON_TYPES>& oRowData)
{
	const PERSON_TYPES& recPersonType = oRowData.GetData();
	//Добавяме първи елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(recPersonType.czPersonType) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonTypesView::SetColumnDisplayDataArray(const CPersonTypesArray& oPersonTypesArray, CTypedPtrDataArray<CRowDataListCtrl<PERSON_TYPES>>& oRowsDataArray)
{
	//Преминаваме през висчки елементи на масива с данни 
	for (INT_PTR nIndex = 0; nIndex < oPersonTypesArray.GetCount(); nIndex++)
	{
		//Достъпваме информацията за един тип телефон от масива
		PERSON_TYPES* pPersonType = oPersonTypesArray.GetAt(nIndex);
		if (pPersonType == nullptr)
		{
			return FALSE;
		}

		//Инициализираме масив, който ще съдържа данните от елемента, който ще се презентира
		CRowDataListCtrl<PERSON_TYPES> oRowData;
		oRowData.SetData(*pPersonType);
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


// CPersonTypeView diagnostics

#ifdef _DEBUG
void CPersonTypesView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonTypesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG
