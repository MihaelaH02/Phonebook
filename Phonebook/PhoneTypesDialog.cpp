// PhoneTypes.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "PhoneTypesDialog.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDialog 

IMPLEMENT_DYNAMIC(CPhoneTypesDialog, CDialog)

// Constructor / Destructor
// ----------------

CPhoneTypesDialog::CPhoneTypesDialog(LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_TYPES_DIALOG, pParent)
{
	m_strPhoneType = "";
	m_oEnableControlsParam = oEnableControls;
}

CPhoneTypesDialog::CPhoneTypesDialog(const PHONE_TYPES& recPhoneTypes, LPARAM oEnableControls /*= ENABLE_DIALOG_CTR_FLAG_ALL*/, CWnd* pParent /*= nullptr*/)
	: CDialog(IDD_PHONE_TYPES_DIALOG, pParent)
{
	m_strPhoneType = recPhoneTypes.czPhoneType;
	m_oEnableControlsParam = oEnableControls;
}


CPhoneTypesDialog::~CPhoneTypesDialog()
{
}

BOOL CPhoneTypesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbPhoneType.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	//Задаване на стойности за контролите
	m_edbPhoneType.SetWindowTextW(m_strPhoneType);

	//Проверка дали са поданени стойности за текстовите променливи
	/*if (!m_strName.IsEmpty())
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки
		SetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, _T(""));
	}*/

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_oEnableControlsParam);

	return TRUE;
}

void CPhoneTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPES, m_edbPhoneType);
}


BEGIN_MESSAGE_MAP(CPhoneTypesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneTypesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPhoneTypesDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

void CPhoneTypesDialog::OnBnClickedOk()
{
	//Проверка за визуализирано съобщение за грешка
	/*if (!HasErrorMsg())
	{
		//Превръщаме въведените данни в коректни с валидатора, ако контролата е активна за писане
		if (m_edbName.IsWindowEnabled())
		{
			m_oValidateStringData.ValidateDataUpperLetter(m_strName);
		}

		if (m_edbRegion.IsWindowEnabled())
		{
			m_oValidateStringData.ValidateDataUpperLetter(m_strRegion);
		}*/
	m_edbPhoneType.GetWindowTextW(m_strPhoneType);

	CDialog::OnOK();
}

void CPhoneTypesDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


// Overrides
// ----------------


// Methods
// ---------------

void CPhoneTypesDialog::EnableControls(LPARAM oEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (oEnableControls)
	{
	case ENABLE_DIALOG_CITIES_CTR_FLAG_ALL:
	{
		m_edbPhoneType.EnableWindow(TRUE);
	}
	break;

	case ENABLE_DIALOG_CITIES_CTR_FLAG_NONE:
	{
		m_edbPhoneType.EnableWindow(FALSE);
	}
	break;
	}
}

BOOL CPhoneTypesDialog::GetControlsData(PHONE_TYPES& recPhoneTypes)
{
	//Задаване на нова структура, която съдържа данните от конторлите
	_tcscpy_s(recPhoneTypes.czPhoneType, m_strPhoneType);

	return TRUE;
}



