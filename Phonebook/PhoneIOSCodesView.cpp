// PhoneIOSCodesView.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PhoneIOSCodesView.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneIOSCodesView

IMPLEMENT_DYNCREATE(CPhoneIOSCodesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneIOSCodesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CPhoneIOSCodesView::InsertPhoneISOCode)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CPhoneIOSCodesView::UpdatePhoneISOCode)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CPhoneIOSCodesView::DeletePhoneISOCode)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CPhoneIOSCodesView::FindPhoneISOCode)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CPhoneIOSCodesView::ReloadPhoneISOCodes)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneIOSCodesView::CPhoneIOSCodesView()
{

}

CPhoneIOSCodesView::~CPhoneIOSCodesView()
{
}


// Overrides
// ----------------
CPhoneISOCodesDoc* CPhoneIOSCodesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneISOCodesDoc)));
	return (CPhoneISOCodesDoc*)m_pDocument;
}

BOOL CPhoneIOSCodesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Задаваме тип репорт на лист контролата
	cs.style |= LVS_REPORT | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

void CPhoneIOSCodesView::OnInitialUpdate()
{
	//Достъп до лист контролата
	CListCtrl& lscPhoneISOCodeList = GetListCtrl();

	//Добавяне на допълнителни стилове за лист контролата
	lscPhoneISOCodeList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	lscPhoneISOCodeList.InsertColumn(PHONE_ISO_CODES_LIST_STR_COLUMN_ISO_CODE, PHONE_ISO_CODES_CTRL_COLUMN_PHONE_ISO_CODE_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);

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

void CPhoneIOSCodesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	ViewPhoneISOCode();
}

void CPhoneIOSCodesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneIOSCodesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneISOCodes = GetListCtrl();

	switch (nChar)
	{

		//При натискане на бутон Ctrl + I да се добави нов запис
	case 'I':
	{
		InsertPhoneISOCode();
		return;
	}
	break;

	//При натискане на бутон Ctrl + F да се търси запис
	case 'F':
	{
		FindPhoneISOCode();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadPhoneISOCodes();
		return;
	}
	break;
	}

	//Другите опрерации са вързможни само ако има избран елемент
	if (oListCtrManager.GetIndexSelectedItem(lscPhoneISOCodes) == -1)
	{
		return;
	}

	switch (nChar)
	{
		//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeletePhoneISOCode();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		ViewPhoneISOCode();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdatePhoneISOCode();
		return;
	}
	break;
	}

	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPhoneIOSCodesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = oListCtrManager.GetIndexSelectedItem(lscPhoneIOSCodes);

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

void CPhoneIOSCodesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//Проверка, при първоначално извикване на метода
	if (lHint == NULL)
	{
		return;
	}

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Обект, който ще се обработва
	if (pHint == nullptr)
	{
		return;
	}

	//Елемент
	PHONE_ISO_CODES& oPhoneISOCode = *(PHONE_ISO_CODES*)pHint;

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = oListCtrManager.GetIndexSelectedItem(lscPhoneIOSCodes);

	if (lHint == OPERATIONS_WITH_DATA_FLAGS_DELETE)
	{
		//Изтриваме ред по поданен индекс
		if (!oListCtrManager.RemoveElement(lscPhoneIOSCodes, nIndexItem))
		{
			AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		}
		return;
	}

	//Превръщаме типа телефон в масив със стрингови данни, които ще се презентират в лист контролата
	CRowDataListCtrl <PHONE_ISO_CODES> oRowData;
	oRowData.SetData(oPhoneISOCode);
	if (!SetColumnDisplayData(oRowData))
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Редактираме, по открития индекс, данните или добавяме елемент при липса на индекс
	if (!oListCtrManager.AddOrEditElement(lscPhoneIOSCodes, oRowData, nIndexItem))
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

