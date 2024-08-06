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

CPersonsDialog::CPersonsDialog(const CAdditionInfo& oAdditionInfo, LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_oAdditionalInfo(oAdditionInfo)
{
	//Инициализираме всички член променливи
	m_strFirstName = "";
	m_strSecondName = "";
	m_strLastName = "";
	m_strEGN = "";
	m_lIdCity = -1;
	m_strAddress = "";
}

CPersonsDialog::CPersonsDialog(const CPersonInfo& oPersonInfo, const CAdditionInfo& oAdditionInfo, LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONS_DIALOG, pParent), m_oPhoneNumbersMap(oPersonInfo.GetPhoneNumbers()), m_oAdditionalInfo(oAdditionInfo)
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
	if (AddItemsInCmbCities())
	{
		return FALSE;
	}

	//Задаваме селектирания елемент да подадения от структурата с клиента
	int nIndexCity = m_cmbCities.GetItemData(m_lIdCity);
	m_cmbCities.SetCurSel(nIndexCity);

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

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPersonsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPersonsDialog::OnBnClickedCancel)
END_MESSAGE_MAP()



// MFC Message Handlers
// ----------------

void CPersonsDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CPersonsDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}



// Overrides
// ----------------


// Methods
// ---------------

BOOL CPersonsDialog::EnableControls(LPARAM oEnableControls)
{
	//Задаване на всички контроли като неактивни за писане
	if(ENABLE_DIALOG_CTR_FLAG_NONE)
	{
		if (!m_edbFirstName.EnableWindow(FALSE))
		{
			return FALSE;
		}

		if(!m_edbSecondName.EnableWindow(FALSE))
		{
			return FALSE;
		}

		if(!m_edbLastName.EnableWindow(FALSE))
		{
			return FALSE;
		}

		if(!m_edbEGN.EnableWindow(FALSE))
		{
			return FALSE;
		}

		if(!m_edbAddress.EnableWindow(FALSE))
		{
			return FALSE;
		}

		if(!m_cmbCities.EnableWindow(FALSE))
		{
			return FALSE;
		}

		if(!m_lscPhoneNumbers.EnableWindow(FALSE))
		{
			return FALSE;
		}
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
		strTextToAdd.Format(_T("%s - %s"), pCities->szCityName, pCities->szRegion);

		//Добавяне на елемент и сответно ид за data към комбо бокса с градове
		int nIndexRow = m_cmbCities.AddString(strTextToAdd);
		m_cmbCities.SetItemData(nIndexRow, pCities->lId);
	}
	return TRUE;
}

BOOL CPersonsDialog::LoadPhoneNumbersInListCtrlFromArray()
{
	//Достъпваме масива с телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!m_oPhoneNumbersMap.GetAllValuesInArray(oPhoneNumbersArray))
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

BOOL CPersonsDialog::FilterItemsFromListCtr(const PHONE_NUMBERS& recCity)
{
	//Проверка дали всички данни от документа са налични
	if (!IsAllPhoneNumbersLoadFromArray())
	{
		if (!LoadPhoneNumbersInListCtrlFromArray())
		{
			return FALSE;
		}
	}
	/*

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
	}*/

	return TRUE;
}

BOOL CPersonsDialog::IsAllPhoneNumbersLoadFromArray()
{
	//Променилава масив, която съдържа всички телефонни номера за клиент
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!m_oPhoneNumbersMap.GetAllValuesInArray(oPhoneNumbersArray))
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

