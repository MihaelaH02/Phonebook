#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "CitiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog 

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

// Constructor / Destructor
// ----------------
CCitiesDialog::CCitiesDialog(LPARAM lEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent), m_lEnableControlsParam(lEnableControls)
{
}

CCitiesDialog::CCitiesDialog(const CITIES& recCity, LPARAM lEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent), m_recCity(recCity), m_lEnableControlsParam(lEnableControls)
{
}

CCitiesDialog::~CCitiesDialog()
{
}


// MFC Overrides
// ----------------

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbName);
	DDX_Control(pDX, IDC_EDB_CITIES_REGION, m_edbRegion);
}

BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbName.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);
	m_edbRegion.SetLimitText(DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	//Задаване на стойности за контролите
	m_edbName.SetWindowTextW(m_recCity.szCityName);
	m_edbRegion.SetWindowTextW(m_recCity.szRegion);

	//Проверка дали са поданени стойности за текстовите променливи
	if (_tcscmp(_T(""), m_recCity.szCityName) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, _T(""));
	}

	//Проверка дали са поданени стойности за текстовите променливи
	if (_tcscmp(_T(""), m_recCity.szRegion) != 0)
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_CITIES_REGION_ERROR_MSG, _T(""));
	}

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_lEnableControlsParam);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCitiesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDB_CITIES_NAME, &CCitiesDialog::OnEnChangeName)
	ON_EN_CHANGE(IDC_EDB_CITIES_REGION, &CCitiesDialog::OnEnChangeRegion)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

void CCitiesDialog::OnBnClickedOk()
{
	//Проверка за визуализирано съобщение за грешка
	if (!HasErrorMsg())
	{
		//Превръщаме въведените данни в коректни с валидатора, ако контролата е активна за писане
		if (m_edbName.IsWindowEnabled())
		{
			CString strEnteredCityName = m_recCity.szCityName;
			m_oValidateStringData.ValidateDataUpperLetter(strEnteredCityName);
			_tcscpy_s(m_recCity.szCityName, strEnteredCityName);
		}

		if (m_edbRegion.IsWindowEnabled())
		{
			CString strEnteredCityRegion = m_recCity.szRegion;
			m_oValidateStringData.ValidateDataUpperLetter(strEnteredCityRegion);
			_tcscpy_s(m_recCity.szRegion, strEnteredCityRegion);
		}

		CDialog::OnOK();
	}
}

void CCitiesDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


// Overrides
// ----------------


// Methods
// ---------------

void CCitiesDialog::EnableControls(LPARAM lEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (lEnableControls)
	{
		case ENABLE_DIALOG_CITIES_CTR_FLAG_ALL:
		{
			m_edbName.EnableWindow(TRUE);
			m_edbRegion.EnableWindow(TRUE);
		}
		break;

		case ENABLE_DIALOG_CITIES_CTR_FLAG_NONE:
		{
			m_edbName.EnableWindow(FALSE);
			m_edbRegion.EnableWindow(FALSE);
		}
		break;

		case ENABLE_DIALOG_CITIES_CTR_FLAG_ONLY_NAME:
		{
			m_edbName.EnableWindow(TRUE);
			m_edbRegion.EnableWindow(FALSE);
		}
		break;

		case ENABLE_DIALOG_CITIES_CTR_FLAG_ONLY_REGION:
		{
			m_edbName.EnableWindow(FALSE);
			m_edbRegion.EnableWindow(TRUE);
		}
	}
}

void CCitiesDialog::OnEnChangeName()
{
	//Времаме данните от котролата
	CString strControlText;
	m_edbName.GetWindowTextW(strControlText);
	_tcscpy_s(m_recCity.szCityName, strControlText);

	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeEdbControla(m_edbName, strControlText, IDC_STT_CITIES_NAME_ERROR_MSG);
}

void CCitiesDialog::OnEnChangeRegion()
{
	//Времаме данните от котролата
	CString strControlText;
	m_edbRegion.GetWindowTextW(strControlText);
	_tcscpy_s(m_recCity.szRegion, strControlText);

	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeEdbControla(m_edbRegion, strControlText, IDC_STT_CITIES_REGION_ERROR_MSG);
}

void CCitiesDialog::DoOnEnChangeEdbControla(CWnd& oControla, CString& strText, int nControlaIDWithError)
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(oControla))
	{
		return;
	}

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(strText, nControlaIDWithError);
}

BOOL CCitiesDialog::GetControlsData(CITIES& recCity)
{
	recCity = m_recCity;

	return TRUE;
}

BOOL CCitiesDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CCitiesDialog::PrintErrorMsg(const CString& strText, int nControlaID)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidFormat(strText);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}

BOOL CCitiesDialog::HasErrorMsg()
{
	//Стренгови променливи, които съдържат празни низове(липса на открита грешка)
	CString strName, strRegion;

	//Визуализация на контролите, съдържащи грешки, само ако са активни, като се присвоява съобещението от променливите
	if (m_edbName.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_CITIES_NAME_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, strName);
	}

	if (m_edbRegion.IsWindowEnabled())
	{
		GetDlgItem(IDC_STT_CITIES_REGION_ERROR_MSG)->ShowWindow(SW_SHOW);
		GetDlgItemText(IDC_STT_CITIES_REGION_ERROR_MSG, strRegion);
	}

	//Проверка за празни контроли, съдържащи грешки
	if (strName.IsEmpty() && strRegion.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;

}