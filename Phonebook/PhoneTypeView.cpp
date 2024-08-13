#include "pch.h"
#include "Phonebook.h"
#include "PhoneTypeView.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypeView

IMPLEMENT_DYNCREATE(CPhoneTypeView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypeView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CPhoneTypeView::InsertPhoneType)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CPhoneTypeView::UpdatePhoneType)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CPhoneTypeView::DeletePhoneType)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CPhoneTypeView::FindPhoneType)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CPhoneTypeView::ReloadPhoneTypes)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
CPhoneTypeView::CPhoneTypeView()
{

}

CPhoneTypeView::~CPhoneTypeView()
{
}

// Overrides
// ----------------

CPhoneTypesDoc* CPhoneTypeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}

BOOL CPhoneTypeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Задаваме тип репорт на лист контролата
	cs.style |= LVS_REPORT | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

void CPhoneTypeView::OnInitialUpdate()
{
	//Достъп до лист контролата
	CListCtrl& lscPhonetypes = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscPhonetypes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscPhonetypes.InsertColumn(PHONE_TYPES_LIST_STR_COLUMN_PHONE_TYPE, PHONE_TYPES_LIST_CTRL_COLUMN_PHONE_TYPE_TITLE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);

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

void CPhoneTypeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	ViewPhoneType();
}

void CPhoneTypeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneTypeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	switch (nChar)
	{

		//При натискане на бутон Ctrl + I да се добави нов запис
	case 'I':
	{
		InsertPhoneType();
		return;
	}
	break;

	//При натискане на бутон Ctrl + F да се търси запис
	case 'F':
	{
		FindPhoneType();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadPhoneTypes();
		return;
	}
	break;
	}

	//Другите опрерации са вързможни само ако има избран елемент
	if (oListCtrManager.GetIndexSelectedItem(lscPhoneTypes) == -1)
	{
		return;
	}

	switch (nChar)
	{
		//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeletePhoneType();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		ViewPhoneType();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdatePhoneType();
		return;
	}
	break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPhoneTypeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = oListCtrManager.GetIndexSelectedItem(lscPhoneTypes);

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

void CPhoneTypeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//Проверка, при първоначално извикване на метода
	if (lHint == NULL)
	{
		return;
	}

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Обект, който ще се обработва
	if (pHint == nullptr)
	{
		return;
	}

	//Елемент
	PHONE_TYPES& oPhoneType = *(PHONE_TYPES*)pHint;

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = oListCtrManager.GetIndexSelectedItem(lscPhoneTypes);

	if (lHint == OPERATIONS_WITH_DATA_FLAGS_DELETE)
	{
		//Изтриваме ред по поданен индекс
		if (!oListCtrManager.RemoveElement(lscPhoneTypes, nIndexItem))
		{
			AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		}
		return;
	}

	//Превръщаме типа телефон в масив със стрингови данни, които ще се презентират в лист контролата
	CRowDataListCtrl <PHONE_TYPES> oRowData;
	oRowData.SetData(oPhoneType);
	if (!SetColumnDisplayData(oRowData))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Редактираме, по открития индекс, данните или добавяме елемент при липса на индекс
	if (!oListCtrManager.AddOrEditElement(lscPhoneTypes, oRowData, nIndexItem))
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