void CPhoneIOSCodesView::ViewPhoneISOCode()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Достъпваме данните от лист контролата
	PHONE_ISO_CODES* pPhoneISOCode = oListCtrManager.GetSelectedItem(lscPhoneIOSCodes);

	//Проверка за открит елемент
	if (pPhoneISOCode == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPhoneISOCodesDialog oDialog(*pPhoneISOCode, ENABLE_DIALOG_PERSON_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPhoneIOSCodesView::InsertPhoneISOCode()
{
	//Достъпваме диалога
	CPhoneISOCodesDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_ISO_CODES oPhoneISOCode;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Вземаме данните от контролите от диалога
	if (!oDialog.GetControlsData(oPhoneISOCode))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Добавяме данните в документа
	if (!GetDocument() || !GetDocument()->InsertPhoneISOCode(oPhoneISOCode))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPhoneIOSCodesView::UpdatePhoneISOCode()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	PHONE_ISO_CODES* pPhoneISOCode = oListCtrManager.GetSelectedItem(lscPhoneIOSCodes);

	//Проверка за открит елемент
	if (pPhoneISOCode == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Запазваме ид-то на записа
	long lId = pPhoneISOCode->lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPhoneISOCodesDialog oDialog(*pPhoneISOCode);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Присвояваме ноивте данни от контролите в диалога със старото ид
	if (!oDialog.GetControlsData(*pPhoneISOCode))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	pPhoneISOCode->lId = lId;

	//Редактираме данните в документа като подаваме стуртура с обновени данни
	if (!GetDocument() || !GetDocument()->UpdatePhoneISOCode(*pPhoneISOCode))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPhoneIOSCodesView::DeletePhoneISOCode()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(WARNING_MSG_DELETE_DATA, MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Достъпваме селектирания запис
	PHONE_ISO_CODES* pPhoneISOCode = oListCtrManager.GetSelectedItem(lscPhoneIOSCodes);

	//Проверка за открит елемент
	if (pPhoneISOCode == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Изтриваме данните в документа по намереното ИД
	if (!GetDocument() || !GetDocument()->DeletePhoneISOCode(*pPhoneISOCode))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPhoneIOSCodesView::FindPhoneISOCode()
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
	CPhoneISOCodesDialog oDialog;

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	PHONE_ISO_CODES recPhoneISOCode;

	//Присвояваме ноивте данни от контролите в диалога със старото ид
	if (!oDialog.GetControlsData(recPhoneISOCode))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);

		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	int nListCrtCountItems = lscPhoneIOSCodes.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		CString strCurrentPhoneType = lscPhoneIOSCodes.GetItemText(nIndex, PHONE_ISO_CODES_LIST_STR_COLUMN_ISO_CODE);

		if (_tcscmp(recPhoneISOCode.czPhoneISOCode, strCurrentPhoneType) != 0)
		{
			if (!lscPhoneIOSCodes.DeleteItem(nIndex))
			{
				AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
				return;
			}
			continue;
		}
	}
}

void CPhoneIOSCodesView::ReloadPhoneISOCodes()
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
BOOL CPhoneIOSCodesView::LoadDataInListCtrFromDoc()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Достъпваме документа
	CPhoneISOCodesDoc* pPhoneISOCodesDoc = GetDocument();
	if (pPhoneISOCodesDoc == nullptr)
	{
		return FALSE;
	}

	const CPhoneISOCodesArray& oPhoneTypesArray = pPhoneISOCodesDoc->GetPhoneISOCodesArray();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTypedPtrDataArray<CRowDataListCtrl<PHONE_ISO_CODES>> oRowsDataListCtrlArray;

	if (!SetColumnDisplayDataArray(oPhoneTypesArray, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!oListCtrManager.LoadDataFromResource(lscPhoneIOSCodes, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneIOSCodesView::IsAllDataLoadFromDoc()
{
	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_ISO_CODES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneIOSCodes = GetListCtrl();

	//Достъпваме документа
	CPhoneISOCodesDoc* pPhoneISOCodesDoc = GetDocument();

	if (pPhoneISOCodesDoc == nullptr)
	{
		return FALSE;
	}

	//връщаме резултата за успех или не
	if (!oListCtrManager.IsAllDataLoadFromResourse(lscPhoneIOSCodes, pPhoneISOCodesDoc->GetPhoneISOCodesArrayCount()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneIOSCodesView::SortItemsListCtr()
{
	//Инстанция на лист контролата
	CListCtrl& lscPhoneISOCodes = GetListCtrl();

	//Изпълняваме метод за сортиране по азбучен ред
	lscPhoneISOCodes.SortItems(CompareFunc, 0);

	return TRUE;
}

int CALLBACK CPhoneIOSCodesView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// Достъпваме указателите от подадените параметри
	PHONE_ISO_CODES* pPhoneISOCode1 = (PHONE_ISO_CODES*)lParam1;
	PHONE_ISO_CODES* pPhoneISOCode2 = (PHONE_ISO_CODES*)lParam2;

	//Проверяваме дали указателите за нулеви
	if (pPhoneISOCode1 == nullptr || pPhoneISOCode2 == nullptr) {
		return 0;
	}

	// Първо сравняваме първите им имена 
	int nResult = _tcscmp(pPhoneISOCode1->czPhoneISOCode, pPhoneISOCode2->czPhoneISOCode);

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPhoneIOSCodesView::SetColumnDisplayData(CRowDataListCtrl<PHONE_ISO_CODES>& oRowData)
{
	const PHONE_ISO_CODES& recPhoneISOCode = oRowData.GetData();
	//Добавяме първи елемент, който ще се презентира
	if (oRowData.AddElementToDisplayData(recPhoneISOCode.czPhoneISOCode) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneIOSCodesView::SetColumnDisplayDataArray(const CPhoneISOCodesArray& oPhoneISOCodesArray, CTypedPtrDataArray<CRowDataListCtrl<PHONE_ISO_CODES>>& oRowsDataArray)
{
	//Преминаваме през висчки елементи на масива с данни 
	for (INT_PTR nIndex = 0; nIndex < oPhoneISOCodesArray.GetCount(); nIndex++)
	{
		//Достъпваме информацията за един елемент от масива
		PHONE_ISO_CODES* pPhoneISOCode = oPhoneISOCodesArray.GetAt(nIndex);
		if (pPhoneISOCode == nullptr)
		{
			return FALSE;
		}

		//Инициализираме масив, който ще съдържа данните от елемента, който ще се презентира
		CRowDataListCtrl<PHONE_ISO_CODES> oRowData;
		oRowData.SetData(*pPhoneISOCode);
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

void CPhoneIOSCodesView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

#ifdef _DEBUG
void CPhoneIOSCodesView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneIOSCodesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG
