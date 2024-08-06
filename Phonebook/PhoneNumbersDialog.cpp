// PhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "PhoneNumbersDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog 

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)


// Constructor / Destructor
// ----------------
CPhoneNumbersDialog::CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, LPARAM oEnableControls /*= ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL*/,CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_PHONE_NUMBERS, pParent), m_oPhoneTypesArray(oPhoneTypesArray)
{
	m_strPhoneNumber = "";
	m_lPhoneType = -1;
	m_oEnableControlsParam = oEnableControls;
}

CPhoneNumbersDialog::CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, const PHONE_NUMBERS& recPhoneNumber, LPARAM oEnableControls /*= ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_PHONE_NUMBERS, pParent), m_oPhoneTypesArray(oPhoneTypesArray)
{
	//Подаване на параметри
	m_strPhoneNumber = recPhoneNumber.szPhone;
	m_lPhoneType = recPhoneNumber.lIdPhoneType;
	m_oEnableControlsParam = oEnableControls;
}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}


// MFC Overrides
// ----------------

void CPhoneNumbersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBER_NUMBER, m_edbPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_NUMBER_TYPE, m_cmbPhoneType);
}


BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneNumbersDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPhoneNumbersDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CPhoneNumbersDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbPhoneNumber.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	//Задаване на стойности за контролите
	m_edbPhoneNumber.SetWindowTextW(m_strPhoneNumber);

	//Запълваме комбо бокса с градове
	if (!AddItemsInCmbPhoneNumber())
	{
		return FALSE;
	}

	//Задаваме селектирания елемент да подадения от структурата с клиента
	for (int nIndex = 0; nIndex < m_cmbPhoneType.GetCount(); nIndex++)
	{
		if (m_cmbPhoneType.GetItemData(nIndex) == m_lPhoneType)
		{
			m_cmbPhoneType.SetCurSel(nIndex);
		}
	}
	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_oEnableControlsParam);

	return TRUE;
}


// MFC Message Handlers
// ----------------

void CPhoneNumbersDialog::OnBnClickedOk()
{
	m_edbPhoneNumber.GetWindowTextW(m_strPhoneNumber);
	int nSelectedIndex = m_cmbPhoneType.GetCurSel();
	m_lPhoneType =(long)m_cmbPhoneType.GetItemData(nSelectedIndex);
	CDialog::OnOK();
}

void CPhoneNumbersDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


// Overrides
// ----------------


// Methods
// ---------------

void CPhoneNumbersDialog::EnableControls(LPARAM oEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (oEnableControls)
	{
	case ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL:
	{
		m_edbPhoneNumber.EnableWindow(TRUE);
		m_cmbPhoneType.EnableWindow(TRUE);
	}
	break;

	case ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_NONE:
	{
		m_edbPhoneNumber.EnableWindow(FALSE);
		m_cmbPhoneType.EnableWindow(FALSE);
	}
	break;

	case ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_NUMBER:
	{
		m_edbPhoneNumber.EnableWindow(TRUE);
		m_cmbPhoneType.EnableWindow(FALSE);
	}
	break;

	case ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_TYPE:
	{
		m_edbPhoneNumber.EnableWindow(FALSE);
		m_cmbPhoneType.EnableWindow(TRUE);
	}
	}
}

BOOL CPhoneNumbersDialog::GetControlsData(PHONE_NUMBERS& recPhoneNumber)
{
	//Задаване на нова структура, която съдържа данните от конторлите
	_tcscpy_s(recPhoneNumber.szPhone, m_strPhoneNumber);
	recPhoneNumber.lIdPhoneType = m_lPhoneType;

	return TRUE;
}

BOOL CPhoneNumbersDialog::AddItemsInCmbPhoneNumber()
{
	//Обход на масива
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetCount(); nIndex++)
	{
		//Променлива, която съдържа настоящия тип телефон от масива
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nIndex);

		//Проверка за открит елемент
		if (pPhoneType == nullptr)
		{
			return FALSE;
		}

		//Променлива, която ще съдържа визуалните данни за комбо бокса с типове телефони
		CString strTextToAdd = pPhoneType->czPhoneType;

		//Добавяне на елемент и сответно ид за data към комбо бокса с типове телефони
		int nIndexRow = m_cmbPhoneType.AddString(strTextToAdd);
		if (nIndexRow == CB_ERR)
		{
			return FALSE;
		}

		m_cmbPhoneType.SetItemData(nIndexRow, pPhoneType->lId);
	}

	/*if (!SortItemsInCmbCities())
	{
		return FALSE;
	}*/

	return TRUE;
}