#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "CitiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog 

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

// Constructor / Destructor
// ----------------
CCitiesDialog::CCitiesDialog(LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	m_strName = "";
	m_strRegion = "";
	m_oEnableControlsParam = oEnableControls;
}

CCitiesDialog::CCitiesDialog(const CITIES& recCity, LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	//Подаване на параметри
	m_strName = recCity.szCityName;
	m_strRegion = recCity.szRegion;
	m_oEnableControlsParam = oEnableControls;
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
	m_edbName.SetWindowTextW(m_strName);
	m_edbRegion.SetWindowTextW(m_strRegion);

	//Проверка дали са поданени стойности за текстовите променливи
	if (!m_strName.IsEmpty() && !m_strRegion.IsEmpty())
	{
		//Задаване на начална празна стойност на контролите за съобщения за грешки  
		SetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, _T(""));
		SetDlgItemText(IDC_STT_CITIES_REGION_ERROR_MSG, _T(""));
	}

	//Промяна на активността на контролите, според подадения параметър
	EnableControls(m_oEnableControlsParam);

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
			m_oValidateStringData.ValidateDataUpperLetter(m_strName);
		}

		if (m_edbRegion.IsWindowEnabled())
		{
			m_oValidateStringData.ValidateDataUpperLetter(m_strRegion);
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

void CCitiesDialog::EnableControls(LPARAM oEnableControls)
{
	//В зависимост от поданета стойност от тип енъм, се активират/деактивират контролите за писане
	switch (oEnableControls)
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
	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeEdbControla(m_edbName, m_strName, IDC_STT_CITIES_NAME_ERROR_MSG);
}

void CCitiesDialog::OnEnChangeRegion()
{
	//Извърване на необходими действия свързани със засичане на грешка
	DoOnEnChangeEdbControla(m_edbRegion, m_strRegion, IDC_STT_CITIES_REGION_ERROR_MSG);
}

void CCitiesDialog::DoOnEnChangeEdbControla(CWnd& oControla, CString& strText, int nControlaIDWithErroe)
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(oControla))
	{
		return;
	}

	//Времаме данните от котролата
	oControla.GetWindowTextW(strText);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(strText, nControlaIDWithErroe);
}

CITIES& CCitiesDialog::GetControlsData()
{
	//Задаване на нова структура, която съдържа данните от конторлите
	CITIES recCity;
	_tcscpy_s(recCity.szCityName, m_strName);
	_tcscpy_s(recCity.szRegion, m_strRegion);

	return recCity;
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
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidStringFormat(strText);

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