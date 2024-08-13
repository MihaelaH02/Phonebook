// PersonsDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsDialog.h"


/////////////////////////////////////////////////////////////////////////////
// PersonsDialog.cpp 

IMPLEMENT_DYNAMIC(CPersonsDialog, CDialog)


// Constructor / Destructor
// ----------------

CPersonsDialog::CPersonsDialog(const CAdditionalDBModelsPersons& oAdditionInfo, LPARAM lEnableControls /*= ENABLE_DIALOG_PHERSON_CTR_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_oAdditionalModels(oAdditionInfo), m_lEnableControlsParam(lEnableControls)
{
}

CPersonsDialog::CPersonsDialog(CPersonDBModel& oPersonDBModel, const CAdditionalDBModelsPersons& oAdditionInfo, LPARAM lEnableControls /*= ENABLE_DIALOG_PHERSON_CTR_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent),m_recPerson(oPersonDBModel.GetPerson()), m_oPhoneNumbersOperationsMap(oPersonDBModel.GetPhoneNumbers()), m_oAdditionalModels(oAdditionInfo), m_lEnableControlsParam(lEnableControls)
{
}

CPersonsDialog::~CPersonsDialog()
{
}


// MFC Overrides
// ----------------

void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRTSNAME, m_edbFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_SECONDNAME, m_edbSecondName);
	DDX_Control(pDX, IDC_EDB_PERSONS_LASTNAME, m_edbLastName);
	DDX_Control(pDX, IDC_EDB_PERSONS_EGN, m_edbEGN);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITIES, m_cmbCities);
	DDX_Control(pDX, IDC_EDB_PERSONS_ADDRESS, m_edbAddress);
	DDX_Control(pDX, IDC_LSC_PHONE_NUMBERS, m_lscPhoneNumbers);
}

BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbFirstName.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbSecondName.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbLastName.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbAddress.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbEGN.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_EGN);

	//Задаване на стойности на контролите по пададените данни, ако има такива
	m_edbFirstName.SetWindowTextW(m_recPerson.szFirstName);
	m_edbSecondName.SetWindowTextW(m_recPerson.szSecondName);
	m_edbLastName.SetWindowTextW(m_recPerson.szLastName);
	m_edbEGN.SetWindowTextW(m_recPerson.szEGN);
	m_edbAddress.SetWindowTextW(m_recPerson.szAddress);

	//Запълваме комбо бокса с градове
	if (!AddItemsInCmbCities())
	{
		return FALSE;
	}

	//Промяна на активността на контролите, според подадения параметър
	if (!EnableControls(m_lEnableControlsParam))
	{
		return FALSE;
	}

	//Добавяне на допълнителни стилове за лист контролата
	m_lscPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	m_lscPhoneNumbers.InsertColumn(PHONE_NUMBERS_LIST_CTR_COLUMN_TYPE_PHONE, PHONE_NUMBERS_LIST_CTRL_COLUMN_PHONE_TYPE_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);
	m_lscPhoneNumbers.InsertColumn(PHONE_NUMBERS_LIST_CTR_COLUMN_PHONE_NUMBER, PHONE_NUMBERS_CTRL_COLUMN_PHONE_NUMBER_TITILE, LVCFMT_LEFT, LIST_CTR_COLUMN_WIDTH);

	//Зареждане на телефонните номера в лист контролата
	if (!LoadPhoneNumbersInListCtrlFromArray())
	{
		return FALSE;
	}

	//Управление на контролети със съобщения за грешки, според инициализираните данни
	ManageErrorMsgControlsInitValues();

	//Сортировка на лист контролата
	if (!SortItemsListCtr())
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::OnDblRButtonListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	//Преглед на селектиран елемент в лест контролата
	ViewPhoneNumberInfo();

	*pResult = 0;
}

void CPersonsDialog::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsDialog::OnKeyDownListCtrl(NMHDR * pNMHDR, LRESULT * pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	//Променлива от тип клас, който управлява елементите в лист контролата
	CListCtrlManager<PHONE_TYPES> oListCtrManager;

	//Инстанция на лист контролата
	CListCtrl& lscPhoneTypes = m_lscPhoneNumbers;

	switch (pLVKeyDow->wVKey)
	{

		//При натискане на бутон Ctrl + I да се добави нов запис
	case 'I':
	{
		InsertPhoneNumber();
		return;
	}
	break;

	//При натискане на бутон Ctrl + F да се търси запис
	case 'F':
	{
		FindPhoneNumber();
		return;
	}
	break;

	//При натискане на бутон Ctrl + R да се презаредят записите
	case 'R':
	{
		ReloadPhoneNumbers();
		return;
	}
	break;
	}

	//Другите опрерации са вързможни само ако има избран елемент
	if (oListCtrManager.GetIndexSelectedItem(lscPhoneTypes) == -1)
	{
		return;
	}

	switch (pLVKeyDow->wVKey)
	{
		//При натискане на бутон Delete да се изтрие записа
	case VK_DELETE:
	{
		DeletePhoneNumber ();
		return;
	}
	break;

	//При натискане на бутона Enter да се изведе в режим преглед записа
	case VK_RETURN:
	{
		ViewPhoneNumberInfo();
		return;
	}
	break;

	//При натискане на Ctrl + U да се редактира селектирания запис
	case 'U':
	{
		UpdatePhoneNumber();
		return;
	}
	break;
	}

	*pResult = 0;
}

void CPersonsDialog::OnContextMenu(CWnd*  pWnd , CPoint point)
{
	//Отваряне на контекстно меню само при натискане в пространството на лист контролата
	if (*pWnd != m_lscPhoneNumbers)
	{
		return;
	}

	//Инстнация на контекстно меню
	CMenu oMenu;
	oMenu.LoadMenu(IDR_CONTEXT_MANU);
	CMenu* pContextMenu = oMenu.GetSubMenu(0);
	if (pContextMenu == nullptr)
	{
		return;
	}

	//Индекс на селектирания запис
	int nSelectedIndex = m_oListCtrlManager.GetIndexSelectedItem(m_lscPhoneNumbers);

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

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPersonsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPersonsDialog::OnBnClickedCancel)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CPersonsDialog::InsertPhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CPersonsDialog::UpdatePhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CPersonsDialog::DeletePhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_FILTER, &CPersonsDialog::FilterPhoneNumbersByType)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CPersonsDialog::FindPhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CPersonsDialog::ReloadPhoneNumbers)
	ON_EN_CHANGE(IDC_EDB_PERSONS_LASTNAME, &CPersonsDialog::OnEnChangeLastname)
	ON_EN_CHANGE(IDC_EDB_PERSONS_FIRTSNAME, &CPersonsDialog::OnEnChangeFirtsname)
	ON_EN_CHANGE(IDC_EDB_PERSONS_SECONDNAME, &CPersonsDialog::OnEnChangeSecondname)
	ON_EN_CHANGE(IDC_EDB_PERSONS_EGN, &CPersonsDialog::OnEnChangeEgn)
	ON_CBN_SELCHANGE(IDC_CMB_PERSONS_CITIES, &CPersonsDialog::OnCbnSelchangeCities)
	ON_EN_CHANGE(IDC_EDB_PERSONS_ADDRESS, &CPersonsDialog::OnEnChangeAddress)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LSC_PHONE_NUMBERS, &CPersonsDialog::OnDeleteItemListCtrl)
	ON_NOTIFY(NM_DBLCLK, IDC_LSC_PHONE_NUMBERS, &CPersonsDialog::OnDblRButtonListCtrl)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LSC_PHONE_NUMBERS, &CPersonsDialog::OnKeyDownListCtrl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSC_PHONE_NUMBERS, &CPersonsDialog::OnChangeItemListCtrl)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

void CPersonsDialog::OnBnClickedOk()
{
	//Превръщаме въведените данни в коректни с валидатора, ако контролата е активна за писане
	if (m_lEnableControlsParam != ENABLE_DIALOG_PERSON_CTR_FLAG_ALL)
	{
		CDialog::OnOK();

	}

	//Проверка за визуализирано съобщение за грешка
	if (!HasErrorMsg())
	{
		ValidateEdbControlsText();

		CDialog::OnOK();
	}
}

void CPersonsDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CPersonsDialog::ViewPhoneNumberInfo()
{
	
	//Достъпваме данните от лист контролата
	PHONE_NUMBERS* pPhoneNumber = m_oListCtrlManager.GetSelectedItem(m_lscPhoneNumbers);

	//Проверка за открит елемент
	if (pPhoneNumber == nullptr)
	{
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPhoneNumbersDialog oDialog(m_oAdditionalModels.GetPhoneTypes(), *pPhoneNumber, ENABLE_DIALOG_PERSON_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPersonsDialog::InsertPhoneNumber()
{
	//Достъпваме диалога
	CPhoneNumbersDialog oDialog(m_oAdditionalModels.GetPhoneTypes());

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_NUMBERS recPhoneNumber;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Вземаме данните от контролите от диалога
	if (!oDialog.GetControlsData(recPhoneNumber))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Добавяме елемента към масива с флаг за добавяне на данни в мапа с телефонни номера
	if (!m_oPhoneNumbersOperationsMap.AddOneElementToDataOperation(recPhoneNumber, OPERATIONS_WITH_DATA_FLAGS_INSERT))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Инстанция на масив, с всички нужни данни на лист контролата, за висчки градове
	CRowDataListCtrl<PHONE_NUMBERS> oRowDataListCtrl;
	oRowDataListCtrl.SetData(recPhoneNumber);
	if (!SetColumnDisplayData(oRowDataListCtrl))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Добавяме нов елемент в лист контролата
	if (!m_oListCtrlManager.AddOrEditElement(m_lscPhoneNumbers, oRowDataListCtrl))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Сортировка на зареденото
	if (!SortItemsListCtr())
	{
		AfxMessageBox(ERROR_MGS_FAIL_SORT_LIST_CTRL);
		return;
	}
}

void CPersonsDialog::UpdatePhoneNumber()
{
	//Достъп до индекса на селектирания запис
	int nIndexItem = m_oListCtrlManager.GetIndexSelectedItem(m_lscPhoneNumbers);

	//Инстанция на обект от тип структура с телефонни номера, със стойности селектирания запис от лист контролата
	PHONE_NUMBERS* pPhoneNumber = m_oListCtrlManager.GetSelectedItem(m_lscPhoneNumbers);

	//Проверка за открит елемент
	if (pPhoneNumber == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Намираме флага под който е записан елемента в мапа с данни
	LPARAM lFlag = m_oPhoneNumbersOperationsMap.FindDataOperationFlagByElement(*pPhoneNumber);
	if (lFlag == -1)
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPhoneNumbersDialog oDialog(m_oAdditionalModels.GetPhoneTypes(), *pPhoneNumber);

	//Проверка за натиснат бутон OK в диалога
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}

	//Инстанция на телефонен номер, който съдържа копие на стойностите от старите данни
	PHONE_NUMBERS recUpdatedPhoneNumber = *pPhoneNumber;

	//Присвояваме ноивте данни от контролите в диалога в променливата копие
	if (!oDialog.GetControlsData(recUpdatedPhoneNumber))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Премахваме стария елемент от мавива с флаг прочетени данни в мапа с телефонни номера
	if (!m_oPhoneNumbersOperationsMap.RemoveElemetFromDataOperation(*pPhoneNumber, lFlag))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Ако тизи елемент е в група за добавяне, да не се проминя флага му
	if (lFlag != OPERATIONS_WITH_DATA_FLAGS_INSERT)
	{
		lFlag = OPERATIONS_WITH_DATA_FLAGS_UPDATE;
	}

	//Добавяме новиея елемент към масива с флаг за редакция на данни в мапа с телефонни номера
	if (!m_oPhoneNumbersOperationsMap.AddOneElementToDataOperation(recUpdatedPhoneNumber, lFlag))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Превръщаме номия телефонен номер в масив със стрингови данни, които ще се презентират в лист контролата
	CRowDataListCtrl<PHONE_NUMBERS> oRowDataListCtrl;
	oRowDataListCtrl.SetData(recUpdatedPhoneNumber);

	if (!SetColumnDisplayData(oRowDataListCtrl))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Редактираме, по открития индекс, с новите данни
	if (!m_oListCtrlManager.AddOrEditElement(m_lscPhoneNumbers, oRowDataListCtrl, nIndexItem))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Сортировка на зареденото
	if (!SortItemsListCtr())
	{
		AfxMessageBox(ERROR_MGS_FAIL_SORT_LIST_CTRL);
		return;
	}
}

void CPersonsDialog::DeletePhoneNumber()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(WARNING_MSG_DELETE_DATA, MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}
	//Достъпваме индекса на селектирания запис
	int nIndexItem = m_oListCtrlManager.GetIndexSelectedItem(m_lscPhoneNumbers);

	//Достъпваме селектирания запис
	PHONE_NUMBERS* pPhoneNumber = m_oListCtrlManager.GetSelectedItem(m_lscPhoneNumbers);

	//Проверка за открит елемент
	if (pPhoneNumber == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_SELECT_ITEM_LIST_CTRL);
		return;
	}

	//Намираме флага под който е записан елемента в мапа с данни
	LPARAM lFlag = m_oPhoneNumbersOperationsMap.FindDataOperationFlagByElement(*pPhoneNumber);
	if (lFlag == -1)
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}

	//Премахваме елеметта от мавива с флаг прочетени данни в мапа с телефонни номера
	if (!m_oPhoneNumbersOperationsMap.RemoveElemetFromDataOperation(*pPhoneNumber, lFlag))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
	}

	//Ако тизи елемент е в група за добавяне, да не се добавя към мапа
	if (lFlag != OPERATIONS_WITH_DATA_FLAGS_INSERT)
	{

		//Добавяме елемента към масива с флаг за изтриване на данни в мапа с гтелефонни номера
		if (!m_oPhoneNumbersOperationsMap.AddOneElementToDataOperation(*pPhoneNumber, OPERATIONS_WITH_DATA_FLAGS_DELETE))
		{
			AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		}
	}

	//Изтриваме ред по поданен индекс
	if (!m_oListCtrlManager.RemoveElement(m_lscPhoneNumbers, nIndexItem))
	{
		AfxMessageBox(ERROR_MSG_FAIL_DO_OPERATION_LIST_CTRL);
		return;
	}
}

void CPersonsDialog::FilterPhoneNumbersByType()
{
	//Достъпваме диалога
	CPhoneNumbersDialog oDialog(m_oAdditionalModels.GetPhoneTypes(), ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_TYPE);

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_NUMBERS recPhoneNumber;

	//При натиснат бутон ОК
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}
	if (!oDialog.GetControlsData(recPhoneNumber))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Променлива, която съдржа открит обект от тип телефон по подадено ид
	PHONE_TYPES* pPhoneType = m_oAdditionalModels.GetPhoneTypeById(recPhoneNumber.lIdPhoneType);

	//Проверка за откритост на тип телефон
	if (pPhoneType == nullptr)
	{
		AfxMessageBox(ERROR_MSG_FAIL_FILTER_LIST_CTRL);
		return;
	}

	//Филтрираме елементите от лист контролата по колона тип телефон
	if (!FilterItemsFromListCtrByCol(pPhoneType->czPhoneType, PHONE_NUMBERS_LIST_CTR_COLUMN_TYPE_PHONE))
	{
		AfxMessageBox(ERROR_MSG_FAIL_FILTER_LIST_CTRL);
		return;
	}
}

void CPersonsDialog::FindPhoneNumber()
{
	//Достъпваме диалога
	CPhoneNumbersDialog oDialog(m_oAdditionalModels.GetPhoneTypes(), ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_NUMBER);

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_NUMBERS recPhoneNumber;

	//При натиснат бутон ОК
	if (oDialog.DoModal() != IDOK)
	{
		return;
	}
	if (!oDialog.GetControlsData(recPhoneNumber))
	{
		AfxMessageBox(ERROR_MSG_FAIL_PROCESS_DATA_DIALOG);
		return;
	}

	//Филтрираме елементите от лист контролата по колона телефонен номер
	if (!FilterItemsFromListCtrByCol(recPhoneNumber.szPhone, PHONE_NUMBERS_LIST_CTR_COLUMN_PHONE_NUMBER))
	{
		AfxMessageBox(ERROR_MSG_FAIL_FIND_LIST_CTRL);
		return;
	}
}

void CPersonsDialog::ReloadPhoneNumbers()
{
	//Зареждане на всички данни
	if (!LoadPhoneNumbersInListCtrlFromArray())
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

void CPersonsDialog::OnEnChangeLastname()
{
	// Времаме данните от котролата
	CString strControlText;
	m_edbLastName.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPerson.szLastName, strControlText);

	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeStringEdbControla(m_edbLastName, strControlText, IDC_STT_PERSONS_LASTNAME_ERROR_MSG);
}

void CPersonsDialog::OnEnChangeFirtsname()
{
	CString strControlText;
	m_edbFirstName.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPerson.szFirstName, strControlText);

	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeStringEdbControla(m_edbFirstName, strControlText, IDC_STT_PERSONS_FIRSTNAME_ERROR_MSG);
}

void CPersonsDialog::OnEnChangeSecondname()
{
	// Времаме данните от котролата
	CString strControlText;
	m_edbSecondName.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPerson.szSecondName, strControlText);

	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeStringEdbControla(m_edbSecondName, strControlText, IDC_STT_PERSONS_SECONDNAME_ERROR_MSG);
}

void CPersonsDialog::OnEnChangeEgn()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbEGN))
	{
		return;
	}

	//Времаме данните от котролата
	CString strControlText;
	m_edbEGN.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPerson.szEGN, strControlText);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(IDC_STT_PERSONS_EGN_ERROR_MSG, strControlText, FALSE, DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_EGN);
}

void CPersonsDialog::OnCbnSelchangeCities()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_cmbCities))
	{
		return;
	}

	int nSelectedIndex = m_cmbCities.GetCurSel();
	int nSelectedData = (long)m_cmbCities.GetItemData(nSelectedIndex);
	m_recPerson.lIdCity = nSelectedData;

	CString strSelectedItem;
	strSelectedItem.Format(_T("%d"), nSelectedData);
	PrintErrorMsg(IDC_STT_PERSONS_CITY_ERROR_MSG, strSelectedItem, NULL);
}

void CPersonsDialog::OnEnChangeAddress()
{
	// Времаме данните от котролата
	CString strControlText;
	m_edbAddress.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPerson.szAddress, strControlText);

	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeStringEdbControla(m_edbAddress, strControlText, IDC_STT_PERSONS_ADDRESS_ERROR_MSG);
}

void CPersonsDialog::DoOnEnChangeStringEdbControla(CWnd& oControla, CString& strText, int nControlaIDWithError)
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(oControla))
	{
		return;
	}

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(nControlaIDWithError, strText);
}

void CPersonsDialog::OnDeleteItemListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strErrorMgs = _T("");
	if (m_lscPhoneNumbers.GetItemCount() <= 1)
	{
		strErrorMgs = _T("Enter phone number!");
	}

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(IDC_STT_PERSONS_PHONE_NUMBERS_ERROR_MSG, strErrorMgs);

	//Правим контролата видима
	GetDlgItem(IDC_STT_PERSONS_PHONE_NUMBERS_ERROR_MSG)->ShowWindow(SW_SHOW);
}

void CPersonsDialog::OnChangeItemListCtrl(NMHDR * pNMHDR, LRESULT * pResult)
{
	CString strErrorMgs = _T("");

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(IDC_STT_PERSONS_PHONE_NUMBERS_ERROR_MSG, strErrorMgs);

	//Правим контролата видима
	GetDlgItem(IDC_STT_PERSONS_PHONE_NUMBERS_ERROR_MSG)->ShowWindow(SW_SHOW);

	*pResult = 0;
}


// Overrides
// ----------------


// Methods
// ---------------

BOOL CPersonsDialog::EnableControls(LPARAM lEnableControls)
{
	//Задаване на всички контроли като неактивни за писане
	if (lEnableControls == ENABLE_DIALOG_PERSON_CTR_FLAG_NONE)
	{
		m_edbFirstName.EnableWindow(FALSE);
		m_edbSecondName.EnableWindow(FALSE);
		m_edbLastName.EnableWindow(FALSE);
		m_edbEGN.EnableWindow(FALSE);
		m_edbAddress.EnableWindow(FALSE);
		m_cmbCities.EnableWindow(FALSE);
		m_lscPhoneNumbers.EnableWindow(FALSE);
	}
	else if(lEnableControls == ENABLE_DIALOG_PERSON_CTR_FLAG_ALL)
	{
		m_edbFirstName.EnableWindow(TRUE);
		m_edbSecondName.EnableWindow(TRUE);
		m_edbLastName.EnableWindow(TRUE);
		m_edbEGN.EnableWindow(TRUE);
		m_edbAddress.EnableWindow(TRUE);
		m_cmbCities.EnableWindow(TRUE);
		m_lscPhoneNumbers.EnableWindow(TRUE);
	}
	return TRUE;
}

BOOL CPersonsDialog::AddItemsInCmbCities()
{
	int nIndexRow = m_cmbCities.AddString(_T("Select city - region..."));
	if (nIndexRow == CB_ERR)
	{
		return FALSE;
	}

	//Добавяне на дата към елемента и го селектираме
	m_cmbCities.SetItemData(nIndexRow, nIndexRow);
	m_cmbCities.SetCurSel(nIndexRow);

	//Променлива с всички градове
	CCitiesArray oCitiesArray = m_oAdditionalModels.GetCities();

	//Обход на масива
	for (INT_PTR nIndex = 0; nIndex < oCitiesArray.GetCount(); nIndex++)
	{
		//Променлива, която съдържа настоящия град от масива
		CITIES* pCities = oCitiesArray.GetAt(nIndex);

		//Проверка за открит елемент
		if (pCities == nullptr)
		{
			return FALSE;
		}

		//Променлива, която ще съдържа визуалните данни за комбо бокса с градове
		CString strTextToAdd;
		strTextToAdd.Format(_T("%s - %s"), pCities->szRegion, pCities->szCityName);

		//Добавяне на елемент и сответно ид за data към комбо бокса с градове
		int nIndexRow = m_cmbCities.AddString(strTextToAdd);
		if (nIndexRow == CB_ERR)
		{
			return FALSE;
		}

		//Задаване дата на текущия елемент, ако в данните на клиента за град е същия го селектираме
		m_cmbCities.SetItemData(nIndexRow, pCities->lId);

		if (pCities->lId == m_recPerson.lIdCity)
		{
			m_cmbCities.SetCurSel(nIndexRow);
		}
	}
	return TRUE;
}

BOOL CPersonsDialog::LoadPhoneNumbersInListCtrlFromArray()
{
	//Достъпваме масива с всички неизтрити телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!m_oPhoneNumbersOperationsMap.GetOnlyActiveValuesFromAllKeysInArray(oPhoneNumbersArray))
	{
		return FALSE;
	}

	//Масив с презентационни данни на всички елементи
	CTypedPtrDataArray<CRowDataListCtrl<PHONE_NUMBERS>> oRowsDataListCtrlArray;

	//Запълваме масив с всички презентационни данни на всички елементи
	if (!SetColumnDisplayDataArray(oPhoneNumbersArray, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!m_oListCtrlManager.LoadDataFromResource(m_lscPhoneNumbers, oRowsDataListCtrlArray))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDialog::FilterItemsFromListCtrByCol(const CString& strDataToFind, LPARAM lColName)
{
	//Проверка дали всички данни от документа са налични
	if (!IsAllPhoneNumbersLoadFromArray())
	{
		if (!LoadPhoneNumbersInListCtrlFromArray())
		{
			return FALSE;
		}
	}

	int nListCrtCountItems = m_lscPhoneNumbers.GetItemCount();

	//Премахва всички елементи, които не са с елемент, като подадения
	for (int nIndex = nListCrtCountItems - 1; nIndex >= 0; --nIndex)
	{
		//Проверка на тип телефон ако е подаден
		CString strDataToCompare = m_lscPhoneNumbers.GetItemText(nIndex, (int)lColName);

		if (_tcscmp(strDataToCompare, strDataToFind) == 0)
		{
			continue;
		}

		if (!m_lscPhoneNumbers.DeleteItem(nIndex))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CPersonsDialog::IsAllPhoneNumbersLoadFromArray()
{
	//Променилава масив, която съдържа всички неизтрити телефонни номера за клиент
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!m_oPhoneNumbersOperationsMap.GetOnlyActiveValuesFromAllKeysInArray(oPhoneNumbersArray))
	{
		return FALSE;
	}

	//Проверка дали размера на записите в лест контролата отговарят на масива с всички телефонни номера за клиент
	if (m_oListCtrlManager.IsAllDataLoadFromResourse(m_lscPhoneNumbers, oPhoneNumbersArray.GetCount()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDialog::SortItemsListCtr()
{
	//Изпълняваме метод за сортиране по азбучен ред
	m_lscPhoneNumbers.SortItems(CompareFunc, (LPARAM)this);

	return TRUE;
}

int CALLBACK CPersonsDialog::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	//Инстанция на диалога, с която ще достъпваме нестатични член променливи
	CPersonsDialog* pDialog = (CPersonsDialog*)lParamSort;
	if (pDialog == nullptr)
	{
		return 0;
	}

	// Достъпваме указателите от подадените параметри
	PHONE_NUMBERS* pPhoneNumber1 = (PHONE_NUMBERS*)lParam1;
	PHONE_NUMBERS* pPhoneNumber2 = (PHONE_NUMBERS*)lParam2;

	//Проверяваме дали указателите не са нулеви
	if (pPhoneNumber1 == nullptr || pPhoneNumber2 == nullptr) 
	{
		return 0;
	}
	
	//Провенливи, които съдържат типа телефонен номер
	PHONE_TYPES* pPhoneType1 = pDialog->m_oAdditionalModels.GetPhoneTypeById(pPhoneNumber1->lIdPhoneType);
	PHONE_TYPES* pPhoneType2 = pDialog->m_oAdditionalModels.GetPhoneTypeById(pPhoneNumber2->lIdPhoneType);

	//Проверка за открити телефонни типове
	if (pPhoneType1 == nullptr || pPhoneType2 == nullptr)
	{
		return 0;
	}

	//Сравнение на двата типа телефонни номера
	int nResult = _tcscmp(pPhoneType1->czPhoneType, pPhoneType2->czPhoneType);

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPersonsDialog::SetColumnDisplayData(CRowDataListCtrl<PHONE_NUMBERS>& oRowDataListCtrl)
{
	const PHONE_NUMBERS& recPhoneNumberData = oRowDataListCtrl.GetData();

	//Променлива, която съдржа открит обект от тип телефон по подадено ид
	PHONE_TYPES* pPhoneType = m_oAdditionalModels.GetPhoneTypeById(recPhoneNumberData.lIdPhoneType);

	//Проверка за откритост
	if (pPhoneType == nullptr)
	{
		return FALSE;
	}

	//Добавяме типа телефонен номер към масива с данни за визуализация
	if (oRowDataListCtrl.AddElementToDisplayData(pPhoneType->czPhoneType) == -1)
	{
		return FALSE;
	}

	//Добавяме телефонен номер към масива с данни за визуализация
	if (oRowDataListCtrl.AddElementToDisplayData(recPhoneNumberData.szPhone) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDialog::SetColumnDisplayDataArray(const CPhoneNumbersArray& oPhoneNumbersArray, CTypedPtrDataArray<CRowDataListCtrl<PHONE_NUMBERS>>& oRowDataListCtrla)
{
	//Преминаваме през висчки елементи на масива с данни за телефонни номера
	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		//Достъпваме елемента, който ще се извежда в лист контролата
		PHONE_NUMBERS* recPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);

		//Проверка за откритост
		if (recPhoneNumber == nullptr)
		{
			return FALSE;
		}

		//Инстанцираме масив, който ще съдържа визуалните данни на текущия елемента
		CRowDataListCtrl<PHONE_NUMBERS> strArrayOneElement;
		strArrayOneElement.SetData(*recPhoneNumber);
		if (!SetColumnDisplayData(strArrayOneElement))
		{
			return FALSE;
		}

		//Добавяме масива с презентационни данни съм масива с всички данни на всички елементи
		if (oRowDataListCtrla.AddElement(strArrayOneElement) == -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CPersonsDialog::GetControlsData(CPersonDBModel& oPersonDBModel)
{
	//Добавяме клиента и телефонните му номера към класа с цялата информация
	oPersonDBModel.AddPerson(m_recPerson);
	if (oPersonDBModel.AddAllPhoneNumbers(m_oPhoneNumbersOperationsMap) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::ManageErrorMsgControlsInitValues()
{
	//Проверка дали са били поданени стойности за всяка контрола
	if (_tcscmp(_T(""),m_recPerson.szFirstName) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_FIRSTNAME_ERROR_MSG, _T(""));
	}

	if (_tcscmp(_T(""), m_recPerson.szSecondName) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_SECONDNAME_ERROR_MSG, _T(""));
	}
	
	if (_tcscmp(_T(""), m_recPerson.szLastName) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_LASTNAME_ERROR_MSG, _T(""));
	}
	
	if (_tcscmp(_T(""), m_recPerson.szEGN) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_EGN_ERROR_MSG, _T(""));
	}
	
	if (_tcscmp(_T(""), m_recPerson.szAddress) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_ADDRESS_ERROR_MSG, _T(""));
	}

	int nIndexSel = m_cmbCities.GetCurSel();
	if (m_cmbCities.GetItemData(nIndexSel) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_CITY_ERROR_MSG, _T(""));
	}

	if (m_lscPhoneNumbers.GetItemCount() != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSONS_PHONE_NUMBERS_ERROR_MSG, _T(""));
	}
}

BOOL CPersonsDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::PrintErrorMsg(int nControlaID, const CString& strControlaTextToCheck, BOOL bValidateString, const int& nMaxValidLenght)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidFormat(strControlaTextToCheck, bValidateString, nMaxValidLenght);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}

BOOL CPersonsDialog::HasErrorMsg()
{
	bool bFlagFoundError = false;
	if (HasErrorInOneControla(IDC_STT_PERSONS_FIRSTNAME_ERROR_MSG))
	{
		bFlagFoundError = true;
	}

	if (HasErrorInOneControla(IDC_STT_PERSONS_SECONDNAME_ERROR_MSG))
	{
		bFlagFoundError = true;
	}

	if (HasErrorInOneControla(IDC_STT_PERSONS_LASTNAME_ERROR_MSG))
	{
		bFlagFoundError = true;
	}
	
	if (HasErrorInOneControla(IDC_STT_PERSONS_EGN_ERROR_MSG))
	{
		bFlagFoundError = true;
	}
	
	if (HasErrorInOneControla(IDC_STT_PERSONS_ADDRESS_ERROR_MSG))
	{
		bFlagFoundError = true;
	}

	if (HasErrorInOneControla(IDC_STT_PERSONS_CITY_ERROR_MSG))
	{
		bFlagFoundError = true;
	}

	if (HasErrorInOneControla(IDC_STT_PERSONS_PHONE_NUMBERS_ERROR_MSG))
	{
		bFlagFoundError = true;
	}

	return bFlagFoundError;
}

BOOL CPersonsDialog::HasErrorInOneControla(const int& nControlaErrorMsgID)
{
	CString strControlaErrorMsg;

	//Визуализация на контролите, съдържащи грешки, само ако са активни, като се присвоява съобещението от променливите
	GetDlgItem(nControlaErrorMsgID)->ShowWindow(SW_SHOW);
	GetDlgItemText(nControlaErrorMsgID, strControlaErrorMsg);

	if (strControlaErrorMsg.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::ValidateEdbControlsText()
{
	CString strEnteredData;

	strEnteredData = m_recPerson.szFirstName;
	m_oValidateStringData.ValidateDataUpperLetter(strEnteredData);
	_tcscpy_s(m_recPerson.szFirstName, strEnteredData);

	strEnteredData = m_recPerson.szSecondName;
	m_oValidateStringData.ValidateDataUpperLetter(strEnteredData);
	_tcscpy_s(m_recPerson.szSecondName, strEnteredData);

	strEnteredData = m_recPerson.szLastName;
	m_oValidateStringData.ValidateDataUpperLetter(strEnteredData);
	_tcscpy_s(m_recPerson.szLastName, strEnteredData);

	strEnteredData = m_recPerson.szAddress;
	m_oValidateStringData.ValidateDataUpperLetter(strEnteredData);
	_tcscpy_s(m_recPerson.szAddress, strEnteredData);
}