void CPhoneTypeView::ViewPhoneType()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме данните от лист контролата
	PHONE_TYPES* pPhoneTypes = oListCtrManager.GetSelectedItem(lscPhoneTypes);

	//Проверка за открит елемент
	if (pPhoneTypes == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPhoneTypesDialog oDialog(*pPhoneTypes, ENABLE_DIALOG_CITIES_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPhoneTypeView::InsertPhoneType()
{
	//Достъпваме диалога
	CPhoneTypesDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_TYPES oPhoneTypes;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Вземаме данните от контролите от диалога
	if (!oDialog.GetControlsData(oPhoneTypes))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Добавяме данните в документа
	if (!GetDocument() || !GetDocument()->InsertPhoneType(oPhoneTypes))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPhoneTypeView::UpdatePhoneType()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	PHONE_TYPES* pPhoneType = oListCtrManager.GetSelectedItem(lscPhoneTypes);

	//Проверка за открит елемент
	if (pPhoneType == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Запазваме ид-то на записа
	long lId = pPhoneType->lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPhoneTypesDialog oDialog(*pPhoneType);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Присвояваме ноивте данни от контролите в диалога със старото ид
	if (!oDialog.GetControlsData(*pPhoneType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	pPhoneType->lId = lId;

	//Редактираме данните в документа като подаваме стуртура с обновени данни
	if (!GetDocument() || !GetDocument()->UpdatePhoneType(*pPhoneType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPhoneTypeView::DeletePhoneType()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(WARNING_MSG_DELETE_DATA, MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме селектирания запис
	PHONE_TYPES* pPhoneType = oListCtrManager.GetSelectedItem(lscPhoneTypes);

	//Проверка за открит елемент
	if (pPhoneType == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Изтриваме данните в документа по намереното ИД
	if (!GetDocument() || !GetDocument()->DeletePhoneType(*pPhoneType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPhoneTypeView::FindPhoneType()
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
	CPhoneTypesDialog oDialog;

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	PHONE_TYPES recPhoneType;

	//Присвояваме ноивте данни от контролите в диалога със старото ид
	if (!oDialog.GetControlsData(recPhoneType))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);

		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	int nListCrtCountItems = lscPhoneTypes.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		CString strCurrentPhoneType = lscPhoneTypes.GetItemText(nIndex, PHONE_TYPES_LIST_STR_COLUMN_PHONE_TYPE);

		if (_tcscmp(recPhoneType.czPhoneType, strCurrentPhoneType) != 0)
		{
			if (!lscPhoneTypes.DeleteItem(nIndex))
			{
				AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
				return;
			}
			continue;
		}
	}
}

void CPhoneTypeView::ReloadPhoneTypes()
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

BOOL CPhoneTypeView::LoadDataInListCtrFromDoc()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме документа
	CPhoneTypesDoc* pPhoneTypesDoc = GetDocument();
	if (pPhoneTypesDoc == nullptr)
	{
		return FALSE;
	}

	const CPhoneTypesArray& oPhoneTypesArray = pPhoneTypesDoc->GetPhoneTypesArray();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTypedPtrDataArray<CRowDataListCtrl<PHONE_TYPES>> oRowsDataListCtrlArray;

	if (!SetColumnDisplayDataArray(oPhoneTypesArray, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!oListCtrManager.LoadDataFromResource(lscPhoneTypes, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypeView::IsAllDataLoadFromDoc()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме документа
	CPhoneTypesDoc* pPhoneTypesDoc = GetDocument();

	if (pPhoneTypesDoc == nullptr)
	{
		return FALSE;
	}

	//връщаме резултата за успех или не
	if (!oListCtrManager.IsAllDataLoadFromResourse(lscPhoneTypes, pPhoneTypesDoc->GetPhoneTypesArrayCount()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypeView::SortItemsListCtr()
{
	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Изпълняваме метод за сортиране по азбучен ред
	lscPhoneTypes.SortItems(CompareFunc, 0);

	return TRUE;
}

int CALLBACK CPhoneTypeView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// Достъпваме указателите от подадените параметри
	PHONE_TYPES* pPhoneType1 = (PHONE_TYPES*)lParam1;
	PHONE_TYPES* pPhoneType2 = (PHONE_TYPES*)lParam2;

	//Проверяваме дали указателите за нулеви
	if (pPhoneType1 == nullptr || pPhoneType2 == nullptr) {
		return 0;
	}

	// Първо сравняваме първите им имена 
	int nResult = _tcscmp(pPhoneType1->czPhoneType, pPhoneType2->czPhoneType);

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPhoneTypeView::SetColumnDisplayData(CRowDataListCtrl<PHONE_TYPES>& oRowData)
{
	const PHONE_TYPES& recPhoneType = oRowData.GetData();
	//Добавяме първи елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(recPhoneType.czPhoneType) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypeView::SetColumnDisplayDataArray(const CTypedPtrDataArray<PHONE_TYPES>& oPhoneTypesArray, CTypedPtrDataArray<CRowDataListCtrl<PHONE_TYPES>>& oRowsDataArray)
{
	//Преминаваме през висчки елементи на масива с данни 
	for (INT_PTR nIndex = 0; nIndex < oPhoneTypesArray.GetCount(); nIndex++)
	{
		//Достъпваме информацията за един тип телефон от масива
		PHONE_TYPES* recPhoneType = oPhoneTypesArray.GetAt(nIndex);
		if (recPhoneType == nullptr)
		{
			return FALSE;
		}

		//Инициализираме масив, който ще съдържа данните от елемента, който ще се презентира
		CRowDataListCtrl<PHONE_TYPES> oRowData;
		oRowData.SetData(*recPhoneType);
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


// CPhoneTypeView diagnostics

#ifdef _DEBUG
void CPhoneTypeView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneTypeView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG
