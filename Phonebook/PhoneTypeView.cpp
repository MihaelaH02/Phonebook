#include "pch.h"
#include "Phonebook.h"
#include "PhoneTypeView.h"
/*
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
	lscPhonetypes.InsertColumn(PHONE_TYPES_LIST_STR_COLUMN_PHONE_TYPE, _T("Phone type"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);

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

void CPhoneTypeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	//Извършване на операция селект
	SelectPhoneType();
}

void CPhoneTypeView::OnRButtonUp(UINT /* nFlags , CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneTypeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
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
	if (m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPhoneTypes) == -1)
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
		SelectPhoneType();
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

void CPhoneTypeView::OnContextMenu(CWnd* /* pWnd , CPoint point)
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
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Индекс на селектирания запис
	int nSelectedIndex = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPhoneTypes);

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

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Обект, който ще се обработва, ако е подаден такъв
	if (pHint == nullptr)
	{
		return;
	}

	PHONE_TYPES& oPhoneType = *(PHONE_TYPES*)pHint;

	//Превръщаме града в масив с стрингови данни, които ще се презентират в лист контролата
	CTableDataArray<CString> strPersonArrayToOperateInListCtrl;
	if (!ConvertElementPhoneTypeToArrayWithDisplayData(oPhoneType, strPersonArrayToOperateInListCtrl))
	{
		return;
	}


	//Проверка за изпълнение на операция добавяне на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_INSERT == lHint)
	{
		//Добавяме данни
		m_oManagerListCtr.ManageAddingDataInElementListCtr(lscPhoneTypes, oPhoneType, strPersonArrayToOperateInListCtrl);
		return;
	}

	//Достъпваме индекса, на избрания елемент, в лист контролата
	int nIndexItem = m_oManagerListCtr.FindIndexByElement(lscPhoneTypes, oPhoneType);
	if (nIndexItem == -1)
	{
		return;
	}

	//Проверка за изпълнение на операция редакция на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_UPDATE == lHint)
	{
		//Редактираме, по открития индекс, данните
		m_oManagerListCtr.ManageAddingDataInElementListCtr(lscPhoneTypes, oPhoneType, strPersonArrayToOperateInListCtrl, nIndexItem);
		return;
	}

	//Проверка за изпълнение на операция изтриване на елемент
	if (OPERATIONS_WITH_DATA_FLAGS_DELETE == lHint)
	{

		//Изтриваме ред по поданен индекс
		m_oManagerListCtr.DeleteElementListCtr(lscPhoneTypes, nIndexItem);
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

void CPhoneTypeView::SelectPhoneType()
{
	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Индекс на селектирания запис
	int nIndexItem = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPhoneTypes);

	//Проверка за избран елемент
	if (nIndexItem == -1)
	{
		AfxMessageBox(_T("Failed to select index of data from list!"));
		return;
	}

	//Достъпваме данните от лист контролата
	PHONE_TYPES& oPhoneTypes = m_oManagerListCtr.GetItemFromListCtr(lscPhoneTypes, nIndexItem);

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	//CPhoneTypesDialog oDialog(oPhoneTypes, ENABLE_DIALOG_CTR_FLAG_NONE);

	//Визуализираме диалога
	//oDialog.DoModal();
}

void CPhoneTypeView::InsertPhoneType()
{
	//Достъпваме диалога
	//CPhoneTypesDialog oDialog;

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_TYPES oPhoneTypes;

	//При натиснат бутон ОК в диалога
	/*if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		oDialog.GetControlsData(oPhoneTypes);

		//Добавяме данните в документа
		if (!(GetDocument() && GetDocument()->Insert(oPhoneTypes)))
		{
			return;
		}
	}
}

void CPhoneTypeView::UpdatePhoneType()
{
	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъп до индекса на селектирания запис
	int nIndexItem = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPhoneTypes);

	//Инстанция на обект от тип структура с градове, със стойности селектирания запис от лист контролата
	PHONE_TYPES& oPhoneType = m_oManagerListCtr.GetItemFromListCtr(lscPhoneTypes, nIndexItem);

	//Запазваме ид-то на записа
	long lId = oPhoneType.lId;

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	//CPhoneTypesDialog oDialog(oPhoneType);

	//Проверка за натиснат бутон OK в диалога
	/*if (oDialog.DoModal() == IDOK)
	{
		//Присвояваме ноивте данни от контролите в диалога със старото ид
		oDialog.GetControlsData(oPhoneType);
		oPhoneType.lId = lId;

		//Редактираме данните в документа като подаваме стуртура с обновени данни
		if (!(GetDocument() && GetDocument()->UpdatePhoneType(oPhoneType)))
		{
			return;
		}
	}
}

void CPhoneTypeView::DeletePhoneType()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(_T("Are you sure you want to delete data?"), MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме индекса на селектирания запис
	int nIndexItem = m_oManagerListCtr.GetSelectedItemListCtrByIndex(lscPhoneTypes);

	//Достъпваме селектирания запис
	PHONE_TYPES& oPhoneType = m_oManagerListCtr.GetItemFromListCtr(lscPhoneTypes, nIndexItem);

	//Изтриваме данните в документа по намереното ИД
	if (!(GetDocument() && GetDocument()->Delete(oPhoneType)))
	{
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
			return ;
		}
	}

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	int nListCrtCountItems = lscPhoneTypes.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		CString strCurrentPhoneType = lscPhoneTypes.GetItemText(nIndex, PHONE_TYPES_LIST_STR_COLUMN_PHONE_TYPE);

		if (recPhoneType.czPhoneType != strCurrentPhoneType)
		{
			if (!lscPhoneTypes.DeleteItem(nIndex))
			{
				return FALSE;
			}
			continue;
		}
	}

	return TRUE
}

void CPhoneTypeView::ReloadPhoneTypes()
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

BOOL CPhoneTypeView::LoadDataInListCtrFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме документа
	CPhoneTypesDoc* pPhoneTypesDoc = GetDocument();
	if (pPhoneTypesDoc == nullptr)
	{
		return FALSE;
	}

	const CPhoneTypesArray& oPhoneTypesArray = pPhoneTypesDoc->GetPhoneTypesArrayElementsCount();

	//Запълваме масив с всички презентационни данни на всички елементи
	CTableDataArray<CTableDataArray<CString>> strPhoneTypesArrayToOperateInListCtrl;

	if (!ConvertAllElementsPhoneTypesToArrayWithDisplayData(oPhoneTypesArray, strPhoneTypesArrayToOperateInListCtrl))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!m_oManagerListCtr.LoadDataInListCtrFromResourse(lscPhoneTypes, oPhoneTypesArray, strPhoneTypesArrayToOperateInListCtrl))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CPhoneTypeView::IsAllDataLoadFromDoc()
{
	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = GetListCtrl();

	//Достъпваме документа
	CPhoneTypesDoc* pPhoneTypesDoc = GetDocument();

	if (pPhoneTypesDoc == nullptr)
	{
		return FALSE;
	}

	//връщаме резултата за успех или не
	return m_oManagerListCtr.IsAllDataLoadFromResourse(lscPhoneTypes, pPhoneTypesDoc->GetPhoneTypesArrayElementsCount());
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

BOOL CPhoneTypeView::ConvertElementPhoneTypeToArrayWithDisplayData(const PHONE_TYPES& recPhoneType, CTableDataArray<CString>& strPhoneTypeArray)
{
	//Добавяме първи елемент, който ще се презентира
	if (strPhoneTypeArray.AddElement(recPhoneType.czPhoneType) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypeView::ConvertAllElementsPhoneTypesToArrayWithDisplayData(const CTableDataArray<PHONE_TYPES>& oPhoneTypesArray, CTableDataArray<CTableDataArray<CString>>& strPhoneTypesArrayToDisplayInListCtrl)
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
		CTableDataArray<CString> strArrayOneElement;
		if (!ConvertElementPhoneTypeToArrayWithDisplayData(*recPhoneType, strArrayOneElement))
		{
			return FALSE;
		}

		//Добавяме масива с презентационни данни към масива с всички данни за всички елементи
		if (strPhoneTypesArrayToDisplayInListCtrl.AddElement(strArrayOneElement) == -1)
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


// CPhoneTypeView message handlers
*/

//void CPhoneTypeView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
/*{
	// TODO: Add your specialized code here and/or call the base class
}
*/