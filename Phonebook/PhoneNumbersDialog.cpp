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
CPhoneNumbersDialog::CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, LPARAM lEnableControls /*= ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL*/,CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_PHONE_NUMBERS, pParent), m_oPhoneTypesArray(oPhoneTypesArray), m_lEnableControlsParam(lEnableControls)
{
}

CPhoneNumbersDialog::CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, const PHONE_NUMBERS& recPhoneNumber, LPARAM lEnableControls /*= ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_PHONE_NUMBERS, pParent), m_recPhoneNumber(recPhoneNumber), m_oPhoneTypesArray(oPhoneTypesArray), m_lEnableControlsParam(lEnableControls)
{
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
	ON_EN_CHANGE(IDC_EDB_PHONE_NUMBER_NUMBER, &CPhoneNumbersDialog::OnEnChangePhoneNumber)
	ON_CBN_SELCHANGE(IDC_CMB_PHONE_NUMBER_TYPE, &CPhoneNumbersDialog::OnChangeSelPhoneType)
END_MESSAGE_MAP()


BOOL CPhoneNumbersDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbPhoneNumber.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_PHONE_NUMBER);

	//Задаване на стойности за контролите
	m_edbPhoneNumber.SetWindowTextW(m_recPhoneNumber.szPhone);

	//Запълваме комбо бокса с градове
	if (!AddItemsInCmbPhoneNumber())
	{
		return FALSE;
	}

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_lEnableControlsParam);

	ManageErrorMsgControlsInitValues();

	return TRUE;
}


// MFC Message Handlers
// ----------------

void CPhoneNumbersDialog::OnBnClickedOk()
{
	//Проверка за визуализирано съобщение за грешка
	if (!HasErrorMsg())
	{
		CDialog::OnOK();
	}
}

void CPhoneNumbersDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CPhoneNumbersDialog::OnChangeSelPhoneType()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_cmbPhoneType))
	{
		return;
	}

	int nSelectedIndex = m_cmbPhoneType.GetCurSel();
	int nSelectedData = (long)m_cmbPhoneType.GetItemData(nSelectedIndex);
	m_recPhoneNumber.lIdPhoneType = nSelectedData;

	CString strSelectedItem;
	strSelectedItem.Format(_T("%d"), nSelectedData);
	PrintErrorMsg(IDC_STT_PHONE_NUMBERS_TYPE_ERROR_MSG, strSelectedItem);
}

void CPhoneNumbersDialog::OnEnChangePhoneNumber()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbPhoneNumber))
	{
		return;
	}

	//Времаме данните от котролата
	CString strControlText;
	m_edbPhoneNumber.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPhoneNumber.szPhone, strControlText);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(IDC_STT_PHONE_NUMBERS_NUMBER_ERROR_MSG, strControlText);
}


// Overrides
// ----------------


// Methods
// ---------------

void CPhoneNumbersDialog::EnableControls(LPARAM lEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (lEnableControls)
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
	recPhoneNumber = m_recPhoneNumber;

	return TRUE;
}

BOOL CPhoneNumbersDialog::AddItemsInCmbPhoneNumber()
{
	int nIndexRow = m_cmbPhoneType.AddString(_T("Select phone type..."));
	if (nIndexRow == CB_ERR)
	{
		return FALSE;
	}

	//Задаване на дата да елемент и го селектира
	m_cmbPhoneType.SetItemData(nIndexRow, nIndexRow);
	m_cmbPhoneType.SetCurSel(nIndexRow);

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

		//Задаване на дата за елементи и ако подадения тип телефон отговаря на текущия го селектира
		m_cmbPhoneType.SetItemData(nIndexRow, pPhoneType->lId);
		if (pPhoneType->lId == m_recPhoneNumber.lIdPhoneType)
		{
			m_cmbPhoneType.SetCurSel(nIndexRow);
		}
	}

	/*if (!SortItemsInCmbCities())
	{
		return FALSE;
	}*/

	return TRUE;
}



BOOL CPhoneNumbersDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CPhoneNumbersDialog::PrintErrorMsg(int nControlaID, const CString& strErrorMsg)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidFormat(strErrorMsg, FALSE, DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_PHONE_NUMBER);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}

BOOL CPhoneNumbersDialog::HasErrorMsg()
{
	//Стрингови променливи, които съдържат празни низове(липса на открита грешка)
	CString strPhoneNumberError, strPhoneTypeError;

	//Визуализация на контролите, съдържащи грешки, само ако са активни, като се присвоява съобещението от променливите
	if (m_edbPhoneNumber.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_PHONE_NUMBERS_NUMBER_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_PHONE_NUMBERS_NUMBER_ERROR_MSG, strPhoneNumberError);
	}

	if (m_cmbPhoneType.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_PHONE_NUMBERS_TYPE_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_PHONE_NUMBERS_TYPE_ERROR_MSG, strPhoneTypeError);
	}

	//Проверка за празни контроли, съдържащи грешки
	if (strPhoneTypeError.IsEmpty() || strPhoneTypeError.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;

}

void CPhoneNumbersDialog::ManageErrorMsgControlsInitValues()
{
	//Проверка дали са били поданени стойности
	if (_tcscmp(_T(""), m_recPhoneNumber.szPhone) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PHONE_NUMBERS_NUMBER_ERROR_MSG, _T(""));
	}

	//Проверка дали са били поданени стойности
	int nIndexSelect = m_cmbPhoneType.GetCurSel();
	if (m_cmbPhoneType.GetItemData(nIndexSelect) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PHONE_NUMBERS_TYPE_ERROR_MSG, _T(""));
	}
}