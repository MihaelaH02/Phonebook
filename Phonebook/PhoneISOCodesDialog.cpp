// PhoneISOCodesDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "PhoneISOCodesDialog.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneISOCodesDialog 

IMPLEMENT_DYNAMIC(CPhoneISOCodesDialog, CDialogEx)


// Constructor / Destructor
// ----------------

CPhoneISOCodesDialog::CPhoneISOCodesDialog(LPARAM lEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ISO_CODES, pParent), m_lEnableControlsParam(lEnableControls)
{
}

CPhoneISOCodesDialog::CPhoneISOCodesDialog(const PHONE_ISO_CODES& recPhoneISOCode, LPARAM lEnableControls /*= ENABLE_DIALOG_CTR_FLAG_ALL*/, CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_ISO_CODES, pParent), m_recPhoneISOCodes(recPhoneISOCode), m_lEnableControlsParam(lEnableControls)
{
}

CPhoneISOCodesDialog::~CPhoneISOCodesDialog()
{
}

BOOL CPhoneISOCodesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbPhoneISOCodes.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_ISO_CODE);

	//Задаване на стойности за контролите
	m_edbPhoneISOCodes.SetWindowTextW(m_recPhoneISOCodes.czPhoneISOCode);

	//Проверка дали са били поданени стойности
	if (_tcscmp(_T(""), m_recPhoneISOCodes.czPhoneISOCode) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_PHONE_ISO_CODES_ERROR_MSG, _T(""));
	}

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_lEnableControlsParam);

	return TRUE;
}

void CPhoneISOCodesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_ISO_CODE, m_edbPhoneISOCodes);
}


BEGIN_MESSAGE_MAP(CPhoneISOCodesDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDB_PHONE_ISO_CODE, &CPhoneISOCodesDialog::OnEnChangePhoneISOCode)
	ON_BN_CLICKED(IDOK, &CPhoneISOCodesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPhoneISOCodesDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

void CPhoneISOCodesDialog::OnBnClickedOk()
{
	//Проверка за визуализирано съобщение за грешка
	if (!HasErrorMsg())
	{
		//Превръщаме въведените данни в коректни с валидатора, ако контролата е активна за писане
		if (m_edbPhoneISOCodes.IsWindowEnabled())
		{
			CString strEnteredPhoneType = m_recPhoneISOCodes.czPhoneISOCode;
			m_oValidateStringData.ValidateDataUpperLetter(strEnteredPhoneType);
			_tcscpy_s(m_recPhoneISOCodes.czPhoneISOCode, strEnteredPhoneType);
		}

		CDialog::OnOK();
	}
}

void CPhoneISOCodesDialog::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


// Overrides
// ----------------


// Methods
// ---------------

void CPhoneISOCodesDialog::EnableControls(LPARAM oEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (oEnableControls)
	{
	case ENABLE_DIALOG_CITIES_CTR_FLAG_ALL:
	{
		m_edbPhoneISOCodes.EnableWindow(TRUE);
	}
	break;

	case ENABLE_DIALOG_CITIES_CTR_FLAG_NONE:
	{
		m_edbPhoneISOCodes.EnableWindow(FALSE);
	}
	break;
	}
}

BOOL CPhoneISOCodesDialog::GetControlsData(PHONE_ISO_CODES& recPhoneISOCode)
{
	recPhoneISOCode = m_recPhoneISOCodes;
	return TRUE;
}

void CPhoneISOCodesDialog::OnEnChangePhoneISOCode()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbPhoneISOCodes))
	{
		return;
	}

	//Времаме данните от котролата
	CString strControlText;
	m_edbPhoneISOCodes.GetWindowTextW(strControlText);
	_tcscpy_s(m_recPhoneISOCodes.czPhoneISOCode, strControlText);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(m_recPhoneISOCodes.czPhoneISOCode, IDC_STT_PHONE_ISO_CODES_ERROR_MSG);
}

BOOL CPhoneISOCodesDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CPhoneISOCodesDialog::PrintErrorMsg(const CString& strText, int nControlaID)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidFormat(strText);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}

BOOL CPhoneISOCodesDialog::HasErrorMsg()
{
	//Стренгови променливи, които съдържат празни низове(липса на открита грешка)
	CString strPhoneISOCode;

	//Визуализация на контролите, съдържащи грешки, само ако са активни, като се присвоява съобещението от променливите
	if (m_edbPhoneISOCodes.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_PHONE_ISO_CODES_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_PHONE_ISO_CODES_ERROR_MSG, strPhoneISOCode);
	}

	//Проверка за празни контроли, съдържащи грешки
	if (strPhoneISOCode.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;

}