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

CPersonsDialog::CPersonsDialog(const CAdditionPersonInfo& oAdditionInfo, LPARAM lEnableControls /*= ENABLE_DIALOG_PHERSON_CTR_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_oAdditionalInfo(oAdditionInfo), m_oEnableControlsParam(lEnableControls)
{
	//Инициализираме всички член променливи
	m_strFirstName = "";
	m_strSecondName = "";
	m_strLastName = "";
	m_strEGN = "";
	m_lIdCity = -1;
	m_strAddress = "";
}

CPersonsDialog::CPersonsDialog(CPersonInfo& oPersonInfo, const CAdditionPersonInfo& oAdditionInfo, LPARAM lEnableControls /*= ENABLE_DIALOG_PHERSON_CTR_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_oPhoneNumbersMap(oPersonInfo.GetPhoneNumbers()), m_oAdditionalInfo(oAdditionInfo), m_oEnableControlsParam(lEnableControls)
{
	//Подаваме всички данни за клиент към член променливите, които съхраняват съответните данни
	PERSONS recPerson = oPersonInfo.GetPerson();
	m_strFirstName = recPerson.szFirstName;
	m_strSecondName = recPerson.szSecondName;
	m_strLastName = recPerson.szLastName;
	m_strEGN = recPerson.szEGN;
	m_lIdCity = recPerson.lIdCity;
	m_strAddress = recPerson.szAddress;
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
	m_edbFirstName.SetWindowTextW(m_strFirstName);
	m_edbSecondName.SetWindowTextW(m_strSecondName);
	m_edbLastName.SetWindowTextW(m_strLastName);
	m_edbEGN.SetWindowTextW(m_strEGN);
	m_edbAddress.SetWindowTextW(m_strAddress);

	//Запълваме комбо бокса с градове
	if (!AddItemsInCmbCities())
	{
		return FALSE;
	}

	//Задаваме селектирания елемент да е подадения от структурата с клиента
	for (int nIndex = 0; nIndex < m_cmbCities.GetCount(); nIndex++)
	{
		if (m_cmbCities.GetItemData(nIndex) == m_lIdCity)
		{
			m_cmbCities.SetCurSel(nIndex);
		}
	}

	//Промяна на активността на контролите, според подадения параметър
	if (!EnableControls(m_oEnableControlsParam))
	{
		return FALSE;
	}

	//Добавяне на допълнителни стилове за лист контролата
	m_lscPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	//Добавяме колони в лист контролата с ляво подравяване и размер на полето
	m_lscPhoneNumbers.InsertColumn(PHONE_NUMBERS_LIST_CTR_COLUMN_TYPE_PHONE, _T("Type phone"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);
	m_lscPhoneNumbers.InsertColumn(PHONE_NUMBERS_LIST_CTR_COLUMN_PHONE_NUMBER, _T("Phone number"), LVCFMT_LEFT, LIST_CTR_HEADER_WIDTH);

	//Зареждане на телефонните номера в лист контролата
	if (!LoadPhoneNumbersInListCtrlFromArray())
	{
		return FALSE;
	}

	//Сортировка на лист контролата
	if (!SortItemsListCtr())
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Проверка дали се намираме в лест контролата
	CWnd* pWnd = ChildWindowFromPoint(point);

	if (pWnd != nullptr && *pWnd  == m_lscPhoneNumbers)
	{
		//Извършване на операция селект
		ViewPhoneNumberInfo();
	}

	CPersonsDialog::OnLButtonDblClk(nFlags, point);

}

void CPersonsDialog::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//Отваряне на контекстно меню
	ClientToScreen(&point);
	OnContextMenu(this, point);
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
	int nSelectedIndex = m_oListCtrlManager.GetIndexSelectedItemListCtrl(m_lscPhoneNumbers);

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
	ON_COMMAND(ID_CONTEXT_MENU_DATA_INSERT, &CPersonsDialog::InsertPhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_UPDATE, &CPersonsDialog::UpdatePhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_DELETE, &CPersonsDialog::DeletePhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_FILTER, &CPersonsDialog::FilterPhoneNumbersByType)
	ON_COMMAND(ID_CONTEXT_MANU_DATA_FIND, &CPersonsDialog::FindPhoneNumber)
	ON_COMMAND(ID_CONTEXT_MENU_DATA_RELOAD, &CPersonsDialog::ReloadPhoneNumbers)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

void CPersonsDialog::OnBnClickedOk()
{
	m_edbFirstName.GetWindowTextW(m_strFirstName);
	m_edbSecondName.GetWindowTextW(m_strSecondName);
	m_edbLastName.GetWindowTextW(m_strLastName);
	m_edbEGN.GetWindowTextW(m_strEGN);
	m_edbAddress.GetWindowTextW(m_strAddress);	
	int nSelectedIndex = m_cmbCities.GetCurSel();
	m_lIdCity = (long)m_cmbCities.GetItemData(nSelectedIndex);

	CDialog::OnOK();
}

void CPersonsDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CPersonsDialog::ViewPhoneNumberInfo()
{
	
	//Достъпваме данните от лист контролата
	PHONE_NUMBERS* pPhoneNumber = m_oListCtrlManager.GetSelectedItemListCtrl(m_lscPhoneNumbers);

	//Проверка за открит елемент
	if (pPhoneNumber == nullptr)
	{
		AfxMessageBox(_T("Failed to select phone number from list!\n Try to reload."));
		return;
	}

	//Достъпваме диалога и задаваме стойности на контролите му, както и че искаме контролите му да са неактивни за модификация
	CPhoneNumbersDialog oDialog(m_oAdditionalInfo.GetAllPhoneTypes(), *pPhoneNumber, ENABLE_DIALOG_PERSON_CTR_FLAG_NONE);

	//Визуализираме диалога
	oDialog.DoModal();
}

void CPersonsDialog::InsertPhoneNumber()
{
	//Достъпваме диалога
	CPhoneNumbersDialog oDialog(m_oAdditionalInfo.GetAllPhoneTypes());

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_NUMBERS recPhoneNumber;

	//При натиснат бутон ОК в диалога
	if (oDialog.DoModal() == IDOK)
	{
		//Вземаме данните от контролите от диалога
		if (!oDialog.GetControlsData(recPhoneNumber))
		{
			AfxMessageBox(_T("Failed to presess data from dialog!\n Try to reload."));
			return;
		}

		//Добавяме елемента към масива с флаг за добавяне на данни в мапа с телефонни номера
		if (!m_oPhoneNumbersMap.AddOneElementToKey(recPhoneNumber, OPERATIONS_WITH_DATA_FLAGS_INSERT))
		{
			AfxMessageBox(_T("Failed to add phone number to list!\n Try to reload."));
			return;
		}


		//Превръщаме телефиния номер в масив със стрингови данни, които ще се презентират в лист контролата
		CTableDataArray<CString> strPhoneNumbersInfoArrayToDisplayInListCtrl;
		if (!ConvertElementPhoneNumberToArrayWithDisplayData(recPhoneNumber, strPhoneNumbersInfoArrayToDisplayInListCtrl))
		{
			AfxMessageBox(_T("Failed to process data of new element in list!\n Try to reload."));
			return;
		}

		//Добавяме нов елемент в лист контролата
		if (!m_oListCtrlManager.ManageAddOrEditElementListCtr(m_lscPhoneNumbers, recPhoneNumber, strPhoneNumbersInfoArrayToDisplayInListCtrl))
		{
			AfxMessageBox(_T("Failed to add new element in list!\n Try to reload."));
			return;
		}
	}
}

void CPersonsDialog::UpdatePhoneNumber()
{
	//Достъп до индекса на селектирания запис
	int nIndexItem = m_oListCtrlManager.GetIndexSelectedItemListCtrl(m_lscPhoneNumbers);

	//Инстанция на обект от тип структура с телефонни номера, със стойности селектирания запис от лист контролата
	PHONE_NUMBERS* pPhoneNumber = m_oListCtrlManager.GetSelectedItemListCtrl(m_lscPhoneNumbers);

	//Проверка за открит елемент
	if (pPhoneNumber == nullptr)
	{
		AfxMessageBox(_T("Failed to select phone numebr from list!\n Try to reload."));
		return;
	}

	//Намираме флага под който е записан елемента в мапа с данни
	LPARAM lFlag = m_oPhoneNumbersMap.FindKeyByValue(*pPhoneNumber);
	if (lFlag == -1)
	{
		AfxMessageBox(_T("Failed to update phone number to list!\n Try to reload."));
		return;
	}

	//Задаваме стойности на контролите в диалога да са тези от селектирания запис
	CPhoneNumbersDialog oDialog(m_oAdditionalInfo.GetAllPhoneTypes(), *pPhoneNumber);

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
		AfxMessageBox(_T("Failed to presess data from dialog!\n Try to reload."));
		return;
	}

	//Премахваме стария елемент от мавива с флаг прочетени данни в мапа с телефонни номера
	if (!m_oPhoneNumbersMap.RemoveElemetFromKey(*pPhoneNumber, lFlag))
	{
		AfxMessageBox(_T("Failed to update phone number to list!\n Try to reload."));
		return;
	}

	//Ако тизи елемент е в група за добавяне, да не се проминя флага му
	if (lFlag != OPERATIONS_WITH_DATA_FLAGS_INSERT)
	{
		lFlag = OPERATIONS_WITH_DATA_FLAGS_UPDATE;
	}

	//Добавяме новиея елемент към масива с флаг за редакция на данни в мапа с телефонни номера
	if (!m_oPhoneNumbersMap.AddOneElementToKey(recUpdatedPhoneNumber, lFlag))
	{
		AfxMessageBox(_T("Failed to update phone number to list!\n Try to reload."));
		return;
	}

	//Превръщаме номия телефонен номер в масив със стрингови данни, които ще се презентират в лист контролата
	CTableDataArray<CString> strPhoneNumberToDisplayInListCtrl;
	if (!ConvertElementPhoneNumberToArrayWithDisplayData(recUpdatedPhoneNumber, strPhoneNumberToDisplayInListCtrl))
	{
		AfxMessageBox(_T("Failed to process data of new element in list!\n Try to reload."));
		return;
	}

	//Редактираме, по открития индекс, с новите данни
	if (!m_oListCtrlManager.ManageAddOrEditElementListCtr(m_lscPhoneNumbers, recUpdatedPhoneNumber, strPhoneNumberToDisplayInListCtrl, nIndexItem))
	{
		AfxMessageBox(_T("Failed to update element in list!\n Try to reload."));
		return;
	}
}

void CPersonsDialog::DeletePhoneNumber()
{
	//Допълнително потвърждение за изтриване
	int nResult = AfxMessageBox(_T("Are you sure you want to delete data?"), MB_YESNO | MB_ICONQUESTION);

	//При натискане на бутон за отказ излизаме от метода и пректратяваме операцията
	if (nResult == IDNO)
	{
		return;
	}
	//Достъпваме индекса на селектирания запис
	int nIndexItem = m_oListCtrlManager.GetIndexSelectedItemListCtrl(m_lscPhoneNumbers);

	//Достъпваме селектирания запис
	PHONE_NUMBERS* pPhoneNumber = m_oListCtrlManager.GetSelectedItemListCtrl(m_lscPhoneNumbers);

	//Проверка за открит елемент
	if (pPhoneNumber == nullptr)
	{
		AfxMessageBox(_T("Failed to select phone number from list!\n Try to reload."));
		return;
	}

	//Намираме флага под който е записан елемента в мапа с данни
	LPARAM lFlag = m_oPhoneNumbersMap.FindKeyByValue(*pPhoneNumber);
	if (lFlag == -1)
	{
		AfxMessageBox(_T("Failed to update phone number to list!\n Try to reload."));
		return;
	}

	//Премахваме елеметта от мавива с флаг прочетени данни в мапа с телефонни номера
	if (!m_oPhoneNumbersMap.RemoveElemetFromKey(*pPhoneNumber, lFlag))
	{
		AfxMessageBox(_T("Failed to delete phone number to list!\n Try to reload."));
	}

	//Ако тизи елемент е в група за добавяне, да не се добавя към мапа
	if (lFlag != OPERATIONS_WITH_DATA_FLAGS_INSERT)
	{

		//Добавяме елемента към масива с флаг за изтриване на данни в мапа с гтелефонни номера
		if (!m_oPhoneNumbersMap.AddOneElementToKey(*pPhoneNumber, OPERATIONS_WITH_DATA_FLAGS_DELETE))
		{
			AfxMessageBox(_T("Failed to delete phone number to list!\n Try to reload."));
		}
	}

	//Изтриваме ред по поданен индекс
	if (!m_oListCtrlManager.DeleteElementListCtr(m_lscPhoneNumbers, nIndexItem))
	{
		AfxMessageBox(_T("Failed to delete element in list!\n Try to reload."));
		return;
	}

}

void CPersonsDialog::FilterPhoneNumbersByType()
{
	//Достъпваме диалога
	CPhoneNumbersDialog oDialog(m_oAdditionalInfo.GetAllPhoneTypes(), ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_TYPE);

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_NUMBERS recPhoneNumber;

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{
		if (!oDialog.GetControlsData(recPhoneNumber))
		{
			AfxMessageBox(_T("Failed to presess data from dialog!\n Try to reload."));
			return;
		}

		//Променлива, която съдржа открит обект от тип телефон по подадено ид
		PHONE_TYPES* pPhoneType = m_oAdditionalInfo.FindPhoneTypesInArrayById(recPhoneNumber.lIdPhoneType);

		//Проверка за откритост на тип телефон
		if (pPhoneType == nullptr)
		{
			AfxMessageBox(_T("Failed to filter elements by type in list!\n Try to reload."));
			return ;
		}

		//Филтрираме елементите от лист контролата по колона тип телефон
		if (!FilterItemsFromListCtrByCol(pPhoneType->czPhoneType, PHONE_NUMBERS_LIST_CTR_COLUMN_TYPE_PHONE))
		{
			AfxMessageBox(_T("Failed to filter elements by type in list!\n Try to reload."));
			return;
		}
	}

	//Филтрираме зареденото
	SortItemsListCtr();
}

void CPersonsDialog::FindPhoneNumber()
{
	//Достъпваме диалога
	CPhoneNumbersDialog oDialog(m_oAdditionalInfo.GetAllPhoneTypes(),ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_NUMBER);

	//Нова структура, която ще съдържа данни за новия запис
	PHONE_NUMBERS recPhoneNumber;

	//При натиснат бутон ОК
	if (oDialog.DoModal() == IDOK)
	{
		if (!oDialog.GetControlsData(recPhoneNumber))
		{
			AfxMessageBox(_T("Failed to presess data from dialog!\n Try to reload."));
			return;
		}

		//Филтрираме елементите от лист контролата по колона телефонен номер
		if (!FilterItemsFromListCtrByCol(recPhoneNumber.szPhone, PHONE_NUMBERS_LIST_CTR_COLUMN_PHONE_NUMBER))
		{
			return;
		}
	}
}

void CPersonsDialog::ReloadPhoneNumbers()
{
	//Зареждане на всички данни
	if (!LoadPhoneNumbersInListCtrlFromArray())
	{
		AfxMessageBox(_T("Failed to reload data in list!\n Try to reload."));
		return;
	}

	//Сортировка на зареденото
	SortItemsListCtr();
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
		//menu
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
	//Променлива с всички градове
	CCitiesArray oCitiesArray = m_oAdditionalInfo.GetAllCities();

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

		m_cmbCities.SetItemData(nIndexRow, pCities->lId);
	}

	return TRUE;
}

BOOL CPersonsDialog::LoadPhoneNumbersInListCtrlFromArray()
{
	//Достъпваме масива с всички неизтрити телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!m_oPhoneNumbersMap.GetOnlyActiveValuesFromAllKeysInArray(oPhoneNumbersArray))
	{
		return FALSE;
	}

	//Масив с презентационни данни на всички елементи
	CTableDataArray<CTableDataArray<CString>> strPhoneNumbersArrayToDisplayInListCtrl;

	//Запълваме масив с всички презентационни данни на всички елементи
	if (!ConvertAllElementsPhoneNumbersToArrayWithDisplayData(oPhoneNumbersArray, strPhoneNumbersArrayToDisplayInListCtrl))
	{
		return FALSE;
	}

	//Зареждаме данните от масива в лист контролата
	if (!m_oListCtrlManager.LoadDataInListCtrFromResourse(m_lscPhoneNumbers, oPhoneNumbersArray, strPhoneNumbersArrayToDisplayInListCtrl))
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

		if (strDataToCompare == strDataToFind)
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
	if (!m_oPhoneNumbersMap.GetOnlyActiveValuesFromAllKeysInArray(oPhoneNumbersArray))
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
	m_lscPhoneNumbers.SortItems(CompareFunc, 0);

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
	PHONE_TYPES* pPhoneType1 = pDialog->m_oAdditionalInfo.FindPhoneTypesInArrayById(pPhoneNumber1->lIdPhoneType);
	PHONE_TYPES* pPhoneType2 = pDialog->m_oAdditionalInfo.FindPhoneTypesInArrayById(pPhoneNumber2->lIdPhoneType);

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

BOOL CPersonsDialog::ConvertElementPhoneNumberToArrayWithDisplayData(const PHONE_NUMBERS& recPhoneNumbers, CTableDataArray<CString>& strPhoneNumbersArray)
{
	//Променлива, която съдржа открит обект от тип телефон по подадено ид
	PHONE_TYPES* pPhoneType = m_oAdditionalInfo.FindPhoneTypesInArrayById(recPhoneNumbers.lIdPhoneType);

	//Проверка за откритост
	if (pPhoneType == nullptr)
	{
		return FALSE;
	}

	//Добавяме типа телефонен номер към масива с данни за визуализация
	if (strPhoneNumbersArray.AddElement(pPhoneType->czPhoneType) == -1)
	{
		return FALSE;
	}

	//Добавяме телефонен номер към масива с данни за визуализация
	if (strPhoneNumbersArray.AddElement(recPhoneNumbers.szPhone) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDialog::ConvertAllElementsPhoneNumbersToArrayWithDisplayData(const CPhoneNumbersArray& oPhoneNumbersArray, CTableDataArray<CTableDataArray<CString>>& strPhoneNumbersArrayToDisplayInListCtrl)
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
		CTableDataArray<CString> strArrayOneElement;
		if (!ConvertElementPhoneNumberToArrayWithDisplayData(*recPhoneNumber, strArrayOneElement))
		{
			return FALSE;
		}

		//Добавяме масива с презентационни данни съм масива с всички данни на всички елементи
		if (strPhoneNumbersArrayToDisplayInListCtrl.AddElement(strArrayOneElement) == -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CPersonsDialog::GetControlsData(CPersonInfo& oPersonInfo)
{
	//Инстанция на обект от тип клиент с всички данни
	PERSONS recPerson;
	_tcscpy_s(recPerson.szFirstName, m_strFirstName);
	_tcscpy_s(recPerson.szSecondName, m_strSecondName);
	_tcscpy_s(recPerson.szLastName, m_strLastName);
	_tcscpy_s(recPerson.szEGN, m_strEGN);
	_tcscpy_s(recPerson.szAddress, m_strAddress);
	recPerson.lIdCity = m_lIdCity;

	//Добавяме клиента и телефонните му номера към класа с цялата информация
	oPersonInfo.AddPerson(recPerson);
	if (oPersonInfo.AddAllPhoneNumbers(m_oPhoneNumbersMap) == -1)
	{
		return FALSE;
	}

	return TRUE;
}