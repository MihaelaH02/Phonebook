// PersonsDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsDialog.h"


/////////////////////////////////////////////////////////////////////////////
// PersonsDialog.cpp 

IMPLEMENT_DYNAMIC(CPersonsDialog, CDialogEx)


// Constructor / Destructor
// ----------------

CPersonsDialog::CPersonsDialog(LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DIALOG, pParent)
{
	SecureZeroMemory(this, sizeof(*this));
}

CPersonsDialog::CPersonsDialog(const CPersonInfo& oPersonInfo, const CAdditionInfo& oAdditionInfo, LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DIALOG, pParent), m_oPhoneNumbersMap(oPersonInfo.GetPhoneNumbers()), m_oAdditionalInfo(oAdditionInfo)
{
	//Подаваме всички данни за клиент към член променливите, които съхраняват съответните данни
	PERSONS recPerson = oPersonInfo.GetPerson();
	m_strFirstName = recPerson.szFirstName;
	m_strSecondName = recPerson.szSecondName;
	m_strLastName = recPerson.szLastName;
	m_strEGN = recPerson.szEGN;
	m_lIdCity = recPerson.lIdCity;
	m_strAddress = recPerson.szAddress;

	//Подаваме данни към масивите, съхраняващи съответните данни
	//m_oPhoneNumbersMap.AddAllElements(oPersonInfo.GetPhoneNumbers());
	//m_oCitiesArray.AddAllElements(oAdditionInfo.GetAllCities());
	//m_oPhoneTypesArray.AddAllElements(oAdditionInfo.GetAllPhoneTypes());
}

CPersonsDialog::~CPersonsDialog()
{
}

// MFC Overrides
// ----------------

void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRTSNAME, m_edbFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_SECONDNAME, m_edbSecondName);
	DDX_Control(pDX, IDC_EDB_PERSONS_LASTNAME, m_edbLastName);
	DDX_Control(pDX, IDC_EDB_PERSONS_EGN, m_edbEGN);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITIES, m_cmbCities);
	DDX_Control(pDX, IDC_REC_PERSONS_ADDRESS, m_recAddress);
	DDX_Control(pDX, IDC_LSC_PHONE_NUMBERS, m_lscPhoneNumbers);
}

BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbFirstName.SetLimitText(DIALOG_CTR_INFO_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbSecondName.SetLimitText(DIALOG_CTR_INFO_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbLastName.SetLimitText(DIALOG_CTR_INFO_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	//m_recAddress
	m_edbEGN.SetLimitText(DIALOG_CTR_INFO_TEXT_BOX_MAX_LENGTH_ENTERED_EGN);

	//Задаване на стойности за контролите
	m_edbFirstName.SetWindowTextW(m_strFirstName);
	m_edbSecondName.SetWindowTextW(m_strSecondName);
	m_edbLastName.SetWindowTextW(m_strLastName);
	m_edbEGN.SetWindowTextW(m_strEGN);
	m_recAddress.SetWindowTextW(m_strAddress);

	if (AddItemsInCmbCities())
	{
		return FALSE;
	}

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

	//Зареждане на телефонните номера от масива
	if (!LoadPhoneNumbersInListCtrlFromArray())
	{
		return FALSE;
	}

	//Сортировка
	if (!SortItemsListCtr())
	{
		return FALSE;
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PHONE_NUMBERS_ADD, &CPersonsDialog::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BTN_PHONE_NUMBERS_EDIT, &CPersonsDialog::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_BTN_PHONE_NUMBERS_DELETE, &CPersonsDialog::OnBnClickedDelete)
	ON_BN_CLICKED(IDOK, &CPersonsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPersonsDialog::OnBnClickedCancel)
END_MESSAGE_MAP()



// MFC Message Handlers
// ----------------

void CPersonsDialog::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
}


void CPersonsDialog::OnBnClickedEdit()
{
	// TODO: Add your control notification handler code here
}


void CPersonsDialog::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
}


void CPersonsDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CPersonsDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



// Overrides
// ----------------


// Methods
// ---------------

BOOL CPersonsDialog::EnableControls(LPARAM oEnableControls)
{
	if(ENABLE_DIALOG_CTR_FLAG_NONE)
	{
		m_edbFirstName.EnableWindow(FALSE);
		m_edbSecondName.EnableWindow(FALSE);
		m_edbLastName.EnableWindow(FALSE);
		m_edbEGN.EnableWindow(FALSE);
		m_recAddress.EnableWindow(FALSE);
		m_cmbCities.EnableWindow(FALSE);
		m_lscPhoneNumbers.EnableWindow(FALSE);
	}

	return TRUE;
}

BOOL CPersonsDialog::AddItemsInCmbCities()
{
	CCitiesArray oCitiesArray = m_oAdditionalInfo.GetAllCities();
	for (INT_PTR nIndex = 0; nIndex < oCitiesArray.GetCount(); nIndex++)
	{
		CITIES* pCities = oCitiesArray.GetAt(nIndex);

		if (pCities == nullptr)
		{
			return FALSE;
		}
		CString strTextToAdd;
		strTextToAdd.Format(_T("%s - %s"), pCities->szCityName, pCities->szRegion);

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

	//Запълваме масив с всички презентационни данни на всички елементи
	CTableDataArray<CTableDataArray<CString>> strPhoneNumbersArrayToDisplayInListCtrl;

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
	//Достъпваме масива с телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!m_oPhoneNumbersMap.GetAllValuesInArray(oPhoneNumbersArray))
	{
		return FALSE;
	}

	//Проверка дали размера на записите в лест контролата отговаря на масива с всички телефонни номера
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
	// Достъпваме указателите от подадените параметри
	PHONE_NUMBERS* pPhoneNumber1 = (PHONE_NUMBERS*)lParam1;
	PHONE_NUMBERS* pPhoneNumber2 = (PHONE_NUMBERS*)lParam2;

	//Проверяваме дали укацателите не са нулеви
	if (pPhoneNumber1 == nullptr || pPhoneNumber2 == nullptr) {
		return 0;
	}

	// Първо сравняваме регионите 
	//инстанция на масив с типове телефони
	//намери типа по ид на днете/сравни
	int nResult = 0;// = _tcscmp(pCity1->szRegion, pCity2->szRegion);

	//Връщаме резултата от сравнението
	return nResult;
}

BOOL CPersonsDialog::ConvertElementPhoneNumberToArrayWithDisplayData(const PHONE_NUMBERS& recPhoneNumbers, CTableDataArray<CString>& strPhoneNumbersArray)
{
	//Добавяме първи елемент, който ще се презентира
	//инстанция на масив с всички телефонни номера
	//намери по ид
	//m_oAdditionalInfo.FindPhoneTypesInArrayById();
	/*if (strPhoneNumbersArray.AddElement(recPhoneNumbers.lIdPhoneType) == -1)
	{
		return FALSE;
	}*/

	//Добавяме втори елемент, който ще се презентира
	/*if (strPhoneNumbersArray.AddElement(recPhoneNumbers.szPhone) == -1)
	{
		return FALSE;
	}*/

	return TRUE;
}

BOOL CPersonsDialog::ConvertAllElementsPhoneNumbersToArrayWithDisplayData(const CPhoneNumbersArray& oPhoneNumbersArray, CTableDataArray<CTableDataArray<CString>>& strPhoneNumbersArrayToDisplayInListCtrl)
{
	//Преминаваме през висчки елементи на масива с данни за градове
	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		//Достъпваме елемента, който ще се извежда в лист контролата
		PHONE_NUMBERS* recPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);
		if (recPhoneNumber == nullptr)
		{
			return FALSE;
		}

		//Инициализираме масив, който ще съдържа данните от елемента, който ще се презентира
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
	PERSONS recPerson;
	_tcscpy_s(recPerson.szFirstName, m_strFirstName);
	_tcscpy_s(recPerson.szSecondName, m_strSecondName);
	_tcscpy_s(recPerson.szLastName, m_strLastName);
	_tcscpy_s(recPerson.szEGN, m_strEGN);
	_tcscpy_s(recPerson.szAddress, m_strAddress);
	recPerson.lIdCity = m_lIdCity;

	oPersonInfo.AddPerson(recPerson);
	oPersonInfo.AddAllPhoneNumbers(m_oPhoneNumbersMap);
	return TRUE;
}

