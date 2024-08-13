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

CPhoneTypesDialog::CPhoneTypesDialog(LPARAM lEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PHONE_TYPES_DIALOG, pParent), m_lEnableControlsParam(lEnableControls)
{
}

CPhoneTypesDialog::CPhoneTypesDialog(const PHONE_TYPES& recPhoneTypes, LPARAM lEnableControls /*= ENABLE_DIALOG_CTR_FLAG_ALL*/, CWnd* pParent /*= nullptr*/)
	: CDialog(IDD_PHONE_TYPES_DIALOG, pParent), m_recPhoneType(recPhoneTypes), m_lEnableControlsParam(lEnableControls)
{
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
	m_edbPhoneType.SetWindowTextW(m_recPhoneType.czPhoneType);

	//Проверка дали са били поданени стойности
	if (_tcscmp(_T(""), m_recPhoneType.czPhoneType) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PHONE_TYPES_ERROR_MSG, _T(""));
	}

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_lEnableControlsParam);

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
	ON_EN_CHANGE(IDC_EDB_PHONE_TYPES, &CPhoneTypesDialog::OnEnChangeEdbPhoneTypes)
ON_EN_CHANGE(IDC_EDB_PHONE_TYPES, &CPhoneTypesDialog::OnEnChangeEdbPhoneTypes)
END_MESSAGE_MAP()

void CPhoneTypesDialog::OnBnClickedOk()
{
	//Проверка за визуализирано съобщение за грешка
	if (!HasErrorMsg())
	{
		//Превръщаме въведените данни в коректни с валидатора, ако контролата е активна за писане
		if (m_edbPhoneType.IsWindowEnabled())
		{
			CString strEnteredPhoneType = m_recPhoneType.czPhoneType;
			m_oValidateStringData.ValidateDataUpperLetter(strEnteredPhoneType);
			_tcscpy_s(m_recPhoneType.czPhoneType, strEnteredPhoneType);
		}

		CDialog::OnOK();
	}
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

BOOL CPhoneTypesDialog::GetControlsData(PHONE_TYPES& recPhoneType)
{
	recPhoneType = m_recPhoneType;
	return TRUE;
}

void CPhoneTypesDialog::OnEnChangeEdbPhoneTypes()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbPhoneType))
	{
		return;
	}

	//Времаме данните от котролата
	CString strControlText;
	m_edbPhoneType.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPhoneType.czPhoneType, strControlText);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(m_recPhoneType.czPhoneType, IDC_STT_PHONE_TYPES_ERROR_MSG);
}

BOOL CPhoneTypesDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CPhoneTypesDialog::PrintErrorMsg(const CString& strText, int nControlaID)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidFormat(strText, FALSE);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}

BOOL CPhoneTypesDialog::HasErrorMsg()
{
	//Стренгови променливи, които съдържат празни низове(липса на открита грешка)
	CString strPhoneType;

	//Визуализация на контролите, съдържащи грешки, само ако са активни, като се присвоява съобещението от променливите
	if (m_edbPhoneType.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_PHONE_TYPES_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_PHONE_TYPES_ERROR_MSG, strPhoneType);
	}

	//Проверка за празни контроли, съдържащи грешки
	if (strPhoneType.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;

}