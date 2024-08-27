// PhoneTypes.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "PersonTypesDialog.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonTypesDialog 

IMPLEMENT_DYNAMIC(CPersonTypesDialog, CDialog)

// Constructor / Destructor
// ----------------

CPersonTypesDialog::CPersonTypesDialog(LPARAM lEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSON_TYPES, pParent), m_lEnableControlsParam(lEnableControls)
{
}

CPersonTypesDialog::CPersonTypesDialog(const PERSON_TYPES& recPersonTypes, LPARAM lEnableControls /*= ENABLE_DIALOG_CTR_FLAG_ALL*/, CWnd* pParent /*= nullptr*/)
	: CDialog(IDD_PERSON_TYPES, pParent), m_recPersonType(recPersonTypes), m_lEnableControlsParam(lEnableControls)
{
}

CPersonTypesDialog::~CPersonTypesDialog()
{
}

BOOL CPersonTypesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbPersonType.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	//Задаване на стойности за контролите
	m_edbPersonType.SetWindowTextW(m_recPersonType.czPersonType);

	//Проверка дали са били поданени стойности
	if (_tcscmp(_T(""), m_recPersonType.czPersonType) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PERSON_TYPES_ERROR_MSG, _T(""));
	}

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_lEnableControlsParam);

	return TRUE;
}

void CPersonTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSON_TYPES, m_edbPersonType);
}


BEGIN_MESSAGE_MAP(CPersonTypesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPersonTypesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPersonTypesDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDB_PERSON_TYPES, &CPersonTypesDialog::OnEnChangeEdbPersonTypes)
END_MESSAGE_MAP()

void CPersonTypesDialog::OnBnClickedOk()
{
	//Проверка за визуализирано съобщение за грешка
	if (!HasErrorMsg())
	{
		//Превръщаме въведените данни в коректни с валидатора, ако контролата е активна за писане
		if (m_edbPersonType.IsWindowEnabled())
		{
			CString strEnteredPersonType = m_recPersonType.czPersonType;
			m_oValidateStringData.ValidateDataUpperLetter(strEnteredPersonType);
			_tcscpy_s(m_recPersonType.czPersonType, strEnteredPersonType);
		}

		CDialog::OnOK();
	}
}

void CPersonTypesDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


// Overrides
// ----------------


// Methods
// ---------------

void CPersonTypesDialog::EnableControls(LPARAM oEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (oEnableControls)
	{
	case ENABLE_DIALOG_CITIES_CTR_FLAG_ALL:
	{
		m_edbPersonType.EnableWindow(TRUE);
	}
	break;

	case ENABLE_DIALOG_CITIES_CTR_FLAG_NONE:
	{
		m_edbPersonType.EnableWindow(FALSE);
	}
	break;
	}
}

BOOL CPersonTypesDialog::GetControlsData(PERSON_TYPES& recPersonType)
{
	recPersonType = m_recPersonType;
	return TRUE;
}

void CPersonTypesDialog::OnEnChangeEdbPersonTypes()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbPersonType))
	{
		return;
	}

	//Времаме данните от котролата
	CString strControlText;
	m_edbPersonType.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPersonType.czPersonType, strControlText);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(m_recPersonType.czPersonType, IDC_STT_PERSON_TYPES_ERROR_MSG);
}

BOOL CPersonTypesDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonTypesDialog::PrintErrorMsg(const CString& strText, int nControlaID)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidFormat(strText);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}

BOOL CPersonTypesDialog::HasErrorMsg()
{
	//Стренгови променливи, които съдържат празни низове(липса на открита грешка)
	CString strPersonType;

	//Визуализация на контролите, съдържащи грешки, само ако са активни, като се присвоява съобещението от променливите
	if (m_edbPersonType.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_PERSON_TYPES_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_PERSON_TYPES_ERROR_MSG, strPersonType);
	}

	//Проверка за празни контроли, съдържащи грешки
	if (strPersonType.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;

}
